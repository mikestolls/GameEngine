-- emulators build script

rootdir = path.join(path.getdirectory(_SCRIPT), "..")

-- Solution
solution "GameEngine"
	language "C++"
	system "Windows"
	architecture "x86"
	configurations { "Debug", "Release" }
	location("../_prj/" .. _ACTION)
    debugdir "../_bin/%{cfg.buildcfg}"
	targetdir "../_bin/%{cfg.buildcfg}"
	objdir "../_obj/%{cfg.buildcfg}/%{prj.name}"
	kind "StaticLib"
    characterset "MBCS"

	defines {
		"_CRT_SECURE_NO_WARNINGS",
	}

    --linkoptions "/opt:ref"
    editandcontinue "on"

    rtti "on"
    exceptionhandling "off"
	
	configuration "Debug*"
		defines { "_DEBUG" }
		-- flags { "FatalWarnings" }
		symbols "on"
				
	configuration "Release*"
		defines { "NDEBUG" }
		optimize "full"

	-- Projects
	project("GameEngine")
		
		flags {
			"NoRuntimeChecks",
		}
			
		files {
            "../data/**",
            "../include/**.h",
			"../src/**.cpp",
			"../submodule/imgui/*.h",
			"../submodule/imgui/*.cpp",
			"../submodule/imgui/misc/freetype/**.h",
			"../submodule/imgui/misc/freetype/**.cpp",
			"../submodule/imgui/examples/libs/gl3w/GL/*.c",
		}
		
        includedirs {
			"../include",
			"../include",
			"../submodule/imgui/examples/libs/glfw/include",
			"../submodule/imgui/examples/libs/gl3w",
			"../submodule/imgui",
			"../submodule/imgui/misc/freetype",
			"../submodule/rapidjson/include",
			"../submodule/glm",
			"../submodule/libfreetype2/freetype2/include",
			"../submodule/assimp/include",
        }
		