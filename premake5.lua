workspace "Pigeon"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
-- Ŀ¼�б�
IncludeDir = {}
IncludeDir["GLFW"] = "Pigeon/vendor/GLFW/include"

-- ����GLFW��premake��Ŀ¼���൱��c++��ͷ�ļ�
include "Pigeon/vendor/GLFW"

project "Pigeon"
	location "Pigeon"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- Ԥ����ͷ�ļ�
	pchheader "pgpch.h"
	pchsource "Pigeon/src/pgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/spdlog-1.14.1-win64/include",
		"%{IncludeDir.GLFW}"
	}

	-- ָ����Ŀ¼
	libdirs 
	{
		"%{prj.name}/vendor/spdlog/spdlog-1.14.1-win64/lib",
	}

	-- ָ��Ҫ���ӵĿ�
	links
	{
		"spdlogd.lib",
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PG_BUILD_DLL",
			"PG_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PG_DEBUG"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "PG_RELEASE"
		optimize "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "PG_DIST"
		optimize "On"
		buildoptions "/MD"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Pigeon/vendor/spdlog/spdlog-1.14.1-win64/include",
		"Pigeon/src"
	}

	libdirs 
	{
		"Pigeon/vendor/spdlog/spdlog-1.14.1-win64/lib"
	}

	links
	{
		"Pigeon",
		"spdlogd.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PG_DIST"
		optimize "On"