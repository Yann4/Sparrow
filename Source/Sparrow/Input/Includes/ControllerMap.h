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
			ControllerMap(uint32_t numPairs, const uint32_t actions[256], const uint32_t elements[256]);
			ControllerMap(std::istream& stream);
			void Serialise(std::ostream& stream) const override;

			bool AllActionsMapped(std::vector<Action>& unmappedActions);


			bool Contains(const Action& action) const { return m_Map.find(action) != m_Map.end(); }
			uint32_t GetElement(const Action& action) const { return m_Map.at(action); }
			uint32_t Size() const { return static_cast<uint32_t>(m_Map.size()); }

		protected:
			uint16_t LatestVersion() const override { return 1; }
		private:
			std::map<Action, uint32_t> m_Map;
		};
	}
}