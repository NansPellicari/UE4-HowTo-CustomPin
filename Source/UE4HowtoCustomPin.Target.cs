using UnrealBuildTool;
using System.Collections.Generic;

public class UE4HowtoCustomPinTarget : TargetRules
{
    public UE4HowtoCustomPinTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "UE4HowtoCustomPin" });
    }
}
