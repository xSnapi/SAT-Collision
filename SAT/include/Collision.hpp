#pragma once

#include "Collider.hpp"

constexpr float INF = std::numeric_limits<float>::infinity();

class Collision {
public:
	static Collision Instance;

	bool SATCollision(const Collider& body, const Collider& other, sf::Vector2f& MTV);

	bool SATCollision(const CircleCollider& body, const Collider& other, sf::Vector2f& MTV);
	bool SATCollision(const Collider& body, const CircleCollider& other, sf::Vector2f& MTV);

	bool SATCollision(const CircleCollider& body, const CircleCollider& other, sf::Vector2f& MTV);

private:
	Collision();
	~Collision();

	sf::Vector2f CircleAxis(sf::Vector2f* vertices, uint32_t count, sf::Vector2f center);

	sf::Vector2f PerpendicularAxis(sf::Vector2f* vertices, uint32_t index, uint32_t count) const;

	sf::Vector2f ProjectOnto(sf::Vector2f* vertices, uint32_t count, sf::Vector2f axis) const;
	sf::Vector2f ProjectCircle(sf::Vector2f circleCenter, float radius, sf::Vector2f axis) const;

	sf::Vector2f GetCenter(const Collider& body) const;

	float Overlap(sf::Vector2f v0, sf::Vector2f v1) const;
};