#include "pch.h"

std::shared_ptr<Sparrow::Input::ControllerConfig> GetController(const MarshalledController& marshalledController)
{
	std::vector<Sparrow::Input::ControllerElement> elements;
	elements.reserve(marshalledController.ElementCount);

	for (uint32_t idx = 0; idx < marshalledController.ElementCount; idx++)
	{
		const MarshalledElement& element = marshalledController.ControllerElements[idx];
		elements.emplace(elements.begin() + idx, element.ID, element.ActivationThreshold, element.Name);
	}

	std::shared_ptr<Sparrow::Input::ControllerConfig> controller = std::make_shared<Sparrow::Input::ControllerConfig>(marshalledController.Name,
		Sparrow::Input::ControllerMap(marshalledController.ActionElementCount, marshalledController.Actions, marshalledController.Elements), elements);

	return controller;
}
