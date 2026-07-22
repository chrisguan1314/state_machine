#pragma once

#include "avp_cruising_action.h"
#include "../../base/state_machine_outputer_base.h"

#include <memory>
#include <iostream>

namespace parking
{
class AvpCruisingOutputer : public StateMachineOutputerBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer, AvpCruisingStateSwitcher>
{
public:
    AvpCruisingOutputer() : StateMachineOutputerBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer, AvpCruisingStateSwitcher>(std::make_shared<AvpCruisingAction>())
    {

    }
public:
    void InitWriters() override 
    {
        std::cout << "Init AvpCruisingOutputer Writers" << std::endl;
    };
    void UpdateAction(std::shared_ptr<AvpCruisingParam> param, std::shared_ptr<AvpCruisingInputer> input, std::shared_ptr<AvpCruisingStateSwitcher> switcher) override
    {
        std::cout << "Update AvpCruisingOutputer Action" << std::endl;
    };
};
};
