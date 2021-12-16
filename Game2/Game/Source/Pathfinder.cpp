#include "Tilemap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* pTilemap)
{
    m_pTilemap = pTilemap;
    m_MapWidth = pTilemap->GetWidth();
    m_MapHeight = pTilemap->GetHeight();

    m_Nodes.resize( m_MapWidth * m_MapHeight );
}

Pathfinder::~Pathfinder()
{
}

bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    Reset();

    // Calculate tile indices.
    int startTileIndex = sy*m_MapWidth + sx;
    int endTileIndex = ey*m_MapWidth + ex;

    // Open the starting node.
    m_Nodes[startTileIndex].cost = 0;
    m_Nodes[startTileIndex].finalCost = 0;
    m_Nodes[startTileIndex].status = PathNode::PathNodeStatus::Open;
    m_OpenTileIndices.push_back( startTileIndex );

    // Loop while nodes are open.
    while( m_OpenTileIndices.size() > 0 )
    {
        int currentTileIndex = FindLowestCostNodeFromOpenListAndRemoveIt();

        // If the lowest cost node was the destination, we found a path.
        if( currentTileIndex == endTileIndex )
        {
            return true; // Found a path.
        }

        // Mark the currentTileIndex as closed.
        m_Nodes[currentTileIndex].status = PathNode::PathNodeStatus::Closed;

        // Loop through this node's neighbours.
        std::vector<int> neighbours = MakeListOfValidNeighbours( currentTileIndex );
        for( int i=0; i<neighbours.size(); i++ )
        {
            int neighbourTileIndex = neighbours[i];

            // If it isn't already in the open list, add it
            if( m_Nodes[neighbourTileIndex].status == PathNode::PathNodeStatus::Unchecked )
            {
                m_Nodes[neighbourTileIndex].status = PathNode::PathNodeStatus::Open;
                m_OpenTileIndices.push_back( neighbourTileIndex );
            }
            
            // Check if we found a cheaper path to this neighbour node.
            int newCost = m_Nodes[currentTileIndex].cost + 1;
            if( newCost < m_Nodes[neighbourTileIndex].cost )
            {
                // This path is cheaper, so update all pathNode properties.
                m_Nodes[neighbourTileIndex].cost = newCost;
                m_Nodes[neighbourTileIndex].heuristic = CalculateHeuristic( neighbourTileIndex, endTileIndex );
                m_Nodes[neighbourTileIndex].finalCost = m_Nodes[neighbourTileIndex].cost + m_Nodes[neighbourTileIndex].heuristic;

                m_Nodes[neighbourTileIndex].parentNodeIndex = currentTileIndex;
            }
        }
    }

    // Ran out of open nodes, there is no path.
    return false;
}

std::vector<int> Pathfinder::GetPath(int ex, int ey)
{
    std::vector<int> path;

    // TODO: Generate a path based on the parentNodeIndex on the PathNode.

    return path;
}

void Pathfinder::Reset()
{
    for( int i=0; i<m_Nodes.size(); i++ )
    {
        m_Nodes[i].status = PathNode::PathNodeStatus::Unchecked;
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].cost = FLT_MAX;
        m_Nodes[i].heuristic = FLT_MAX;
        m_Nodes[i].finalCost = FLT_MAX;
    }
}

int Pathfinder::FindLowestCostNodeFromOpenListAndRemoveIt()
{
    // TODO: Find node with lowest finalCost in the open list.
    float tempLowestFC = FLT_MAX;
    int index;
    int returnIndex;
    float tempCurrent=FLT_MAX;
    for (int i = 0; i < m_OpenTileIndices.size(); i++) {
        tempCurrent = m_Nodes[m_OpenTileIndices[i]].finalCost;
        if (tempCurrent < tempLowestFC) {
            index = i;
        }
    }
    returnIndex = m_OpenTileIndices[index];
    m_OpenTileIndices.erase(m_OpenTileIndices.begin() + index);
    return returnIndex;
}

std::vector<int> Pathfinder::MakeListOfValidNeighbours(int tileIndex)
{
    std::vector<int> neighbours;
    const int numNeighbors = 4;
    int currentY = tileIndex / m_MapWidth;
    int currentX = tileIndex % m_MapWidth;
    //Checks each side for inconsistency in x and y values, then adds them if they exist
    if (currentX - 1 >= 0) {
        neighbours.push_back((currentY * m_MapWidth) + currentX - 1);//LEFT
    }
    if (currentX + 1 <= m_MapWidth) {
        neighbours.push_back((currentY * m_MapWidth) + currentX + 1);//RIGHT
    }
    if (currentY - 1 >= 0) {
        neighbours.push_back((currentY - 1 * m_MapWidth) + currentX);//DOWN
    }
    if (currentY + 1 <= m_MapHeight) {
        neighbours.push_back((currentY + 1 * m_MapWidth) + currentX);//UP
    }
    for (int i = 0; i < neighbours.size(); i++) {
        if (m_Nodes[neighbours[i]].status == PathNode::PathNodeStatus::Closed) {
            neighbours.erase(neighbours.begin() + i);
        }
        if (!(m_pTilemap->IsTileWalkable(neighbours[i]))) {
            neighbours.erase(neighbours.begin() + i);
        }
    }
    // TODO: Check for out of bounds tiles. CHECK
    // Check if the node is already closed. CHECK
    // Check if the tile in walkable in the tilemap. CHECK

    return neighbours;
}

int Pathfinder::CalculateHeuristic(int index1, int index2)
{
    // TODO: Calculate the manhatten distance between these two nodes.
    int startX= index1 % m_MapWidth;
    int startY= index1 / m_MapWidth;
    int endX= index2 % m_MapWidth;
    int endY= index2 / m_MapWidth;
    int distance = abs(startX-endX) + abs(startY-endY);
    return distance;
}
