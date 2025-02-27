#include <iostream>

#include "Instance.h"
#include "Object.h"

using namespace std;
using namespace sf;

// =============== Менеджер объектов ===============
int countBlocks = 0,
	countInstances = 0,
	countActives = 0,
	indexTarget = 0;

Instance	*instances[10],
			*bestInstance;

Block *blocks[10];

// Добавление блока
void blocksAdd(int _pos_x, int _pos_y, int _size_x, int _size_y, int _heightEmptyTarget)
{
	blocks[countBlocks] = new Block(_pos_x, _pos_y, _size_x, _size_y, _heightEmptyTarget);
	countBlocks++;
}

// Удаление блока
int blocksRemove()
{
	if (blocks[countBlocks - 1] != NULL)
	{
		delete blocks[countBlocks - 1];
		blocks[countBlocks - 1] = NULL;
		countBlocks--;

		return 0;
	}

	return 1;
}

// Добавление птицы
void instancesAdd(int _pos_x, int _pos_y, int _size_x, int _size_y)
{
	instances[countInstances] = new Instance(_pos_x, _pos_y, _size_x, _size_y);
	countInstances++;
	countActives++;
}

// Удаление птицы
int instancesRemove()
{
	if (instances[countInstances - 1] != NULL)
	{
		delete instances[countInstances - 1];
		instances[countInstances - 1] = NULL;
		countInstances--;

		return 0;
	}
	
	return 1;
}

// ===============    ===============

unsigned short countFramesForFrequency = 400;

unsigned char marker = 0;

double delta = 0.00399;


Object cam(0, 0, 0, 0);


RenderWindow window(VideoMode(1024, 768, 32U), "AI Learning", Style::Close);

Texture backgroundTexture;
Sprite backgroundSprite;

int main()
{
	srand(time(0));
	//window.setFramerateLimit(240);

	// Загрузка фона
	backgroundTexture.loadFromFile("resources/background.png");
	backgroundSprite.setTexture(backgroundTexture);

	// Создаем 10 экземпляров птиц
	for (int i = 0; i < 10; i++)
	{
		instancesAdd(0, 0, 64, 32);
	}

	// Определяем самого первого наилучшим
	bestInstance = instances[0];

	// Таймер для вывода в консоль
	Clock clock;

	while (window.isOpen())
	{
		// Вывод сообщений в консоль каждую секунду   1000000  = 1 sec
		if (clock.getElapsedTime().asMicroseconds() - 1000000 >= 0)
		{
			system("CLS");

			cout << "Number of active instances: " << countActives << '/' << countInstances << endl;

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					cout << bestInstance->weight_0[i][j] << "      " << bestInstance->weight_1[j] << endl;
				}

				cout << endl;
			}

			clock.restart();
		}

		// Обработка событий SFML
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// Если в поколении есть еще активные экземпляры, то цикл продолжается
		if (countActives)
		{
			// Рисуем фон
			window.draw(backgroundSprite);

			// Добавление нового блока в игровое пространство
			if (countFramesForFrequency == 400)
			{
				blocksAdd(cam.pos.x + 512, rand() % 512 - 256, 64, 768, 136);
				countFramesForFrequency = 0;
			}

			// Отрисовка блоков
			for (int i = 0; i < countBlocks; i++)
			{
				blocks[i]->render(window, cam);
			}

			// Если есть хотя бы один блок
			if (blocks[indexTarget] != NULL)
			{
				// Если крайний левый блок вышел за левую рамку экрана
				if (cam.pos.x - blocks[0]->pos.x - blocks[0]->size.x >= 512)
				{
					indexTarget--;

					for (int i = 1; i < countBlocks; i++)
					{
						if (blocks[i - 1])
						{
							delete blocks[i - 1];
							blocks[i - 1] = NULL;
						}

						blocks[i - 1] = new Block(blocks[i]->pos.x, blocks[i]->pos.y, blocks[i]->size.x, blocks[i]->size.y, 128);
					}

					if (blocksRemove())
					{
						window.close();
					}
				}

				// Если птица пролетела блок
				if (cam.pos.x - 32 >= blocks[indexTarget]->pos.x + blocks[indexTarget]->size.x)
				{
					indexTarget++;
				}
			}

			// Производим обновление состояния каждой птицы
			for (int i = 0; i < countInstances; i++)
			{
				if (instances[i]->update(*blocks[indexTarget]))
				{
					countActives--;
				}

				// Рисуем птицу
				instances[i]->render(window, cam);
			}

			// Движение камеры вправо
			cam.pos += Vector2i(1, 0);

			// Вывод буфера изобрадения на экран
			window.display();
			
			// Счетчик кадров для создания блока
			countFramesForFrequency++;
		}
		else
		{
			//Удаляем все блоки из памяти
			while (countBlocks != 0)
			{
				if (blocksRemove())
				{
					window.close();
				}
			}

			// Самый лучший default образец - нулевой
			bestInstance = instances[0];
		
			// Генерация силы изменения гена
			double a = rand() % 128 - 64;

			if (a == 0)
			{
				a += 0.001f;
			}

			delta = 1.f / (a);

			// Поиск наилучшего (тот кто преодолел больше всех) из всего списка испытуемых
			for (int i = 0; i < countInstances; i++)
			{
				if (instances[i]->pos.x > bestInstance->pos.x)
				{
					bestInstance = instances[i];
				}

				// Обновление всего состояния птицы, кроме нейронной сети
				instances[i]->train();
			}

			// Лучшая птица дает потомство в остальных собратьев. Передается память, гены
			for (int i = 0; i < countInstances; i++)
			{
				if (instances[i] == bestInstance)
				{
					continue;
				}

				bestInstance->estrus(instances[i]);
			}

			// Изменение случайного гена у второй птицы
			if (marker > 11)
			{
				instances[1]->weight_1[marker % 10] = 1.f / (rand() % 16 - 8);
			}
			else
			{
				instances[1]->weight_0[marker / 6][marker % 6] = 1.f / (rand() % 16 - 8);
			}

			// Изменение генов у остальных особей с зависимостью от i
			for (int i = 2; i < countInstances; i++)
			{
				if (marker > 11)
				{
					instances[i]->weight_1[marker % 6] += delta * (i - 1);
				}
				else
				{
					instances[i]->weight_0[marker / 6][marker % 6] += delta * (i - 1);
				}

				delta *= -1;
			}

			// Обнуление камеры
			cam.pos = Vector2i(0, 0);

			// Обработка маркера
			if (marker == 17)
			{
				marker = 0;
			}
			else
			{
				marker++;
			}

			// Возврат переменных к значениям по умолчанию
			countFramesForFrequency = 400;
			countActives = countInstances;
			indexTarget = 0;
		}
	}

	// Очищение памяти от птиц
	for (int i = 0; i < countInstances; i++)
	{
		if (instancesRemove())
		{
			window.close();
		}
	}

	// Очищение памяти от блоков
	for (int i = 0; i < countBlocks; i++)
	{
		if (blocksRemove())
		{
			window.close();
		}
	}

	return 0;
}