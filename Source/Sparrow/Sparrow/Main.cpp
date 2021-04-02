#include "Main.h"
#include "Rendering/GLRenderer.h"

#include <memory>
#include <iostream>
#include <functional>

#include "Serialisation/AssetManager.h"
#include "Serialisation/Serialisable.h"
#include "Core/Utilities/Hash.h"

class Test : public Sparrow::Serialisation::Serialisable
{
public:
	Test(uint16_t version, std::istream& stream) :
		Serialisable(version, stream)
	{
		if (version == 1)
		{
			stream >> m_float;
			stream >> m_int;
		}
	}

	Test(float fl, int i) :
		Serialisable(1),
		m_float(fl), m_int(i)
	{}

	void Serialise(std::ostream& stream) const override
	{
		Serialisable::Serialise(stream);

		stream << m_float << Delimiter;
		stream << m_int << Delimiter;
	}

private:
	float m_float;
	int m_int;
};

int main(int argc, char** argv)
{
	Test test(0.1f, 1);

	const char* testPath = "test";
	Sparrow::Serialisation::AssetManager::Save(Sparrow::Serialisation::AssetClass::Config, testPath, test);

	Sparrow::Serialisation::AssetLoadedEvent<Test> loaded = [](bool success, Sparrow::Serialisation::AssetReference<Test> asset)
	{
		if (success)
		{
			std::cout << "yay";
		}
	};

	Sparrow::Serialisation::AssetManager::Load(Sparrow::Serialisation::AssetClass::Config, testPath, loaded);

	std::unique_ptr<Sparrow::Rendering::Renderer> renderer = std::make_unique<Sparrow::Rendering::GLRenderer>(800, 600, "Sparrow");

	while (!renderer->GetWindow()->ShouldClose())
	{
		renderer->Update();
	}

	return 0;
}