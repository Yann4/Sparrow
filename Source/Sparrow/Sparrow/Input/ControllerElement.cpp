#include "ControllerElement.h"
#include <iostream>

namespace Sparrow
{
	namespace Input
	{
		ControllerElement::ControllerElement(uint32_t id, float activationThreshold, const char* name) :
			m_ElementID(id), m_ActivationThreshold(activationThreshold), m_Name(name), 
			m_Value(0.0f), m_ActiveLastFrame(false)
		{ }

		ControllerElement::ControllerElement(const char* json) : m_Value(0.0f), m_ActiveLastFrame(false)
		{
			//TODO
		}

		void ControllerElement::Update(float value)
		{
			m_ActiveLastFrame = IsActive();
			m_Value = value;

			if (BecameActiveThisFrame())
			{
				OnActivate.Invoke(m_ElementID);
			}

			if (!IsActive() && WasActiveLastFrame())
			{
				OnDeactivate.Invoke(m_ElementID);
			}
		}

		const char* ControllerElement::GetJSON() const 
		{
			//TODO
			return nullptr;
		}
	}
}