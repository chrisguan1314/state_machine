#pragma once

#include <type_traits>
#include <map>
#include <functional>

template<typename T, typename = typename std::enable_if<std::is_enum_v<T>>>
class State
{
public: 
    using data_type = T;
    using switch_list = std::map<State, std::function<bool(const State&)>>
private:
    T value_{static_cast<T>(0)};
public:
    State(const T& value) : value_(value) {};
public:

};