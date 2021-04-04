#include "Controller.h"

namespace Sparrow
{
	namespace Input
	{
		Controller::Controller(ControllerConfig config) :
			m_Config(config)
		{ }

		bool Controller::GetAction(Action action) const
		{
			return m_Config.GetElements()[m_Config.GetMap().GetElement(action)].IsActive();
		}

		bool Controller::GetActionUp(Action action) const
		{
			const ControllerElement& element = m_Config.GetElements()[m_Config.GetMap().GetElement(action)];
			return element.WasActiveLastFrame() && !element.IsActive();
		}

		bool Controller::GetActionDown(Action action) const
		{
			return m_Config.GetElements()[m_Config.GetMap().GetElement(action)].BecameActiveThisFrame();
		}

		float Controller::GetValue(Action action) const
		{
			return m_Config.GetElements()[m_Config.GetMap().GetElement(action)].Value();
		}
	}
}