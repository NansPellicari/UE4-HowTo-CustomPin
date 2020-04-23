// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE4HowtoCustomPin : ModuleRules
{
    public UE4HowtoCustomPin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "CustomPin", "Slate", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
