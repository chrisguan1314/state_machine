#pragma once

#include "rpa_switch_param.h"
#include "rpa_value_param.h"

#include <memory>

struct RpaParam
{
public:
    RpaSwitchParam switch_param_;
    RpaValueParam value_param_;
};