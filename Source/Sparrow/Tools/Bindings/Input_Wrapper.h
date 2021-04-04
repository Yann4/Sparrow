#pragma once
#include "ControllerElement.h"
#include "ControllerConfig.h"

DLLEXPORT constexpr uint32_t GetControllerLimit() { return 128; }

struct MarshalledElement
{
public:
	uint32_t ID;
	float ActivationThreshold;
	const char* Name;
};

struct MarshalledController
{
public:
	char* Name;

	uint32_t ElementCount;
	MarshalledElement ControllerElements[GetControllerLimit()];

	uint32_t ActionElementCount;
	uint32_t Actions[GetControllerLimit()];
	uint32_t Elements[GetControllerLimit()];
};

std::shared_ptr<Sparrow::Input::ControllerConfig> GetController(const MarshalledController& marshalledController);