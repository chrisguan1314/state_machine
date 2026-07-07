#pragma once

#include "avp_switch_param.h"
#include "avp_value_param.h"

#include <memory>

struct AvpParam
{
public:
    AvpSwitchParam switch_param_;
    AvpValueParam value_param_;
};