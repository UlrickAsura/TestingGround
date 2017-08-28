// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestingGroundGameMode.h"
#include "TestingGroundHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "Terrain/Tile.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPoolComponent.h"

ATestingGroundGameMode::ATestingGroundGameMode()
	: Super()
{
	ActorPool = CreateDefaultSubobject<UActorPoolComponent>(FName("NavMeshBoundVolume Pool"));
}

ATile* ATestingGroundGameMode::SpawnTile()
{
	check(TileBlueprint != nullptr && "Did you forget to specify a blueprint for the tile")
	if (TileBlueprint)
	{
		if (GetWorld())
		{
			ATile* Tile = GetWorld()->SpawnActor<ATile>(TileBlueprint);
			if (Tile)
			{
				//Give the reference of the actor pool to the tile
				Tile->SetActorPool(ActorPool);
				Tile->SetActorTransform(NextTileTransform);
				Tile->Lock();
				Tile->PositionNavMeshBoundsVolume();
				NextTileTransform = Tile->GetAttachLocation();
			}
			return Tile;
		}
	}
	return nullptr;
}
void ATestingGroundGameMode::BeginPlay()
{
	Super::BeginPlay();
	ATile* CurrentTile = SpawnTile();
	if (CurrentTile)
	{
		CurrentTile->UnLock();
	}
	SpawnTile();
	PopulateBoundsVolumePool();
}

void ATestingGroundGameMode::AddToPool(ANavMeshBoundsVolume *NavMeshBoundsVolume)
{
	if (ActorPool)
	{
		ActorPool->Add(NavMeshBoundsVolume);
	}
}

void ATestingGroundGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavMeshIterator(GetWorld());
	while (NavMeshIterator)
	{
		AddToPool(*NavMeshIterator);
		++NavMeshIterator;
	}
}