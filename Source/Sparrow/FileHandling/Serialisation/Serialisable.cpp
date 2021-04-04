#include "Serialisable.h"

namespace Sparrow
{
	namespace Serialisation
	{
		const char* Serialisable::Delimiter = "\n";

		Serialisable::Serialisable(std::istream& stream)
		{
			stream >> m_Version;
		}

		Serialisable::Serialisable(uint16_t version) :
			m_Version(version)
		{}

		void Serialisable::Serialise(std::ostream& stream) const
		{
			stream << m_Version << Delimiter;
		}
	}
}