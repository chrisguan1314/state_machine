#pragma once

#include <string>
#include <filesystem>

struct PublicParam
{
public: 
    std::filesystem::path public_param_path_;
public:
    template <typename T, typename = typename std::enable_if_t<std::is_convertible_v<std::decay_t<T>,  std::filesystem::path>>>
    PublicParam(T && path) : public_param_path_(std::forward<T>(path))
    {
    }
};