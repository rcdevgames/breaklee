#pragma once

#include "Base.h"

#define RUNTIME_MAX_ANIMA_MASTERY_PRESET_COUNT					5
#define RUNTIME_MAX_ANIMA_MASTERY_CATEGORY_COUNT				10
#define RUNTIME_MAX_ANIMA_MASTERY_STORAGE_COUNT					5
#define RUNTIME_MAX_ANIMA_MASTERY_SLOT_COUNT					10

#define RUNTIME_ACCOUNT_MAX_CHARACTER_COUNT						16

#define RUNTIME_CHARACTER_MAX_NAME_LENGTH						16
#define RUNTIME_CHARACTER_MAX_AURA_MASTERY_SLOT_COUNT			40
#define RUNTIME_CHARACTER_MAX_BUFF_SLOT_COUNT					32
#define RUNTIME_CHARACTER_MAX_SKILL_SLOT_COUNT					255
#define RUNTIME_CHARACTER_MAX_QUICK_SLOT_COUNT					296
#define RUNTIME_CHARACTER_MAX_QUEST_SLOT_COUNT					20
#define RUNTIME_CHARACTER_MAX_QUEST_FLAG_COUNT					512
#define RUNTIME_CHARACTER_MAX_QUEST_DUNGEON_FLAG_COUNT			128
#define RUNTIME_CHARACTER_MAX_MISSION_DUNGEON_FLAG_COUNT		128
#define RUNTIME_CHARACTER_QUEST_DUNGEON_FLAG_LIMIT				4096
#define RUNTIME_CHARACTER_QUEST_FLAG_SIZE						8
#define RUNTIME_CHARACTER_MAX_ACHIEVEMENT_SLOT_COUNT			512
#define RUNTIME_CHARACTER_MAX_BLESSING_BEAD_SLOT_COUNT			16
#define RUNTIME_CHARACTER_MAX_COOLDOWN_SLOT_COUNT				16
#define RUNTIME_CHARACTER_MAX_DAILY_QUEST_SLOT_COUNT			16
#define RUNTIME_CHARACTER_MAX_DAMAGE_BOOSTER_SLOT_COUNT			2
#define RUNTIME_CHARACTER_MAX_EQUIPMENT_COUNT					51
#define RUNTIME_CHARACTER_MAX_EQUIPMENT_PRESET_SLOT_COUNT		(8 * 8)
#define RUNTIME_CHARACTER_MAX_RECOVERY_SLOT_COUNT				9
#define RUNTIME_CHARACTER_AXP_PER_LEVEL							10000000
#define RUNTIME_CHARACTER_MAX_ABILITY_POINT						700
#define RUNTIME_CHARACTER_MAX_ACCOUNT_COSTUME_SLOT_COUNT		128
#define RUNTIME_CHARACTER_MAX_COSTUME_PAGE_SLOT_COUNT			7
#define RUNTIME_CHARACTER_MAX_COSTUME_PAGE_COUNT				5
#define RUNTIME_CHARACTER_ESSENCE_ABILITY_SLOT_COUNT			16
#define RUNTIME_CHARACTER_BLENDED_ABILITY_SLOT_COUNT			3
#define RUNTIME_CHARACTER_KARMA_ABILITY_SLOT_COUNT				10
#define RUNTIME_CHARACTER_MAX_EVENT_PASS_MISSION_PAGE_COUNT		8
#define RUNTIME_CHARACTER_MAX_EVENT_PASS_MISSION_SLOT_COUNT		64
#define RUNTIME_CHARACTER_MAX_EVENT_PASS_REWARD_SLOT_COUNT		128
#define RUNTIME_CHARACTER_MAX_ESSENCE_ABILITY_SLOT_COUNT		60
#define RUNTIME_CHARACTER_MAX_BLENDED_ABILITY_SLOT_COUNT		30
#define RUNTIME_CHARACTER_MAX_KARMA_ABILITY_SLOT_COUNT			60
#define RUNTIME_CHARACTER_MAX_HONOR_MEDAL_SLOT_COUNT			40
#define RUNTIME_CHARACTER_MAX_OVERLORD_MASTERY_SLOT_COUNT		32
#define RUNTIME_CHARACTER_MAX_PREMIUM_SERVICE_SLOT_COUNT		16
#define RUNTIME_CHARACTER_MAX_COLLECTION_SLOT_COUNT				512
#define RUNTIME_CHARACTER_MAX_COLLECTION_ITEM_COUNT				6
#define RUNTIME_CHARACTER_MAX_CRAFT_SLOT_COUNT					16
#define RUNTIME_CHARACTER_MAX_REQUEST_CRAFT_SLOT_COUNT			5
#define RUNTIME_CHARACTER_MAX_SECRET_SHOP_SLOT_COUNT			5
#define RUNTIME_CHARACTER_MAX_FORCE_WING_RANK					6
#define RUNTIME_CHARACTER_MAX_FORCE_WING_ARRIVAL_STATS_COUNT	2
#define RUNTIME_CHARACTER_MAX_FORCE_WING_ARRIVAL_STATS_RATE		1000000
#define RUNTIME_CHARACTER_MAX_FORCE_WING_ARRIVAL_SKILL_COUNT	6
#define RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_PAGE_COUNT		5
#define RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_PAGE_SIZE		12
#define RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_TRAINING_COUNT	6
#define RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_SLOT_COUNT		(RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_PAGE_COUNT * RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_PAGE_SIZE * RUNTIME_CHARACTER_MAX_FORCE_WING_PRESET_TRAINING_COUNT)
#define RUNTIME_CHARACTER_FORCE_WING_LEVEL_TRAINING_POINT_COUNT 2
#define RUNTIME_CHARACTER_FORCE_WING_GRADE_TRAINING_POINT_COUNT 10
#define RUNTIME_CHARACTER_MAX_GIFT_BOX_SLOT_COUNT				5
#define RUNTIME_CHARACTER_MAX_GOLD_MERIT_MASTERY_SLOT_COUNT		64
#define RUNTIME_CHARACTER_MAX_PLATINUM_MERIT_MEMORIZE_COUNT		6
#define RUNTIME_CHARACTER_MAX_PLATINUM_MERIT_MASTERY_SLOT_COUNT	64
#define RUNTIME_CHARACTER_MAX_PLATINUM_MERIT_SPECIAL_MASTERY_SLOT_COUNT	10
#define RUNTIME_CHARACTER_MAX_DIAMOND_MERIT_MEMORIZE_COUNT		6
#define RUNTIME_CHARACTER_MAX_DIAMOND_MERIT_MASTERY_SLOT_COUNT	64
#define RUNTIME_CHARACTER_MAX_DIAMOND_MERIT_SPECIAL_MASTERY_SLOT_COUNT	10
#define RUNTIME_CHARACTER_MAX_MERCENARY_SLOT_COUNT				16
#define RUNTIME_CHARACTER_MAX_EXPLORATION_SLOT_COUNT			10
#define RUNTIME_CHARACTER_MAX_MYTH_SLOT_COUNT					80
#define RUNTIME_CHARACTER_MAX_STELLAR_SLOT_COUNT				40
#define RUNTIME_CHARACTER_MAX_TRANSCENDENCE_SLOT_COUNT			32
#define RUNTIME_CHARACTER_MAX_TRANSFORM_SLOT_COUNT				40
#define RUNTIME_CHARACTER_MAX_VEHICLE_INVENTORY_SLOT_COUNT		50
#define RUNTIME_CHARACTER_MAX_WARP_SERVICE_SLOT_COUNT			16
#define RUNTIME_CHARACTER_MAX_RAGE								10
#define RUNTIME_CHARACTER_MAX_BP								10000
#define RUNTIME_CHARACTER_MAX_RESEARCH_SUPPORT_MATERIAL_COUNT	10
#define RUNTIME_CHARACTER_MAX_RESEARCH_SUPPORT_SLOT_COUNT		10
#define RUNTIME_CHARACTER_MAX_RESEARCH_SUPPORT_BOARD_COUNT		10
#define RUNTIME_CHARACTER_MAX_NEWBIE_SUPPORT_SLOT_COUNT			512
#define RUNTIME_CHARACTER_MAX_HONOR_MEDAL_SEAL_SLOT_COUNT		10

#define RUNTIME_DROP_BASE_CURRENCY_MULTIPLIER					10
#define RUNTIME_DROP_BASE_CURRENCY_RATE							4500
#define RUNTIME_DROP_BASE_CURRENCY_BOMB_STACK_SIZE				10
#define RUNTIME_DROP_BASE_CURRENCY_BOMB_MULTIPLIER				5
#define RUNTIME_DROP_BASE_CURRENCY_BOMB_RATE					100

#define RUNTIME_PET_MAX_SLOT_COUNT								32

#define RUNTIME_MAX_FORCE_EFFECT_CODE_COUNT						4
#define RUNTIME_MAX_FORCE_EFFECT_ATTRIBUTE_COUNT				4

#define RUNTIME_ENCHANT_MAX_STAT_INCREASE_LEVEL					7
#define RUNTIME_ENCHANT_SLOPE_MULTIPLIER_LIMIT					4
#define RUNTIME_ENCHANT_SLOPE_DIVIDER							3
#define RUNTIME_ENCHANT_UPGRADE_BASIC_LEVEL_LIMIT				15

#define RUNTIME_MOB_FIND_COUNT_UNMOVABLE						100000000
#define RUNTIME_MOB_MAX_FIND_LEVEL_DIFFERENCE					100
#define RUNTIME_MOB_MAX_REACTION_DISTANCE						16
#define RUNTIME_MOB_MAX_ATTACK_RESULT_COUNT						8
#define RUNTIME_MOB_MAX_EVENT_COUNT								4
#define RUNTIME_MOB_MAX_TILE_COUNT								16

#define RUNTIME_MOB_PATROL_MAX_LINK_COUNT						4

#define RUNTIME_MOB_PATTERN_MAX_PARAMETER_COUNT					4
#define RUNTIME_MOB_PATTERN_MAX_ACTION_COUNT					8
#define RUNTIME_MOB_PATTERN_MAX_ACTION_GROUP_COUNT				32
#define RUNTIME_MOB_PATTERN_MAX_TRIGGER_GROUP_COUNT				32

#define RUNTIME_INVENTORY_PAGE_WIDTH							8
#define RUNTIME_INVENTORY_PAGE_HEIGHT							8
#define RUNTIME_INVENTORY_PAGE_SIZE								(RUNTIME_INVENTORY_PAGE_WIDTH * RUNTIME_INVENTORY_PAGE_HEIGHT)
#define RUNTIME_INVENTORY_PAGE_COUNT							8
#define RUNTIME_INVENTORY_TOTAL_SIZE							(RUNTIME_INVENTORY_PAGE_SIZE * RUNTIME_INVENTORY_PAGE_COUNT)

#define RUNTIME_WAREHOUSE_PAGE_WIDTH							8
#define RUNTIME_WAREHOUSE_PAGE_HEIGHT							16
#define RUNTIME_WAREHOUSE_PAGE_SIZE								(RUNTIME_WAREHOUSE_PAGE_WIDTH * RUNTIME_WAREHOUSE_PAGE_HEIGHT)
#define RUNTIME_WAREHOUSE_PAGE_COUNT							8
#define RUNTIME_WAREHOUSE_TOTAL_SIZE							(RUNTIME_WAREHOUSE_PAGE_SIZE * RUNTIME_WAREHOUSE_PAGE_COUNT)

#define RUNTIME_ITEM_MASK_ID									(~(RUNTIME_ITEM_MASK_BINDING | RUNTIME_ITEM_MASK_LEVEL))
#define RUNTIME_ITEM_MAX_OPTION_COUNT							3
#define RUNTIME_ITEM_MAX_ARTIFACT_OPTION_COUNT					8

#define RUNTIME_MOVEMENT_MAX_WAYPOINT_COUNT						32
#define RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH					64
#define RUNTIME_MOVEMENT_MAX_ERROR_TOLERANCE					256
#define RUNTIME_MOVEMENT_SPEED_BASE								450
#define RUNTIME_MOVEMENT_SPEED_SCALE							100
#define RUNTIME_MOVEMENT_MAX_DISTANCE_IN_RANGE					8
#define RUNTIME_MOVEMENT_MAX_PATH_FIND_NODE_COUNT				1024

#define RUNTIME_NATION_COUNT						            3

#define RUNTIME_MAX_QUEST_COUNTER_COUNT					        3
#define RUNTIME_MAX_QUEST_DUNGEON_INDEX_COUNT					8

#define RUNTIME_SHOP_MAX_ITEM_COUNT                             128

#define RUNTIME_TRAINER_MAX_SKILL_COUNT                         512

#define RUNTIME_PARTY_MAX_MEMBER_COUNT							7
#define RUNTIME_PARTY_MAX_INVENTORY_SLOT_COUNT					8
#define RUNTIME_PARTY_MAX_QUEST_SLOT_COUNT						8

#define RUNTIME_WORLD_SIZE							            256
#define RUNTIME_WORLD_CHUNK_SIZE					            16
#define RUNTIME_WORLD_CHUNK_SIZE_EXPONENT			            4
#define RUNTIME_WORLD_CHUNK_COUNT								(RUNTIME_WORLD_SIZE / RUNTIME_WORLD_CHUNK_SIZE)
#define RUNTIME_WORLD_CHUNK_VISIBLE_RADIUS						2
#define RUNTIME_WORLD_TILE_SIZE_EXPONENT                        4
#define RUNTIME_WORLD_MAX_NPC_COUNT				                16

#define RUNTIME_DUNGEON_MAX_PATTERN_PART_COUNT	                16
#define RUNTIME_DUNGEON_MAX_TRIGGER_MOB_COUNT                   64
#define RUNTIME_DUNGEON_MAX_TIMER_COUNT							64
#define RUNTIME_DUNGEON_MAX_TIMER_MOB_COUNT						16
#define RUNTIME_DUNGEON_MAX_START_KILL_MOB_COUNT				16
#define RUNTIME_DUNGEON_MAX_IMMUNE_CONTROL_COUNT				128

#define RUNTIME_BATTLE_MODE_SP_CONSUMPTION						5000
#define RUNTIME_REGENERATION_INTERVAL							2000

#define RUNTIME_MAX_SETTINGS_DATA_LENGTH						1024

#define RUNTIME_MEMORY_MAX_SCRIPT_COUNT							256
#define RUNTIME_MEMORY_MAX_ENTITY_COUNT				            (0xFFFF - 1)
#define RUNTIME_MEMORY_MAX_CHARACTER_COUNT			            0xFF
#define RUNTIME_MEMORY_MAX_CHARACTER_SKILL_DATA_COUNT           1024
#define RUNTIME_MEMORY_MAX_ITEM_DATA_COUNT			            8192
#define RUNTIME_MEMORY_MAX_MOB_COUNT				            1024
#define RUNTIME_MEMORY_MAX_MOB_DATA_COUNT			            8192
#define RUNTIME_MEMORY_MAX_MOB_SKILL_GROUP_COUNT                8
#define RUNTIME_MEMORY_MAX_MOB_AGGRO_COUNT                      8
#define RUNTIME_MEMORY_MAX_MOB_ENEMY_COUNT						8
#define RUNTIME_MEMORY_MAX_MOB_PATROL_COUNT						128
#define RUNTIME_MEMORY_MAX_MOB_PATTERN_COUNT					1024
#define RUNTIME_MEMORY_MAX_ITEM_COUNT				            (0xFF - 1)
#define RUNTIME_MEMORY_MAX_NPC_COUNT				            4096
#define RUNTIME_MEMORY_MAX_PARTY_COUNT							RUNTIME_MEMORY_MAX_CHARACTER_COUNT
#define RUNTIME_MEMORY_MAX_TRAINER_DATA_COUNT                   128
#define RUNTIME_MEMORY_MAX_QUEST_NPC_COUNT			            32
#define RUNTIME_MEMORY_MAX_QUEST_DATA_COUNT			            2048
#define RUNTIME_MEMORY_MAX_QUEST_REWARD_ITEM_DATA_COUNT         64
#define RUNTIME_MEMORY_MAX_QUEST_REWARD_ITEM_SET_DATA_COUNT     512
#define RUNTIME_MEMORY_MAX_WARP_INDEX_COUNT			            1024
#define RUNTIME_MEMORY_MAX_WARP_COUNT				            1024
#define RUNTIME_MEMORY_MAX_WORLD_DATA_COUNT                     256
#define RUNTIME_MEMORY_MAX_GLOBAL_WORLD_CONTEXT_COUNT		    256
#define RUNTIME_MEMORY_MAX_PARTY_WORLD_CONTEXT_COUNT		    256
#define RUNTIME_MEMORY_MAX_LEVEL_COUNT				            256
#define RUNTIME_MEMORY_MAX_SLOPE_DATA_COUNT                     8
#define RUNTIME_MEMORY_MAX_SLOPE_FORMULA_COUNT                  256
#define RUNTIME_MEMORY_MAX_SKILL_VALUE_DATA_COUNT				32
#define RUNTIME_MEMORY_MAX_SKILL_LEVEL_DATA_COUNT               32
#define RUNTIME_MEMORY_MAX_SKILL_RANK_DATA_COUNT                32
#define RUNTIME_MEMORY_MAX_BATTLE_RANK_DATA_COUNT               32
#define RUNTIME_MEMORY_MAX_HONOR_LEVEL_DATA_COUNT               64
