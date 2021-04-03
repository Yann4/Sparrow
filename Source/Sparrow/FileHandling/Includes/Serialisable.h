#pragma once
#include <istream>
#include <ostream>
#include <cstdint>

namespace Sparrow
{
	namespace Serialisation
	{
		class Serialisable
		{
		public:
			Serialisable(std::istream& stream)
			{
				stream >> m_Version;
			}

			Serialisable(uint16_t version) :
				m_Version(version)
			{}

			virtual void Serialise(std::ostream& stream) const
			{
				stream << m_Version << Delimiter;
			}

		protected:
			virtual uint16_t LatestVersion() const = 0;
			const char* Delimiter = "\n";

		protected:
			uint16_t m_Version;
		};
	}
}

/*
* Example of a serialisable class
* #include "Serialisable.h"

class Example : public Sparrow::Serialisation::Serialisable
{
public:
	Example(std::istream& stream) :
		Serialisable(stream)
	{
		if (m_Version == 1)
		{
			stream >> m_float;
			stream >> m_int;
		}
	}

	Example(float fl, int i) :
		Serialisable(1),
		m_float(fl), m_int(i)
	{}

	void Serialise(std::ostream& stream) const override
	{
		Serialisable::Serialise(stream);

		stream << m_float << Delimiter;
		stream << m_int << Delimiter;
	}

private:
	float m_float;
	int m_int;
};
*/
