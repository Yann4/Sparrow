#pragma once

#include "Action.h"
#include "Serialisable.h"

#include <map>
#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class ControllerMap : public Serialisation::Serialisable
		{
		public:
			ControllerMap();
			ControllerMap(std::istream& stream);
			void Serialise(std::ostream& stream) const override;

			bool AllActionsMapped(std::vector<Action>& unmappedActions);
			
			uint32_t GetElement(const Action& action) const { return m_Map.at(action); }
		protected:
			uint16_t LatestVersion() const override { return 1; }
		private:
			std::map<Action, uint32_t> m_Map;
		};
	}
}