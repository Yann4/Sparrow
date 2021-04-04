#include "pch.h"

#include "Input.h"

bool SaveController(const MarshalledController& marshalledController)
{
	std::shared_ptr<Sparrow::Input::ControllerConfig> controller = GetController(marshalledController);

	Sparrow::String path = Sparrow::Input::Manager::ConfigPath();
	path += controller->GetName();
	path += Sparrow::Input::Manager::ControllerConfigExtension();

	return Sparrow::Serialisation::AssetManager::Save(Sparrow::Serialisation::AssetClass::Config, path.c_str(), *controller);
}
