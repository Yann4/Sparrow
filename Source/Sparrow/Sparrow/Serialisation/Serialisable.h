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

/*
* Example of a serialisable class
* #include "Serialisation/Serialisable.h"

class Example : public Sparrow::Serialisation::Serialisable
{
public:
	Example(uint16_t version, std::istream& stream) :
		Serialisable(version, stream)
	{
		if (version == 1)
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
