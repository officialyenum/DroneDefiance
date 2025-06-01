// Copyright Chukwuyenum Opone All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class DroneDefianceTarget : TargetRules
{
	public DroneDefianceTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "DroneDefiance" } );
	}
}
