#pragma once
#include "AssetManager.h"
#include "Input_Wrapper.h"

extern "C" {
	DLLEXPORT bool SaveController(const MarshalledController& controller);
}