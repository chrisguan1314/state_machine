#pragma once

#include "state_machine_param_base.h"
#include "state_machine_input_base.h"
#include "state_machine_switch_base.h"
#include "state_machine_output_base.h"

#include <iostream>
#include <chrono>
#include <type_traits>
#include <iomanip>
#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include <functional>

// 类模板的模板声明（the declaration of class template, including 1 default template argument）
template <typename T, typename = typename std::enable_if_t<std::is_enum_v<T>>>
class StateMachineBase;

// alias declaration by using of class template 
template <typename T>
using PrinterType = std::function<void(const StateMachineBase<T>&)>;

// 在定义类模板时，不再需要指定默认模板参数
// don't need to specify that default template argument when define the class template 
template <typename T, typename>
class StateMachineBase
{
private:
    std::unique_ptr<PrinterType<T>> func_{nullptr};
    // 整体的这里的标志位都应该用原子变量，以避免可能带来的数据竞争

    // 其实这个使能标志位应该是由调度器来加载相关参数的
    // 根据加载的结果来决定是否生成该状态机对象
    std::atomic_bool enable_flag_{false};
    // 如果功能开关打开，则对该状态机进行初始化
    // 初始化大概分为参数加载和通信协议适配
    std::atomic_bool init_flag_{false};
    // 当初始化完成之后，我们就可以创建线程开始工作了
    std::atomic_bool setup_flag_{false};
    // the frequency of print log
    uint32_t freq_{20};

    std::shared_ptr<StateMachineParamBase> param_sptr_{nullptr};
    std::shared_ptr<StateMachineInputBase> input_sptr_{nullptr};
    std::shared_ptr<StateMachineSwtichBase<T>> switch_sptr_{nullptr};
    std::shared_ptr<StateMachineOutputBase> output_sptr_{nullptr};
    std::unique_ptr<std::thread> thrd_uptr_{nullptr};
    std::string name_;
protected:
    StateMachineBase(std::string name) : 
    name_(name),
    param_sptr_{std::make_shared<StateMachineParamBase>()},
    input_sptr_{std::make_shared<StateMachineInputBase>()},
    switch_sptr_{std::make_shared<StateMachineSwtichBase<T>>()}, 
    output_sptr_{std::make_shared<StateMachineOutputBase>()}
    {
        
    }
    StateMachineBase(std::string name, std::shared_ptr<StateMachineParamBase> && param, std::shared_ptr<StateMachineInputBase> && input, std::shared_ptr<StateMachineSwtichBase<T>> && switches, std::shared_ptr<StateMachineOutputBase> && output) :
    name_(name),
    param_sptr_{param},
    input_sptr_{input},
    switch_sptr_{switches}, 
    output_sptr_{output}
    {
        Init();
    }
    ~StateMachineBase()
    {
        if (thrd_uptr_ && thrd_uptr_->joinable())
        {
            thrd_uptr_->join();
        }
    }
public:
    void Init() 
    {
        param_sptr_->Init();
        input_sptr_->Init();;
        switch_sptr_->Init();
        output_sptr_->Init();

        thrd_uptr_ = std::make_unique<std::thread>(&StateMachineBase::Run, this);
    }
    void Run()
    {
        while (true)
        {
            param_sptr_->UpdateParam();
            input_sptr_->UpdateEvent();
            switch_sptr_->UpdateState(input_sptr_);
            output_sptr_->UpdateAction();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
protected:
    void SetEnableFlag(bool flag = false) noexcept
    {
        enable_flag_.store(flag);
    }
    void SetInitFlag(bool flag = false) noexcept
    {
        init_flag_.store(flag);
    }
    void SetSetupFlag(bool flag = false) noexcept
    {
        setup_flag_.store(flag);
    }
    bool GetEnableFlag() const noexcept
    {
        return enable_flag_.load();
    }
    bool GetInitFlag() const noexcept
    {
        return init_flag_.load();
    }
    bool GetSetupFlag() const noexcept
    {
        return setup_flag_.load();
    }
};