#pragma once

#include "Action.h"
#include "Serialisable.h"

#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class ActionMap : public Serialisation::Serialisable
		{
		public:
			ActionMap(std::istream& stream);
			
			void Serialise(std::ostream& stream) const override;
			uint16_t LatestVersion() const override { return 1; }

			bool ActionInMap(Action action) const;

		private:
			std::vector<Action> m_Actions;

		public:
			bool Enabled = true;
		};
	}
}