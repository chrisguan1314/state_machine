#pragma once

#include "concept_base.h"
#include "state_machine_event_base.h"
#include "state_machine_param_base.h"

#include <memory>
#include <stdexcept>

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
    using EventSPtr = std::shared_ptr<StateMachineEventBase>;
private:
    EventSPtr event_sptr_{nullptr};
public:
#if __cplusplus >= 202002L
    template <is_event_sptr_base EventSPtr>
#else
    template <typename EventSPtr, typename = typename std::enable_if_t<std::is_base_of_v<StateMachineEventBase, typename EventSPtr::element_type>>>
#endif
    StateMachineInputerBase(EventSPtr && event) : event_sptr_(std::forward<EventSPtr>(event))
    {
        if (!event_sptr_)
        {
            throw std::invalid_argument("StateMachineInputerBase: event_sptr_ is nullptr");
        }
    }
public:
    void Init()
    {
        InitReaders();
    }
public:
    virtual void InitReaders() = 0;
    virtual void UpdateEvent(ParamSPtr param) = 0;
};



#if __cplusplus >= 202002L
template <typename T, typename Param>
concept is_inputer_base = is_param_base<Param> && std::derived_from<T, StateMachineInputerBase<Param>>;
#endif