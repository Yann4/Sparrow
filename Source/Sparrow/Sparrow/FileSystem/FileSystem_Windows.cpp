#include "Core/Defines.h"

#if SPARROW_WINDOWS
#include "FileSystem/FileSystem.h"
#include <fstream>

namespace Sparrow
{
	namespace FileSystem
	{
		bool Save(std::ofstream& stream, const char* path)
		{
			stream.rdbuf()->sgetn()
			std::ofstream fstream(path, std::fstream::out);
			fstream << stream.rdbuf();
			fstream.close();

			return fstream.good();
		}

		void Load(const char* path, std::function<void(std::ifstream& /*stream*/)> onLoaded)
		{
			std::ifstream fstream(path, std::fstream::in);
			onLoaded(fstream);
		}
	}
}
#endif //SPARROW_WINDOWS