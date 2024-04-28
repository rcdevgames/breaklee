RUNTIME_DATA_FILE_BEGIN(divineupgrade.enc)

RUNTIME_DATA_TYPE_BEGIN(DivineUpgradeMain, "divine_upgrade.divine_upgrade_main.divine", 128)
	RUNTIME_DATA_PROPERTY(Int32, Group, "group")
	RUNTIME_DATA_PROPERTY(Int32, ItemGrade, "grade")
	RUNTIME_DATA_PROPERTY(RTDataItemType, ItemType, "type")
RUNTIME_DATA_TYPE_END(DivineUpgradeMain)

RUNTIME_DATA_TYPE_BEGIN(DivineUpgradeGroupCost, "divine_upgrade.divine_needs_core", 32)
	RUNTIME_DATA_PROPERTY(Int32, Group, "group")
	RUNTIME_DATA_TYPE_BEGIN_CHILD(DivineUpgradeGroupCostLevel, "core", 16)
		RUNTIME_DATA_PROPERTY(Int32, Level, "level")
		RUNTIME_DATA_PROPERTY(Int32, RequiredCoreCount, "needs_core")
		RUNTIME_DATA_PROPERTY(Int32, RequiredSafeCount, "needs_buffer")
		RUNTIME_DATA_PROPERTY_ARRAY(Int32, Result, "result", 6, ',')
	RUNTIME_DATA_TYPE_END_CHILD(DivineUpgradeGroupCostLevel, 16)
RUNTIME_DATA_TYPE_END(DivineUpgradeGroupCost)
RUNTIME_DATA_TYPE_INDEX(DivineUpgradeGroupCost, Int32, Group)
RUNTIME_DATA_TYPE_INDEX_CHILD(DivineUpgradeGroupCost, DivineUpgradeGroupCostLevel, Int32, Level)

RUNTIME_DATA_TYPE_BEGIN(DivineUpgradeGroupValue, "divine_upgrade.divine_value", 32)
	RUNTIME_DATA_PROPERTY(Int32, Group, "group")
	RUNTIME_DATA_TYPE_BEGIN_CHILD(DivineUpgradeGroupValueLevel, "value", 64)
		RUNTIME_DATA_PROPERTY(Int32, Level, "level")
		RUNTIME_DATA_PROPERTY(Int32, ForceIndex, "divine_forceid")
		RUNTIME_DATA_PROPERTY(Int32, ForceValue, "force_value")
		RUNTIME_DATA_PROPERTY(Int32, ForceValueType, "value_type")
	RUNTIME_DATA_TYPE_END_CHILD(DivineUpgradeGroupValueLevel, 64)
RUNTIME_DATA_TYPE_END(DivineUpgradeGroupValue)
RUNTIME_DATA_TYPE_INDEX(DivineUpgradeGroupValue, Int32, Group)

RUNTIME_DATA_FILE_END
