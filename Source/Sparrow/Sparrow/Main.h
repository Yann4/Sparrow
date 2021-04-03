#pragma once

#include "Rendering/Renderer.h"
#include "Input.h"

#include <memory>

namespace Sparrow
{
	class Application
	{
	public:
		Application();

		void Run();
	public:
		std::unique_ptr<Rendering::Renderer> Renderer;
		std::unique_ptr<Input::Manager> InputManager;
	};
}