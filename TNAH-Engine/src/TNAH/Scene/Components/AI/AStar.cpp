#include "tnahpch.h"
#include "AStar.h"

namespace tnah
{
    std::array<std::array<Node, (Y_MAX / Y_STEP)>,(X_MAX / X_STEP)> AStar::allMap = std::array<std::array<Node, (Y_MAX / Y_STEP)>,(X_MAX / X_STEP)>();
}