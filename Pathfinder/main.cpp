#include <iostream>
#include "source/AStar.hpp"
#include <chrono>
#include <thread>

int main()
{
	AStar::Generator generator;
	int width = 40;
	int height = 20;
	generator.setWorldSize({ width,height });

	for (int x = 10; x < 32; x++)
	{
		generator.addCollision({ x,15 });
	}
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(true);
	std::cout << "Generate path ... \n";
	AStar::Vec2i start;
	AStar::Vec2i end;
	std::cout << "Insert Start Coordinate X: ";
	int x;
	int y;
	std::cin >> x;
	std::cout << "Insert Start Coordinate Y: ";
	std::cin >> y;
	start = { x,y };
	std::cout << "Insert End Coordinate X: ";
	std::cin >> x;
	std::cout << "Insert End Coordinate Y: ";
	std::cin >> y;
	end = { x,y };
	auto path = generator.findPath(start, end);
	char** map = new char*[height];
	for (size_t i = 0; i < height; i++)
	{
		char* temp = new char[width];
		for (size_t j = 0; j < width; j++)
		{
			temp[j] = '-';
		}
		map[i] = temp;
	}
	for (auto i:path)
	{
		map[i.y][i.x] = '+';
	}
	for (int x = 10; x < 32; x++)
	{
		map[15][x] = 'O';
	}
	for (auto i = path.rbegin(); i < path.rend(); i++)
	{
		system("cls");
		map[i->y][i->x] = 'X';
		for (size_t y = 0; y < height; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				std::cout << map[y][x];
			}
			std::cout << std::endl;
		}
		map[i->y][i->x] = '+';
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
}