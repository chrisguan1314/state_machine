#pragma once

#include "apa_event_manager.h"
#include "../../../../str_map.h"
#include "../../../state_machine_switcher_base.h"
#include "../../../state_switch_table.h"

#include <iostream>
#include <sstream>

namespace parking
{
    inline std::string ApaFormator(const std::string &value)
    {
        return Format(value, apa_str_map);
    }

    /**
     * @brief 管理 APA 自动泊车功能的状态转换。
     *
     * @details
     * 该切换器在 Init() 中构建 APA 状态转换表，将每个源状态可切换的目标状态
     * 与对应的转换条件关联。状态覆盖空闲、待命、车位搜索、准备完成、遥控泊车
     * 准备完成、泊车、暂停、人工接管、成功、失败和终止等阶段。
     *
     * 转换条件由私有 SwitchFrom... 函数提供。当前仅 PREPARED_4 到
     * RPA_PREPARED_5 的转换会根据 ApaParam::IsRpaEnable() 判定；其余条件函数
     * 均为占位实现并返回 false，因此对应转换暂不会自动触发。
     *
     * @note 在执行状态调度前必须调用 Init() 注册转换表。
     */
    class ApaStateSwitcher final : public StateMachineSwitcherBase<ApaStateType>
    {
    public:
        /**
         * @brief 构造 APA 状态切换器。
         *
         * @details 初始化 APA 状态机切换基类；转换规则需随后通过 Init() 注册。
         */
        ApaStateSwitcher() : StateMachineSwitcherBase<ApaStateType>() {}

    public:
        /**
         * @brief 初始化 APA 状态转换表。
         *
         * @details 注册各 APA 源状态可达的目标状态及其条件函数。状态表包括：
         * IDLE、STANDBY、SEARCHING、SEARCHED、PREPARED、RPA_PREPARED、PARKING、
         * SUSPEND、OVERRIDE、SUCCESS、FAILED 和 TERMINATE。
         */
        void Init() override
        {
            using SwitchSubTable = StateSwitchTable<ApaStateType>::SwitchSubTable;

            SwitchSubTable idle_to_table =
                {
                    {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromIdleToStandby, this)},
            };
            SwitchSubTable standby_to_table =
                {
                    {ApaStateType::IDLE_0, std::bind(&ApaStateSwitcher::SwitchFromStandbyToIdle, this)},
                    {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromStandbyToSearching, this)},
            };
            SwitchSubTable searching_to_table =
                {
                    {ApaStateType::SEARCHED_3, std::bind(&ApaStateSwitcher::SwitchFromSearchingToSearched, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSearchingToTerminate, this)},
            };
            SwitchSubTable searched_to_table =
                {
                    {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromSearchedToSearching, this)},
                    {ApaStateType::PREPARED_4, std::bind(&ApaStateSwitcher::SwitchFromSearchedToPrepared, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSearchedToTerminate, this)},
            };
            SwitchSubTable prepared_to_table =
                {
                    {ApaStateType::SEARCHING_2, std::bind(&ApaStateSwitcher::SwitchFromPreparedToSearching, this)},
                    {ApaStateType::SEARCHED_3, std::bind(&ApaStateSwitcher::SwitchFromPreparedToSearched, this)},
                    {ApaStateType::RPA_PREPARED_5, std::bind(&ApaStateSwitcher::SwitchFromPreparedToRpaPrepared, this)},
                    {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromPreparedToParking, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromPreparedToTerminate, this)},
            };
            SwitchSubTable rpa_prepared_to_table =
                {
                    {ApaStateType::PREPARED_4, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToPrepared, this)},
                    {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToParking, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromRpaPreparedToTerminate, this)},
            };
            SwitchSubTable parking_to_table =
                {
                    {ApaStateType::SUSPEND_7, std::bind(&ApaStateSwitcher::SwitchFromParkingToSuspend, this)},
                    {ApaStateType::OVERRIDE_8, std::bind(&ApaStateSwitcher::SwitchFromParkingToOverride, this)},
                    {ApaStateType::SUCCESS_9, std::bind(&ApaStateSwitcher::SwitchFromParkingToSuccess, this)},
                    {ApaStateType::FAILED_10, std::bind(&ApaStateSwitcher::SwitchFromParkingToFailed, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromParkingToTerminate, this)},
            };
            SwitchSubTable suspend_to_table =
                {
                    {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromSuspendToParking, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromSuspendToTerminate, this)},
            };
            SwitchSubTable override_to_table =
                {
                    {ApaStateType::PARKING_6, std::bind(&ApaStateSwitcher::SwitchFromOverrideToParking, this)},
                    {ApaStateType::TERMINATE_11, std::bind(&ApaStateSwitcher::SwitchFromOverrideToTerminate, this)},
            };
            SwitchSubTable success_to_table =
                {
                    {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromSuccessToStandby, this)},
            };
            SwitchSubTable failed_to_table =
                {
                    {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromFailedToStandby, this)},
            };
            SwitchSubTable terminate_to_table =
                {
                    {ApaStateType::STANDBY_1, std::bind(&ApaStateSwitcher::SwitchFromTerminateToStandby, this)},
            };

            AddStateSwitch(ApaStateType::IDLE_0, std::move(idle_to_table));
            AddStateSwitch(ApaStateType::STANDBY_1, std::move(standby_to_table));
            AddStateSwitch(ApaStateType::SEARCHING_2, std::move(searching_to_table));
            AddStateSwitch(ApaStateType::SEARCHED_3, std::move(searched_to_table));
            AddStateSwitch(ApaStateType::PREPARED_4, std::move(prepared_to_table));
            AddStateSwitch(ApaStateType::RPA_PREPARED_5, std::move(rpa_prepared_to_table));
            AddStateSwitch(ApaStateType::PARKING_6, std::move(parking_to_table));
            AddStateSwitch(ApaStateType::SUSPEND_7, std::move(suspend_to_table));
            AddStateSwitch(ApaStateType::OVERRIDE_8, std::move(override_to_table));
            AddStateSwitch(ApaStateType::SUCCESS_9, std::move(success_to_table));
            AddStateSwitch(ApaStateType::FAILED_10, std::move(failed_to_table));
            AddStateSwitch(ApaStateType::TERMINATE_11, std::move(terminate_to_table));

            std::cout << "[StateMachine] Init Switcher Table" << std::endl;
        }

        /**
         * @brief 判断 APA 功能是否已进入运行阶段。
         *
         * @details 当前状态大于 STANDBY_1 时返回 true；空闲和待命状态均视为未运行。
         * @return APA 状态机处于运行阶段时返回 true，否则返回 false。
         */
        static bool IsRunning() noexcept
        {
            return GetCrntState() > ApaStateType::STANDBY_1;
        }

        /**
         * @brief 输出 APA 状态切换信息。
         *
         * @details 将当前、上一和前序状态格式化后输出，同时输出当前状态持续时间，
         * 用于运行时状态机诊断。
         */
        void PrintStateInfo(bool flag) override
        {
            std::stringstream ss;
            ss << "[APA] Last : " << ApaFormator(apa_str_map.at(GetLastState()))
                << ", Crnt : " << ApaFormator(apa_str_map.at(GetCrntState()))
                << ", Prvs : " << ApaFormator(apa_str_map.at(GetPrvsState()))
                << ", Duration : " << GetDuration().count() << "(S)";
            if (flag &&  ApaEventManager::GetEventType() > ParkingEventType::NONE_0)
            {
                ss << ", Event : " << EventFormator(ApaEventManager::GetEventName())
                    << ", Type : " << ApaEventManager::GetEventTypeName();
            }
            std::cout << ss.str() << std::endl;
        }

    private:
        bool SwitchFromIdleToStandby() const noexcept
        {
            if (GetCount() > 60)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromStandbyToIdle() const noexcept
        {
            return false;
        }
        bool SwitchFromStandbyToSearching() const noexcept
        {
            if (ApaEventManager::GetActv() > ApaActvType::NONE_0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromSearchingToSearched() const noexcept
        {
            if (GetCount() > 60)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromSearchingToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToSearching() const noexcept
        {
            return false;
        }
        bool SwitchFromSearchedToPrepared() const noexcept
        {
            if (GetCount() > 60)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromSearchedToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToSearching() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToSearched() const noexcept
        {
            return false;
        }
        bool SwitchFromPreparedToRpaPrepared() const noexcept
        {
            if (ApaParam::IsRpaEnable())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromPreparedToParking() const noexcept
        {
            if (ApaEventManager::GetGuidance() > ApaGuidanceType::NONE_0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromPreparedToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToPrepared() const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromRpaPreparedToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuspend() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToOverride() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToSuccess() const noexcept
        {
            if (ApaEventManager::GetSuccess() > ApaSuccessType::NONE_0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromParkingToFailed() const noexcept
        {
            return false;
        }
        bool SwitchFromParkingToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromSuspendToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToParking() const noexcept
        {
            return false;
        }
        bool SwitchFromOverrideToTerminate() const noexcept
        {
            return false;
        }
        bool SwitchFromSuccessToStandby() const noexcept
        {
            if (GetCount() > 60 || ApaEventManager::GetExit() > ApaExitType::NONE_0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool SwitchFromFailedToStandby() const noexcept
        {
            return false;
        }
        bool SwitchFromTerminateToStandby() const noexcept
        {
            return false;
        }
    };
}