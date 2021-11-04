#include "PhysicsLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtx/string_cast.hpp>

namespace tnah
{
    PhysicsProperties::PhysicsProperties(std::string line)
    {
        std::stringstream ss(line);
        int s;
        ss >> s;
        shape = (Shape)s;
        if(s == box)
        {
            ss >> mass >> position.x >> position.y >> position.z >>  lengths.x >> lengths.y >> lengths.z;   
        }
        else
        {
            ss >> mass >> position.x >> position.y >> position.z >>  radius;
        }
    }

    void PhysicsLoader::LoadFile(std::string file)
    {
        std::ifstream physicsFile(file);
        std::string line, temp;
        physicsObjects.clear();
        bool first = true;
        if(physicsFile.is_open())
        {
            while(std::getline(physicsFile, line))
            {
                if(first)
                {
                    if(line.compare("physics"))
                    {
                        first = false; 
                    }
                    else
                        break;
                }
                else
                {
                    physicsObjects.push_back(PhysicsProperties(line));
                }
            }

            physicsFile.close();
            loaded = true;
        }
        else
            loaded = false;
    }


    PhysicsProperties PhysicsLoader::GetObjectAt(int i)
    {
        std::cout << (int)physicsObjects[i].shape << " " << glm::to_string(physicsObjects[i].lengths) << " " << physicsObjects[i].mass << std::endl;
        return physicsObjects[i];
    }
}
