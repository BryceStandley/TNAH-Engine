#include "tnahpch.h"
#include "AStar.h"

namespace tnah
{
        //Just checking it is in bounds atm not for any obstacles
         bool AStar::IsValid(Int2 point)
        {
            if(usedPositions[point.x][point.y])
                return false;
            
            if (point.x < startingPos.x || point.y < startingPos.y || point.x > startingPos.x + size.x || point.y > startingPos.y + size.y)
            {
                return false;
            }
            else
                return true;
        }

         void AStar::Update()
        {
            for(Int2 values : usedPositionsHolder)
            {
                usedPositions[values.x][values.y] = false;
            }

             usedPositionsHolder.clear();
        }
        
         bool AStar::Reached(Int2 point, Node destination)
        {
            if (point.CheckSame(destination.position))
            {

                return true;
            }

            return false;
        }

         double AStar::calculateH(Int2 point, Node destination) {
            double H = (sqrt((point.x - destination.position.x)*(point.x - destination.position.x)
                + (point.y - destination.position.y)*(point.y - destination.position.y)));
            return H;
        }
        
         void AStar::Init(Int2 startingPosition, Int2 xySize)
        {
            startingPos = startingPosition;
            size = xySize;
            initilised = true;
            for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                for (int y = startingPos.y; y < startingPos.y + size.y; y++) {
                    allMap[x][y].f= FLT_MAX;
                    allMap[x][y].g = FLT_MAX;
                    allMap[x][y].h = FLT_MAX;
                    allMap[x][y].parent =  {-1, -1};
                    allMap[x][y].position = {x, y};
                }
            }
        }
        
         std::deque<Node> AStar::Algorithm(Node point, Node destination)
        {
            if(!initilised)
            {
                return {};    
            }
            
            if(!IsValid(destination.position))
            {
                return {};
            }
            if(!IsValid(point.position))
            {
                return {};
            }
            if(Reached(point.position, destination))
            {
                return {};
            }

            for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                for (int y = startingPos.y; y < startingPos.y + size.y; y++) {
                    allMap[x][y].f= FLT_MAX;
                    allMap[x][y].g = FLT_MAX;
                    allMap[x][y].h = FLT_MAX;
                    allMap[x][y].parent =  {-1, -1};
                    allMap[x][y].position = {x, y};
                    closedList[x][y] = false;
                }
            }
            
            Int2 position = point.position;
            allMap[position.x][position.y].f = 0.0;
            allMap[position.x][position.y].g = 0.0;
            allMap[position.x][position.y].h = 0.0;
            allMap[position.x][position.y].parent = position;

            std::vector<Node> openList;  
            openList.emplace_back(allMap[position.x][position.y]);

            while (!openList.empty()) {
                Node node;
                do {
                    float temp = FLT_MAX;
                    std::vector<Node>::iterator itNode;
                    for (std::vector<Node>::iterator it = openList.begin();
                        it != openList.end(); it = next(it)) {
                        Node n = *it;
                        if (n.f < temp) {
                            temp = n.f;
                            itNode = it;
                        }
                        }
                    node = *itNode;
                    openList.erase(itNode);
                } while (IsValid(node.position) == false);

                position = node.position;
                
                closedList[position.x][position.y] = true;
                
                for (int newX = -1; newX <= 1; newX++) {
                    for (int newY = -1; newY <= 1; newY++) {
                        double gNew, hNew, fNew;
                        if (IsValid(Int2(position.x + newX, position.y + newY))) {
                            if (Reached(Int2(position.x + newX, position.y + newY), destination))
                            {
                                allMap[position.x + newX][position.y + newY].parent = {position.x, position.y};
                                return makePath(allMap, destination);
                            }
                            else if (closedList[position.x + newX][position.y + newY] == false)
                            {
                                gNew = node.g + 1.0;
                                hNew = calculateH(Int2(position.x + newX, position.y + newY), destination);
                                fNew = gNew + hNew;
                                if (allMap[position.x + newX][position.y + newY].f == FLT_MAX ||
                                    allMap[position.x + newX][position.y + newY].f > fNew)
                                {
                                    allMap[position.x + newX][position.y + newY].f = fNew;
                                    allMap[position.x + newX][position.y + newY].g = gNew;
                                    allMap[position.x + newX][position.y + newY].h = hNew;
                                    allMap[position.x + newX][position.y + newY].parent = {position.x, position.y};
                                    openList.emplace_back(allMap[position.x + newX][position.y + newY]);
                                }
                            }
                        }
                    }
                }
            }
            
                return {};
        }

         std::deque<Node> AStar::makePath(std::unordered_map<int, std::unordered_map<int, Node>> map, Node destination) {
            try {
                int x = destination.position.x;
                int y = destination.position.y;
                std::stack<Node> path;
                std::deque<Node> usablePath;

                while (!(map[x][y].parent.x == x && map[x][y].parent.y == y))
                {
                    if(x == 0 && y == 0)
                    {
                        return {};
                    }
                    path.push(map[x][y]);
                    int tempX = map[x][y].parent.x;
                    int tempY = map[x][y].parent.y;
                    x = tempX;
                    y = tempY;

                }
                path.push(map[x][y]);

                while (!path.empty()) {
                    Node top = path.top();
                    path.pop();
                    usablePath.push_back(top);
                }
                return usablePath;
            }
            catch(const std::exception& e){
                return {};
            }
        }

         Node AStar::GenerateRandomPosition(Int2 currentPosition)
        {
             bool notFound = false;
            while(!notFound)
            {
                std::random_device d;
                std::mt19937 gen(d());
                std::uniform_int_distribution<int> xRand(startingPos.x,  startingPos.x + size.x-1);
                std::uniform_int_distribution<int> yRand(startingPos.y,  startingPos.y + size.y-1);
                Int2 newPos(xRand(gen), yRand(gen));
                
                if(!newPos.CheckSame(currentPosition) && IsValid(newPos))
                {
                    return newPos;
                    notFound = true;   
                }
            }
            return Int2(0, 0);
        }
         std::unordered_map<int, std::unordered_map<int, Node>> AStar::GetMapPoints()
        {
            if(!generated)
            {
                for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                    for (int y = startingPos.y; y < startingPos.y + size.y; y++) {
                        allMap[x][y].parent =  {-1, -1};
                        allMap[x][y].position = {x, y};
                    }
                }
                generated = true;
            }

            return allMap;
        }

         std::unordered_map<int, std::unordered_map<int, bool>> AStar::GetUsedPoints()
        {
            return usedPositions;
        }

         void AStar::AddUsedPosition(Int2 position, bool dynamic)
        {
            usedPositions[position.x][position.y] = true;

            if(dynamic)
                usedPositionsHolder.push_back(position);
            
            /*usedPositions[position.x-1][position.y] = true;
            usedPositions[position.x+1][position.y] = true;
            usedPositions[position.x][position.y-1] = true;
            usedPositions[position.x][position.y+1] = true;*/
        }
        
     Int2 AStar::GetStartingPos()
        {
            return startingPos;
        }

     Int2 AStar::GetEndPosition()
        {
            return Int2(startingPos.x + size.x, startingPos.y + size.y);
        }
}