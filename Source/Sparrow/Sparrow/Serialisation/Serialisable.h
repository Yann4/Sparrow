#pragma once
#include <iostream>

namespace Sparrow
{
	namespace Serialisation
	{
		class Serialisable
		{
		public:
			Serialisable(uint16_t version, std::istream& stream) :
				Version(version)
			{}

			Serialisable(uint16_t version) :
				Version(version)
			{}

			virtual void Serialise(std::ostream& stream) const
			{
				stream << Version << Delimiter;
			}

		protected:
			const char* Delimiter = "\n";

		protected:
			uint16_t Version;
		};
	}
}

