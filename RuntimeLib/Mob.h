#pragma once

#include "Base.h"
#include "BattleSystem.h"
#include "Entity.h"
#include "Movement.h"
#include "MobPattern.h"

EXTERN_C_BEGIN

#define MOB_EVENT_SPAWN		"on_spawn"
#define MOB_EVENT_DESPAWN	"on_despawn"
#define MOB_EVENT_UPDATE	"on_update"
#define MOB_EVENT_DAMAGE	"on_damage"

enum {
	RUNTIME_MOB_AGGRESSIVE_TYPE_PASSIVE,
	RUNTIME_MOB_AGGRESSIVE_TYPE_AGGRESSIVE,
	RUNTIME_MOB_AGGRESSIVE_TYPE_NATIONONLY,
};

enum {
	RUNTIME_MOB_ATTACK_TYPE_CONCENTRATE,
	RUNTIME_MOB_ATTACK_TYPE_SELECT,
	RUNTIME_MOB_ATTACK_TYPE_REVENGE,
	RUNTIME_MOB_ATTACK_TYPE_NONE
};

enum {
	RUNTIME_MOB_ATTACK_PATTERN_TYPE_NONE = 0,
	RUNTIME_MOB_ATTACK_PATTERN_TYPE_HP_TRIGGER = 1,
	RUNTIME_MOB_ATTACK_PATTERN_TYPE_SITUATIONAL = 2,
	RUNTIME_MOB_ATTACK_PATTERN_TYPE_BY_REACH = 3,
	RUNTIME_MOB_ATTACK_PATTERN_TYPE_SELECTIVE = 4,
};

enum {
	RUNTIME_MOB_PHASE_NONE,
	RUNTIME_MOB_PHASE_MOVE,
	RUNTIME_MOB_PHASE_FIND_PASSIVE,
	RUNTIME_MOB_PHASE_FIND_AGGRESSIVE,
	RUNTIME_MOB_PHASE_FIND_INFINITE,
	RUNTIME_MOB_PHASE_CHASE_CONCENTRATE,
	RUNTIME_MOB_PHASE_CHASE_SELECT,
	RUNTIME_MOB_PHASE_CHASE_REVENGE,
	RUNTIME_MOB_PHASE_ATTACK_CONCENTRATE,
	RUNTIME_MOB_PHASE_ATTACK_SELECT,
	RUNTIME_MOB_PHASE_ATTACK_REVENGE,

	RUNTIME_MOB_PHASE_DEAD,
	RUNTIME_MOB_PHASE_STUN,
	RUNTIME_MOB_PHASE_CHASE_DUNGEON,
	RUNTIME_MOB_PHASE_REQUEST_HELP,
	RUNTIME_MOB_PHASE_ESCAPE,

	RUNTIME_MOB_PHASE_SPAWN,
	RUNTIME_MOB_PHASE_KILL,

	RUNTIME_MOB_PHASE_COUNT
};

enum {
	RUNTIME_MOB_SUBPHASE_NEUTRAL,
	RUNTIME_MOB_SUBPHASE_AGGRESSIVE,

	RUNTIME_MOB_SUBPHASE_COUNT
};

enum {
	RUNTIME_MOB_EVENT_NONE = 0,
	RUNTIME_MOB_EVENT_SPAWN = 1,
	RUNTIME_MOB_EVENT_KILL = 2,
	RUNTIME_MOB_EVENT_DELETE = 3,
	RUNTIME_MOB_EVENT_REVIVE = 4,
};

struct _RTMobSkillData {
	Int32 PhysicalAttackMin;
	Int32 PhysicalAttackMax;
	Int32 Reach;
	Int32 Range;
	Int32 Stance;
	Int32 SkillGroup;
	Timestamp Interval;
	Int32 Distance;
	Int32 Offset;
};

// TODO: Add additional missing fields like resists...
struct _RTMobSpeciesData {
	Int32 MobSpeciesIndex;
	Int32 Level;
	Int64 HP;
	Int32 HPRecharge;
	Int32 AttackRate;
	Int32 DefenseRate;
	Int32 Defense;
	Int32 DamageReduction;
	Int32 Accuracy;
	Int32 Penetration;
	Int32 ResistCriticalRate;
	Int32 IgnoreAccuracy;
	Int32 IgnoreDamageReduction;
	Int32 IgnorePenetration;
	Int32 AbsoluteDamage;
	Int32 ResistSkillAmp;
	Int32 ResistCriticalDamage;
	Int32 ResistSuppression;
	Int32 ResistSilence;
	Int32 ReflectDamage;
	Float32 MoveSpeed;
	Float32 ChaseSpeed;
	Float32 Radius;
	Int32 Property;
	Int32 AttackPattern;
	Int32 AggressiveType;
	Int32 Cooperate;
	Int32 Escape;
	Int32 AttackType;
	Int32 Scale;
	Int32 FindCount;
	Int32 FindInterval;
	Int32 MoveInterval;
	Int32 ChaseInterval;
	Int32 AlertRange;
	Int32 ChaseRange;
	Int32 LimitRangeB;
	struct _RTMobSkillData DefaultSkill;
	struct _RTMobSkillData SpecialSkill;
	Int32 AttackSignal;
	Int32 IsWorldBoss;
	Int32 CanAttack;
	Int32 CanMove;
	UInt64 Exp;
};

struct _RTMobPhaseData {
	Int32 Move;
	Int32 Find;
	Int32 Chase;
	Int32 Attack;
	Int32 Dead;
	Int32 Stun;
};

struct _RTMobSpawnData {
	Index PatternPartIndex;
	Index MobSpeciesIndex;
	Int32 MobPatternIndex;
	Int32 AreaX;
	Int32 AreaY;
	Int32 AreaWidth;
	Int32 AreaHeight;
	Int32 SpawnInterval;
	Int32 SpawnCount;
	Int32 SpawnDefault;
	Int32 Level;
	Int32 IsMissionGate;
	Int32 PerfectDrop;
	Int32 SpawnTriggerID;
	Int32 KillTriggerID;
	Int32 LootDelay;
	Int32 TileCount;
	UInt32 TileAttributes;
	RTPosition Tiles[RUNTIME_MOB_MAX_TILE_COUNT];
	Int32 EventProperty[RUNTIME_MOB_MAX_EVENT_COUNT];
	Int32 EventMobs[RUNTIME_MOB_MAX_EVENT_COUNT];
	Int32 EventInterval[RUNTIME_MOB_MAX_EVENT_COUNT];
	Char Script[MAX_PATH];
};

struct _RTMobAggroData {
	Int32 Count;
	RTEntityID Entities[RUNTIME_MEMORY_MAX_MOB_AGGRO_COUNT];
	Int64 ReceivedDamage[RUNTIME_MEMORY_MAX_MOB_AGGRO_COUNT];
};

struct _RTMob {
	RTEntityID ID;
	RTMobSpeciesDataRef SpeciesData;
	RTEntityID DropOwner;
	struct _RTMobPhaseData PhaseData;
	Int32 Phase;
	Int32 SubPhase;
	Bool IsSpawned;
	Bool IsKilled;
	Bool IsDead;
	Bool IsIdle;
	Bool IsInfiniteSpawn;
	Bool IsPermanentDeath;
	Bool IsChasing;
	Bool IsWall;
	Bool IsAttacked;
	Bool IsAttackingCharacter;
	Bool IsTimerMob;
	Int32 RemainingFindCount;
	Int32 RemainingSpawnCount;
	Int32 AlertRange;
	Int32 ChaseRange;
	Int32 LimitRangeB;
	Timestamp SpawnTimestamp;
	Timestamp DespawnTimestamp;
	Timestamp EscapeTimestamp;
	Timestamp PhaseTimeout;
	Timestamp NextTimestamp;
	Timestamp EventSpawnTimestamp;
	Timestamp EventDespawnTimestamp;
	RTEntityID EventSpawnLinkID;
	RTEntityID EventDespawnLinkID;

	RTMobSkillDataRef ActiveSkill;
	RTDataMobAttackDataRef SpecialAttack;
	RTDataMobSkillRef SpecialAttackSkill;

	Timestamp NextPhaseTimestamp;
	Timestamp NextRegenTimestamp;
	Int64 HPTriggerThreshold;
	Int32 AggroTargetDistance;
	Int32 LinkMobIndex;
	RTEntityID LinkEntityID;

	UInt32 ImmunityFlags;
	Int32 SpecialActionIndex;
	Timestamp SpecialActionStartTimestamp;

	struct _RTMobSpawnData Spawn;
	struct _RTMobAggroData Aggro;
    struct _RTMovement Movement;
	struct _RTBattleAttributes Attributes;
	
	Int32 EnemyCount;
	Int32 Enemies[RUNTIME_MEMORY_MAX_MOB_ENEMY_COUNT];
	RTScriptRef Script;
	RTMobPatternRef Pattern;
};

Void RTMobInit(
	RTRuntimeRef Runtime,
	RTMobRef Mob
);

Void RTMobApplyDamage(
	RTRuntimeRef Runtime,
	RTWorldContextRef World,
	RTMobRef Mob,
	RTEntityID Source,
	Int64 Damage
);

Void RTMobUpdate(
	RTRuntimeRef Runtime,
	RTWorldContextRef World,
	RTMobRef Mob
);

Bool RTMobCanRespawn(
	RTMobRef Mob
);

Bool RTMobIsAlive(
	RTMobRef Mob
);

Void RTMobOnEvent(
	RTRuntimeRef Runtime,
	RTWorldContextRef World,
	RTMobRef Mob,
	CString Event
);

Void RTMobStartSpecialAction(
	RTRuntimeRef Runtime,
	RTWorldContextRef WorldContext,
	RTMobRef Mob,
	Int32 SpecialActionIndex
);

Void RTMobCancelSpecialAction(
	RTRuntimeRef Runtime,
	RTWorldContextRef WorldContext,
	RTMobRef Mob
);

Void RTMobHeal(
	RTRuntimeRef Runtime,
	RTWorldContextRef WorldContext,
	RTMobRef Mob,
	Int64 Amount
);

EXTERN_C_END
