#include "Board.h"

#include <algorithm>

using namespace std::placeholders;

bool AStar::Vec2i::operator == (const Vec2i& coordinates_)
{
	return (x == coordinates_.x && y == coordinates_.y);
}



AStar::Vec2i operator + (const AStar::Vec2i& left_, const AStar::Vec2i& right_)
{
	return{ left_.x + right_.x, left_.y + right_.y };
}



AStar::Node::Node(Vec2i coordinates_, Node *parent_)
{
	parent = parent_;
	coords = coordinates_;
	G = H = 0;
}



AStar::uint AStar::Node::getScore()
{
	return G + H;
}



AStar::Generator::Generator()
{
	setDiagonalMovement(false);
	setHeuristic(&Heuristic::manhattan);
	direction = {
		{ 0, 1 }	,{ 1, 0 }	,{ 0, -1 }	,{ -1, 0 },
		{ -1, -1 }	,{ 1, 1 }	,{ -1, 1 }	,{ 1, -1 }
	};
}

void AStar::Generator::setWorldSize(Vec2i worldSize_)
{
	worldSize = worldSize_;
}


void AStar::Generator::setDiagonalMovement(bool enable_)
{
	directions = (enable_ ? 8 : 4);
}


void AStar::Generator::setHeuristic(HeuristicFunc heuristic_)
{
	heuristic = std::bind(heuristic_, _1, _2); //{}
}

void AStar::Generator::addCollision(Vec2i coordinates_)
{
	walls.push_back(coordinates_);
}


void AStar::Generator::removeCollision(Vec2i coordinates_)
{
	auto it = std::find(walls.begin(), walls.end(), coordinates_);
	if (it != walls.end()) {
		walls.erase(it);
	}
}


void AStar::Generator::clearCollisions()
{
	walls.clear();
}


AStar::CoordList AStar::Generator::findPath(Vec2i start, Vec2i finish)
{
	Node *thisNode = nullptr;
	NodeSet openSet, closedSet;
	openSet.insert(new Node(start));

	while (!openSet.empty()) {
		thisNode = *openSet.begin();
		for (Node* node : openSet) {
			if (node->getScore() <= thisNode->getScore()) {
				thisNode = node;
			}
		}

		if (thisNode->coords == finish) {
			break;
		}


		closedSet.insert(thisNode);
		openSet.erase(std::find(openSet.begin(), openSet.end(), thisNode));

		for (uint i = 0; i < directions; ++i) {
			Vec2i newCoordinates(thisNode->coords + direction[i]);
			if (detectCollision(newCoordinates) ||
				findNodeOnList(closedSet, newCoordinates)) {
				continue;
			}

			uint totalCost = thisNode->G + ((i < 4) ? 10 : 14);

			Node *next = findNodeOnList(openSet, newCoordinates);
			if (next == nullptr) {
				next = new Node(newCoordinates, thisNode);
				next->G = totalCost;
				next->H = heuristic(next->coords, finish);
				openSet.insert(next);
			}
			else if (totalCost < next->G) {
				next->parent = thisNode;
				next->G = totalCost;
			}
		}
	}


	CoordList path;
	while (thisNode != nullptr) {
		path.push_back(thisNode->coords);
		thisNode = thisNode->parent;
	}

	releaseNodes(openSet);
	releaseNodes(closedSet);

	return path;
}



AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes_, Vec2i coordinates_)
{
	for (auto node : nodes_) {
		if (node->coords == coordinates_) {
			return node;
		}
	}

	return nullptr;
}



void AStar::Generator::releaseNodes(NodeSet& nodes_)
{
	for (auto it = nodes_.begin(); it != nodes_.end();) {
		delete *it;
		it = nodes_.erase(it);
	}
}

bool
hasWalls(int x, int y) {
	return board_walls[x][y] == 1 || board_walls[x][y] == 5;
}

bool AStar::Generator::detectCollision(Vec2i coordinates_)
{
	if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
		coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
		hasWalls(coordinates_.x, coordinates_.y)) {
		return true;
	}
	return false;
}

AStar::Vec2i AStar::Heuristic::getDelta(Vec2i source_, Vec2i target_)
{
	return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}



AStar::uint AStar::Heuristic::manhattan(Vec2i source_, Vec2i target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return static_cast<uint>(10 * (delta.x + delta.y));
}



AStar::uint AStar::Heuristic::euclidean(Vec2i source_, Vec2i target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}



AStar::uint AStar::Heuristic::octagonal(Vec2i source_, Vec2i target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return 10 * (delta.x + delta.y) + (-6) * delta.x < delta.y ? delta.x: delta.y;
}