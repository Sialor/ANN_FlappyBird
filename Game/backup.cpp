//#include <iostream>
//#include <SFML/System.hpp>
//#include <SFML/Graphics.hpp>
//#include <math.h>
//
//using namespace std;
//
//class Vector2
//{
//private:
//	int __x;
//	int __y;
//public:
//	__declspec(property(get = get__X, put = set__X)) int x;
//	__declspec(property(get = get__Y, put = set__Y)) int y;
//
//	Vector2(int _x, int _y)
//	{
//		__x = _x;
//		__y = _y;
//	}
//
//	Vector2()
//	{
//		__x = 0;
//		__y = 0;
//	}
//
//	~Vector2()
//	{
//
//	}
//
//	void set__X(int _x = 0)
//	{
//		__x = _x;
//	}
//
//	int get__X()
//	{
//		return __x;
//	}
//
//	void set__Y(int _y = 0)
//	{
//		__y = _y;
//	}
//
//	int get__Y()
//	{
//		return __y;
//	}
//
//	operator sf::Vector2f()
//	{
//		return sf::Vector2f(x, y);
//	}
//
//	Vector2 operator + (Vector2 _vector)
//	{
//		return Vector2(x + _vector.x, y + _vector.y);
//	}
//
//	Vector2 operator - (Vector2 _vector)
//	{
//		return Vector2(x - _vector.x, y - _vector.y);
//	}
//
//	Vector2 operator - (int _int)
//	{
//		return Vector2(x - _int, y - _int);
//	}
//
//	Vector2 operator * (Vector2 _vector)
//	{
//		return Vector2(x * _vector.x, y * _vector.y);
//	}
//
//	Vector2 operator * (int _int)
//	{
//		return Vector2(x * _int, y * _int);
//	}
//
//	Vector2 operator / (Vector2 _vector)
//	{
//		return Vector2(x / _vector.x, y / _vector.y);
//	}
//
//	Vector2 operator / (int _int)
//	{
//		return Vector2(x / _int, y / _int);
//	}
//};
//
//class Object
//{
//private:
//	Vector2 __pos;
//	Vector2 __size;
//
//public:
//	__declspec(property(get = getPos, put = setPos)) Vector2 pos;
//	__declspec(property(get = getSize, put = setSize)) Vector2 size;
//
//	Object(int _pos_x, int _pos_y, int _size_x, int _size_y)
//	{
//		__pos = Vector2(_pos_x, _pos_y);
//		__size = Vector2(_size_x, _size_y);
//	}
//
//	~Object()
//	{
//
//	}
//
//	void setPos(Vector2 _vector2)
//	{
//		__pos.x = _vector2.x;
//		__pos.y = _vector2.y;
//	}
//
//	Vector2 getPos()
//	{
//		return __pos;
//	}
//
//	void setSize(Vector2 _vector2)
//	{
//		__size.x = _vector2.x;
//		__size.y = _vector2.y;
//	}
//
//	Vector2 getSize()
//	{
//		return __size;
//	}
//};
//
//class Camera : public Object
//{
//public:
//	Camera(int _pos_x, int _pos_y) : Object(_pos_x, _pos_y, 0, 0)
//	{
//
//	}
//
//	~Camera()
//	{
//
//	}
//};
//
//class Instance : public Object
//{
//private:
//	bool enabled;
//	double weight_0[2][6];
//	double weight_1[6];
//	float gravity;
//	sf::Texture texture;
//	sf::Sprite sprite;
//public:
//	double sigmoid(double _x)
//	{
//		return 1 / (1 + exp(-_x));
//	}
//
//	int predict(int _data_00, int _data_01, double(*_weight_0)[6], double* _weight_1)
//	{
//		double data_1[6];
//
//		data_1[0] = sigmoid(_data_00 * _weight_0[0][0] + _data_01 * _weight_0[1][0]);
//		data_1[1] = sigmoid(_data_00 * _weight_0[0][1] + _data_01 * _weight_0[1][1]);
//		data_1[2] = sigmoid(_data_00 * _weight_0[0][2] + _data_01 * _weight_0[1][2]);
//		data_1[3] = sigmoid(_data_00 * _weight_0[0][3] + _data_01 * _weight_0[1][3]);
//		data_1[4] = sigmoid(_data_00 * _weight_0[0][4] + _data_01 * _weight_0[1][4]);
//		data_1[5] = sigmoid(_data_00 * _weight_0[0][5] + _data_01 * _weight_0[1][5]);
//
//		double sum = 0;
//
//		for (int i = 0; i < 6; i++)
//		{
//			data_1[i] = _data_00 * _weight_0[0][i] + _data_01 * _weight_0[1][i];
//		}
//
//		if (sigmoid(data_1[0] * _weight_1[0] + data_1[1] * _weight_1[1] + data_1[2] * _weight_1[2] + data_1[3] * _weight_1[3] + data_1[4] * _weight_1[4] + data_1[5] * _weight_1[5]) > 0.5f)
//		{
//			return 1;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//
//
//	Instance(int _pos_x, int _pos_y, int _size_x, int _size_y) : Object(_pos_x, _pos_y, _size_x, _size_y)
//	{
//		for (int i = 0; i < 2; i++)
//		{
//			for (int j = 0; j < 6; j++)
//			{
//				weight_0[i][j] = 1.f / (rand() % 512);
//			}
//		}
//
//		for (int i = 0; i < 6; i++)
//		{
//			weight_1[i] = 1.f / (rand() % 512);
//		}
//
//		gravity = 1;
//
//		if (!texture.loadFromFile("resources/instance.png"))
//		{
//			texture.create(64, 64);
//		}
//
//		texture.setSmooth(true);
//
//		sprite.setTexture(texture);
//		sprite.setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
//	}
//
//	~Instance()
//	{
//
//	}
//
//	int update()
//	{
//		if (enabled)
//		{
//			if (predict(pos.x - gm.blocks[gm.indexTarget]->pos.x, pos.y - gm.blocks[gm.indexTarget]->pos.y + 32, weight_0, weight_1))
//			{
//				gravity = -2.f; // gravity = -2;
//			}
//
//			pos += Vector2(1, (int)gravity);
//			gravity += 0.05f; // gravity += 0.05
//
//			if (pos.y + size.y / 2 >= 768)
//			{
//				activate(false);
//
//				return 1;
//			}
//			else
//				if (pos.y - size.y / 2 <= 0)
//				{
//					activate(false);
//
//					return 1;
//				}
//				else
//					if ((pos.x + size.x / 2 >= gm.blocks[gm.indexTarget]->pos.x) || (pos.x - size.x / 2 <= gm.blocks[gm.indexTarget]->pos.x + gm.blocks[gm.indexTarget]->size.x && pos.x - size.x / 2 >= gm.blocks[gm.indexTarget]->pos.x))
//					{
//						if (pos.y - size.y / 2 <= gm.blocks[gm.indexTarget]->pos.y || pos.y + size.y / 2 - gm.blocks[gm.indexTarget]->heightEmptyTarget / 2 >= gm.blocks[gm.indexTarget]->pos.y + gm.blocks[gm.indexTarget]->heightEmptyTarget / 2)
//						{
//							activate(false);
//
//							return 1;
//						}
//					}
//		}
//
//		return 0;
//	}
//
//	void move(bool direction)
//	{
//		pos -= Vector2(0, (direction - 0.5) * 2) * 8;
//	}
//
//	void render(sf::RenderWindow* _canvas, Camera _cam)
//	{
//		sprite.setPosition((sf::Vector2f)(pos + _cam.pos - size / 2));
//		_canvas->draw(sprite);
//
//		//sprite.setPosition((sf::Vector2f)(pos - size / 2));
//		//_canvas->draw(sprite);
//
//		//sf::CircleShape shape(1.f);
//		//shape.setOutlineThickness(2.f);
//		//shape.setFillColor(sf::Color(255, 255, 255, 0));
//
//		//shape.setOutlineColor(sf::Color(127, 127, 255));
//
//
//		//shape.setPosition((sf::Vector2f)(pos - 3));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + size - 3));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(0, 1) * size - 3));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(1, 0) * size - 3));
//		//_canvas->draw(shape);
//
//
//		//shape.setOutlineColor(sf::Color(255, 127, 127));
//
//
//		//shape.setPosition((sf::Vector2f)(pos - size / 2 - 3));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + size / 2 - 3));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(-1, 1) * size / 2 - 3));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(1, -1) * size / 2 - 3));
//		//_canvas->draw(shape);
//	}
//
//	void activate(bool _enable)
//	{
//		enabled = _enable;
//	}
//
//	void train()
//	{
//		pos = Vector2(512, 384);
//		gravity = 0.f;
//	}
//};
//
//class Block : public Object
//{
//private:
//	int __heightEmptyTarget;
//	sf::Texture texture;
//	sf::Sprite sprite;
//public:
//	__declspec(property(get = getHeightEmptyTarget, put = setHeightEmptyTarget)) int heightEmptyTarget;
//
//	Block(int _pos_x, int _pos_y, int _size_x, int _size_y, int _heightEmptyTarget) : Object(_pos_x, _pos_y, _size_x, _size_y)
//	{
//		heightEmptyTarget = _heightEmptyTarget;
//
//		if (!texture.loadFromFile("resources/block.png"))
//		{
//			texture.create(64, 768);
//		}
//
//		texture.setSmooth(true);
//
//		sprite.setTexture(texture);
//	}
//
//	~Block()
//	{
//
//	}
//
//	void update()
//	{
//		pos -= Vector2(1, 0);
//	}
//
//	void render(sf::RenderWindow* _canvas, Camera _cam)
//	{
//		sprite.setPosition((sf::Vector2f)(pos + _cam.pos - Vector2(0, 768 + heightEmptyTarget / 2)));
//		sprite.setRotation(0);
//		_canvas->draw(sprite);
//
//		sprite.move(size.x, 768 * 2 + heightEmptyTarget);
//		sprite.setRotation(180);
//		_canvas->draw(sprite);
//
//		//sprite.setPosition((sf::Vector2f)(pos - Vector2(0, 768 + heightEmptyTarget / 2)));
//		//sprite.setRotation(0);
//		//_canvas->draw(sprite);
//
//		//sprite.move(size.x, 768 * 2 + heightEmptyTarget);
//		//sprite.setRotation(180);
//		//_canvas->draw(sprite);
//
//		//sf::CircleShape shape(1.f);
//		//shape.setOutlineThickness(2.f);
//		//shape.setFillColor(sf::Color(255, 255, 255, 0));
//
//
//		//shape.setOutlineColor(sf::Color(255, 127, 127));
//
//
//		//shape.setPosition((sf::Vector2f)(pos - Vector2(0, heightEmptyTarget / 2)));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(0, heightEmptyTarget / 2)));
//		//_canvas->draw(shape);
//
//
//		//shape.setPosition((sf::Vector2f)(pos - Vector2(-size.x, heightEmptyTarget / 2)));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(size.x, heightEmptyTarget / 2)));
//		//_canvas->draw(shape);
//
//
//		//shape.setOutlineColor(sf::Color(127, 127, 255));
//
//
//		//shape.setPosition((sf::Vector2f)(pos - Vector2(0, 768)));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(size.x, 768)));
//		//_canvas->draw(shape);
//
//
//		//shape.setPosition((sf::Vector2f)(pos - Vector2(0, -768)));
//		//_canvas->draw(shape);
//
//		//shape.setPosition((sf::Vector2f)(pos + Vector2(size.x, 768)));
//		//_canvas->draw(shape);
//	}
//
//	void setHeightEmptyTarget(int _heightEmptyTarget)
//	{
//		__heightEmptyTarget = _heightEmptyTarget;
//	}
//
//	int getHeightEmptyTarget()
//	{
//		return __heightEmptyTarget;
//	}
//};
//
//class GameManager
//{
//public:
//	int countBlocks;
//	int countInstances;
//	int countActives;
//	int indexTarget;
//
//	//GameManager* pointer;
//
//	Instance* instances[10];
//	Block* blocks[10];
//
//	GameManager()
//	{
//		countBlocks = 0;
//		countInstances = 0;
//		countActives = 0;
//		indexTarget = 0;
//	}
//
//	void blocksAdd(int _pos_x, int _pos_y, int _size_x, int _size_y, int _heightEmptyTarget)
//	{
//		blocks[countBlocks] = new Block(_pos_x, _pos_y, _size_x, _size_y, _heightEmptyTarget);
//		countBlocks++;
//	}
//
//	void blocksRemove()
//	{
//		delete blocks[countBlocks - 1];
//		countBlocks--;
//	}
//
//	void blocksRemove(short _indexBlocks)
//	{
//		delete blocks[_indexBlocks];
//	}
//
//	void instancesAdd(int _pos_x, int _pos_y, int _size_x, int _size_y)
//	{
//		instances[countInstances] = new Instance(_pos_x, _pos_y, _size_x, _size_y);
//		countInstances++;
//		countActives++;
//	}
//
//	void instancesRemove()
//	{
//		delete instances[countInstances - 1];
//		countInstances--;
//	}
//
//	void instancesRemove(short _indexInstances)
//	{
//		delete instances[_indexInstances];
//	}
//};
//
//int width = 1024, height = 768;
//
//int frequency = 200;
//int countFramesForFrequency = 400;
//
//sf::RenderWindow window(sf::VideoMode(width, height, 32U), "AI Learning", sf::Style::Close);
//
//unsigned long int fps = 0;
//
//GameManager gm;
//Camera cam(width / 2, height / 2);
//
//sf::Texture backgroundTexture;
//sf::Sprite backgroundSprite;
//
//void preSettings()
//{
//	//srand(time(0));
//
//	//window.setVerticalSyncEnabled(true);
//	window.setFramerateLimit(250);
//	window.setPosition(sf::Vector2i(1920, 0));
//
//	backgroundTexture.loadFromFile("resources/background.png");
//	backgroundTexture.setSmooth(true);
//	backgroundSprite.setTexture(backgroundTexture);
//}
//
//int main()
//{
//	preSettings();
//
//	for (int i = 0; i < 1; i++)
//	{
//		gm.instancesAdd(width / 2, height / 2, 64, 32);
//	}
//
//	sf::Clock clock;
//
//	while (window.isOpen())
//	{
//		if (clock.getElapsedTime().asMicroseconds() - 1000000 >= 0)
//		{
//			if (system("CLS"))
//			{
//				system("clear");
//			}
//
//			cout << fps << endl;
//			fps = 0;
//			clock.restart();
//		}
//
//		sf::Event event;
//
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				window.close();
//				break;
//			case sf::Event::KeyPressed:
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//				{
//					gm.instances[0]->move(1);
//				}
//				else
//					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//					{
//						gm.instances[0]->move(0);
//					}
//			default:
//				break;
//			}
//		}
//
//		if (gm.countActives)
//		{
//			window.draw(backgroundSprite);
//
//			if (countFramesForFrequency == 400)
//			{
//				gm.blocksAdd(width, rand() % 768, 64, 768, 128);
//				countFramesForFrequency = 0;
//			}
//
//			for (int i = 0; i < gm.countBlocks; i++)
//			{
//				gm.blocks[i]->update();
//				gm.blocks[i]->render(&window, cam);
//			}
//
//			if (gm.blocks[gm.indexTarget] != NULL)
//			{
//				if (gm.blocks[0]->pos.x + gm.blocks[0]->size.x <= 0)
//				{
//					gm.indexTarget--;
//
//					delete gm.blocks[0];
//
//					for (int i = 1; i < gm.countBlocks; i++)
//					{
//						gm.blocks[i - 1] = gm.blocks[i];
//					}
//
//					gm.countBlocks--;
//				}
//
//				if (gm.blocks[gm.indexTarget]->pos.x + gm.blocks[gm.indexTarget]->size.x < 512)
//				{
//					gm.indexTarget++;
//				}
//			}
//
//			for (int i = 0; i < gm.countInstances; i++)
//			{
//				if (gm.instances[i]->update())
//				{
//					gm.countActives--;
//				}
//
//				gm.instances[i]->render(&window, cam);
//			}
//
//			cam.pos += Vector2(0, 0);
//
//			window.display();
//			fps++;
//			countFramesForFrequency++;
//		}
//		else
//		{
//			while (gm.countBlocks != 0)
//			{
//				gm.blocksRemove();
//			}
//
//			for (int i = 0; i < gm.countInstances; i++)
//			{
//				gm.instances[i]->activate(true);
//				gm.instances[i]->train();
//			}
//
//			countFramesForFrequency = 400;
//			gm.countActives = gm.countInstances;
//		}
//	}
//
//	for (int i = 0; i < gm.countInstances; i++)
//	{
//		gm.instancesRemove();
//	}
//
//	for (int i = 0; i < gm.countBlocks; i++)
//	{
//		gm.blocksRemove();
//	}
//
//	return 0;
//}