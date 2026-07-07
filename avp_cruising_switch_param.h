#pragma once

class AvpCruisingSwitchParam
{
private:
    bool front_camera_switch_{false};
    bool rear_camera_switch_{false};
    bool left_camera_switch_{false};
    bool right_camera_switch_{false};
    bool front_left_door_switch_{false};
    bool front_right_door_switch_{false};
    bool rear_left_door_switch_{false};
    bool rear_right_door_switch_{false};
    bool frunk_door_swtich_{false};
    bool trunk_door_switch_{false};
public:
    const bool GetFrontCameraSwitch() const noexcept
    {
        return front_camera_switch_;
    }
    const bool GetRearCameraSwitch() const noexcept
    {
        return rear_camera_switch_;
    }
    const bool GetLeftCameraSwitch() const noexcept
    {
        return left_camera_switch_;
    }
    const bool GetRightCameraSwitch() const noexcept
    {
        return right_camera_switch_;
    }
};