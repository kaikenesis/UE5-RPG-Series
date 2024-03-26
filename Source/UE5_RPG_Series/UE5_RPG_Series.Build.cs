// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_RPG_Series : ModuleRules
{
	public UE5_RPG_Series(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
    }
}
