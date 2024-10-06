workspace "Engine"
    location "../"
    architecture "x64"
    configurations { "release", "debug" }
    flags { "MultiProcessorCompile" }

    startproject = "Engine"

    BUILD_DIR = "%{wks.location}/Bin"
    OBJS_DIR = "%{BUILD_DIR}/objs"

group "Engine"
    include "../Engine/premake5.lua"
group ""