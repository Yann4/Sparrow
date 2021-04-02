#include "FileSystem.h"

namespace Sparrow
{
	namespace FileSystem
	{
		std::ifstream CreateStream(const char* data, uint32_t length)
		{
			std::ifstream stream;
			stream.rdbuf()->sputn(data, length);
			return stream;
		}

		uint64_t GetStreamData_NoAlloc(std::ofstream& stream, char* buffer)
		{
			std::streamsize size = stream.rdbuf()->pubseekoff(0, stream.end);
			stream.rdbuf()->pubseekoff(0, stream.beg);
			stream.rdbuf()->sgetn(buffer, size);
			return size;
		}

		uint64_t GetStreamData(std::ofstream& stream, char* buffer)
		{
			std::streamsize size = stream.rdbuf()->pubseekoff(0, stream.end);
			buffer = static_cast<char*>(malloc(size));
			return GetStreamData_NoAlloc(stream, buffer);
		}
	}
}