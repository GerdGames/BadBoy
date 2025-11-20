// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BadBoyEditorTarget : TargetRules
{
	public BadBoyEditorTarget(TargetInfo Target) : base(Target)
	{
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "BadBoy" } );

		DefaultBuildSettings = BuildSettingsVersion.V6;

    }
}
