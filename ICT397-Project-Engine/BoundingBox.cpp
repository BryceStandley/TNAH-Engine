#include "BoundingBox.h"

BoundingBox BoundingBox::GenerateBoundingBox(Mesh* mesh)
{
    float minX = 0.0f, minY = 0.0f, minZ = 0.0f;
    float maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;
    glm::vec3 size, origin;
    glm::mat4 transform;
    for(Vertex & vertice : mesh->vertices)
    {
        if(minX > vertice.Position.x) {minX = vertice.Position.x;}
        if(maxX < vertice.Position.x) {maxX = vertice.Position.x;}

        if(minY > vertice.Position.y) {minY = vertice.Position.y;}
        if(maxY > vertice.Position.y) {maxY = vertice.Position.y;}

        if(minZ > vertice.Position.z) {minZ = vertice.Position.z;}
        if(maxZ > vertice.Position.z) {maxZ = vertice.Position.z;}
    }

    std::vector<glm::vec3> box;
    std::vector<int> ind;

    //All vertex data for all 8 required vertices
    box.emplace_back(glm::vec3(minX, maxY, maxZ));
    box.emplace_back(glm::vec3(maxX, maxY, maxZ));
    box.emplace_back(glm::vec3(maxX, minY, maxZ));
    box.emplace_back(glm::vec3(minX, minY, maxZ));

    box.emplace_back(glm::vec3(minX, maxY, minZ));
    box.emplace_back(glm::vec3(maxX, maxY, minZ));
    box.emplace_back(glm::vec3(maxX, minY, minZ));
    box.emplace_back(glm::vec3(minX, minY, minZ));

    size = glm::vec3(maxX-minX, maxY-minY, maxZ-minZ);
    origin = glm::vec3((minX+maxX)/2, (minY + maxY), (minZ + maxZ)/2);
    transform = glm::translate(glm::mat4(1), origin) * glm::scale(glm::mat4(1), size);

    //index of all the triangles
    int indi[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };
    ind.insert(ind.begin(), std::begin(indi), std::end(indi));

    GenerateBoundingBoxNormals();

    return BoundingBox(box, ind);
}

void BoundingBox::GenerateBoundingBoxNormals()
{
    //left and right
    normals.emplace_back(glm::vec3(-1, 0, 0));
    normals.emplace_back(glm::vec3(1, 0, 0));

    //top and bottom
    normals.emplace_back(glm::vec3(0, -1, 0));
    normals.emplace_back(glm::vec3(0, 1, 0));

    //front and back
    normals.emplace_back(glm::vec3(0, 0, -1));
    normals.emplace_back(glm::vec3(0, 0, 1));
}
