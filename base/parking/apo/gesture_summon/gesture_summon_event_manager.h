 #pragma once

#include "gesture_summon_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

/** @brief 保存和查询手势召唤事件。 */
class GestureSummonEventManager : public ParkingEventManager<GestureSummonActvType, GestureSummonActvIhbtType,
												   GestureSummonGuidanceType, GestureSummonGuidanceIhbtType,
												   GestureSummonPauseType, GestureSummonSuccessType,
												   GestureSummonFailType, GestureSummonExitType>
{
protected:
	void UpdateEvent() noexcept override {}

	void LogEventChange(ParkingEventType event_type, int value) const noexcept override
	{
		const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
			const auto it = strmap.find(event_value);
			if (it != strmap.end()) std::clog << "GestureSummonEventManager: " << event_name << " = " << it->second << std::endl;
		};
		switch (event_type)
		{
			case ParkingEventType::ACTV_1: log(gesture_summon_actv_strmap, "ACTV", static_cast<GestureSummonActvType>(value)); break;
			case ParkingEventType::ACTV_IHBT_2: log(gesture_summon_actv_ihbt_strmap, "ACTV_IHBT", static_cast<GestureSummonActvIhbtType>(value)); break;
			case ParkingEventType::GUIDANCE_3: log(gesture_summon_guidance_strmap, "GUIDANCE", static_cast<GestureSummonGuidanceType>(value)); break;
			case ParkingEventType::GUIDANCE_IHBT_4: log(gesture_summon_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<GestureSummonGuidanceIhbtType>(value)); break;
			case ParkingEventType::PAUSE_5: log(gesture_summon_pause_strmap, "PAUSE", static_cast<GestureSummonPauseType>(value)); break;
			case ParkingEventType::SUCCESS_6: log(gesture_summon_success_strmap, "SUCCESS", static_cast<GestureSummonSuccessType>(value)); break;
			case ParkingEventType::FAIL_7: log(gesture_summon_fail_strmap, "FAIL", static_cast<GestureSummonFailType>(value)); break;
			case ParkingEventType::EXIT_8: log(gesture_summon_exit_strmap, "EXIT", static_cast<GestureSummonExitType>(value)); break;
			case ParkingEventType::NONE_0: default: break;
		}
	}
};

}  // namespace parking
