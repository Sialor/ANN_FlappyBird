#pragma once

#include <SFML/System.hpp>

class Object
{
private:
	sf::Vector2i __pos;
	sf::Vector2i __size;

public:
	__declspec(property(get = getPos, put = setPos)) sf::Vector2i pos;
	__declspec(property(get = getSize, put = setSize)) sf::Vector2i size;

	Object(int, int, int, int);

	void setPos(sf::Vector2i);
	void setSize(sf::Vector2i);

	sf::Vector2i getPos();
	sf::Vector2i getSize();
};