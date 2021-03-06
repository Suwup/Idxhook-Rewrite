include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Idxhook"
	architecture "x64"
	startproject "Idxhook"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/Idxhook/vendor/imgui"
IncludeDir["minhook"] = "%{wks.location}/Idxhook/vendor/minhook/include"

group "Core"
	include "Idxhook"
group ""

group "Dependencies"
	include "vendor/premake"
	include "Idxhook/vendor/imgui"
	include "Idxhook/vendor/minhook"
group ""