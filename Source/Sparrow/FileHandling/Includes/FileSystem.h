#pragma once
#include "SparrowString.h"

#include <ostream>
#include <istream>
#include <fstream>
#include <vector>

#include <functional>

namespace Sparrow
{
	namespace FileSystem
	{
		bool Save(const Sparrow::String& path, std::ostream& stream);
		void Load(const Sparrow::String& path, std::function<void(std::istream& /*stream*/)> onLoaded);
		void EnsurePathExists(const Sparrow::String& path);
		std::vector<Sparrow::String> GetFiles(const Sparrow::String& directory, const Sparrow::String& fileType = Sparrow::String::Empty);

		std::ifstream CreateStream(const Sparrow::String& data);

		uint64_t GetStreamData_NoAlloc(std::ofstream& stream, char* buffer);
		uint64_t GetStreamData(std::ofstream& stream, char* buffer);
	}
}