#pragma once
#include <cstdint>
namespace structure { namespace function { namespace parking {
enum class RaEventType : std::uint8_t { NONE_0, ACTV_1, ACTV_IHBT_2, GUIDANCE_3, GUIDANCE_IHBT_4, PAUSE_5, SUCCESS_6, FAIL_7, EXIT_8 };
enum class RaActvType : std::uint8_t { NONE_0, BTN_1, KEY_2, APP_3, AUTO_4 };
enum class RaActvIhbtType : std::uint8_t { NONE_0, UNKNOWN_1, SYS_FAULT_2 };
enum class RaGuidanceType : std::uint8_t { NONE_0, ACTIVE_1 };
enum class RaGuidanceIhbtType : std::uint8_t { NONE_0, UNKNOWN_1, SYS_FAULT_2 };
enum class RaPauseType : std::uint8_t { NONE_0, USER_REQ_1, SYS_FAULT_2, VEH_COND_3, SENSOR_UNAVAIL_4 };
enum class RaSuccessType : std::uint8_t { NONE_0, DATA_VALID_1, RESULT_SAVED_2 };
enum class RaFailType : std::uint8_t { NONE_0, SYS_FAULT_1, SENSOR_FAIL_2, INVALID_DATA_3, STORAGE_FAIL_4, USER_CANCEL_5, TIMEOUT_6 };
enum class RaExitType : std::uint8_t { NONE_0, SUCCESS_1, FAILURE_2, USER_REQ_3, SYS_FAULT_4, VEH_COND_5 };
} } }
