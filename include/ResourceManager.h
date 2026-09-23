#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/Utilities.h"

template<typename Derived, typename T>
class ResourceManager
{
public:
	ResourceManager(const std::string& l_pathsFile) : m_resources() { LoadPaths(l_pathsFile); }
	virtual ~ResourceManager() { PurgeResources(); }

	T* GetResource(const std::string& l_id)
	{
		auto resource = Find(l_id);
		return(resource ? resource->first : nullptr);
	}

	std::string GetPath(const std::string& l_id)
	{
		auto path = m_paths.find(l_id);
		return(path != m_paths.end() ? path->second : "");
	}

	bool RequireResource(const std::string& l_id)
	{
		auto res = Find(l_id);
		if (res)
		{
			++res->second;
			return true;
		}
		auto path = m_paths.find(l_id);
		if (path == m_paths.end())
			return false;
		T* resource = Load(path->second);
		if (!resource)
			return false;
		m_resources.emplace(l_id, std::make_pair(resource, 1));
		return true;
	}

	bool ReleaseResource(const std::string& l_id)
	{
		auto resource = Find(l_id);
		if (!resource)
			return false;
		--resource->second;
		if (!resource->second)
			Unload(l_id);
		return true;
	}

	void PurgeResources()
	{
		while (m_resources.begin() != m_resources.end())
		{
			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}
	}

protected:
	T* Load(const std::string& l_path)
	{
		return static_cast<Derived*>(this)->Load(l_path);
	}

private:
	std::pair<T*, unsigned int>* Find(const std::string& l_id)
	{
		auto itr = m_resources.find(l_id);
		return (itr != m_resources.end() ? &itr->second : nullptr);
	}

	bool Unload(const std::string& l_id)
	{
		auto itr = m_resources.find(l_id);
		if (itr == m_resources.end())
			return false;
		delete itr->second.first;
		m_resources.erase(itr);
		return true;
	}

	void LoadPaths(const std::string& l_pathFile)
	{
		bool engineLoaded = LoadPathsFromFile(Utils::GetEngineConfigDirectory() + l_pathFile, false);
		LoadPathsFromFile(Utils::GetGameConfigDirectory() + l_pathFile, true);
		if (!engineLoaded)
			std::cerr << "! Failed loading the path file: " << l_pathFile << '\n';
	}

	bool LoadPathsFromFile(const std::string& l_path, bool l_allowOverride)
	{
		std::ifstream paths;
		paths.open(l_path);
		if (!paths.is_open())
			return false;
		std::string line;
		while (std::getline(paths, line))
		{
			std::stringstream keystream(line);
			std::string pathName;
			std::string path;
			keystream >> pathName;
			keystream >> path;
			if (pathName.empty() || path.empty())
				continue;
			if (l_allowOverride)
				m_paths[pathName] = path;
			else
				m_paths.emplace(pathName, path);
		}
		paths.close();
		return true;
	}

	std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_paths;

};
