// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"

#include "HGBBTypes.generated.h"

UENUM(BlueprintType)
enum class Base : uint8 {
    Home = 0 UMETA(DisplayName = "Home"),
    First = 1 UMETA(DisplayName = "First"),
    Second = 2 UMETA(DisplayName = "Second"),
    Third = 3 UMETA(DisplayName = "Third"),
};

UENUM(BlueprintType)
enum class EFieldingPosition : uint8 {
    FirstBase = 0 UMETA(DisplayName = "First Base"),
};

UENUM(BlueprintType)
enum class EHandedness : uint8 {
    RightHanded = 0 UMETA(DisplayName = "Right Handed"),
    LeftHanded = 1 UMETA(DisplayName = "Left Handed"),
};

UENUM(BlueprintType)
enum class EHitArc : uint8 {
    GroundBall = 0 UMETA(DisplayName = "Ground Ball"),
};

UENUM(BlueprintType)
enum class EHitDirection : uint8 {
    LeftField = 0 UMETA(DisplayName = "Left Field"),
};

UENUM(BlueprintType)
enum class ETeamType : uint8 {
    Home = 0 UMETA(DisplayName = "Home"),
    Away = 1 UMETA(DisplayName = "Away"),
};

