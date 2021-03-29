#pragma once

#include "Action.h"
#include "ActionMap.h"
#include "Controller.h"

#include <memory>
#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class Manager
		{
		public:
			Manager();

			bool GetAction(Action action) const;
			bool GetActionUp(Action action) const;
			bool GetActionDown(Action action) const;

			void Update();

			std::shared_ptr<Controller> CurrentController() const { return m_Controllers[m_CurrentControllerIndex]; }
		private:
			bool IsActionEnabled(Action action) const;

		private:
			std::vector<ActionMap> m_ActionMaps;
			std::vector<std::shared_ptr<Controller>> m_Controllers;
			uint32_t m_CurrentControllerIndex = 0;
		};
	}
}