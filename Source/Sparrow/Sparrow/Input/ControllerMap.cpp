#include "ControllerMap.h"

namespace Sparrow
{
	namespace Input
	{
		ControllerMap LoadMap(const char* json)
		{
			//TODO
			return ControllerMap();
		}

		bool AllActionsMapped(const ControllerMap& map, std::vector<Action>& unmappedActions)
		{
			for (uint32_t actionIdx = 0; actionIdx < static_cast<uint32_t>(Action::MAX); actionIdx++)
			{
				Action action = static_cast<Action>(actionIdx);
				if (map.find(action) == map.end())
				{
					unmappedActions.push_back(action);
				}
			}

			return unmappedActions.size() == 0;
		}
	}
}