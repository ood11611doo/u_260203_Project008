// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class u_260203_Project008 : ModuleRules
{
	public u_260203_Project008(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
