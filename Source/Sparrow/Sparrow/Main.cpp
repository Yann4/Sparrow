#include "Main.h"
#include "Rendering/GLRenderer.h"

int main(int argc, char** argv)
{
	Sparrow::Application app;

	app.Run();

	return 0;
}

namespace Sparrow
{
	Application::Application() :
		Renderer(std::make_unique<Rendering::GLRenderer>(800, 600, "Sparrow")),
		InputManager(std::make_unique<Input::Manager>())
	{ }

	void Application::Run()
	{
		while (!Renderer->GetWindow()->ShouldClose())
		{
			InputManager->Update();

			Renderer->Update();
		}
	}
}