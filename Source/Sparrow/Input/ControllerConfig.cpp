#include "ControllerConfig.h"

namespace Sparrow
{
	namespace Input
	{
		ControllerConfig::ControllerConfig(const String& name, const ControllerMap& map, const std::vector<ControllerElement>& elements) :
			Serialisable(LatestVersion()),
			m_Name(name), m_Map(map), m_Elements(elements)
		{ }

		ControllerConfig::ControllerConfig(std::istream& stream) :
			Serialisable(stream)
		{
			if (m_Version == 1)
			{
				stream >> m_Name;

				m_Map = ControllerMap(stream);

				size_t numElements;
				stream >> numElements;
				m_Elements.reserve(numElements);

				for (size_t idx = 0; idx < numElements; idx++)
				{
					m_Elements[idx] = ControllerElement(stream);
				}
			}
			else
			{
				throw std::exception("Unknown version " + m_Version);
			}
		}

		void ControllerConfig::Serialise(std::ostream& stream) const
		{
			Serialisable::Serialise(stream);
			stream << m_Name << Delimiter;

			m_Map.Serialise(stream);

			stream << m_Elements.size();
			for (const ControllerElement& element : m_Elements)
			{
				element.Serialise(stream);
			}
		}
	}
}