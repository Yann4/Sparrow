#include "ActionMap.h"

namespace Sparrow
{
	namespace Input
	{
		ActionMap::ActionMap(const char* json) :
			m_Actions()
		{ }

		bool ActionMap::ActionInMap(Action action) const 
		{
			return std::find(m_Actions.begin(), m_Actions.end(), action) != m_Actions.end();
		}
	}
}