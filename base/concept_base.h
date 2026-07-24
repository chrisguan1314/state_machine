#pragma once

#include <type_traits>

#if __cplusplus >= 202002L
template <typename T>
concept is_enum = std::is_enum_v<T>;
#endif
