#include "ControllerMap.h"

namespace Sparrow
{
	namespace Input
	{
		ControllerMap::ControllerMap() :
			Serialisable(LatestVersion())
		{ }

		ControllerMap::ControllerMap(std::istream& stream) :
			Serialisable(stream)
		{
			if (m_Version == 1)
			{
				size_t numElements;
				stream >> numElements;

				for (size_t idx = 0; idx < numElements; idx++)
				{
					uint32_t action;
					uint32_t element;
					stream >> action;
					stream >> element;

					m_Map.emplace(static_cast<Action>(action), element);
				}
			}
			else
			{
				throw std::exception("Unknown version " + m_Version);
			}
		}

		void ControllerMap::Serialise(std::ostream& stream) const
		{
			Serialisable::Serialise(stream);

			stream << m_Map.size();

			for (auto const& val : m_Map)
			{
				stream << static_cast<uint32_t>(val.first) << Delimiter;
				stream << val.second << Delimiter;
			}
		}

		bool ControllerMap::AllActionsMapped(std::vector<Action>& unmappedActions)
		{
			for (uint32_t actionIdx = 0; actionIdx < static_cast<uint32_t>(Action::MAX); actionIdx++)
			{
				Action action = static_cast<Action>(actionIdx);
				if (m_Map.find(action) == m_Map.end())
				{
					unmappedActions.push_back(action);
				}
			}

			return unmappedActions.size() == 0;
		}
	}
}