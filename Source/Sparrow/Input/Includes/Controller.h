#pragma once

#include "ControllerElement.h"
#include "ControllerMap.h"
#include "Action.h"

#include "Serialisable.h"

#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class Controller : public Serialisation::Serialisable
		{
		public:
			Controller(std::istream& stream);

			void Serialise(std::ostream& stream) const override;

			//Must be overridden per controller type & update the per-frame state of all of the elements
			virtual void Update() = 0;

			bool GetAction(Action action) const;
			bool GetActionUp(Action action) const;
			bool GetActionDown(Action action) const;
			float GetValue(Action action) const;

		protected:
			uint16_t LatestVersion() const override { return 1; }
		protected:
			ControllerMap m_ControllerMap;
			std::vector<ControllerElement> m_Elements;
		};
	}
}