#include "Controller.h"

namespace Sparrow
{
	namespace Input
	{
		Controller::Controller(const char* json) :
			m_ControllerMap()
		{ }

		bool Controller::GetAction(Action action) const
		{
			return m_Elements[m_ControllerMap.at(action)].IsActive();
		}

		bool Controller::GetActionUp(Action action) const
		{
			const ControllerElement& element = m_Elements[m_ControllerMap.at(action)];
			return element.WasActiveLastFrame() && !element.IsActive();
		}

		bool Controller::GetActionDown(Action action) const
		{
			return m_Elements[m_ControllerMap.at(action)].BecameActiveThisFrame();
		}

		float Controller::GetValue(Action action) const
		{
			return m_Elements[m_ControllerMap.at(action)].Value();
		}
	}
}