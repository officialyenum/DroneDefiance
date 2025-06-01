// Copyright Chukwuyenum Opone All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class DroneDefianceEditorTarget : TargetRules
{
	public DroneDefianceEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "DroneDefiance" } );
	}
}
