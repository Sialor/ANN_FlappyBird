#pragma once

#include "Object.h"
#include "Block.h"

#include <SFML/Graphics.hpp>

#include "Object.h"

class Instance : public Object
{
private:
	bool enabled;

	float gravity;

	sf::Texture texture;
	sf::Sprite sprite;
public:
	double	weight_0[2][6],
			weight_1[6];

	Instance(int, int, int, int);

	double sigmoid(double _x);

	int predict(int, int, double(*_weight_0)[6], double*);
	int update(Block &);

	void render(sf::RenderWindow &, Object &);
	void estrus(Instance* &);
	void train();
};