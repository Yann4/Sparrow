#pragma once

#include <istream>
#include <ostream>

#include <functional>

namespace Sparrow
{
	namespace FileSystem
	{
		bool Save(std::ofstream& stream, const char* path);
		void Load(const char* path, std::function<void(std::ifstream& /*stream*/)> onLoaded);
	}
}