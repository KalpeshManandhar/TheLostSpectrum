workspace "TheLostSpectrum"  
    configurations { "Debug", "Release" } 
    architecture "x64"
    project "TheLostSpectrum"  
    kind "ConsoleApp"   
    language "C++"   
    targetdir "bin/%{cfg.buildcfg}" 
    files {"./src/**.cpp" } 
    architecture "x64"
    
    includedirs {"include"}
    libdirs {"lib"}
    links {
        "msvcrt", 
        "raylib", 
        "OpenGL32", 
        "Gdi32", 
        "WinMM", 
        "kernel32", 
        "shell32", 
        "User32",
    }
    ignoredefaultlibraries {"libcmt"}

    filter "configurations:Debug"
    defines { "DEBUG" }  
    symbols "On" 
    filter "configurations:Release"  
    defines { "NDEBUG" }    
    optimize "On" 