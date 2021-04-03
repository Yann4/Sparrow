#include "Controller.h"

namespace Sparrow
{
	namespace Input
	{
		Controller::Controller(std::istream& stream) :
			Serialisable(stream)
		{
			if (m_Version == 1)
			{
				m_ControllerMap = ControllerMap(stream);

				size_t numElements;
				stream >> numElements;
				m_Elements.reserve(numElements);

				for (size_t idx = 0; idx < numElements; idx++)
				{
					m_Elements[idx] = ControllerElement(stream);
				}
			}
			else
			{
				throw std::exception("Unknown version " + m_Version);
			}
		}

		void Controller::Serialise(std::ostream& stream) const
		{
			Serialisable::Serialise(stream);
			m_ControllerMap.Serialise(stream);

			stream << m_Elements.size();
			for (const ControllerElement& element : m_Elements)
			{
				element.Serialise(stream);
			}
		}

		bool Controller::GetAction(Action action) const
		{
			return m_Elements[m_ControllerMap.GetElement(action)].IsActive();
		}

		bool Controller::GetActionUp(Action action) const
		{
			const ControllerElement& element = m_Elements[m_ControllerMap.GetElement(action)];
			return element.WasActiveLastFrame() && !element.IsActive();
		}

		bool Controller::GetActionDown(Action action) const
		{
			return m_Elements[m_ControllerMap.GetElement(action)].BecameActiveThisFrame();
		}

		float Controller::GetValue(Action action) const
		{
			return m_Elements[m_ControllerMap.GetElement(action)].Value();
		}
	}
}