#pragma once
#include <cstdint>

#include "Core/Callback.h"

namespace Sparrow
{
	namespace Input
	{
		class ControllerElement
		{
		public:
			ControllerElement(uint32_t id, float activationThreshold, const char* name);
			ControllerElement(const char* json);

			void Update(float value);

			bool IsActive() const { return m_Value > m_ActivationThreshold; }
			bool WasActiveLastFrame() const { return m_ActiveLastFrame; }
			bool BecameActiveThisFrame() const { return !WasActiveLastFrame() && IsActive(); }
			float Value() const { return m_Value; }

			const char* GetJSON() const;
		public:
			Callback<void, uint32_t /*ElementID*/> OnActivate;
			Callback<void, uint32_t /*ElementID*/> OnDeactivate;
		private:
			//Configuration values
			uint32_t m_ElementID;
			float m_ActivationThreshold;
			const char* m_Name;
			//TODO: Image m_Glyph;

			float m_Value;
			bool m_ActiveLastFrame;
		};
	}
}