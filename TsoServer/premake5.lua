workspace "TsoServer"
    -- architecture "x64"
    configurations { "Debug", "Release", "Dist" }
	location "build"
	-- startproject "TsoServer"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "TsoServer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("../bin/"..outputdir.."/%{prj.name}")
	objdir  ("../bin-int/"..outputdir.."/%{prj.name}")
    
	files { "src/**.h", "src/**.cpp"}

	defines
	{
		"TSO_SERVER",
	}

    includedirs
	{
		"%{wks.location}/TsoServer/src"
		-- "%{wks.location}/TsoEngine/src/Tso",
		-- "%{wks.location}/TsoEngine/third_party/glm",
		-- "%{wks.location}/TsoEngine/third_party/imgui",
		-- "%{wks.location}/TsoEngine/third_party/entt",
		-- "%{wks.location}/TsoEngine/third_party/yaml-cpp/include",
		-- "%{wks.location}/TsoEngine/third_party/box2d/include",
		-- "%{wks.location}/TsoEngine/third_party/mono/include",
		-- "%{wks.location}/TsoEngine/third_party/msdf-atlas-gen/msfgen/include",
		-- "%{wks.location}/TsoEngine/third_party/msdf-atlas-gen/msdf-atlas-gen",
		-- "%{wks.location}/TsoEngine/third_party/msdf-atlas-gen/msdfgen"
	}

	filter { "configurations:Release"}
		defines { "NDEBUG" }
		optimize "On"
		if _ACTION == "vs2022" then
			buildoptions "/MT"
		end

	filter { "configurations:Dist"}
		defines { "NDEBUG"}
		optimize "On"
		if _ACTION == "vs2022" then
			buildoptions "/MT"
		end

