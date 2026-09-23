#pragma once
#define RUNNING_WINDOWS
#include <iostream>
#include <string>
#include <algorithm>

namespace Utils
{
	#ifdef RUNNING_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Shlwapi.h>
	#include <iostream>

	inline std::string GetWorkingDirectory()
	{
		HMODULE hModule = GetModuleHandle(nullptr);
		if (hModule) {
			char path[256];
			GetModuleFileNameA(hModule, path, sizeof(path));
			PathRemoveFileSpecA(path);
			strcat_s(path, "\\");
			return std::string(path);
		}
		return "";
	}
	#elif defined RUNNING_LINUX
	#include <unistd.h>
	inline std::string GetWorkingDirectory()
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != nullptr)
			return std::string(cwd) + std::string("/");
		return "";
	}
	#endif

	// These directories are relative to the running executable and can be
	// overridden by the build system (see PixEngine's CMakeLists.txt) so the
	// same source works whether PixEngine is built standalone (with its
	// bundled example project) or embedded as a subdirectory inside another
	// project. Defaults below match the standalone/example build.
	#ifndef PIXENGINE_ENGINE_ASSETS_DIR
	#define PIXENGINE_ENGINE_ASSETS_DIR "assets/"
	#endif
	#ifndef PIXENGINE_ENGINE_CONFIG_DIR
	#define PIXENGINE_ENGINE_CONFIG_DIR "config/"
	#endif
	#ifndef PIXENGINE_GAME_ASSETS_DIR
	#define PIXENGINE_GAME_ASSETS_DIR "example/assets/"
	#endif
	#ifndef PIXENGINE_GAME_CONFIG_DIR
	#define PIXENGINE_GAME_CONFIG_DIR "example/config/"
	#endif

	inline std::string GetGameResourceDirectory()
	{
		return GetWorkingDirectory() + std::string(PIXENGINE_GAME_ASSETS_DIR);
	}

	inline std::string GetEngineResourceDirectory()
	{
		return GetWorkingDirectory() + std::string(PIXENGINE_ENGINE_ASSETS_DIR);
	}

	inline std::string GetEngineConfigDirectory()
	{
		return GetWorkingDirectory() + std::string(PIXENGINE_ENGINE_CONFIG_DIR);
	}

	inline std::string GetGameConfigDirectory()
	{
		return GetWorkingDirectory() + std::string(PIXENGINE_GAME_CONFIG_DIR);
	}

}
