#include "stpch.h"
#include "Application.hpp"

Application* Application::Instance = nullptr;
float		 Application::DT	   = 0.0f;

const float& dt = Application::DT;

Application::Application() {
	InitWindow();
	m_circleCollider.Create(100.0f);

	//m_boxCollider.Create(sf::Vector2f(100.0f, 100.0f));
	//m_boxCollider.SetPosition(sf::Vector2f(400.0f, 400.0f));
	//m_boxCollider.SetOrigin(sf::Vector2f(50.0f, 50.0f));
	//m_boxCollider.SetRotation(sf::degrees(45.0f));

	m_circleCollider.SetPosition(sf::Vector2f(100.0f, 100.0f));
	//m_circleCollider.SetOrigin(sf::Vector2f(20.0f, 20.0f));

	m_boxCollider2.Create(sf::Vector2f(200.0f, 200.0f));
	m_boxCollider2.SetPosition(sf::Vector2f(600.0f, 400.0f));
	m_boxCollider2.SetOrigin(sf::Vector2f(50.0f, 50.0f));
	//m_boxCollider2.SetRotation(sf::degrees(5.0f));

	/*m_circleCollider2.Create(100.0f);
	m_circleCollider2.SetPosition(sf::Vector2f(400.0f, 500.0f));
	*/
	c.Create(6);

	c[0] = sf::Vector2f(100.0f,  0.0f);
	c[1] = sf::Vector2f(200.0f,  0.0f);
	c[2] = sf::Vector2f(260.0f,  60.0f);
	c[3] = sf::Vector2f(160.0f,  120.0f);
	c[4] = sf::Vector2f(80.0f,  120.0f);
	c[5] = sf::Vector2f(0.0f,   50.0f);

	c.SetPosition(sf::Vector2f(400.0f, 400.0f));
	/*
	c2.Create(6);

	c2[0] = sf::Vector2f(100.0f, 0.0f);
	c2[1] = sf::Vector2f(200.0f, 0.0f);
	c2[2] = sf::Vector2f(260.0f, 60.0f);
	c2[3] = sf::Vector2f(160.0f, 120.0f);
	c2[4] = sf::Vector2f(80.0f, 120.0f);
	c2[5] = sf::Vector2f(0.0f, 50.0f);

	c2.SetPosition(sf::Vector2f(400.0f, 400.0f));

	c.SetOrigin(sf::Vector2f(100.0f, 60.0f));*/
}

Application::~Application() {

}

void Application::Run() {
	m_dtClock.restart();

	while (Window.isOpen()) {
		HandleEvents();
		Update();

		Window.clear(sf::Color(13, 17, 31));
		Render();
		Window.display();

		DT = m_dtClock.restart().asSeconds();
	}
}

void Application::Update() {
	sf::Vector2f mousePos(MousePos(Window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_boxCollider2.Rotate(sf::degrees(100.0f * dt));

	m_circleCollider.SetPosition(mousePos);

	sf::Vector2f MTV;
	if (Collision::Instance.SATCollision(m_circleCollider, c, MTV))
		m_circleCollider.Move(MTV);
		//m_circleCollider.Move(MTV);
}

void Application::Render() {
	//Window.draw(m_boxCollider2);
	Window.draw(m_circleCollider);
	//Window.draw(m_circleCollider2);
	Window.draw(c);
}

void Application::HandleEvents() {
	while (Window.pollEvent(Event)) {
		switch (Event.type) {
		case sf::Event::Closed:
			Window.close();
		}
	}
}

void Application::InitWindow() {
	sf::VideoMode mode;
	mode.width  = WINDOW_WIDTH;
	mode.height = WINDOW_HEIGHT;

	sf::ContextSettings settings;

	Window.create(mode, "SAT Collision", sf::Style::Close, settings);
	Window.setFramerateLimit(144);
}
