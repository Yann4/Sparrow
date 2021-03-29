#pragma once

#include "Action.h"

#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class ActionMap
		{
		public:
			ActionMap(const char* json);

			bool ActionInMap(Action action) const;
		public:
			bool Enabled = true;

		private:
			std::vector<Action> m_Actions;
		};
	}
}