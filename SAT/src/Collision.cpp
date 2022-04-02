#include "stpch.h"
#include "Collision.hpp"

Collision Collision::Instance;

bool Collision::SATCollision(const Collider& body, const Collider& other, sf::Vector2f& MTV) {
	float minOverlap = INF;

	auto& bodyV  = body.m_vertices;
	auto& otherV = other.m_vertices;

	const uint32_t countB = body.m_verticesCount;
	const uint32_t countO = other.m_verticesCount;

	const uint32_t all = countB + countO;

	sf::Vector2f* axis = new sf::Vector2f[all];

	for (uint32_t i = 0; i < countB; i++)
		axis[i] = PerpendicularAxis(bodyV, i, countB);

	for (uint32_t i = countB; i < all; i++)
		axis[i] = PerpendicularAxis(otherV, i - countB, countO);

	for (uint32_t i = 0; i < all; i++) {
		auto& a = axis[i];

		sf::Vector2f bodyProjection  = ProjectOnto(bodyV, countB, a);
		sf::Vector2f otherProjection = ProjectOnto(otherV, countO, a);

		float overlap = Overlap(bodyProjection, otherProjection);

		if (overlap == 0.0f) {
			delete[] axis;

			MTV = sf::Vector2f(0.0f, 0.0f);

			return false;
		}
		else {
			if (overlap < minOverlap) {
				minOverlap = overlap;
				MTV = a * overlap;
			}
		}
	}

	if (DotProduct(GetCenter(body) - GetCenter(other), MTV) < 0.0f)
		MTV *= -1.0f;

	delete[] axis;
	return true;
}

bool Collision::SATCollision(const CircleCollider& body, const Collider& other, sf::Vector2f& MTV) {
	float minOverlap = INF;

	auto& vert = other.m_vertices;

	uint32_t count = other.m_verticesCount;
	uint32_t all   = count + 1;

	sf::Vector2f center = body.GetPosition();

	sf::Vector2f* axis = new sf::Vector2f[all];

	for (uint32_t i = 0; i < count; i++)
		axis[i] = PerpendicularAxis(vert, i, count);

	axis[count] = CircleAxis(vert, count, center);

	for (uint32_t i = 0; i < all;  i++) {
		auto& a = axis[i];

		sf::Vector2f circleProjection = ProjectCircle(center, body.GetRadius(), a);
		sf::Vector2f otherProjection  = ProjectOnto(vert, count, a);

		float overlap = Overlap(circleProjection, otherProjection);

		if (overlap == 0.0f) {
			delete[] axis;

			MTV = sf::Vector2f(0.0f, 0.0f);

			return false;
		}
		else {
			if (overlap < minOverlap) {
				minOverlap = overlap;
				MTV = a * overlap;
			}
		}
	}

	if (DotProduct(center - GetCenter(other), MTV) < 0.0f)
		MTV *= -1.0f;

	delete[] axis;
	return true;
}

bool Collision::SATCollision(const Collider& body, const CircleCollider& other, sf::Vector2f& MTV) {
	bool temp = SATCollision(other, body, MTV);
	MTV *= -1.0f;

	return temp;
}

bool Collision::SATCollision(const CircleCollider& body, const CircleCollider& other, sf::Vector2f& MTV) {
	sf::Vector2f diff(body.GetPosition() - other.GetPosition());

	float length = Length(diff);
	float sum	 = body.GetRadius() + other.GetRadius();

	if (length >= sum) 
		return false;

	sum -= length;

	diff = Normalize(diff);

	MTV = diff * sum;

	return true;
}

sf::Vector2f Collision::GetCenter(const Collider& body) const {
	sf::Vector2f center;

	uint32_t count = body.m_verticesCount;

	float A = 0.0f;

	float area = 0.0f;

	for (uint32_t i = 0; i < count; i++) {
		auto& v0 = body.m_vertices[i];
		auto& v1 = body.m_vertices[i + 1 != count ? i + 1 : 0];

		float b = v0.x * v1.y - v1.x * v0.y;

		A += b;

		center += (v0 + v1) * b;
	}

	center *= 1.0f / (3.0f * A);

	return center;
}

sf::Vector2f Collision::CircleAxis(sf::Vector2f* vertices, uint32_t count, sf::Vector2f circleCenter) {
	sf::Vector2f axis;

	uint32_t index = 0;
	float	 dist  = INF;

	for (uint32_t i = 0; i < count; i++) {
		auto& v = vertices[i];

		float d = Distance(v, circleCenter);

		if (d >= dist)
			continue;

		dist  = d;
		index = i;
	}

	return Normalize(circleCenter - vertices[index]);
}

sf::Vector2f Collision::PerpendicularAxis(sf::Vector2f* vertices, uint32_t index, uint32_t count) const {
	uint32_t i0 = index + 1;
	uint32_t i1 = index;

	if (i0 == count) {
		i0 = 0;
		i1 = count - 1;
	}

	sf::Vector2f v = Normalize(vertices[i0] - vertices[i1]);

	return
	{
		-v.y,
		 v.x
	};
}

sf::Vector2f Collision::ProjectOnto(sf::Vector2f* vertices, uint32_t count, sf::Vector2f axis) const {
	float min =  INF;
	float max = -INF;

	for (uint32_t i = 0; i < count; i++) {
		float projection = DotProduct(vertices[i], axis);

		if (projection < min)
			min = projection;

		if (projection > max)
			max = projection;
	}

	return
	{
		min,
		max
	};
}

sf::Vector2f Collision::ProjectCircle(sf::Vector2f center, float radius, sf::Vector2f axis) const {
	sf::Vector2f dir = radius * axis;

	sf::Vector2f p1 = center + dir;
	sf::Vector2f p2 = center - dir;

	float min = DotProduct(p1, axis);
	float max = DotProduct(p2, axis);

	if (min > max)
		std::swap(min, max);

	return
	{
		min,
		max
	};
}

float Collision::Overlap(sf::Vector2f v0, sf::Vector2f v1) const {
	return !(v0.x <= v1.y && v0.y >= v1.x) ? 0.0f : std::min(v0.y, v1.y) - std::max(v0.x, v1.x);
}

Collision::Collision() {

}

Collision::~Collision() {

}