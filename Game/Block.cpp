#include "Block.h"

#include <SFML/Graphics.hpp>

Block::Block(int _pos_x, int _pos_y, int _size_x, int _size_y, int _heightEmptyTarget) : Object(_pos_x, _pos_y, _size_x, _size_y)
{
	heightEmptyTarget = _heightEmptyTarget;

	if (!texture.loadFromFile("resources/block.png"))
	{
		texture.create(64, 768);
	}

	texture.setSmooth(true);

	sprite.setTexture(texture);
}

void Block::render(sf::RenderWindow &_canvas, Object &_cam)
{
	sprite.setPosition((sf::Vector2f)(pos - _cam.pos - sf::Vector2i(0, 768 + heightEmptyTarget / 2) + sf::Vector2i(512, 384)));
	sprite.setRotation(0);
	_canvas.draw(sprite);

	sprite.move(size.x, 768 * 2 + heightEmptyTarget);
	sprite.setRotation(180);
	_canvas.draw(sprite);
}

void Block::setHeightEmptyTarget(int _heightEmptyTarget)
{
	__heightEmptyTarget = _heightEmptyTarget;
}

int Block::getHeightEmptyTarget()
{
	return __heightEmptyTarget;
}