#pragma once

constexpr float PI = 3.14159265f;

template <typename T>
inline float DotProduct(sf::Vector2<T> v0, sf::Vector2<T> v1) {
	return v0.x * v1.x + v0.y * v1.y;
}

template <typename T>
inline float Distance(sf::Vector2<T> v0, sf::Vector2<T> v1) {
	return sqrtf((v0 - v1).x * (v0 - v1).x + (v0 - v1).y * (v0 - v1).y);
}

template <typename T>
inline float Length(sf::Vector2<T> v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

template <typename T>
static sf::Vector2<T> Normalize(sf::Vector2<T> v) {
	float length = Length(v);

	return length ? v / length : sf::Vector2<T>();
}

template <typename T>
static sf::Vector2<T> Rotate(sf::Vector2<T> point, sf::Vector2<T> center, sf::Angle angle) {
	float r = angle.asRadians();

	return sf::Vector2<T>
	{
		cosf(r)* (point.x - center.x) - sinf(r) * (point.y - center.y) + center.x,
		sinf(r)* (point.x - center.x) + cosf(r) * (point.y - center.y) + center.y
	};
}

template <typename T>
inline sf::Vector2<T> VecAbs(sf::Vector2<T> v) {
	return sf::Vector2f
	{
		v.x < 0.0f ? -v.x : v.x,
		v.y < 0.0f ? -v.y : v.y
	};
}


inline sf::Vector2f MousePos(const sf::RenderWindow& window = *(sf::RenderWindow*)nullptr) {
	return !&window ? (sf::Vector2f)sf::Mouse::getPosition() : window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

#ifdef DEBUG
	template<typename ...T>
	void Print(T&&... args) {
		(std::cout << ... << args);
	}

	#define LOG(...) Print(__VA_ARGS__)

#else

	#define LOG(...)

#endif
