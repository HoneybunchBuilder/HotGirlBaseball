// Copyright Ada Tufankjian 2025

#pragma once

#include "CoreMinimal.h"

#include "HGBBTypes.generated.h"

UENUM(BlueprintType)
enum class EBase : uint8 {
    Home = 0 UMETA(DisplayName = "Home"),
    First = 1 UMETA(DisplayName = "First"),
    Second = 2 UMETA(DisplayName = "Second"),
    Third = 3 UMETA(DisplayName = "Third"),
};

UENUM(BlueprintType)
enum class EFieldingPosition : uint8 {
    Pitcher = 0 UMETA(DisplayName = "Pitcher"),
    Catcher = 1 UMETA(DisplayName = "Catcher"),
    FirstBase = 2 UMETA(DisplayName = "First Base"),
    SecondBase = 3 UMETA(DisplayName = "Second Base"),
    Shortstop = 4 UMETA(DisplayName = "Shortstop"),
    ThirdBase = 5 UMETA(DisplayName = "Third Base"),
    LeftField = 6 UMETA(DisplayName = "Left Field"),
    CenterField = 7 UMETA(DisplayName = "Center Field"),
    RightField = 8 UMETA(DisplayName = "Right Field"),
};

UENUM(BlueprintType)
enum class EHandedness : uint8 {
    RightHanded = 0 UMETA(DisplayName = "Right Handed"),
    LeftHanded = 1 UMETA(DisplayName = "Left Handed"),
};

UENUM(BlueprintType)
enum class EHitArc : uint8 {
    GroundBall = 0 UMETA(DisplayName = "Ground Ball"),
    LineDrive = 1 UMETA(DisplayName = "Line Drive"),
    PopFly = 2 UMETA(DisplayName = "Pop Fly"),
};

UENUM(BlueprintType)
enum class EHitDirection : uint8 {
    Left = 0 UMETA(DisplayName = "Left"),
    Center = 1 UMETA(DisplayName = "Center"),
    Right = 2 UMETA(DisplayName = "Right"),
    Foul = 3 UMETA(DisplayName = "Foul"),
    HomeRun = 4 UMETA(DisplayName = "Home Run"),
};

UENUM(BlueprintType)
enum class ETeamType : uint8 {
    Home = 0 UMETA(DisplayName = "Home"),
    Away = 1 UMETA(DisplayName = "Away"),
};

