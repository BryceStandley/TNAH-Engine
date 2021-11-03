#pragma once
#include <string>
#include <vector>
#include <glm/vec3.hpp>

#include <TNAH-App.h>

namespace tnah
{
    class Scene;
    class GameObject;
    
    struct PhysicsProperties
    {
        PhysicsProperties(std::string line);
        enum Shape
        {
            box = 1, sphere = 2
        };
        
        glm::vec3 position;
        Shape shape;
        float mass;
        glm::vec3 lengths;
        float radius;
    };
    
    
    class PhysicsLoader
    {
    public:
        PhysicsLoader(std::string file);
        int size() const {return physicsObjects.size();}
        PhysicsProperties GetObjectAt(int i);
    private:
        bool loaded;
        std::vector<PhysicsProperties> physicsObjects;
    };
    
}
