project "Idxhook"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ihpch.h"
	pchsource "src/ihpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
        "_CRT_SECURE_NO_WARNINGS",
        "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
	}

	includedirs
	{
        "src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.minhook}"
	}

	links
	{	
		"ImGui",
		"minhook",
		"d3d11"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "IH_DEBUG"
		runtime "Release"
		symbols "on"

	filter "configurations:Release"
		defines "IH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IH_DIST"
		runtime "Release"
		optimize "on"
