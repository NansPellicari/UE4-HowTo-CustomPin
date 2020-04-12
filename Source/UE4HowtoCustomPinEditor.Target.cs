using UnrealBuildTool;
using System.Collections.Generic;

public class UE4HowtoCustomPinEditorTarget : TargetRules
{
    public UE4HowtoCustomPinEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "UE4HowtoCustomPin" });
    }
}
