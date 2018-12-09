#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

class Block : public Object
{
private:
	int __heightEmptyTarget;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	__declspec(property(get = getHeightEmptyTarget, put = setHeightEmptyTarget)) int heightEmptyTarget;

	Block(int, int, int, int, int);

	void render(sf::RenderWindow &, Object &);

	void setHeightEmptyTarget(int);

	int getHeightEmptyTarget();
};