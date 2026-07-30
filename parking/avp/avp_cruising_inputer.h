#pragma once

#include "avp_cruising_event.h"
#include "../../base/state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class AvpCruisingInputer : public StateMachineInputerBase<AvpCruisingParam, AvpCruisingEvent>
{
private:
    // readers to be added here
private:
    // inputting data structures to be added here
public:
    AvpCruisingInputer() : StateMachineInputerBase<AvpCruisingParam, AvpCruisingEvent>(std::make_shared<AvpCruisingEvent>())
    {

    }
public:
    virtual void InitReaders() override 
    {
        std::cout << "Init AvpCruisingInputer Readers" << std::endl;
    };
    void UpdateEvent(std::shared_ptr<AvpCruisingParam> param) override
    {
        // Update the event based on the provided parameter
        // This is where you would implement the logic to update the event based on the parameter
    };
};
};
