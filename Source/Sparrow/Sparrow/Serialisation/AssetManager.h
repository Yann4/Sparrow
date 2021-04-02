#pragma once
#include <functional>
#include <memory>
#include <type_traits>
#include <sstream>

#include "FileSystem/FileSystem.h"
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

		template <class DataType = char*>
		class Asset
		{
		public:
			Asset(AssetClass type, const char* path, std::shared_ptr<DataType> data) :
				Type(type), Path(path), Data(data)
			{}

			const char* Path;
			AssetClass Type;
			std::shared_ptr<DataType> Data;
		};

		template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
		using AssetReference = std::shared_ptr<Asset<AssetType>>;

		template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
		using AssetLoadedEvent = std::function<void(bool /*success*/, AssetReference<AssetType> /*LoadedAsset*/)>;
		template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
		using ReadOnlyAssetLoadedEvent = std::function<void(bool /*success*/, Asset<AssetType> /*LoadedAsset*/)>;

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

					std::shared_ptr<AssetType> data = std::make_shared<AssetType>(version, stream);
					AssetReference<AssetType> loadedAsset = std::make_shared<Asset<AssetType>>(type, path, data);
					OnLoaded(stream.good(), loadedAsset);
				});

				return true;
			}

			template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
			static bool LoadReadOnly(AssetClass type, const char* path, ReadOnlyAssetLoadedEvent<AssetType> OnLoaded)
			{
				AssetLoadedEvent performCopy = [](bool success, AssetReference<AssetType> loadedAsset)
				{
					if (OnLoaded != nullptr)
					{
						//OnLoaded(success, loadedAsset.get());
					}
				};

				return Load(type, path, performCopy);
			}
		};
	}
}