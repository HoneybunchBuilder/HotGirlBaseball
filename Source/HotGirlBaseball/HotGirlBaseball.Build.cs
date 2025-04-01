// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HotGirlBaseball : ModuleRules
{
    public HotGirlBaseball(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Slate", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "MoviePlayer", 
            "AIModule", 
            "UMG", 
            "CustomizableObject", 
            "GameplayAbilities",
        });
    }
}
