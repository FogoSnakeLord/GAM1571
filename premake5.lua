workspace "Game"
	configurations{ "Debug", "Release" }
	platforms { "x64" }

project "Game"
	kind "WindowedApp"

	files{
		"Game/Source/**.cpp",
		"Game/Source/**.h",
		"premake5.lua"
	}