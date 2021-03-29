#pragma once

#include "Action.h"

#include <map>
#include <vector>

namespace Sparrow
{
	namespace Input
	{
		typedef std::map<Action, uint32_t> ControllerMap;

		ControllerMap LoadMap(const char* json);
		bool AllActionsMapped(const ControllerMap& map, std::vector<Action>& unmappedActions);
	}
}