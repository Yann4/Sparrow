#pragma once

#include "Action.h"

namespace Sparrow
{
	namespace Input
	{
		bool GetAction(Action action);
		bool GetActionUp(Action action);
		bool GetActionDown(Action action);

		void Update();
	}
}