#pragma once

#include <ostream>
#include <istream>
#include <fstream>

#include <functional>

namespace Sparrow
{
	namespace FileSystem
	{
		bool Save(std::ostream& stream, const char* path);
		void Load(const char* path, std::function<void(std::istream& /*stream*/)> onLoaded);

		std::ifstream CreateStream(const char* data, uint32_t length);

		uint64_t GetStreamData_NoAlloc(std::ofstream& stream, char* buffer);
		uint64_t GetStreamData(std::ofstream& stream, char* buffer);
	}
}