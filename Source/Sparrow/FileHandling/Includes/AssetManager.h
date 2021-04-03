#pragma once
#include <functional>
#include <memory>
#include <sstream>

#include "FileSystem.h"
#include "Serialisable.h"

namespace Sparrow
{
	namespace Serialisation
	{
		enum class AssetClass
		{
			Config,
			GameData,
			UserGenerated
		};

		template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
		using AssetReference = std::shared_ptr<AssetType>;

		template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
		using AssetLoadedEvent = std::function<void(bool /*success*/, AssetReference<AssetType> /*LoadedAsset*/)>;

		class AssetManager
		{
		public:
			template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
			static bool Save(AssetClass type, const char* path, const AssetType& serialise)
			{
				std::stringstream stream;
				serialise.Serialise(stream);
				
				FileSystem::Save(stream, path);

				return true;
			}

			template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
			static bool Load(AssetClass type, const char* path, AssetLoadedEvent<AssetType> OnLoaded)
			{
				FileSystem::Load(path, [type, path, OnLoaded](std::istream & stream)
				{
					uint16_t version;
					stream >> version;

					std::shared_ptr<AssetType> loadedAsset = std::make_shared<AssetType>(version, stream);
					OnLoaded(stream.good(), loadedAsset);
				});

				return true;
			}
		};
	}
}