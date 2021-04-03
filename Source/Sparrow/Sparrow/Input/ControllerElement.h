#pragma once
#include <cstdint>
#include <string>

#include "Core/Utilities/Callback.h"
#include "Serialisation/Serialisable.h"

namespace Sparrow
{
	namespace Input
	{
		class ControllerElement : public Serialisation::Serialisable
		{
		public:
			ControllerElement(uint32_t id, float activationThreshold, const char* name);
			ControllerElement(uint16_t version, std::istream& stream);

			void Update(float value);

			bool IsActive() const { return m_Value > m_ActivationThreshold; }
			bool WasActiveLastFrame() const { return m_ActiveLastFrame; }
			bool BecameActiveThisFrame() const { return !WasActiveLastFrame() && IsActive(); }
			float Value() const { return m_Value; }

			void Serialise(std::ostream& stream) const override;

		protected:
			uint16_t LatestVersion() const override { return 1; }
		public:
			Callback<void, uint32_t /*ElementID*/> OnActivate;
			Callback<void, uint32_t /*ElementID*/> OnDeactivate;
		private:
			//Configuration values
			uint32_t m_ElementID;
			float m_ActivationThreshold;
			std::string m_Name;
			//TODO: Image m_Glyph;

			float m_Value;
			bool m_ActiveLastFrame;
		};
	}
}