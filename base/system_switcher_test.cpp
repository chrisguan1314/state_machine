#include "system_switcher.h"

#include <cassert>

int main()
{
    using function::SystemSubMode;
    using function::SystemSwitcher;

    SystemSwitcher switcher;
    bool manual_to_acc_called = false;
    switcher.AddSwitchEntry(
        SystemSubMode::MANUL_LOW_0,
        SystemSubMode::PILOT_ACC_10,
        [&manual_to_acc_called]()
        {
            manual_to_acc_called = true;
            return true;
        });

    auto manual_switches = switcher.GetSubSwitchTable(SystemSubMode::MANUL_LOW_0);
    assert(manual_switches.has_value());
    assert(manual_switches->size() == 1);
    assert(manual_switches->at(SystemSubMode::PILOT_ACC_10)());
    assert(manual_to_acc_called);
    assert(switcher.HasEntry(
        SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_ACC_10));
    assert(!switcher.HasEntry(
        SystemSubMode::MANUL_LOW_0, SystemSubMode::PARKING_APA_30));

    auto manual_switches_reference = switcher[SystemSubMode::MANUL_LOW_0];
    assert(manual_switches_reference.has_value());
    manual_switches_reference->get().emplace(
        SystemSubMode::PILOT_LCC_11, []
        { return true; });
    assert(switcher.HasEntry(
        SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_LCC_11));
    assert(!switcher[SystemSubMode::AS_AEB_50].has_value());

    switcher.AddSwitchEntry(
        SystemSubMode::MANUL_LOW_0,
        SystemSubMode::PARKING_APA_30,
        []
        { return true; });

    manual_switches = switcher.GetSubSwitchTable(SystemSubMode::MANUL_LOW_0);
    assert(manual_switches->size() == 3);
    assert(manual_switches->contains(SystemSubMode::PILOT_ACC_10));
    assert(manual_switches->contains(SystemSubMode::PILOT_LCC_11));
    assert(manual_switches->contains(SystemSubMode::PARKING_APA_30));

    switcher.AddSwitchEntry(
        SystemSubMode::MANUL_LOW_0,
        SystemSubMode::PARKING_APA_30,
        []
        { return false; });

    manual_switches = switcher.GetSubSwitchTable(SystemSubMode::MANUL_LOW_0);
    assert(manual_switches->size() == 3);
    assert(!manual_switches->at(SystemSubMode::PARKING_APA_30)());

    SystemSwitcher::SwitchSubTable pilot_switches;
    pilot_switches.emplace(SystemSubMode::PARKING_AVP_MAPPING_33, []
                           { return false; });
    switcher.AddSwitchTable(SystemSubMode::PILOT_ACC_10, std::move(pilot_switches));

    const auto configured_pilot_switches =
        switcher.GetSubSwitchTable(SystemSubMode::PILOT_ACC_10);
    assert(configured_pilot_switches.has_value());
    assert(configured_pilot_switches->size() == 1);
    assert(!configured_pilot_switches->at(SystemSubMode::PARKING_AVP_MAPPING_33)());

    switcher.ClearEntry(SystemSubMode::MANUL_LOW_0, SystemSubMode::PILOT_ACC_10);
    manual_switches = switcher.GetSubSwitchTable(SystemSubMode::MANUL_LOW_0);
    assert(manual_switches.has_value());
    assert(manual_switches->size() == 2);
    assert(!manual_switches->contains(SystemSubMode::PILOT_ACC_10));
    assert(manual_switches->contains(SystemSubMode::PILOT_LCC_11));
    assert(manual_switches->contains(SystemSubMode::PARKING_APA_30));

    assert(!switcher.GetSubSwitchTable(SystemSubMode::AS_AEB_50).has_value());

    switcher.ClearTable(SystemSubMode::PILOT_ACC_10);
    assert(!switcher.GetSubSwitchTable(SystemSubMode::PILOT_ACC_10).has_value());

    switcher.Clear();
    assert(switcher.GetSwitchTable().empty());
    return 0;
}