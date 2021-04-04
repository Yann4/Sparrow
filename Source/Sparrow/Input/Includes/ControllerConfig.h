#pragma once

#include "SparrowString.h"
#include "Serialisable.h"
#include "ControllerMap.h"
#include "ControllerElement.h"

#include <vector>

namespace Sparrow
{
	namespace Input
	{
		class ControllerConfig : public Serialisation::Serialisable
		{
		public:
			ControllerConfig(const String& name, const ControllerMap& map, const std::vector<ControllerElement>& elements);
			ControllerConfig(std::istream& stream);
			void Serialise(std::ostream& stream) const override;

			const String& GetName() const { return m_Name; }
			const ControllerMap& GetMap() const { return m_Map; }
			const std::vector<ControllerElement>& GetElements() const { return m_Elements; }

		protected:
			uint16_t LatestVersion() const override { return 1; }
		private:
			String m_Name;
			ControllerMap m_Map;
			std::vector<ControllerElement> m_Elements;
		};
	}
}