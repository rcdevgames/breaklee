RUNTIME_DATA_FILE_BEGIN(ability.enc)

RUNTIME_DATA_TYPE_BEGIN(PassiveAbilityCost, "ability.passive_ability.cost.cost_abilityitem", 64)
    RUNTIME_DATA_PROPERTY(UInt32, Index, "index")
    RUNTIME_DATA_TYPE_BEGIN_CHILD(PassiveAbilityCostLevel, "ability_cost", 32)
        RUNTIME_DATA_PROPERTY(Int32, Level, "level")
        RUNTIME_DATA_PROPERTY(Int32, AP, "ap")
        RUNTIME_DATA_PROPERTY_ARRAY(UInt64, Item1, "item1", 3, ':')
        RUNTIME_DATA_PROPERTY_ARRAY(UInt64, Item2, "item2", 3, ':')
    RUNTIME_DATA_TYPE_END_CHILD(PassiveAbilityCostLevel, 32)
RUNTIME_DATA_TYPE_END(PassiveAbilityCost)
RUNTIME_DATA_TYPE_INDEX(PassiveAbilityCost, UInt32, Index)
RUNTIME_DATA_TYPE_INDEX_CHILD(PassiveAbilityCost, PassiveAbilityCostLevel, Int32, Level)

RUNTIME_DATA_TYPE_BEGIN(PassiveAbilityValue, "ability.passive_ability.value.value_abilityitem", 64)
    RUNTIME_DATA_PROPERTY(UInt32, Index, "index")
    RUNTIME_DATA_PROPERTY(Int32, ForceCode, "forcecode")
    RUNTIME_DATA_PROPERTY(Int32, ValueType, "valuetype")
    RUNTIME_DATA_PROPERTY(Int32, Grade, "grade")
    RUNTIME_DATA_TYPE_BEGIN_CHILD(PassiveAbilityValueLevel, "ability_value", 32)
        RUNTIME_DATA_PROPERTY(Int32, Level, "level")
        RUNTIME_DATA_PROPERTY(Int32, ForceValue, "force_value")     
    RUNTIME_DATA_TYPE_END_CHILD(PassiveAbilityValueLevel, 32)
RUNTIME_DATA_TYPE_END(PassiveAbilityValue)
RUNTIME_DATA_TYPE_INDEX(PassiveAbilityValue, UInt32, Index)
RUNTIME_DATA_TYPE_INDEX_CHILD(PassiveAbilityValue, PassiveAbilityValueLevel, Int32, Level)

RUNTIME_DATA_TYPE_BEGIN(BlendedAbilityRecipe, "ability.blended_ability.recipe.ability_recipe", 64)
    RUNTIME_DATA_PROPERTY(Int32, ID, "id")
    RUNTIME_DATA_PROPERTY(Int32, Rate, "rate")
    RUNTIME_DATA_PROPERTY(Int32, Alz, "alz")
    RUNTIME_DATA_PROPERTY_ARRAY(Int32, Material1, "material1", 2, ':')
    RUNTIME_DATA_PROPERTY_ARRAY(Int32, Material2, "material2", 2, ':')
    RUNTIME_DATA_PROPERTY_ARRAY(Int32, Material3, "material3", 2, ':')
    RUNTIME_DATA_PROPERTY(Int32, ResultIndex, "result_index")
RUNTIME_DATA_TYPE_END(BlendedAbilityRecipe)

RUNTIME_DATA_TYPE_BEGIN(BlendedAbilityCost, "ability.blended_ability.cost.ability_cost", 64)
    RUNTIME_DATA_PROPERTY(Int32, Index, "index")
    RUNTIME_DATA_PROPERTY(Int32, AP, "ap")
    RUNTIME_DATA_PROPERTY_ARRAY(UInt64, ItemCost, "cost", 2, ':')
RUNTIME_DATA_TYPE_END(BlendedAbilityCost)
RUNTIME_DATA_TYPE_INDEX(BlendedAbilityCost, Int32, Index)

RUNTIME_DATA_TYPE_BEGIN(BlendedAbilityValue, "ability.blended_ability.value.value_abilityitem", 64)
    RUNTIME_DATA_PROPERTY(Int32, Index, "index")
    RUNTIME_DATA_PROPERTY(Int32, ActRate, "act_rate")
    RUNTIME_DATA_PROPERTY(Int32, TargetType, "target_type")
    RUNTIME_DATA_TYPE_BEGIN_CHILD(BlendedAbilityValueEffect, "ability_value", 16)
        RUNTIME_DATA_PROPERTY_ARRAY(Int32, Effect1, "effect1", 3, ':')
        RUNTIME_DATA_PROPERTY_ARRAY(Int32, Effect2, "effect2", 3, ':')
        RUNTIME_DATA_PROPERTY_ARRAY(Int32, Effect3, "effect3", 3, ':')
        RUNTIME_DATA_PROPERTY_ARRAY(Int32, Effect4, "effect4", 3, ':')
    RUNTIME_DATA_TYPE_END_CHILD(BlendedAbilityValueEffect, 16)
RUNTIME_DATA_TYPE_END(BlendedAbilityValue)

RUNTIME_DATA_TYPE_BEGIN(KarmaAbilityCost, "ability.karma_ability.cost.cost_abilityitem", 64)
    RUNTIME_DATA_PROPERTY(UInt32, Index, "index")
    RUNTIME_DATA_TYPE_BEGIN_CHILD(KarmaAbilityCostLevel, "ability_cost", 128)
        RUNTIME_DATA_PROPERTY(Int32, Level, "level")
        RUNTIME_DATA_PROPERTY(Int32, AP, "ap")
        RUNTIME_DATA_PROPERTY_ARRAY(Int32, Item1, "item1", 3, ':')
        RUNTIME_DATA_PROPERTY_ARRAY(Int32, Item2, "item2", 3, ':')
    RUNTIME_DATA_TYPE_END_CHILD(KarmaAbilityCostLevel, 128)
RUNTIME_DATA_TYPE_END(KarmaAbilityCost)
RUNTIME_DATA_TYPE_INDEX(KarmaAbilityCost, UInt32, Index)
RUNTIME_DATA_TYPE_INDEX_CHILD(KarmaAbilityCost, KarmaAbilityCostLevel, Int32, Level)

RUNTIME_DATA_TYPE_BEGIN(KarmaAbilityValue, "ability.karma_ability.value.value_abilityitem", 64)
    RUNTIME_DATA_PROPERTY(UInt32, Index, "index")
    RUNTIME_DATA_PROPERTY(Int32, ForceCode, "forcecode")
    RUNTIME_DATA_PROPERTY(Int32, ValueType, "valuetype")
    RUNTIME_DATA_PROPERTY(Int32, Grade, "grade")
    RUNTIME_DATA_TYPE_BEGIN_CHILD(KarmaAbilityValueLevel, "ability_value", 128)
        RUNTIME_DATA_PROPERTY(Int32, Level, "level")
        RUNTIME_DATA_PROPERTY(Int32, ForceValue, "force_value")
    RUNTIME_DATA_TYPE_END_CHILD(KarmaAbilityValueLevel, 128)
RUNTIME_DATA_TYPE_END(KarmaAbilityValue)
RUNTIME_DATA_TYPE_INDEX(KarmaAbilityValue, UInt32, Index)
RUNTIME_DATA_TYPE_INDEX_CHILD(KarmaAbilityValue, KarmaAbilityValueLevel, Int32, Level)

RUNTIME_DATA_FILE_END

RUNTIME_DATA_FILE_BEGIN(ability.xml)

RUNTIME_DATA_TYPE_BEGIN(PassiveAbilitySlotLimit, "ability.ability_slot_limit.passive_ability_slot", 1)
    RUNTIME_DATA_PROPERTY(Int32, MinCount, "min_count")
    RUNTIME_DATA_PROPERTY(Int32, MaxCount, "max_count")
RUNTIME_DATA_TYPE_END(PassiveAbilitySlotLimit)
RUNTIME_DATA_TYPE_INDEX_SINGLE(PassiveAbilitySlotLimit)

RUNTIME_DATA_TYPE_BEGIN(BlendedAbilitySlotLimit, "ability.ability_slot_limit.blended_ability_slot", 1)
    RUNTIME_DATA_PROPERTY(Int32, MinCount, "min_count")
    RUNTIME_DATA_PROPERTY(Int32, MaxCount, "max_count")
RUNTIME_DATA_TYPE_END(BlendedAbilitySlotLimit)
RUNTIME_DATA_TYPE_INDEX_SINGLE(BlendedAbilitySlotLimit)

RUNTIME_DATA_TYPE_BEGIN(KarmaAbilitySlotLimit, "ability.ability_slot_limit.karma_ability_slot", 1)
    RUNTIME_DATA_PROPERTY(Int32, MinCount, "min_count")
    RUNTIME_DATA_PROPERTY(Int32, MaxCount, "max_count")
RUNTIME_DATA_TYPE_END(KarmaAbilitySlotLimit)
RUNTIME_DATA_TYPE_INDEX_SINGLE(KarmaAbilitySlotLimit)

RUNTIME_DATA_TYPE_BEGIN(AxpFieldRate, "ability.axp_field_rate.rate_limit", 16)
    RUNTIME_DATA_PROPERTY(Int32, MinLevel, "min_level")
    RUNTIME_DATA_PROPERTY(Int32, MaxLevel, "max_level")
    RUNTIME_DATA_PROPERTY(Int32, Rate, "rate")
RUNTIME_DATA_TYPE_END(AxpFieldRate)
RUNTIME_DATA_TYPE_INDEX_RANGE(AxpFieldRate, Int32, MinLevel, MaxLevel)

RUNTIME_DATA_FILE_END
