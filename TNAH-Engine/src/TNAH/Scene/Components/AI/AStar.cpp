#include "tnahpch.h"
#include "AStar.h"

namespace tnah
{
   std::unordered_map<int, std::unordered_map<int, Node>> AStar::allMap = std::unordered_map<int, std::unordered_map<int, Node>>();
   bool AStar::initilised = false;
   Int2 AStar::startingPos = {0, 0};
   Int2 AStar::size = {10, 10};
}