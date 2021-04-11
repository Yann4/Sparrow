#pragma once
#include "AssetManager.h"
#include "Input_Wrapper.h"

#include <chrono>
#include <thread>
#include <vector>

using namespace Sparrow;

extern "C" {
	DLLEXPORT bool SaveController(const MarshalledController& controller);

	DLLEXPORT void LoadAllControllers();
	DLLEXPORT uint32_t GetControllerCount();
	DLLEXPORT MarshalledController GetController(uint32_t index);
}

template<class AssetType>
std::vector<Serialisation::AssetReference<AssetType>> LoadAllSynchronous(Serialisation::AssetClass type, const String& path)
{
	std::vector<Serialisation::AssetReference<AssetType>> loadedAssets;

	Serialisation::AssetLoadedEvent<AssetType> onLoaded = [&](bool success, Serialisation::AssetReference<AssetType> asset)
	{
		if (success)
		{
			loadedAssets.push_back(asset);
		}
	};

	std::vector<String> paths = Serialisation::AssetManager::GetFiles(type, path);

	for (const String& path : paths)
	{
		Serialisation::AssetManager::Load(type, path, onLoaded);
	}

	while (loadedAssets.size() < paths.size()) { std::this_thread::sleep_for(std::chrono::milliseconds(16)); }

	return loadedAssets;
}