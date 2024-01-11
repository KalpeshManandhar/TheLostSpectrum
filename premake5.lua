-- EDIT THIS TO THE RAYLIB DIR IN YOUR SYSTEM
raylib_dir = "E:\\libraries\\raylib\\raylibMSVC\\raylib-4.5.0_win64_msvc16"

workspace "TheLostSpectrum"  
    configurations { "Debug", "Release" } 
    architecture "x64"
    project "TheLostSpectrum"  
    kind "ConsoleApp"   
    language "C++"   
    targetdir "bin/%{cfg.buildcfg}" 
    files {"./src/**.cpp" } 

    
    includedirs {"./src/", raylib_dir .. "/include"}
    libdirs {raylib_dir .. "/lib"}
    links {
        -- "msvcrt", 
        -- "msvcrtd", 
        -- "libcmt", 
        -- "libcmtd", 
        "raylib", 
        -- "OpenGL32", 
        -- "Gdi32", 
        "WinMM", 
        "kernel32", 
        "shell32", 
        "User32",
    }
    -- ignoredefaultlibraries {"libcmt"}
    
    filter "configurations:Debug"
    defines { "DEBUG" }  
    symbols "On" 
    filter "configurations:Release"  
    defines { "NDEBUG" }    
    optimize "On" 