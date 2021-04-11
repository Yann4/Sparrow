#pragma once
#include "SparrowString.h"
#include "FileSystem.h"
#include "Serialisable.h"

#include <functional>
#include <memory>
#include <sstream>

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
			static bool Save(AssetClass type, const String& path, const AssetReference<AssetType>& serialise)
			{
				return Save(type, path, *serialise);
			}

			template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
			static bool Save(AssetClass type, const String& path, const AssetType& serialise)
			{
				std::stringstream stream;
				serialise.Serialise(stream);
				
				FileSystem::Save(GetDataPath(type, path) + GetFileType(type), stream);

				return true;
			}

			template <class AssetType, typename = std::enable_if<std::is_base_of_v<Serialisable, AssetType>>>
			static bool Load(AssetClass type, const String& path, AssetLoadedEvent<AssetType> OnLoaded)
			{
				FileSystem::Load(GetDataPath(type, path), [type, path, OnLoaded](std::istream & stream)
				{
					std::shared_ptr<AssetType> loadedAsset = std::make_shared<AssetType>(stream);
					OnLoaded(stream.good(), loadedAsset);
				});

				return true;
			}

			static std::vector<Sparrow::String> GetFiles(AssetClass type, const Sparrow::String& fileName)
			{
				return FileSystem::GetFiles(GetDataPath(type, fileName), GetFileType(type));
			}

		private:
			static String RootDirectory()
			{
				return "E:/Dev/Sparrow/";
			}

			static String GetDataPath(AssetClass asset, const String& relativeAssetPath)
			{
				String path = RootDirectory();
				switch (asset)
				{
				case AssetClass::Config:
					path += "Data/Config/";
					break;
				case AssetClass::GameData:
					path += "Data/";
					break;
				case AssetClass::UserGenerated:
					path = "%APPDATA%/Sparrow/";
					break;
				default:
					throw std::exception("AssetClass not implemented");
				}

				//If the path begins the same it means it's actually an absolute path that's been passed in
				if (relativeAssetPath.Contains(path))
				{
					return relativeAssetPath;
				}

				path += relativeAssetPath;

				return path;
			}

			static String GetFileType(AssetClass asset)
			{
				switch (asset)
				{
				case AssetClass::Config:
					return ".conf";
				case AssetClass::GameData:
					return ".sasset";
				case AssetClass::UserGenerated:
					return ".sugc";
				default:
					throw std::exception("AssetClass not implemented");
				}
			}
		};
	}
}