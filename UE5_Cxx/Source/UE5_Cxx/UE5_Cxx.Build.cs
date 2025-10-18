// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_Cxx : ModuleRules
{
	public UE5_Cxx(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] 
		{
            "UE5_Cxx",
            "R1",
		});

        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities",
			"NavigationSystem",
			"AIModule",
			"Niagara",
			"UMG",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
