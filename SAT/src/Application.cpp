#include "stpch.h"
#include "Application.hpp"

Application* Application::Instance = nullptr;
float		 Application::DT = 0.0f;

const float& dt = Application::DT;

Application::Application() {
	InitWindow();

	CreateColliders();
}

Application::~Application() {
	for (auto& c : m_Colliders)
		delete c;
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

void Application::CheckCollision() {
	for (auto& c : m_Colliders) {
		sf::Vector2f MTV;
		Collision::Instance.SATCollision(m_box, *c, MTV);

		m_box.Move(MTV);
	}
}

void Application::UpdateBox() {
	constexpr float smoothness = 16.0f;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_box.Rotate(sf::degrees(100.0f * dt));

	sf::Vector2f start = m_box.GetPosition();
	sf::Vector2f end   = MousePos(Window);
	sf::Vector2f pos   = Lerp(start, end, smoothness * dt);

	m_box.SetPosition(pos);
}

void Application::Update() {
	UpdateBox();
	CheckCollision();
}

void Application::Render() {
	for (auto& c : m_Colliders)
		Window.draw(*c);

	Window.draw(m_box);
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
	mode.width = WINDOW_WIDTH;
	mode.height = WINDOW_HEIGHT;

	sf::ContextSettings settings;

	Window.create(mode, "SAT Collision", sf::Style::Close, settings);
	Window.setFramerateLimit(144);
}

void Application::CreateColliders() {
	{
		m_box.Create(sf::Vector2f(100.0f, 100.0f));
		m_box.SetOrigin(sf::Vector2f(50.0f, 50.0f));
		m_box.SetPosition(MousePos(Window));
	}

	{
		CircleCollider* c = new CircleCollider();

		c->Create(100.0f);

		c->SetPosition(sf::Vector2f(220.0f, 220.0f));

		m_Colliders.push_back(c);
	}

	{
		CircleCollider* c = new CircleCollider();

		c->Create(50.0f);

		c->SetPosition(sf::Vector2f(920.0f, 150.0f));

		m_Colliders.push_back(c);
	}

	{
		BoxCollider* c = new BoxCollider();

		c->Create(sf::Vector2f(200.0f, 200.0f));

		c->SetPosition(sf::Vector2f(650.0f, 330.0f));

		c->SetRotation(sf::degrees(45.0f));

		m_Colliders.push_back(c);
	}

	{
		BoxCollider* c = new BoxCollider();

		c->Create(sf::Vector2f(300.0f, 200.0f));

		c->SetPosition(sf::Vector2f(120.0f, 560.0f));

		c->SetRotation(sf::degrees(25.0f));

		m_Colliders.push_back(c);
	}

	{

		CustomCollider* c = new CustomCollider(3);

		c->GetVertices(0) = sf::Vector2f(0.0f, 0.0f);
		c->GetVertices(1) = sf::Vector2f(200.0f, 200.0f);
		c->GetVertices(2) = sf::Vector2f(200.0f, 0.0f);

		c->SetPosition(sf::Vector2f(1230.0f, 80.0f));

		c->SetRotation(sf::degrees(15.0f));

		m_Colliders.push_back(c);
	}

	{

		CustomCollider* c = new CustomCollider(6);

		c->GetVertices(0) = sf::Vector2f(100.0f, 0.0f  );
		c->GetVertices(1) = sf::Vector2f(200.0f, 0.0f  );
		c->GetVertices(2) = sf::Vector2f(260.0f, 60.0f );
		c->GetVertices(3) = sf::Vector2f(160.0f, 120.0f);
		c->GetVertices(4) = sf::Vector2f(80.0f , 120.0f);
		c->GetVertices(5) = sf::Vector2f(0.0f  , 50.0f );

		c->SetPosition(sf::Vector2f(1340.0f, 450.0f));

		c->SetRotation(sf::degrees(15.0f));

		m_Colliders.push_back(c);
	}

	{

		CustomCollider* c = new CustomCollider(4);

		c->GetVertices(0) = sf::Vector2f(0.0f  ,  0.0f	);
		c->GetVertices(1) = sf::Vector2f(200.0f,  200.0f);
		c->GetVertices(2) = sf::Vector2f(200.0f,  0.0f	);
		c->GetVertices(3) = sf::Vector2f(0.0f  , -200.0f);

		c->SetPosition(sf::Vector2f(950.0f, 600.0f));

		c->SetRotation(sf::degrees(75.0f));

		m_Colliders.push_back(c);
	}
}
