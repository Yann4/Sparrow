#include "Defines.h"

#if SPARROW_WINDOWS
#include "FileSystem.h"
#include <filesystem>

namespace Sparrow
{
	namespace FileSystem
	{
		bool Save(const Sparrow::String& path, std::ostream& stream)
		{
			EnsurePathExists(path);

			stream.seekp(0);

			std::ofstream file(path.c_str(), std::ofstream::out | std::ofstream::trunc);
			if (!file.is_open() || !file.good())
			{
				return false;
			}

			file << stream.rdbuf();

			file.flush();
			file.close();

			return file.good();
		}

		void Load(const Sparrow::String& path, std::function<void(std::istream& /*stream*/)> onLoaded)
		{
			std::ifstream fstream(path.c_str(), std::fstream::in);
			onLoaded(fstream);
		}

		void EnsurePathExists(const Sparrow::String& path)
		{
			std::filesystem::path toCheck = path.c_str();
			if (!std::filesystem::exists(toCheck.parent_path()))
			{
				std::filesystem::create_directories(toCheck.parent_path());
			}
		}

		std::vector<Sparrow::String> GetFiles(const Sparrow::String& directory, const Sparrow::String& fileType)
		{
			std::filesystem::path dir = directory.c_str();
			std::vector<Sparrow::String> files;
			if (std::filesystem::exists(dir))
			{
				for (const auto& path : std::filesystem::directory_iterator(dir))
				{
					if (path.is_regular_file()
						&& (fileType.IsEmpty() || path.path().extension().compare(fileType.c_str()) == 0))
					{
						files.emplace_back(path.path().string().c_str());
					}
				}
			}

			return files;
		}
	}
}
#endif //SPARROW_WINDOWS