// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HotGirlBaseBall : ModuleRules
{
    public HotGirlBaseBall(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Slate", "Engine", "InputCore", "EnhancedInput", "MoviePlayer", "AIModule", "UMG", "CustomizableObject", });
    }
}
