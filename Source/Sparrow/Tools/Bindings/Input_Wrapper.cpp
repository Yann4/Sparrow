#include "pch.h"

std::shared_ptr<Input::ControllerConfig> GetController(const MarshalledController& marshalledController)
{
	std::vector<Input::ControllerElement> elements;
	elements.reserve(marshalledController.ElementCount);

	for (uint32_t idx = 0; idx < marshalledController.ElementCount; idx++)
	{
		const MarshalledElement& element = marshalledController.ControllerElements[idx];
		elements.emplace(elements.begin() + idx, element.ID, element.ActivationThreshold, element.Name);
	}

	std::shared_ptr<Input::ControllerConfig> controller = std::make_shared<Input::ControllerConfig>(marshalledController.Name,
		Input::ControllerMap(marshalledController.ActionElementCount, marshalledController.Actions, marshalledController.Elements), elements);

	return controller;
}

MarshalledController GetMarshalledController(std::shared_ptr<Input::ControllerConfig> Controller)
{
	MarshalledController marshalled;
	strncpy_s(marshalled.Name, sizeof(marshalled.Name), Controller->GetName().c_str(), Controller->GetName().Length());

	marshalled.ElementCount = static_cast<uint32_t>(Controller->GetElements().size());
	for (unsigned int idx = 0; idx < marshalled.ElementCount; idx++)
	{
		marshalled.ControllerElements[idx] = Controller->GetElements()[idx];
	}

	const Input::ControllerMap& map = Controller->GetMap();
	marshalled.ActionElementCount = map.Size();
	
	int idx = 0;
	for (int act = 0; act < static_cast<int>(Input::Action::MAX); act++)
	{
		Input::Action action = static_cast<Input::Action>(act);
		if (map.Contains(action))
		{
			marshalled.Actions[idx] = idx;
			marshalled.Elements[idx] = map.GetElement(action);
			idx++;
		}
	}

	return marshalled;
}