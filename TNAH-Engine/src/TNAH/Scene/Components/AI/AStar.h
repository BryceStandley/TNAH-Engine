#pragma once
#define X_MAX 1000
#define X_STEP 20
#define Y_MAX 500
#define Y_STEP 20
#include <stack>

namespace tnah
{
    //typedef std::pair<int, int> IntPair;
    typedef std::tuple<float, int, int> Tuple;
    struct Node
    {
        glm::vec2 position;
        glm::vec2 parent;

        float f;
        float g;
        float h;

        Node(glm::vec2 p = {0, 0}) : position(p), parent(-1), f(-1), g(-1), h(-1)
        {}
    };

    inline bool operator < (const Node& left, const Node & right)
    {
        return left.f < right.f;
    }
    
    class AStar
    {
    public:
        AStar() : rowSize(0), colSize(0) {}
        ~AStar() = default;

        //Just checking it is in bounds atm not for any obstacles
        static bool IsValid(glm::vec2 point)
        {
            int id = point.x + point.y * (X_MAX / X_STEP);
            if (point.x < 0 || point.y < 0 || point.x >= (X_MAX / X_STEP) || point.y >= (Y_MAX / Y_STEP))
            {
                return false;
            }
            else
                return true;
        }

        bool NotBlocked()
        {
                
        }
        
        static bool Reached(glm::vec2 point, Node destination)
        {
            if (point.x == destination.position.x && point.y == destination.position.y)
            {
                return true;
            }
        }

        static double calculateH(glm::vec2 point, Node destination) {
            double H = (sqrt((point.x - destination.position.x)*(point.x - destination.position.x)
                + (point.y - destination.position.y)*(point.y - destination.position.y)));
            return H;
        }
        
        static std::vector<Node> Algorithm(Node point, Node destination)
        {
            if(Reached(point.position, destination))
            {
                return {};
            }
            
            bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];
            std::array<std::array<Node, (Y_MAX / Y_STEP)>,(X_MAX / X_STEP)> allMap;
            for (int x = 0; x < (X_MAX / X_STEP); x++) {
                for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
                    allMap[x][y].f= FLT_MAX;
                    allMap[x][y].g = FLT_MAX;
                    allMap[x][y].h = FLT_MAX;
                    allMap[x][y].parent =  {-1, -1};
                    allMap[x][y].position = {x, y};

                    closedList[x][y] = false;
                }
            }

            glm::vec2 position = point.position;
            allMap[position.x][position.y].f = 0.0;
            allMap[position.x][position.y].g = 0.0;
            allMap[position.x][position.y].h = 0.0;
            allMap[position.x][position.y].parent = position;

            std::vector<Node> openList;  
            openList.emplace_back(allMap[position.x][position.y]);
            bool destinationFound = false;

            while (!openList.empty()&&openList.size()<(X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
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
                
                closedList[(int)position.x][(int)position.y] = true;
                
                for (int newX = -1; newX <= 1; newX++) {
                    for (int newY = -1; newY <= 1; newY++) {
                        double gNew, hNew, fNew;
                        if (IsValid(glm::vec2(position.x + newX, position.y + newY))) {
                            if (Reached(glm::vec2(position.x + newX, position.y + newY), destination))
                            {
                                allMap[position.x + newX][position.y + newY].parent = {position.x, position.y};
                                destinationFound = true;
                                return makePath(allMap, destination);
                            }
                            else if (closedList[(int)position.x + newX][(int)position.y + newY] == false)
                            {
                                gNew = node.g + 1.0;
                                hNew = calculateH(glm::vec2(position.x + newX, position.y + newY), destination);
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

        static std::vector<Node> makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node destination) {
            try {
                int x = destination.position.x;
                int y = destination.position.y;
                std::stack<Node> path;
                std::vector<Node> usablePath;

                while (!(map[x][y].parent.x == x && map[x][y].parent.y == y)
                    && map[x][y].position.x != -1 && map[x][y].position.y != -1) 
                {
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
                    usablePath.emplace_back(top);
                }
                return usablePath;
            }
            catch(const std::exception& e){
                TNAH_WARN("Threw exception in a star");
            }
        }

    static Node GenerateRandomPosition(glm::vec2 currentPosition)
        {
            
        }
    private:
        int rowSize;
        int colSize;
    };
}
