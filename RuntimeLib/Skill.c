#include "Character.h"
#include "Mob.h"
#include "Runtime.h"
#include "Skill.h"

Int32 RTCharacterSkillDataGetSkillType(
	RTCharacterSkillDataRef Skill,
	Bool IsPassiveSword,
	Bool IsPassiveMagic
) {
	if (IsPassiveSword && !IsPassiveMagic) return RUNTIME_SKILL_TYPE_SWORD;
	if (!IsPassiveSword && IsPassiveMagic) return RUNTIME_SKILL_TYPE_MAGIC;

	if (IsPassiveSword && IsPassiveMagic) {
		if (Skill->SkillType == RUNTIME_SKILL_TYPE_SWORD) return RUNTIME_SKILL_TYPE_MAGIC;
		if (Skill->SkillType == RUNTIME_SKILL_TYPE_MAGIC) return RUNTIME_SKILL_TYPE_SWORD;
	}

	return Skill->SkillType;
}

Int32 RTCharacterSkillDataGetSkillExp(
	RTCharacterSkillDataRef Skill,
	Int32 SkillResult
) {
	if (SkillResult == RUNTIME_SKILL_RESULT_CRITICAL) return Skill->SkillExp2;
	if (SkillResult == RUNTIME_SKILL_RESULT_NORMAL) return Skill->SkillExp1;

	return 0;
}

Int32 RTCalculateDistance(
	Int32 X1,
	Int32 Y1,
	Int32 X2,
	Int32 Y2
) {
	Int32 DeltaX = ABS(X2 - X1);
	Int32 DeltaY = ABS(Y2 - Y1);

	return (DeltaX >= DeltaY) ? DeltaX : DeltaY;
}

// TODO: The Radius is a float so we should calculate the distance in real world coords
Bool RTCheckSkillTargetDistance(
	RTCharacterSkillDataRef Skill,
	Float32 Radius,
	Int32 Scale,
	Int32 SourceX,
	Int32 SourceY,
	Int32 TargetX,
	Int32 TargetY
) {
	Int32 Permutations[9][2] = {
		{SourceX, SourceY},
		{SourceX + Radius, SourceY},
		{SourceX - Radius, SourceY},
		{SourceX, SourceY + Radius},
		{SourceX, SourceY - Radius},
		{SourceX + Radius, SourceY - Radius},
		{SourceX - Radius, SourceY + Radius},
		{SourceX + Radius, SourceY + Radius},
		{SourceX - Radius, SourceY - Radius}
	};

	Int32 ErrorTolerance = 2;
	Int32 MaxDistance = (Skill->RangeType == RUNTIME_SKILL_RANGE_TYPE_RECT) ? Skill->Range - 1 : Skill->Reach;
	MaxDistance += ErrorTolerance;

	for (Int32 Index = 0; Index < 9; Index++) {
		Int32 Distance = RTCalculateDistance(TargetX, TargetY, Permutations[Index][0], Permutations[Index][1]);
		if (Distance <= MaxDistance) return true;
	}

	return false;
}

Int32 RTCalculateSkillSlopeValue(
	Int32 CoefficientA,
	Int32 CoefficientB,
	Int32 Level
) {
	return (CoefficientA * Level + CoefficientB) / 10;
}

RTCharacterSkillValue RTCalculateSkillValue(
	RTCharacterSkillDataRef SkillData,
	Int32 Level,
	Int32 Rage
) {
	RTCharacterSkillValue Result = { 0 };
	if (SkillData->DamageType == RUNTIME_SKILL_DAMAGE_TYPE_SWORD) {
		Result.SwordSkillAmp = RTCalculateSkillSlopeValue(SkillData->SAmp[0], SkillData->SAmp[1], Level);
		Result.Attack = RTCalculateSkillSlopeValue(SkillData->Atk[0], SkillData->Atk[1], Level);
		Result.Attack += Rage * ((SkillData->Atk[2] * Level) / 10);
	}
	else {
		Result.MagicSkillAmp = RTCalculateSkillSlopeValue(SkillData->SAmp[0], SkillData->SAmp[1], Level);
		Result.MagicAttack = RTCalculateSkillSlopeValue(SkillData->SAmp[0], SkillData->SAmp[1], Level);
		Result.MagicAttack += Rage * ((SkillData->Atk[2] * Level) / 10);
	}

	Result.AttackRate = RTCalculateSkillSlopeValue(SkillData->SHit[0], SkillData->SHit[1], Level);
	Result.Penetration = RTCalculateSkillSlopeValue(SkillData->SPenet[0], SkillData->SPenet[1], Level);
	Result.CriticalDamage = RTCalculateSkillSlopeValue(SkillData->CritDmg[0], SkillData->CritDmg[1], Level);
	Result.Mp = RTCalculateSkillSlopeValue(SkillData->Mp[0], SkillData->Mp[1], Level);
	return Result;
}

Int32 RTCalculateSkillDuration(
	RTCharacterSkillDataRef SkillData
) {
	if (SkillData->Sp > 0) {
		return 10000000 / SkillData->Sp;
	}

	// TODO: Calculate normal skill duration
	return 0;
}

Int32 RTCharacterApplyBuff(
    RTRuntimeRef Runtime,
    RTCharacterRef Character,
	Int32 ForceEffectIndex,
	Int32 ForceEffectValue,
	Int32 Duration,
	Int32 Cooldown
) {
    Int32 BuffResult = 0;
	// TODO: Add force effect system with buff support...
    
	return RUNTIME_SKILL_RESULT_BUFF_SUCCESS;
}

Int32 RTCharacterGetBattleModeSkillIndex(
	RTRuntimeRef Runtime,
	RTCharacterRef Character,
	Int32 BattleModeIndex
) {
	Int32 SkillSlotIndices[] = {
		RUNTIME_SPECIAL_SKILL_SLOT_BATTLE_MODE_1,
		RUNTIME_SPECIAL_SKILL_SLOT_BATTLE_MODE_2,
		RUNTIME_SPECIAL_SKILL_SLOT_BATTLE_MODE_3,
	};

	for (Int32 Index = 0; Index < sizeof(SkillSlotIndices) / sizeof(SkillSlotIndices[0]); Index += 1) {
		RTSkillSlotRef SkillSlot = RTCharacterGetSkillSlotBySlotIndex(Runtime, Character, SkillSlotIndices[Index]);
		if (!SkillSlot) continue;

		RTCharacterSkillDataRef SkillData = RTRuntimeGetCharacterSkillDataByID(Runtime, SkillSlot->ID);
		if (!SkillData) continue;
		if (SkillData->Intensity != BattleModeIndex) continue;

		return SkillData->SkillID;
	}

	return 0;
}

Int32 RTCharacterGetAuraModeSkillIndex(
	RTRuntimeRef Runtime,
	RTCharacterRef Character,
	Int32 AuraModeIndex
) {
	Int32 SkillSlotIndices[] = {
		RUNTIME_SPECIAL_SKILL_SLOT_AURA_MODE_1,
		RUNTIME_SPECIAL_SKILL_SLOT_AURA_MODE_2,
		RUNTIME_SPECIAL_SKILL_SLOT_AURA_MODE_3,
		RUNTIME_SPECIAL_SKILL_SLOT_AURA_MODE_4,
		RUNTIME_SPECIAL_SKILL_SLOT_AURA_MODE_5,
	};

	for (Int32 Index = 0; Index < sizeof(SkillSlotIndices) / sizeof(SkillSlotIndices[0]); Index += 1) {
		RTSkillSlotRef SkillSlot = RTCharacterGetSkillSlotBySlotIndex(Runtime, Character, SkillSlotIndices[Index]);
		if (!SkillSlot) continue;

		RTCharacterSkillDataRef SkillData = RTRuntimeGetCharacterSkillDataByID(Runtime, SkillSlot->ID);
		if (!SkillData) continue;
		if (SkillData->Intensity != AuraModeIndex) continue;

		return SkillData->SkillID;
	}

	return 0;
}
