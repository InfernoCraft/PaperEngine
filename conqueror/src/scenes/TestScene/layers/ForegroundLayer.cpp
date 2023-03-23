#include "_Game.h"
#include "ForegroundLayer.h"


void ForegroundLayer::OnAttach()
{
	character1 = new GameObject("character1", Transform(glm::vec2(3.0f, 3.0f), glm::vec2(2.0f, 2.0f)));
	character2 = new GameObject("character2", Transform(glm::vec2(0.0f, 3.0f), glm::vec2(2.0f, -1.0f), 115.0f));
	object1 = new GameObject("object1", Transform(glm::vec2(-3, 3), glm::vec2(2.0f, 2.0f)));

	// nobody cares about the transform for lines
	// TODO: annoy pascal that his code sucks
	// ps: mine isn't any better
	lineObject1 = new GameObject("lineObject1", Transform(glm::vec2(0.0, 1.0f), glm::vec2(5.0f, 2.0f)));
	lineObject2 = new GameObject("lineObje23432ct1", Transform(glm::vec2(3.0, 3.0f), glm::vec2(0.0f, 3.0f)));

	character1->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("james_webb.png"), SpriteRenderer::RECTANGLE));
	character2->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("placeholder_texture_256x256.png"), SpriteRenderer::TRIANGLE));
	object1->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("antimarx.png"), SpriteRenderer::RECTANGLE));
	lineObject1->AddComponent(new LineRenderer(glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 3.0f), glm::vec4(1.0f, 1.0f, 0.324f, 1.0f), 0.6f));
	lineObject2->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), SpriteRenderer::LINE, 1.0f));

	this->AddGameObjectToLayer(character1);
	this->AddGameObjectToLayer(character2);
	this->AddGameObjectToLayer(object1);
	this->AddGameObjectToLayer(lineObject1);
	this->AddGameObjectToLayer(lineObject2);
}

void ForegroundLayer::OnDetach()
{
}

void ForegroundLayer::Update(const float dt)
{
	static bool con = true;
	if (Input::IsKeyPressed(KEY_Y) && con && false)
	{
		con = false;
		character2->Stop();
	}
	if (Input::IsKeyPressed(KEY_T) && !con && false)
	{
		con = true;
	}
	gameObjects[0]->transform.rotation -= 150 * dt;
}

void ForegroundLayer::Imgui(const float dt)
{
}

void ForegroundLayer::OnEvent(Event& event)
{
}