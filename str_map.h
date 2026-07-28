#pragma once

#include "enum.h"
#include "log_base.h"

const std::string Convert(std::string&& str, const char c = '_')
{
    auto pos = str.find(c);
    return (pos != std::string::npos) ? (str.substr(0, pos) + "[" + str.substr(pos + 1, (str.size() - pos - 1)) + "]") : str;
}