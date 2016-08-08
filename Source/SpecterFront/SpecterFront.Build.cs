// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpecterFront : ModuleRules
{
	public SpecterFront(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		//if (Target.Configuration == UnrealTargetConfiguration.DebugGame)
		//{
		//BuildConfiguration.bUseUnityBuild = false;
		//}
	}
}
