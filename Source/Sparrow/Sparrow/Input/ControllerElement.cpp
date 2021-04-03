#include "ControllerElement.h"
#include <iostream>

namespace Sparrow
{
	namespace Input
	{
		ControllerElement::ControllerElement(uint32_t id, float activationThreshold, const char* name) :
			Serialisation::Serialisable(LatestVersion()),
			m_ElementID(id), m_ActivationThreshold(activationThreshold), m_Name(name), 
			m_Value(0.0f), m_ActiveLastFrame(false)
		{ }

		ControllerElement::ControllerElement(uint16_t version, std::istream& stream) :
			Serialisation::Serialisable(version),
			m_Value(0.0f), m_ActiveLastFrame(false)
		{
			if (version == 1)
			{
				stream >> m_Name;
				stream >> m_ElementID;
				stream >> m_ActivationThreshold;
			}
			else
			{
				throw std::exception("Unexpected serialisation version " + version);
			}
		}

		void ControllerElement::Serialise(std::ostream& stream) const
		{
			stream << m_Name << Delimiter;
			stream << m_ElementID << Delimiter;
			stream << m_ActivationThreshold << Delimiter;
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
	}
}