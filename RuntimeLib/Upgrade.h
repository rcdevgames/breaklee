#pragma once

#include "Base.h"
#include "Constants.h"

EXTERN_C_BEGIN

#pragma pack(push, 1)

enum {
    RUNTIME_UPGRADE_RATE_TYPE_UPGRADE_1 = 0,
    RUNTIME_UPGRADE_RATE_TYPE_UPGRADE_2 = 1,
    RUNTIME_UPGRADE_RATE_TYPE_DOWNGRADE_0 = 2,
    RUNTIME_UPGRADE_RATE_TYPE_DOWNGRADE_1 = 3,
    RUNTIME_UPGRADE_RATE_TYPE_DOWNGRADE_2 = 4,
    RUNTIME_UPGRADE_RATE_TYPE_DOWNGRADE_RESET = 5,
};

enum {
    RUNTIME_UPGRADE_RESULT_ERROR        = 0,
    RUNTIME_UPGRADE_RESULT_UPGRADE_1    = 1,
    RUNTIME_UPGRADE_RESULT_UPGRADE_2    = 2,
    RUNTIME_UPGRADE_RESULT_DOWNGRADE_0  = 3,
    RUNTIME_UPGRADE_RESULT_DOWNGRADE_1  = 4,
    RUNTIME_UPGRADE_RESULT_DOWNGRADE_2  = 5,
    RUNTIME_UPGRADE_RESULT_DESTROYED    = 6,
    RUNTIME_UPGRADE_RESULT_DOWNGRADE_3  = 8,
};

enum {
    RUNTIME_CHAOS_UPGRADE_RATE_TYPE_UPGRADE_1 = 0,
    RUNTIME_CHAOS_UPGRADE_RATE_TYPE_DOWNGRADE_RESET = 1,
    RUNTIME_CHAOS_UPGRADE_RATE_TYPE_DOWNGRADE_0 = 2,
    RUNTIME_CHAOS_UPGRADE_RATE_TYPE_DOWNGRADE_1 = 3,
    RUNTIME_CHAOS_UPGRADE_RATE_TYPE_DOWNGRADE_2 = 4,
    RUNTIME_CHAOS_UPGRADE_RATE_TYPE_DOWNGRADE_3 = 5,
};

enum {
    RUNTIME_CHAOS_UPGRADE_RESULT_UPGRADE = 0,
    RUNTIME_CHAOS_UPGRADE_RESULT_ERROR = 1,
    RUNTIME_CHAOS_UPGRADE_RESULT_DOWNGRADE_1 = 2,
    RUNTIME_CHAOS_UPGRADE_RESULT_DOWNGRADE_2 = 3,
    RUNTIME_CHAOS_UPGRADE_RESULT_DOWNGRADE_0 = 4,
    RUNTIME_CHAOS_UPGRADE_RESULT_DESTROYED = 5,
    RUNTIME_CHAOS_UPGRADE_RESULT_DOWNGRADE_3 = 6,
    RUNTIME_CHAOS_UPGRADE_RESULT_DESTROYED_SEAL = 7,
};

enum {
    RUNTIME_DIVINE_UPGRADE_RATE_TYPE_UPGRADE_1 = 0,
    RUNTIME_DIVINE_UPGRADE_RATE_TYPE_DOWNGRADE_0 = 1,
    RUNTIME_DIVINE_UPGRADE_RATE_TYPE_DOWNGRADE_RESET = 2,
    RUNTIME_DIVINE_UPGRADE_RATE_TYPE_DOWNGRADE_1 = 3,
    RUNTIME_DIVINE_UPGRADE_RATE_TYPE_DOWNGRADE_2 = 4,
    RUNTIME_DIVINE_UPGRADE_RATE_TYPE_DOWNGRADE_3 = 5,
};

enum {
    RUNTIME_DIVINE_UPGRADE_RESULT_UPGRADE   = 0,
    RUNTIME_DIVINE_UPGRADE_RESULT_DOWNGRADE = 1,
    RUNTIME_DIVINE_UPGRADE_RESULT_RESET     = 2,
    RUNTIME_DIVINE_UPGRADE_RESULT_DESTROYED = 3,
    RUNTIME_DIVINE_UPGRADE_RESULT_ERROR     = 4,
};

#pragma pack(pop)

Int32 RTItemUpgradeNormal(
    RTRuntimeRef Runtime,
    RTItemSlotRef Item,
    Int32 UpgradeType,
    Int32* UpgradePoint,
    Int32* Seed
);

Int32 RTItemUpgradeChaos(
    RTRuntimeRef Runtime,
    RTItemSlotRef Item,
    Int32* UpgradePoint,
    Int32* Seed,
    Bool* DestroyItem
);

Int32 RTItemUpgradeDivine(
    RTRuntimeRef Runtime,
    RTItemSlotRef Item,
    Int32* Seed,
    Int32* ResultLevel
);

EXTERN_C_END