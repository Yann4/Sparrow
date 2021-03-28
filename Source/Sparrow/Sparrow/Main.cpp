#include "Main.h"
#include "Rendering/GLRenderer.h"

#include <memory>
int main(int argc, char** argv)
{
	std::unique_ptr<Sparrow::Rendering::Renderer> renderer = std::make_unique<Sparrow::Rendering::GLRenderer>(800, 600, "Sparrow");

	while (!renderer->GetWindow()->ShouldClose())
	{
		renderer->Update();
	}

	return 0;
}