#pragma once
#include <stack>

namespace tnah
{
    struct Int2
    {
        int x;
        int y;
        
        Int2(int o = 0, int t = 0) : x(o), y(t) {}
        bool CheckSame(Int2 other)
        {
            if(x == other.x && y == other.y)
                return true;

            return false;
        }
    };
    
    struct Node
    {
        Int2 position;
        Int2 parent;

        float f;
        float g;
        float h;

        Node(Int2 p = {0, 0}) : position(p), parent(-1, -1), f(-1), g(-1), h(-1)
        {}
    };

    inline bool operator < (const Node& left, const Node & right)
    {
        return left.f < right.f;
    }
    
    class AStar
    {
    public:
        AStar() {}
        ~AStar() = default;

        //Just checking it is in bounds atm not for any obstacles
        static bool IsValid(Int2 point)
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

        static void Update()
        {
            for(Int2 values : usedPositionsHolder)
            {
                usedPositions[values.x][values.y] = false;
            }
        }
        
        static bool Reached(Int2 point, Node destination)
        {
            if (point.CheckSame(destination.position))
            {

                return true;
            }

            return false;
        }

        static double calculateH(Int2 point, Node destination) {
            double H = (sqrt((point.x - destination.position.x)*(point.x - destination.position.x)
                + (point.y - destination.position.y)*(point.y - destination.position.y)));
            return H;
        }
        
        static void Init(Int2 startingPosition, Int2 xySize)
        {
            startingPos = startingPosition;
            size = xySize;
            initilised = true;
        }
        
        static std::deque<Node> Algorithm(Node point, Node destination)
        {
            if(!initilised)
            {
                TNAH_CORE_WARN("AStar not inisilised");
                return {};    
            }
            
            if(!IsValid(destination.position))
            {
                TNAH_CORE_INFO("V Empty");
                return {};
            }
            if(!IsValid(point.position))
            {
                TNAH_CORE_INFO("Starting Empty");
                return {};
            }
            if(Reached(point.position, destination))
            {
                TNAH_CORE_INFO("R Empty");
                return {};
            }

            for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                for (int y = startingPos.y + 1; y < startingPos.y + size.y; y++) {
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
            bool destinationFound = false;

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
            if (destinationFound == false)
            {
                return {};
            }
        }

        static std::deque<Node> makePath(std::unordered_map<int, std::unordered_map<int, Node>> map, Node destination) {
            try {
                int x = destination.position.x;
                int y = destination.position.y;
                std::stack<Node> path;
                std::deque<Node> usablePath;

                while (!(map[x][y].parent.x == x && map[x][y].parent.y == y))
                {
                    if(x == 0 && y == 0)
                    {
                        TNAH_CORE_INFO("Error");
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
                TNAH_WARN("Threw exception in a star");
            }
        }

        static Node GenerateRandomPosition(Int2 currentPosition)
        {
            while(1)
            {
                std::random_device d;
                std::mt19937 gen(d());
                std::uniform_int_distribution<int> xRand(startingPos.x,  startingPos.x + size.x-1);
                std::uniform_int_distribution<int> yRand(startingPos.y,  startingPos.y + size.y-1);
                Int2 newPos(xRand(gen), yRand(gen));
                
                if(!newPos.CheckSame(currentPosition) && IsValid(newPos))
                    return newPos;
            }
        }
        static std::unordered_map<int, std::unordered_map<int, Node>> GetMapPoints()
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

        static std::unordered_map<int, std::unordered_map<int, bool>> GetUsedPoints()
        {
            return usedPositions;
        }

        static void AddUsedPosition(Int2 position)
        {
            usedPositions[position.x][position.y] = true;
            usedPositionsHolder.push_back(position);
            /*usedPositions[position.x-1][position.y] = true;
            usedPositions[position.x+1][position.y] = true;
            usedPositions[position.x][position.y-1] = true;
            usedPositions[position.x][position.y+1] = true;*/
        }
        
    static Int2 GetStartingPos()
        {
            return startingPos;
        }

    static Int2 GetEndPosition()
        {
            return Int2(startingPos.x + size.x, startingPos.y + size.y);
        }
    private:
        static Int2 startingPos;
        static Int2 size;
        static bool initilised;
        inline static bool generated = false;
        inline static std::unordered_map<int, std::unordered_map<int, bool>> closedList = std::unordered_map<int, std::unordered_map<int, bool>>();
        inline static std::unordered_map<int, std::unordered_map<int, bool>> usedPositions = std::unordered_map<int, std::unordered_map<int, bool>>();
        //static std::array<std::array<Node, (Y_MAX / Y_STEP)>,(X_MAX / X_STEP)> allMap;
        static std::unordered_map<int, std::unordered_map<int, Node>> allMap;
        inline static std::vector<Int2> usedPositionsHolder = std::vector<Int2>();
    };

    struct AStarComponent
    {
        Int2 StartingPos = {0, 0};
        Int2 Size = {5, 5};
        bool DisplayMap = false;
        bool reset = true;
    private:
        inline static std::string s_SearchString = "AStar Component";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::ConcaveMeshCollider},
{{ComponentCategory::Physics}}
        };
        friend class EditorUI;
    };
}
