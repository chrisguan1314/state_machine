#pragma once

#include "state_machine_param_base.h"
#include <memory>

#include <type_traits>

#if __cplusplus >= 202002L
template <is_param_base Param>
#else
template <typename Param, typename = typename std::enable_if_t<std::is_base_of_v<StateMachineParamBase, Param>>>
#endif
class StateMachineInputerInterface
{
public:
    /**
     * @brief Initialize the readers for the inputer.
     */
    virtual void InitReaders() = 0;

    /**
     * @brief Update the event based on the given parameter.
     * @param param Shared pointer to the parameter object.
     */
    virtual void UpdateEvent(std::shared_ptr<Param> param) = 0;
};