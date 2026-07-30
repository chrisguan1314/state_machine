#pragma once

#include "concept_base.h"
#include "state_machine_event_base.h"
#include "state_machine_param_base.h"
#include "state_machine_inputer_data.h"

#include <memory>
#include <stdexcept>

#if __cplusplus >= 202002L
template <is_param_base Param, is_event_base Event>
#else
template <typename Param, typename Event,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>,
typename = typename std::enable_if_t<std::is_base_of_v<StateMachineEventBase, Event>>>
#endif
class StateMachineInputerBase
{
public:
    using ParamType = Param;
    using EventType = Event;
    using ParamSPtr = std::shared_ptr<ParamType>;
    using EventSPtr = std::shared_ptr<EventType>;
    using DataSPtr = std::shared_ptr<StateMachineInputerData>;
private:
    EventSPtr event_sptr_{nullptr};
    DataSPtr data_sptr_{nullptr};
public:
#if __cplusplus >= 202002L
    template <is_event_sptr_base EventSPtr>
#else
    template <typename EventSPtr, typename = typename std::enable_if_t<std::is_base_of_v<StateMachineEventBase, typename EventSPtr::element_type>>>
#endif
    StateMachineInputerBase(EventSPtr && event) : event_sptr_(std::forward<EventSPtr>(event)), data_sptr_(std::make_shared<StateMachineInputerData>())
    {
        if (!event_sptr_)
        {
            throw std::invalid_argument("StateMachineInputerBase: event_sptr_ is nullptr");
        }
        if (!data_sptr_)
        {
            throw std::invalid_argument("StateMachineInputerBase: data_sptr_ is nullptr");
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
public: 
    EventSPtr GetEvent() const noexcept
    {
        return event_sptr_;
    }
    DataSPtr GetData() const noexcept
    {
        return data_sptr_;
    }
};



#if __cplusplus >= 202002L
template <typename T, typename Param, typename Event>
concept is_inputer_base = is_param_base<Param> && is_event_base<Event> && std::derived_from<T, StateMachineInputerBase<Param, Event>>;
#endif