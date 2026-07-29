#pragma once

#include "state_machine_event_base.h"
#include "state_machine_action_base.h"

#include <type_traits>

#if __cplusplus >= 202002L
template <typename T>
concept is_enum = std::is_enum_v<T>;

template <typename T>
concept is_convertible_to_string = std::is_convertible_v<T, std::string>;

template <typename T>
concept is_event_sptr_base = std::derived_from<typename T::element_type, StateMachineEventBase>;

template <typename T>
concept is_action_base = std::derived_from<T, StateMachineActionBase>;

template <typename T>
concept is_action_sptr_base = std::derived_from<typename T::element_type, StateMachineActionBase>;

#endif
