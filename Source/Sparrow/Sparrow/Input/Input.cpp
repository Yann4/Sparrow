#include "Input.h"

#include <assert.h>

namespace Sparrow
{
	namespace Input
	{
		Manager::Manager() :
			m_ActionMaps(), m_Controllers(), m_CurrentControllerIndex(0)
		{
			CheckConnectedControllers();
		}

		void Manager::CheckConnectedControllers()
		{
			//TODO
		}

		bool Manager::GetAction(Action action) const
		{
			if (IsActionEnabled(action))
			{
				return CurrentController()->GetAction(action);
			}

			return false;
		}

		bool Manager::GetActionDown(Action action) const
		{
			if (IsActionEnabled(action))
			{
				return CurrentController()->GetActionDown(action);
			}

			return false;
		}
		
		bool Manager::GetActionUp(Action action) const
		{
			if (IsActionEnabled(action))
			{
				return CurrentController()->GetActionUp(action);
			}

			return false;
		}

		bool Manager::IsActionEnabled(Action action) const
		{
			for (const ActionMap& map : m_ActionMaps)
			{
				if (map.ActionInMap(action))
				{
					return map.Enabled;
				}
			}

			assert(false); //Action not in any map
			return false;
		}

		void Manager::Update()
		{
			for (const std::shared_ptr<Controller>& controller : m_Controllers)
			{
				controller->Update();
			}
		}
	}
}