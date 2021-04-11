#include "Input.h"

#include <assert.h>

namespace Sparrow
{
	namespace Input
	{

		Manager::Manager() :
			m_ActionMaps(), m_Controllers(), m_CurrentControllerIndex(0)
		{
			LoadAllControllerConfigs();
			CheckConnectedControllers();
		}

		void Manager::CheckConnectedControllers()
		{
			//TODO
		}

		void Manager::LoadAllControllerConfigs()
		{
			Serialisation::AssetLoadedEvent<ControllerConfig> onLoaded = [&](bool success, Serialisation::AssetReference<ControllerConfig> config)
			{
				if (success)
				{
					m_ControllerConfigs.push_back(config);
				}
			};

			const String configPath = Sparrow::String("Input/Controllers/");
			std::vector<String> paths = Serialisation::AssetManager::GetFiles(Serialisation::AssetClass::Config, configPath);
			m_ControllerConfigsFound = static_cast<uint8_t>(paths.size());

			for (const String& path : paths)
			{
				Serialisation::AssetManager::Load(Serialisation::AssetClass::Config, path, onLoaded);
			}
		}

		bool Manager::GetAction(Action action) const
		{
			if (IsActionEnabled(action))
			{
				return CurrentController()->GetAction(action);
			}

			return false;
		}

		bool Manager::GetActionDown(Action action) const
		{
			if (IsActionEnabled(action))
			{
				return CurrentController()->GetActionDown(action);
			}

			return false;
		}
		
		bool Manager::GetActionUp(Action action) const
		{
			if (IsActionEnabled(action))
			{
				return CurrentController()->GetActionUp(action);
			}

			return false;
		}

		bool Manager::IsActionEnabled(Action action) const
		{
			for (const ActionMap& map : m_ActionMaps)
			{
				if (map.ActionInMap(action))
				{
					return map.Enabled;
				}
			}

			assert(false); //Action not in any map
			return false;
		}

		void Manager::Update()
		{
			for (const std::shared_ptr<Controller>& controller : m_Controllers)
			{
				controller->Update();
			}
		}
	}
}