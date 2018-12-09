#include "Object.h"

#include <SFML/System.hpp>

using namespace sf;

Object::Object(int _pos_x, int _pos_y, int _size_x, int _size_y)
{
	__pos = Vector2i(_pos_x, _pos_y);
	__size = Vector2i(_size_x, _size_y);
}

void Object::setPos(Vector2i _Vector2i)
{
	__pos.x = _Vector2i.x;
	__pos.y = _Vector2i.y;
}

void Object::setSize(Vector2i _Vector2i)
{
	__size.x = _Vector2i.x;
	__size.y = _Vector2i.y;
}

Vector2i Object::getPos()
{
	return __pos;
}

Vector2i Object::getSize()
{
	return __size;
}