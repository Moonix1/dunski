workspace "Duski"
	architecture "x86_64"
	configurations { "Debug", "Release" }

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/libs/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/libs/GLAD/include"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "libs"

include "libs/GLFW/"
include "libs/GLAD/"

group ""

project "Duski"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"
	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin/obj/%{cfg.buildcfg}"

	files {
		"include/**.h",
		"src/**.h", "src/**.cpp",
		"examples/**.h", "examples/**.cpp",
	}

	includedirs {
		"libs/spdlog/include",
		"%{wks.location}/src",
		"%{wks.location}/include",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}",
	}

	links {
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}
	
	filter "configurations:Debug"
        defines { "DUSKI_DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "DUSKI_RELEASE" }
        optimize "On"