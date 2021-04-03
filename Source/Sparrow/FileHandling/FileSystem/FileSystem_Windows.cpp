#include "Defines.h"

#if SPARROW_WINDOWS
#include "FileSystem.h"

namespace Sparrow
{
	namespace FileSystem
	{
		bool Save(std::ostream& stream, const char* path)
		{
			stream.seekp(0);

			std::ofstream file(path, std::ofstream::out | std::ofstream::trunc);
			if (!file.is_open() || !file.good())
			{
				return false;
			}

			file << stream.rdbuf();

			file.flush();
			file.close();

			return file.good();
		}

		void Load(const char* path, std::function<void(std::istream& /*stream*/)> onLoaded)
		{
			std::ifstream fstream(path, std::fstream::in);
			onLoaded(fstream);
		}
	}
}
#endif //SPARROW_WINDOWS