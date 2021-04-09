/**
 * @author Bryce Standley
 * @brief Class to control and generate boudningbox information for a given object
 * @date 06/04/2021
 */

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"

/**
 * @class BoundingBox
 * @brief Class to hold all collision and bounding box information of a game object
 * @todo Implement bounding box collisions
 */

class BoundingBox {
public:
    /**
     * @brief Bounding box constructor with empty objects
     */
    BoundingBox() = default;

    /**
     * @brief Bounding box constructor with vertex and indice data
     * @param vector vec3 v
     * @param vector int i
     */
    BoundingBox(std::vector<glm::vec3> v, std::vector<int> i) {vertex = v; indice = i;};

    /**
     * @brief Sets the vertex data of a bounding box
     * @param vector vec3 v
     */
    void SetVertexData(std::vector<glm::vec3> v) {vertex = v;}

    /**
     * @brief Sets the indice data of a bounding box
     * @param vector int i
     */
    void SetIndiceData(std::vector<int> i) {indice = i;}

    /**
     * @brief Sets the normals data of a bounding box
     * @param vector vec3 n
     */
    void SetNormalsData(std::vector<glm::vec3> n) {normals = n;}

    /**
     * @brief Gets vertex data of a bounding box
     * @return vector vec3
     */
    std::vector<glm::vec3> GetVertexData(){return vertex;}

    /**
     * @brief Gets indice data of a bounding box
     * @return vector int
     */
    std::vector<int> GetIndiceData(){return indice;}

    /**
     * @brief Gets normal data of a bounding box
     * @return vector vec3
     */
    std::vector<glm::vec3> GetNormalData(){return normals;}

    /**
     * @brief Takes a mesh and generates a basix bounding box based off min and max
     * values of the mesh in X,Y,Z directions
     * @param mesh
     * @return boundingBox
     */
    BoundingBox GenerateBoundingBox(Mesh* mesh);

    /**
     * @brief Generates normals of the bounding box
     */
    void GenerateBoundingBoxNormals();


    /**
     * @brief Collision tag used for collision checking on a object
     */
    enum CollisionTag{
        PLAYER,
        TOKEN,
        STATIC_OBJECT,
        ENEMY
    };


private:
    std::vector<glm::vec3> vertex;
    std::vector<int> indice;
    std::vector<glm::vec3> normals;
};


#endif //BOUNDINGBOX_H
