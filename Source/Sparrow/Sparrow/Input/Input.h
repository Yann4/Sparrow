#pragma once

#include "InputAction.h"

namespace Sparrow
{
	namespace Input
	{
		bool GetAction(InputAction action);
		bool GetActionUp(InputAction action);
		bool GetActionDown(InputAction action);

		void Update();
	}
}