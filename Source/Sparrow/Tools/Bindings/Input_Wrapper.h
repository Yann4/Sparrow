#pragma once
#include "ControllerElement.h"
#include "ControllerConfig.h"

using namespace Sparrow;

extern "C"
{
	DLLEXPORT constexpr uint32_t GetControllerLimit() { return 64; }
}

struct MarshalledElement
{
public:
	MarshalledElement() :
		ID(0), ActivationThreshold(0.0f), Name()
	{ }

	MarshalledElement(const Input::ControllerElement& other) :
		ID(other.ElementID()), ActivationThreshold(other.ActivationThreshold())
	{
		strncpy_s(Name, sizeof(Name), other.Name().c_str(), other.Name().Length());
	}

public:
	uint32_t ID;
	float ActivationThreshold;
	char Name[64];
};

struct MarshalledController
{
public:
	char Name[64];

	uint32_t ElementCount;
	MarshalledElement ControllerElements[GetControllerLimit()];

	uint32_t ActionElementCount;
	uint32_t Actions[GetControllerLimit()];
	uint32_t Elements[GetControllerLimit()];
};

std::shared_ptr<Input::ControllerConfig> GetController(const MarshalledController& marshalledController);
MarshalledController GetMarshalledController(std::shared_ptr<Input::ControllerConfig> Controller);