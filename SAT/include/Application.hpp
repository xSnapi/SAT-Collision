#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Collider.hpp"
#include "Collision.hpp"

class Application {
public:
	Application();
	~Application();

	void Run();

	static Application* Instance;
	static float		DT;

	sf::RenderWindow Window;
	sf::Event		 Event;

private:
	//BoxCollider m_boxCollider;
	BoxCollider m_boxCollider2;
	CircleCollider m_circleCollider;
	//CircleCollider m_circleCollider2;

	CustomCollider c;
	//CustomCollider c2;

	sf::Clock m_dtClock;

	void Update();
	void Render();

	void HandleEvents();

	void InitWindow();
};
