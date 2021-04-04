#pragma once

#include "ControllerElement.h"
#include "ControllerMap.h"
#include "Action.h"
#include "ControllerConfig.h"

#include "Serialisable.h"

#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class Controller
		{
		public:
			Controller(ControllerConfig config);

			//Must be overridden per controller type & update the per-frame state of all of the elements
			virtual void Update() = 0;

			bool GetAction(Action action) const;
			bool GetActionUp(Action action) const;
			bool GetActionDown(Action action) const;
			float GetValue(Action action) const;

		private:
			ControllerConfig m_Config;
		};
	}
}