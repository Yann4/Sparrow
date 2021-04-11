#include "pch.h"

#include "ControllerConfig.h"

std::vector<MarshalledController> m_LoadedControllers;

bool SaveController(const MarshalledController& marshalledController)
{
	std::shared_ptr<Input::ControllerConfig> controller = GetController(marshalledController);

	String path = String("Input/Controllers/");
	path += controller->GetName();

	return Serialisation::AssetManager::Save(Serialisation::AssetClass::Config, path, controller);
}

void LoadAllControllers()
{
	m_LoadedControllers.clear();

	const String configPath = String("Input/Controllers/");

	for (const std::shared_ptr<Input::ControllerConfig>& config : LoadAllSynchronous<Input::ControllerConfig>(Serialisation::AssetClass::Config, configPath))
	{
		m_LoadedControllers.push_back(GetMarshalledController(config));
	}
}

MarshalledController GetController(uint32_t index)
{
	return m_LoadedControllers[index];
}

uint32_t GetControllerCount()
{
	return static_cast<uint32_t>(m_LoadedControllers.size());
}
