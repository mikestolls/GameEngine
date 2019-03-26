function isVisualStudio()
	return string.startswith(_ACTION, "vs")
end

function getExistingUUID(filepath)
	local fileext = ".vcxproj"
	local pattern = "<ProjectGuid>{(.+)}</ProjectGuid>"

	filepath = path.join(workspace().location, filepath) .. fileext

	if isVisualStudio() then
		local file, errmsg, errno = io.open(filepath, "r")
		if not file then 
			print(string.format("Could not load %s", filepath))
			return ""
		end

		local content = file:read("*all")
		local _, _, guid = string.find(content, pattern)
		file:close()

		return guid
	else
		return p.uuid
	end
end

function ref_project(name, loc, debug, release)
	local prjPath = path.join(loc, name)
	local absLoc = path.join(workspace().location, loc)
	
	local prjuuid = getExistingUUID(prjPath)

	if isVisualStudio() then
        local prjuuid = getExistingUUID(prjPath)

        externalproject(name)
            location(absLoc)
            uuid(prjuuid)
            kind "StaticLib"
            language "C++"
            configmap {
                ["Debug"] = debug,
                ["Release"] = release
            }
    else
        externalproject(name)
            location(loc)
            kind "StaticLib"
            language "C++"
    end
end

-- sample build script

rootdir = path.join(path.getdirectory(_SCRIPT), "..")

-- Solution
solution "GameEngineSample"
	language "C++"
	system "Windows"
	architecture "x86"
	configurations { "Debug", "Release" }
	location("../_prj/" .. _ACTION)
    characterset "MBCS"

	defines {
		"_CRT_SECURE_NO_WARNINGS",
	}

    --linkoptions "/opt:ref"
    editandcontinue "on"

    rtti "off"
    exceptionhandling "off"
	
	configuration "Debug*"
		defines { "_DEBUG" }
		-- flags { "FatalWarnings" }
		symbols "on"
		
	configuration "Release*"
		defines { "NDEBUG" }
		optimize "full"

	-- Projects
	project("GameEngineSample")
		location("../_prj/" .. _ACTION)
		targetdir "../_bin/%{cfg.buildcfg}"
		debugdir "../_bin/%{cfg.buildcfg}"
		objdir "../_obj/%{cfg.buildcfg}"
        kind "ConsoleApp"
		
		flags {
			"NoRuntimeChecks",
		}
			
		files {
            "../src/**.h",
			"../src/**.cpp",
		}
		
        includedirs {
            "../src",
			"../../include",
        }
		
        links {
			"legacy_stdio_definitions.lib",
            "opengl32.lib",
            "winmm.lib",
			"glfw3.lib",
			"GameEngine.lib",
			"assimp-vc140-mt.lib"
        }
		
		dependson { "GameEngine" }
		
        defines {
		
        }

        libdirs {
            "../../_bin/%{cfg.buildcfg}",
			"../../submodule/imgui/examples/libs/glfw/lib-vc2010-32",
			"../../submodule/assimp/lib/%{cfg.buildcfg}"
        }

        configuration "Debug*"
            links {
			
            }

        configuration "Release*"
            links {
			
            }

        -- postbuildcommands {
        --     "copy \"" .. path.translate(path.join(rootdir, "data", "*.*")) .. '" "' ..
        --         path.translate(path.join(rootdir, "_Bin", "%{cfg.platform}", "%{cfg.buildcfg}", "%{prj.name}")) .. '"'
        -- }

		configuration "Win*"
			defines {
				"WIN32",
			}
			
	-- dependencies
	ref_project("GameEngine", "../../../_prj/" .. _ACTION, "Debug", "Release")
	