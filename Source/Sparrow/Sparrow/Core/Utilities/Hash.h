#pragma once
#include <functional>

namespace Sparrow
{
	namespace Hash
	{
		template<class Key>
		uint64_t GetHash(Key hash)
		{
			return std::hash<Key>{}(hash);
		}
	}
}