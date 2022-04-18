#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector2.hpp"

#include <functional>

class Collision;

class Collider : public sf::Drawable {
public:
	Collider(uint32_t count);
	virtual ~Collider();

	// Modifiers
	void SetPosition(sf::Vector2f position);
	void SetOrigin	(sf::Vector2f origin);
	void SetRotation(sf::Angle angle);
	void Move		(sf::Vector2f offset);
	void Rotate		(sf::Angle angle);

	// Accessors
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetOrigin()   const;
	sf::Angle	 GetRotation() const;

	std::function<void()> Trigger;

protected:
	sf::Vector2f  m_position;
	sf::Vector2f  m_origin;
	sf::Angle	  m_rotation;

	sf::Vector2f* m_vertices;
	uint32_t	  m_verticesCount = 0;

private:
	friend class Collision;
};

class BoxCollider : public Collider {
public:
	BoxCollider();
	~BoxCollider();

	void Create(sf::Vector2f size);

private:
	sf::Vector2f m_size;

	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
};

class CircleCollider : public Collider {
public:
	CircleCollider();
	~CircleCollider();

	void Create(float radius);

	float GetRadius() const;

private:
	float m_radius = 0.0f;

	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
};

class CustomCollider : public Collider {
public:
	CustomCollider();

	CustomCollider(uint32_t count);

	~CustomCollider();

	sf::Vector2f* GetVertices();
	sf::Vector2f& GetVertices(uint32_t index);

	void Create(uint32_t count);

	sf::Vector2f& operator[](uint32_t index);

private:
	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
};
