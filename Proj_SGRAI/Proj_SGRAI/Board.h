#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include "globalHeader.h"
#include "image_loader.h"
#include <vector>
#include <functional>
#include <set>



namespace AStar
{
	struct Vec2i
	{
		int x, y;
		bool operator == (const Vec2i& coordinates_);
	};

	using uint = unsigned int;
	using HeuristicFunc = std::function<uint(Vec2i, Vec2i)>;
	using CoordList = std::vector<Vec2i>;

	struct Node
	{
		uint G, H;
		Vec2i coords;
		Node *parent;
		Node(Vec2i coord_, Node *parent_ = nullptr);
		uint getScore();
	};

	using NodeSet = std::set<Node*>;

	class Generator

	{

		bool detectCollision(Vec2i coordinates_);
		Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);
		void releaseNodes(NodeSet& nodes_);



	public:

		Generator();
		void setWorldSize(Vec2i worldSize_);
		void setDiagonalMovement(bool enable_);
		void setHeuristic(HeuristicFunc heuristic_);
		CoordList findPath(Vec2i source_, Vec2i target_);
		void addCollision(Vec2i coordinates_);
		void removeCollision(Vec2i coordinates_);
		void clearCollisions();

	private:

		HeuristicFunc heuristic;
		CoordList direction, walls;
		Vec2i worldSize;
		uint directions;
	};



	class Heuristic
	{
		static Vec2i getDelta(Vec2i source_, Vec2i target_);


	public:

		static uint manhattan(Vec2i source_, Vec2i target_);
		static uint euclidean(Vec2i source_, Vec2i target_);
		static uint octagonal(Vec2i source_, Vec2i target_);
	};

} //end of namespace 'AStar'


//0 -> wall
//1 -> path
// Sujeito a alterações (seria mais eficiente se fosse desenhado por faces, para evitar que paredes tivessem mais faces do que o desejado)
//		Para isso é necessário colocar mais numeros para além de 0 e 1
static int board_walls[31][28] =
{


	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 5,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1 },
	{ 1,	0,	1,	0,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	0,	0,	1,	1 },
	{ 1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1 },
	{ 1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1 },
	{ 1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	0,	1,	1,	0,	0,	1 },
	{ 1,	1,	1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	1,	0,	0,	1,	1,	1,	1 },
	{ 1,	0,	1,	0,	0,	1,	0,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	0,	1,	1,	1,	0,	0,	0,	1 },
	{ 1,	0,	1,	1,	0,	1,	0,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1 },
	{ 1,	0,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1 },
	{ 1,	0,	0,	0,	0,	1,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1 },
	{ 1,	1,	0,	1,	0,	0,	0,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	0,	1 },
	{ 1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	1 },
	{ 1,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1 },
	{ 1,	1,	1,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	1 },
	{ 1,	0,	1,	1,	0,	1,	0,	1,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	1 },
	{ 1,	0,	1,	1,	0,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	0,	1,	1 },
	{ 1,	0,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	1 },
	{ 1,	1,	0,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	1,	1 },
	{ 1,	0,	0,	0,	0,	0,	1,	1,	1,	0,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
	{ 1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
	{ 1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
	{ 1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
	{ 1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	1,	1 },
	{ 1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	0,	1,	1 },
	{ 1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1 },
	{ 1,	0,	0,	0,	0,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1 },
	{ 1,	1,	0,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	1 },
	{ 1,	1,	0,	1,	0,	0,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1 },
	{ 1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 }
};

class Board {

	
	private:

		void initAStarGenerator();
		void drawWalls(void);

		void DRAW_WALLS_SOUTH(void);
		void DRAW_WALLS_NORTH(void);
		void DRAW_WALLS_WEST(void);
		void DRAW_WALLS_EAST(void);
		void DRAW_WALLS_BOTTOM(void);
		void DRAW_WALLS_TOP(void);

		void MYcube(void);
		void face(int, int, int, int);

		byte DRAW_DOOR = 128;	// 10000000
		byte WALLS_NORTH = 64;	// 01000000
		byte WALLS_SOUTH = 32;	// 00100000
		byte WALLS_EAST = 16;	// 00010000
		byte WALLS_WEST = 4;	// 00001000
		byte WALLS_TOP = 2;		// 00000100
		byte WALLS_BOTTOM = 1;	// 00000010
		byte WALLS_EMPTY = 0;	// 00000001



	public:
		void loadTextures(void);
		#define NUM_WALLS		6

		static const float BOARD_WALL_SIZE;
		static const int BOARD_X = 28;
		static const int BOARD_Y = 31;
		float ang;

		struct savePositionMonsters
		{
			int linha, coluna;
		};
		std::vector<savePositionMonsters> VecPositionMonsters;

		struct savePositionObjects
		{
			int x, y, type;
		};
		std::vector<savePositionObjects> VecPositionObjects;

		//Construtor
		Board();

		//Destructor
		~Board();

		//this function returns whether or not a location is open or is a wall
		bool IsOpen(float, float);

		//this function returns whether or not a location is a Door or not
		bool IsDoor(int, int);

		//this function returns whether or not a location is a Door or not
		void OpenDoor(int, int);

		// Retorna o valor do board
		int getBoardValue(int, int);

		//this function returns whether or not a location is a Door or not
		void makeWall
		(int, int);

		//Restores objects to lab (not implemented yet -> for example, restores keys to open a door (when board is reloaded for example))
		void tp_restore(void);

		//Desenha Labirinto
		void Draw(void);

		//Retorna uma lista de coordenadas do mapa por onde se deve passar desde {x,y} até {xf, yf}
		AStar::CoordList getPath(int x, int y, int xF, int yF);

		// Gera monstros aleatorios no mapa
		void GenerateRandoMonstersPositions(void);


		//gera objetos aleatorios no mapa
		void generateRandomObjectsPosition(void);

		//Imprime board
		void ImprimeBoarder(void);

};






#endif


