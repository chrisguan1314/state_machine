#pragma once

#include "avm_switch_param.h"
#include "avm_value_param.h"

#include <memory>

struct AvmParam
{
public:
    AvmSwitchParam switch_param_;
    AvmValueParam value_param_;
};