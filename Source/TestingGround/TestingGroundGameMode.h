// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestingGroundGameMode.generated.h"

UCLASS(minimalapi)
class ATestingGroundGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestingGroundGameMode();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Setup")
	TSubclassOf<class ATile> TileBlueprint;

	UFUNCTION(BlueprintCallable)
	class ATile* SpawnTile();

	UFUNCTION(BlueprintCallable,Category= "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:
	virtual void BeginPlay() override;
private:
	FTransform NextTileTransform = FTransform::Identity;

	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
};



