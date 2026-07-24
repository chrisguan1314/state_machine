#pragma once

#include "state_machine_event_base.h"
#include "state_machine_param_base.h"

#include <memory>

#if __cplusplus >= 202002L
template <is_param_base Param>
#else
template <typename Param, typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>>
#endif
class StateMachineInputerBase
{
public:
    using ParamType = Param;
    using ParamSPtr = std::shared_ptr<ParamType>;
private:
    std::shared_ptr<StateMachineEventBase> event_sptr_{std::make_shared<StateMachineEventBase>()};
public:
    StateMachineInputerBase(std::shared_ptr<StateMachineEventBase> && event = std::make_shared<StateMachineEventBase>()) : event_sptr_(std::move(event))
    {

    }
public:
    void Init()
    {
        InitReaders();
    }
public:
    virtual void InitReaders() = 0;
    virtual void UpdateEvent(std::shared_ptr<Param> param) = 0;
};



#if __cplusplus >= 202002L
template <typename T, typename Param>
concept is_inputer_base = is_param_base<Param> && std::derived_from<T, StateMachineInputerBase<Param>>;
#endif