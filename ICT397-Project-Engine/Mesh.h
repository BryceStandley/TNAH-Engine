#pragma once
#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include <string>
#include <vector>

    /// struct containing all vertices required to generate a mesh 
struct Vertex {
        /// position
    glm::vec3 Position;
        /// normal
    glm::vec3 Normal;
        /// texCoords
    glm::vec2 TexCoords;
        /// tangent
    glm::vec3 Tangent;
        /// bitangent
    glm::vec3 Bitangent;
};

    /// struct containing the id, type and location of a texture that will be attached to the mesh
struct TextureMesh {
    unsigned int id;
    std::string type;
    std::string path;
};

    /**
    * @class Mesh
    * @brief A class that uses mesh data to setup and draw all the meshes that a model is made of 
    *
    * @author Dylan Blereau
    * @version 01
    * @date 24/03/2021 Dylan Blereau, Started
    *
    **/
class Mesh {
public:
        /// mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureMesh>      textures;
    glm::mat4 transform;
    unsigned int VAO;

        /**
        * @brief A constructor that takes in mesh data and uses said data to set up the mesh by calling the setupMesh function
        * @param vertices - a vector containing all the vertices for the mesh
        * @param indices - a vector containing all the indices for the mesh
        * @param textures -  a vector containing all the textures for the mesh
        * @param transform - represents the transformation matrix
        */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureMesh> textures, glm::mat4& transform)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        this->transform = transform;
    }

        /**
        * @brief A function that binds each texture (if the mesh has more than one) and draws the mesh  
        * @param shader - a reference to a shader object
        */
    void Draw(Shader& shader)
    {
            /// bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); 
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); 
            else if (name == "texture_height")
                number = std::to_string(heightNr++);

                /// now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);

                /// bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

            /// draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

            /// always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
    unsigned int VBO, EBO;
private:

        /**
        * @brief places mesh data into the buffers and arrays required to set up the mesh 
        * 
        */
    void setupMesh()
    {
            /// create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        
            /// vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            /// vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            /// vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            /// vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
            /// vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }
};
