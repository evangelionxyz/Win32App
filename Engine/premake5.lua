project "Program"
    kind "WindowedApp"
    language "c++"
    cppdialect "c++20"
    location "."

    targetdir (BUILD_DIR)
    objdir (OBJS_DIR)

    links { "opengl32", "gdi32", "Dwmapi"}

    files {
        "src/**.cpp",
        "src/**.h",
        "src/**.hpp",

        "third_party/glad/src/glad.c",
    }

    includedirs {
        "src",
        "third_party/glad/include"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
        "NOMINMAX",
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:debug"
        optimize "off"
        symbols "on"
        defines {
            "OGN_DEBUG", "_DEBUG"
        }
    filter "configurations:release"
        optimize "on"
        symbols "on"
        runtime "release"
        defines {
            "ONG_RELEASE", "NDEBUG"
        }