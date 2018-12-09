#include "Instance.h"

#include <SFML/Graphics.hpp>

using namespace sf;

Instance::Instance(int _pos_x, int _pos_y, int _size_x, int _size_y) : Object(_pos_x, _pos_y, _size_x, _size_y)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			weight_0[i][j] = 1.f / (rand() % 512 - 256);
			//weight_0[i][j] = 0.f; // Забивка мозгов нулями
		}
	}

	for (int i = 0; i < 6; i++)
	{
		weight_1[i] = 1.f / (rand() % 512 - 256);
		//weight_1[i] = 0.f; // Забивка мозгов нулями
	}

	gravity = 0;

	if (!texture.loadFromFile("resources/instance.png"))
	{
		texture.create(64, 64);
	}

	texture.setSmooth(true);

	sprite.setTexture(texture);
	sprite.setColor(Color(rand() % 256, rand() % 256, rand() % 256, 255));
}

double Instance::sigmoid(double _x)
{
	return 1 / (1 + exp(-_x));
}

int Instance::predict(int _data_00, int _data_01, double(*_weight_0)[6], double* _weight_1)
{
	double data_1[6];

	for (int i = 0; i < 6; i++)
	{
		data_1[i] = sigmoid(_data_00 * _weight_0[0][i] + _data_01 * _weight_0[1][i]);
	}

	double sum = 0;

	for (int i = 0; i < 6; i++)
	{
		data_1[i] = _data_00 * _weight_0[0][i] + _data_01 * _weight_0[1][i];
	}

	return sigmoid(	data_1[0] * _weight_1[0] + 
					data_1[1] * _weight_1[1] + 
					data_1[2] * _weight_1[2] + 
					data_1[3] * _weight_1[3] + 
					data_1[4] * _weight_1[4] + 
					data_1[5] * _weight_1[5] ) > 0.5f;
}

int Instance::update(Block &_target)
{
	if (enabled)
	{
		if (predict(pos.x - _target.pos.x, pos.y - _target.pos.y, weight_0, weight_1))
		{
			gravity = -2.f;
		}

		pos += Vector2i(1, (int)gravity);
		gravity += 0.05f;

		if (pos.y + size.y / 2 >= 384)
		{
			enabled = false;

			return 1;
		}
		else
			if (pos.x + size.x / 2 > _target.pos.x && pos.x < _target.pos.x ||
				pos.x - size.x / 2 < _target.pos.x + _target.size.x && pos.x > _target.pos.x + _target.size.x)
			{
				if (pos.y + size.y / 2 >= _target.pos.y + _target.heightEmptyTarget / 2 ||
					pos.y - size.y / 2 <= _target.pos.y - _target.heightEmptyTarget / 2)
				{
					enabled = false;

					return 1;
				}
			}
	}

	return 0;
}

void Instance::render(RenderWindow &_canvas, Object &_cam)
{
	sprite.setPosition((Vector2f)(pos - _cam.pos - size / 2 + Vector2i(512, 384)));
	_canvas.draw(sprite);
}

void Instance::estrus(Instance* &_male)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_male->weight_0[i][j] = weight_0[i][j];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		_male->weight_1[i] = weight_1[i];
	}
}

void Instance::train()
{
	enabled = true;
	pos = Vector2i(0, 0);
	gravity = 0.f;
}