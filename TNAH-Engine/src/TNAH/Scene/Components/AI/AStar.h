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

    struct AStarObstacleComponent
    {
        AStarObstacleComponent() = default;
        AStarObstacleComponent(bool b) : dynamic(b) {}
        bool dynamic = false;
    private:
        inline static std::string s_SearchString = "AStar Obstacle Component";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::AStarObstacle},
{{ComponentCategory::Objects}}
        };
        friend class EditorUI;
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
        
        static bool IsValid(Int2 point);

        static void Update();
        
        static bool Reached(Int2 point, Node destination);

        static double calculateH(Int2 point, Node destination);
        
        static void Init(Int2 startingPosition, Int2 xySize);
        
        static std::deque<Node> Algorithm(Node point, Node destination);

        static std::deque<Node> makePath(std::unordered_map<int, std::unordered_map<int, Node>> map, Node destination);

        static Node GenerateRandomPosition(Int2 currentPosition);
        
        static std::unordered_map<int, std::unordered_map<int, Node>> GetMapPoints();

        static std::unordered_map<int, std::unordered_map<int, bool>> GetUsedPoints();

        static void AddUsedPosition(Int2 position, bool dynamic);
        
    static Int2 GetStartingPos();

    static Int2 GetEndPosition();
    
    private:
        inline static bool initilised = false;
        inline static Int2 startingPos = {0, 0};
        inline static Int2 size = {10, 10};
        inline static bool generated = false;
        
        inline static std::unordered_map<int, std::unordered_map<int, bool>> closedList = std::unordered_map<int, std::unordered_map<int, bool>>();
        inline static std::unordered_map<int, std::unordered_map<int, bool>> usedPositions = std::unordered_map<int, std::unordered_map<int, bool>>();
        inline static std::unordered_map<int, std::unordered_map<int, Node>> allMap = std::unordered_map<int, std::unordered_map<int, Node>>();
        
        inline static std::vector<Int2> usedPositionsHolder = std::vector<Int2>();
    };

    struct AStarComponent
    {
        AStarComponent() = default;
        AStarComponent(Int2 pos, Int2 s) : StartingPos(pos), Size(s) {}
        AStarComponent(const AStarComponent &copy)
        {
            StartingPos = copy.StartingPos;
            Size = copy.Size;
        }
        
        Int2 StartingPos = {0, 0};
        Int2 Size = {5, 5};
        bool DisplayMap = false;
        bool reset = true;
    private:
        inline static std::string s_SearchString = "AStar Component";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::AStar},
{{ComponentCategory::Objects}}
        };
        friend class EditorUI;
    };
}
