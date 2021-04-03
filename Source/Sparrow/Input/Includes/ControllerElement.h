#pragma once
#include <cstdint>
#include <string>

#include "Utilities/Callback.h"
#include "Serialisable.h"

namespace Sparrow
{
	namespace Input
	{
		class ControllerElement : public Serialisation::Serialisable
		{
		public:
			ControllerElement(uint32_t id, float activationThreshold, const char* name);
			ControllerElement(std::istream& stream);
			void Serialise(std::ostream& stream) const override;

			void Update(float value);

			bool IsActive() const { return m_Value > m_ActivationThreshold; }
			bool WasActiveLastFrame() const { return m_ActiveLastFrame; }
			bool BecameActiveThisFrame() const { return !WasActiveLastFrame() && IsActive(); }
			float Value() const { return m_Value; }


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