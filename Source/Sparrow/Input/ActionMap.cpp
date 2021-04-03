#include "ActionMap.h"

namespace Sparrow
{
	namespace Input
	{
		ActionMap::ActionMap(std::istream& stream) :
			Serialisable(stream)
		{
			if (m_Version == 1)
			{
				size_t numActions;
				stream >> numActions;

				m_Actions.reserve(numActions);
				for (size_t idx = 0; idx < numActions; idx++)
				{
					uint32_t action;
					stream >> action;
					m_Actions[idx] = static_cast<Action>(action);
				}
			}
			else
			{
				throw std::exception("Unknown version " + m_Version);
			}
		}

		void ActionMap::Serialise(std::ostream& stream) const
		{
			Serialisable::Serialise(stream);

			stream << m_Actions.size() << Delimiter;
			for (const Action& action : m_Actions)
			{
				stream << static_cast<uint32_t>(action) << Delimiter;
			}
		}

		bool ActionMap::ActionInMap(Action action) const 
		{
			return std::find(m_Actions.begin(), m_Actions.end(), action) != m_Actions.end();
		}
	}
}