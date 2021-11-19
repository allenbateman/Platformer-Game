#pragma once
#include "Point.h"
#include "DynArray.h"
#include "List.h"
#include "PQueue.h"
#include "Queue.h"
#include "List.h"
#include "SString.h"
#include "PugiXml\src\pugixml.hpp"
#include "Map.h"


#define COST_MAP_SIZE	100
struct SDL_Texture;

class Pathfinding
{

	// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

	// L05: DONE 2: Add orthographic world to map coordinates
	iPoint WorldToMap(int x, int y) const;
	// L10: BFS Pathfinding methods
	void ResetPath();
	void DrawPath();
	bool IsWalkable(int x, int y) const;

	// L11: More pathfinding methods
	int MovementCost(int x, int y) const;
	void ComputePath(int x, int y);

	// L12a: AStar pathfinding
	void ComputePathAStar(int x, int y);

	// Propagation methods
	void PropagateBFS();
	void PropagateDijkstra();
	// L12a: AStar propagation
	void PropagateAStar(int heuristic);

private:

	MapData data;
	Map map;


	pugi::xml_document mapFile;
	SString folder;
	bool mapLoaded;

	// L10: BFS Pathfinding variables
	PQueue<iPoint> frontier;
	List<iPoint> visited;

	// L11: Additional variables
	List<iPoint> breadcrumbs;
	uint costSoFar[COST_MAP_SIZE][COST_MAP_SIZE];
	DynArray<iPoint> path;

	// L12: AStar (A*) variables
	iPoint goalAStar;			// Store goal target tile
	bool finishAStar = false;	// Detect when reached goal

	SDL_Texture* tileX = nullptr;

};

