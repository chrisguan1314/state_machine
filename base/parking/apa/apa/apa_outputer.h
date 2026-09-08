#pragma once

#include "../../../../enum.h"
#include "apa_action.h"
#include "apa_switcher.h"
#include "../../../state_machine_outputer_base.h"

#include <iostream>

namespace parking
{
    /**
     * @brief 执行 APA 状态机各状态对应的输出动作。
     *
     * @details
     * 该输出器持有 ApaAction 实例，并将 APA 状态枚举映射到对应的处理函数。
     * 动作函数通过 ApaStateSwitcher 判断是否刚切换至目标状态，只有在状态变化时
     * 才执行配置更新或输出日志，避免在同一状态的重复调度中重复执行副作用。
     *
     * 在待命状态会清除功能开启类型和激活类型；搜索状态会设置 TICE 开启类型；
     * 进入泊车状态时，根据前序状态设置 TICE 或 KEY 激活类型。
     *
     * @note 调用方应先执行 InitWriters() 和 InitActionTable()，再调度状态动作。
     */
    class ApaOutputer final : public StateMachineOutputer<ApaStateType>
    {
    public:
        /**
         * @brief 构造 APA 状态机输出器。
         *
         * @details 创建 ApaAction 并传递给状态机输出基类，用于执行已注册的状态动作。
         */
        ApaOutputer() : StateMachineOutputer<ApaStateType>(std::make_shared<ApaAction>()) {}

    public:
        /**
         * @brief 初始化 APA 输出通道。
         *
         * @details 当前实现输出初始化日志，保留该重写点以便后续接入实际 writer。
         */
        void InitWriters() override
        {
            std::cout << "[StateMachine] Init ApaOutputer Writers" << std::endl;
        }

        /**
         * @brief 注册所有 APA 状态对应的输出动作。
         *
         * @details 为 IDLE、STANDBY、SEARCHING、SEARCHED、PREPARED、RPA_PREPARED、
         * PARKING、SUSPEND、OVERRIDE、SUCCESS、FAILED 和 TERMINATE 状态建立动作映射。
         */
        void InitActionTable() override
        {
            AddAction(ApaStateType::IDLE_0, std::bind(&ApaOutputer::ActionOfIdle, this));
            AddAction(ApaStateType::STANDBY_1, std::bind(&ApaOutputer::ActionOfStandby, this));
            AddAction(ApaStateType::SEARCHING_2, std::bind(&ApaOutputer::ActionOfSearching, this));
            AddAction(ApaStateType::SEARCHED_3, std::bind(&ApaOutputer::ActionOfSearched, this));
            AddAction(ApaStateType::PREPARED_4, std::bind(&ApaOutputer::ActionOfPrepared, this));
            AddAction(ApaStateType::RPA_PREPARED_5, std::bind(&ApaOutputer::ActionOfRpaPrepared, this));
            AddAction(ApaStateType::PARKING_6, std::bind(&ApaOutputer::ActionOfParking, this));
            AddAction(ApaStateType::SUSPEND_7, std::bind(&ApaOutputer::ActionOfSuspend, this));
            AddAction(ApaStateType::OVERRIDE_8, std::bind(&ApaOutputer::ActionOfOverride, this));
            AddAction(ApaStateType::SUCCESS_9, std::bind(&ApaOutputer::ActionOfSuccess, this));
            AddAction(ApaStateType::FAILED_10, std::bind(&ApaOutputer::ActionOfFailed, this));
            AddAction(ApaStateType::TERMINATE_11, std::bind(&ApaOutputer::ActionOfTerminate, this));
        }

        /**
         * @brief 获取 APA 状态机当前状态。
         * @return ApaStateSwitcher 维护的当前 APA 状态。
         */
        ApaStateType GetCrntState() const noexcept override
        {
            return ApaStateSwitcher::GetCrntState();
        }

    private:
        /**
         * @brief 处理切换至空闲状态的输出动作。
         * @details 仅在状态机刚切换至 IDLE_0 时输出空闲状态日志。
         */
        void ActionOfIdle()
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::IDLE_0))
            {
                std::cout << "ApaOutputer Action : IDLE" << std::endl; 
            }
        }

        /**
         * @brief 处理切换至待命状态的输出动作。
         * @details 仅在切换至 STANDBY_1 时，将功能开启类型和激活类型重置为 NONE_0，
         * 并输出待命状态日志。
         */
        void ActionOfStandby() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::STANDBY_1))
            {
                ApaStateSwitcher::SetOpenType(FuncOpenType::NONE_0);
                ApaStateSwitcher::SetActvType(FuncActvType::NONE_0);
                std::cout << "ApaOutputer Action : STANDBY" << std::endl; 
            }
        }

        /**
         * @brief 处理切换至车位搜索状态的输出动作。
         * @details 仅在切换至 SEARCHING_2 时，将功能开启类型设置为 TICE_1，
         * 并输出搜索状态日志。
         */
        void ActionOfSearching() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::SEARCHING_2))
            {
                ApaStateSwitcher::SetOpenType(FuncOpenType::TICE_1);
                std::cout << "ApaOutputer Action : SEARCHING" << std::endl; 
            }
        }

        /**
         * @brief 处理切换至已搜索状态的输出动作。
         * @details 仅在状态机刚切换至 SEARCHED_3 时输出状态日志。
         */
        void ActionOfSearched() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::SEARCHED_3))
            {
                std::cout << "ApaOutputer Action : SEARCHED" << std::endl; 
            }
        }

        /**
         * @brief 处理切换至准备完成状态的输出动作。
         * @details 仅在状态机刚切换至 PREPARED_4 时输出状态日志。
         */
        void ActionOfPrepared() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::PREPARED_4))
            {
                std::cout << "ApaOutputer Action : PREPARED" << std::endl; 
            }
        }

        /**
         * @brief 处理切换至遥控泊车准备完成状态的输出动作。
         * @details 仅在状态机刚切换至 RPA_PREPARED_5 时输出状态日志。
         */
        void ActionOfRpaPrepared() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::RPA_PREPARED_5))
            {
                std::cout << "ApaOutputer Action : RPA_PREPARED" << std::endl; 
            }
        }

        /**
         * @brief 处理切换至泊车状态的输出动作。
         * @details 仅在切换至 PARKING_6 时执行。若来自 PREPARED_4，则将激活类型设置为
         * TICE_1；若来自 RPA_PREPARED_5，则设置为 KEY_5；随后输出泊车状态日志。
         */
        void ActionOfParking() 
        { 
            if (ApaStateSwitcher::IsChangeTo(ApaStateType::PARKING_6))
            {
                if (ApaStateSwitcher::IsChangeFrom(ApaStateType::PREPARED_4))
                {
                    ApaStateSwitcher::SetActvType(FuncActvType::TICE_1);
                    std::cout << "ApaOutputer Action : PARKING" << std::endl; 
                }
                else if (ApaStateSwitcher::IsChangeFrom(ApaStateType::RPA_PREPARED_5))
                {
                    ApaStateSwitcher::SetActvType(FuncActvType::KEY_5);
                    std::cout << "ApaOutputer Action : PARKING" << std::endl; 
                }
            }
        }

        /**
         * @brief 处理切换至暂停状态的输出动作。
         * @details 输出暂停状态日志，不修改功能配置。
         */
        void ActionOfSuspend() 
        { 
            std::cout << "ApaOutputer Action : SUSPEND" << std::endl; 
        }

        /**
         * @brief 处理切换至人工接管状态的输出动作。
         * @details 输出接管状态日志，不修改功能配置。
         */
        void ActionOfOverride() 
        { 
            std::cout << "ApaOutputer Action : OVERRIDE" << std::endl; 
        }

        /**
         * @brief 处理切换至成功状态的输出动作。
         * @details 输出成功状态日志，不修改功能配置。
         */
        void ActionOfSuccess()
        { 
            std::cout << "ApaOutputer Action : SUCCESS" << std::endl; 
        }

        /**
         * @brief 处理切换至失败状态的输出动作。
         * @details 输出失败状态日志，不修改功能配置。
         */
        void ActionOfFailed() 
        { 
            std::cout << "ApaOutputer Action : FAILED" << std::endl; 
        }

        /**
         * @brief 处理切换至终止状态的输出动作。
         * @details 输出终止状态日志，不修改功能配置。
         */
        void ActionOfTerminate() 
        { 
            std::cout << "ApaOutputer Action : TERMINATE" << std::endl; 
        }
    };
}