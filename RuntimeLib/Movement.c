#include "Movement.h"
#include "Runtime.h"

Void RTMovementInitialize(
	RTRuntimeRef Runtime,
	RTMovementRef Movement,
	RTEntityID Entity,
	Int32 X,
	Int32 Y,
	Int32 Speed,
	UInt32 CollisionMask
) {
	memset(Movement, 0, sizeof(struct _RTMovement));

	Movement->WorldContext = NULL;
    Movement->WorldChunk = NULL;
	Movement->Entity = Entity;
	Movement->PositionBegin.X = X;
	Movement->PositionBegin.Y = Y;
	Movement->PositionCurrent.X = X;
	Movement->PositionCurrent.Y = Y;
	Movement->PositionEnd.X = X;
	Movement->PositionEnd.Y = Y;
	Movement->PositionTile.X = X;
	Movement->PositionTile.Y = Y;
	Movement->CollisionMask = CollisionMask;
	Movement->IgnoreMask = 0;
	Movement->TickCount = (UInt32)PlatformGetTickCount();
	RTMovementSetSpeed(Runtime, Movement, Speed);
}

Void RTMovementStartDeadReckoning(
    RTRuntimeRef Runtime,
    RTMovementRef Movement
) {
	RTPositionRef WaypointA = &Movement->Waypoints[0];
	RTPositionRef WaypointB = &Movement->Waypoints[1];
	Int32 DeltaX = WaypointB->X - WaypointA->X;
	Int32 DeltaY = WaypointB->Y - WaypointA->Y;
	Int32 AbsDeltaX = (DeltaX >= 0) ? DeltaX : -DeltaX;
	Int32 AbsDeltaY = (DeltaY >= 0) ? DeltaY : -DeltaY;

	if (AbsDeltaX >= RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH) {
		AbsDeltaX = RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH - 1;
	}

	if (AbsDeltaY >= RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH) {
		AbsDeltaY = RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH - 1;
	}

	Movement->WaypointIndex = 0;
	Movement->Distance = Runtime->MovementDistanceCache[AbsDeltaX + AbsDeltaY * RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH];
	Movement->Base = 0;
	Movement->Sin = (Float32)DeltaY / Movement->Distance;
	Movement->Cos = (Float32)DeltaX / Movement->Distance;
	Movement->IsMoving = true;
	Movement->IsDeadReckoning = true;
	Movement->TickCount = (UInt32)PlatformGetTickCount();

	if (Movement->Entity.EntityType == RUNTIME_ENTITY_TYPE_CHARACTER) {
		RTWorldTileDecreaseCharacterCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
		Movement->PositionTile.X = Movement->PositionEnd.X;
		Movement->PositionTile.Y = Movement->PositionEnd.Y;
		RTWorldTileIncreaseCharacterCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
	}
	else if (Movement->Entity.EntityType == RUNTIME_ENTITY_TYPE_MOB) {
		RTWorldTileDecreaseMobCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
		Movement->PositionTile.X = Movement->PositionEnd.X;
		Movement->PositionTile.Y = Movement->PositionEnd.Y;
		RTWorldTileIncreaseMobCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
	}
}

Void RTMovementRestartDeadReckoning(
	RTRuntimeRef Runtime,
	RTMovementRef Movement
) {
	assert(Movement->IsMoving);

	RTPositionRef WaypointA = &Movement->Waypoints[0];
	RTPositionRef WaypointB = &Movement->Waypoints[1];
	Int32 DeltaX = WaypointB->X - WaypointA->X;
	Int32 DeltaY = WaypointB->Y - WaypointA->Y;
	Int32 AbsDeltaX = (DeltaX >= 0) ? DeltaX : -DeltaX;
	Int32 AbsDeltaY = (DeltaY >= 0) ? DeltaY : -DeltaY;

	if (AbsDeltaX >= RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH) {
		AbsDeltaX = RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH - 1;
	}

	if (AbsDeltaY >= RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH) {
		AbsDeltaY = RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH - 1;
	}

	Movement->WaypointIndex = 0;
	Movement->Distance = Runtime->MovementDistanceCache[AbsDeltaX + AbsDeltaY * RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH];
	Movement->Base += Movement->Distance;
	Movement->Sin = (Float32)DeltaY / Movement->Distance;
	Movement->Cos = (Float32)DeltaX / Movement->Distance;
	Movement->IsDeadReckoning = true;

	if (Movement->Entity.EntityType == RUNTIME_ENTITY_TYPE_CHARACTER) {
		RTWorldTileDecreaseCharacterCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
		Movement->PositionTile.X = Movement->PositionEnd.X;
		Movement->PositionTile.Y = Movement->PositionEnd.Y;
		RTWorldTileIncreaseCharacterCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
	}
	else if (Movement->Entity.EntityType == RUNTIME_ENTITY_TYPE_MOB) {
		RTWorldTileDecreaseMobCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
		Movement->PositionTile.X = Movement->PositionEnd.X;
		Movement->PositionTile.Y = Movement->PositionEnd.Y;
		RTWorldTileIncreaseMobCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
	}
}

Void RTMovementEndDeadReckoning(
    RTRuntimeRef Runtime,
    RTMovementRef Movement
) {
	Movement->PositionBegin.X = Movement->PositionEnd.X;
	Movement->PositionBegin.Y = Movement->PositionEnd.Y;
	Movement->IsMoving = false;
	Movement->IsDeadReckoning = false;

	if (Movement->Entity.EntityType == RUNTIME_ENTITY_TYPE_CHARACTER) {
		RTWorldTileDecreaseCharacterCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
		Movement->PositionTile.X = Movement->PositionEnd.X;
		Movement->PositionTile.Y = Movement->PositionEnd.Y;
		RTWorldTileIncreaseCharacterCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
	}
	else if (Movement->Entity.EntityType == RUNTIME_ENTITY_TYPE_MOB) {
		RTWorldTileDecreaseMobCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
		Movement->PositionTile.X = Movement->PositionEnd.X;
		Movement->PositionTile.Y = Movement->PositionEnd.Y;
		RTWorldTileIncreaseMobCount(Runtime, Movement->WorldContext, Movement->PositionTile.X, Movement->PositionTile.Y);
	}
}

Void RTMovementUpdateDeadReckoning(
    RTRuntimeRef Runtime,
    RTMovementRef Movement
) {
	if (!Movement->IsDeadReckoning) return;

	UInt32 ElapsedTime = (UInt32)PlatformGetTickCount() - Movement->TickCount;
	Float32 Distance = Movement->Speed * (Float32)ElapsedTime / 1000;
	Float32 Overflow = Distance - Movement->Base;
	if (Overflow < 0) return;

	RTPositionRef WaypointA = &Movement->Waypoints[Movement->WaypointIndex];
	RTPositionRef WaypointB = &Movement->Waypoints[Movement->WaypointIndex + 1];

	while (Overflow >= Movement->Distance) {
		Movement->Base += Movement->Distance;

		WaypointA = WaypointB;

		if (Movement->WaypointIndex + 2 >= Movement->WaypointCount) {
			Movement->IsDeadReckoning = false;
			Movement->PositionCurrent.X = WaypointA->X;
			Movement->PositionCurrent.Y = WaypointA->Y;
			return;
		}

		Movement->WaypointIndex += 1;
		WaypointB = &Movement->Waypoints[Movement->WaypointIndex + 1];

		Int32 DeltaX = WaypointB->X - WaypointA->X;
		Int32 DeltaY = WaypointB->Y - WaypointA->Y;
		Int32 AbsDeltaX = (DeltaX >= 0) ? DeltaX : -DeltaX;
		Int32 AbsDeltaY = (DeltaY >= 0) ? DeltaY : -DeltaY;

		if (AbsDeltaX >= RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH) {
			AbsDeltaX = RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH - 1;
		}

		if (AbsDeltaY >= RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH) {
			AbsDeltaY = RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH - 1;
		}

		Overflow -= Movement->Distance;
		Movement->Distance = Runtime->MovementDistanceCache[AbsDeltaX + AbsDeltaY * RUNTIME_MOVEMENT_MAX_DISTANCE_LENGTH];
		Movement->Sin = (Float32)DeltaY / Movement->Distance;
		Movement->Cos = (Float32)DeltaX / Movement->Distance;
	}

	Int32 DeltaX = WaypointB->X - WaypointA->X;
	Int32 DeltaY = WaypointB->Y - WaypointA->Y;
	Int32 AbsDeltaX = (DeltaX >= 0) ? DeltaX : -DeltaX;
	Int32 AbsDeltaY = (DeltaY >= 0) ? DeltaY : -DeltaY;
	Int32 NewPositionX;
	Int32 NewPositionY;

	if (AbsDeltaX > AbsDeltaY) {
		Int32 PositionX = (Int32)(Overflow * Movement->Cos);
		Int32 OffsetX = (PositionX < 0) ? -PositionX : PositionX;
		Int32 OffsetY = (AbsDeltaY * OffsetX + (AbsDeltaX >> 1)) / AbsDeltaX;

		if (DeltaX < 0) {
			OffsetX = -OffsetX;
		}

		if (DeltaY < 0) {
			OffsetY = -OffsetY;
		}

		NewPositionX = WaypointA->X + OffsetX;
		NewPositionY = WaypointA->Y + OffsetY;
	}
	else {
		Int32 PositionY = (Int32)(Overflow * Movement->Sin);
		Int32 OffsetY = (PositionY < 0) ? -PositionY : PositionY;
		Int32 OffsetX = (AbsDeltaX * OffsetY + (AbsDeltaY >> 1)) / AbsDeltaY;

		if (DeltaX < 0) {
			OffsetX = -OffsetX;
		}

		if (DeltaY < 0) {
			OffsetY = -OffsetY;
		}

		NewPositionX = WaypointA->X + OffsetX;
		NewPositionY = WaypointA->Y + OffsetY;
	}

	Movement->PositionCurrent.X = NewPositionX;
	Movement->PositionCurrent.Y = NewPositionY;
}

Void RTMovementSetSpeed(
	RTRuntimeRef Runtime,
	RTMovementRef Movement,
	Int32 Speed
) {
	Movement->Speed = (Float32)Speed / RUNTIME_MOVEMENT_SPEED_SCALE;
}

Void RTMovementSetPosition(
	RTRuntimeRef Runtime,
	RTMovementRef Movement,
	Int32 X,
	Int32 Y
) {
	Movement->PositionCurrent.X = X;
	Movement->PositionCurrent.Y = Y;
	Movement->PositionBegin.X = X;
	Movement->PositionBegin.Y = Y;
	Movement->PositionEnd.X = X;
	Movement->PositionEnd.Y = Y;

	if (Movement->WorldContext && Movement->WorldChunk && !RTEntityIsNull(Movement->Entity)) {
		RTWorldChunkUpdate(Movement->WorldChunk, Movement->Entity);
	}
}

Int32 RTMovementDistance(
	RTMovementRef Lhs,
	RTMovementRef Rhs
) {
	return RTCalculateDistance(
		Lhs->PositionCurrent.X, 
		Lhs->PositionCurrent.Y, 
		Rhs->PositionCurrent.X, 
		Rhs->PositionCurrent.Y
	);
}

Bool RTMovementIsInRange(
	RTRuntimeRef Runtime,
	RTMovementRef Movement,
	Int32 X,
	Int32 Y
) {
	if (Movement->IsDeadReckoning) {
		RTMovementUpdateDeadReckoning(Runtime, Movement);
	}

	Int32 DeltaX = X - Movement->PositionCurrent.X;
	Int32 DeltaY = Y - Movement->PositionCurrent.Y;

	return (DeltaX * DeltaX + DeltaY * DeltaY) < (RUNTIME_MOVEMENT_MAX_DISTANCE_IN_RANGE * RUNTIME_MOVEMENT_MAX_DISTANCE_IN_RANGE);
}
