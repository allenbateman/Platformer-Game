#include "Pathfinding.h"

#include "Point.h"

iPoint Pathfinding::MapToWorld(int x, int y) const
{
	iPoint ret;

	// L05: DONE 1: Add isometric map to world coordinates
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tileWidth;
		ret.y = y * data.tileHeight;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tileWidth / 2);
		ret.y = (x + y) * (data.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint Pathfinding::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// L05: DONE 3: Add the case for isometric maps to WorldToMap
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tileWidth;
		ret.y = y / data.tileHeight;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{

		float halfWidth = data.tileWidth * 0.5f;
		float halfHeight = data.tileHeight * 0.5f;
		ret.x = int((x / halfWidth + y / halfHeight) / 2);
		ret.y = int((y / halfHeight - (x / halfWidth)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

void Pathfinding::ResetPath()
{
	frontier.Clear();
	visited.Clear();
	breadcrumbs.Clear();
	path.Clear();

	frontier.Push(iPoint(10, 14), 0);
	visited.Add(iPoint(10, 14));
	breadcrumbs.Add(iPoint(10, 14));

	memset(costSoFar, 0, sizeof(uint) * COST_MAP_SIZE * COST_MAP_SIZE);
}

void Pathfinding::DrawPath()
{
	iPoint point;

	// Draw visited
	ListItem<iPoint>* item = visited.start;

	while (item)
	{
		point = item->data;
		TileSet* tileset = map.GetTilesetFromTileId(26);

		SDL_Rect rec = tileset->GetTileRect(26);
		iPoint pos = MapToWorld(point.x, point.y);

		App->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = map.GetTilesetFromTileId(25);

		SDL_Rect rec = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);
	}

	// Draw path
	for (uint i = 0; i < path.Count(); ++i)
	{
		iPoint pos = MapToWorld(path[i].x, path[i].y);
		app->render->DrawTexture(tileX, pos.x, pos.y);
	}
}

bool Pathfinding::IsWalkable(int x, int y) const
{
	return false;
}

int Pathfinding::MovementCost(int x, int y) const
{
	return 0;
}

void Pathfinding::ComputePath(int x, int y)
{
}

void Pathfinding::ComputePathAStar(int x, int y)
{
}

void Pathfinding::PropagateBFS()
{
	// L10: DONE 1: If frontier queue contains elements
	// pop the last one and calculate its 4 neighbors
	iPoint curr;
	if (frontier.Pop(curr))
	{
		// L10: DONE 2: For each neighbor, if not visited, add it
		// to the frontier queue and visited list
		iPoint neighbors[4];
		neighbors[0].Create(curr.x + 1, curr.y + 0);
		neighbors[1].Create(curr.x + 0, curr.y + 1);
		neighbors[2].Create(curr.x - 1, curr.y + 0);
		neighbors[3].Create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			if (IsWalkable(neighbors[i].x, neighbors[i].y))
			{
				if (visited.Find(neighbors[i]) == -1)
				{
					frontier.Push(neighbors[i], 0);
					visited.Add(neighbors[i]);

					// L11: DONE 1: Record the direction to the previous node 
					// with the new list "breadcrumps"
					breadcrumbs.Add(curr);
				}
			}
		}
	}
}

void Pathfinding::PropagateDijkstra()
{

	iPoint curr;
	if (frontier.Pop(curr))
	{
		iPoint neighbors[4];
		neighbors[0].Create(curr.x + 1, curr.y + 0);
		neighbors[1].Create(curr.x + 0, curr.y + 1);
		neighbors[2].Create(curr.x - 1, curr.y + 0);
		neighbors[3].Create(curr.x + 0, curr.y - 1);
		int cost;
		for (uint i = 0; i < 4; ++i)
		{
			cost = MovementCost(neighbors[i].x, neighbors[i].y);
			if (cost >= 0 && (cost < costSoFar[neighbors[i].x][neighbors[i].y] || visited.Find(neighbors[i]) == -1))
			{
				costSoFar[neighbors[i].x][neighbors[i].y] = cost;
				frontier.Push(neighbors[i], cost);
				visited.Add(neighbors[i]);
				breadcrumbs.Add(curr);

			}
		}
	}
}

void Pathfinding::PropagateAStar(int heuristic)
{
	iPoint curr;
	if (frontier.Pop(curr))
	{
		iPoint neighbors[4];
		neighbors[0].Create(curr.x + 1, curr.y + 0);
		neighbors[1].Create(curr.x + 0, curr.y + 1);
		neighbors[2].Create(curr.x - 1, curr.y + 0);
		neighbors[3].Create(curr.x + 0, curr.y - 1);
		int cost;
		for (uint i = 0; i < 4; ++i)
		{
			cost = MovementCost(neighbors[i].x, neighbors[i].y);
			if (cost >= 0 && (cost < costSoFar[neighbors[i].x][neighbors[i].y] || visited.Find(neighbors[i]) == -1))
			{
				costSoFar[neighbors[i].x][neighbors[i].y] = cost;
				frontier.Push(neighbors[i], cost);
				visited.Add(neighbors[i]);
				breadcrumbs.Add(curr);

			}
		}
	}

}