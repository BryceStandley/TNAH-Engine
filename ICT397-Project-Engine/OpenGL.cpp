#include "OpenGL.h"

#include "glad/glad.h"
#include "stb_image.h"
void OpenGL::RenderTerrain(unsigned int VAO, int size)
{
    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void OpenGL::RenderExitScreen(unsigned int VAO,unsigned int EBO, unsigned int texture) {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE5, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void OpenGL::BindTexture(std::vector<unsigned int> textures)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
}

void OpenGL::DepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGL::RenderSkybox(unsigned int VAO, unsigned int texture)
{
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void OpenGL::RenderModel(Shader& shader, glm::mat4 newModel, Mesh mesh)
{
    shader.setMat4("model", newModel);
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < mesh.textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = mesh.textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
    }

    // draw mesh
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void OpenGL::SetShader(Shader shader, View lens)
{
    shader.use();
    shader.setMat4("projection", lens.GetProjection());
    shader.setMat4("view", lens.GetView());
    shader.setMat4("model", lens.GetModel());
}

void OpenGL::SetShaderTerrain(Shader &shader, View lens)
{
    shader.use();
    shader.setMat4("projection", lens.GetProjection());
    shader.setMat4("view", lens.GetView());
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::scale(m, glm::vec3(0.2f));
    shader.setMat4("model", m);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos", (256 * 12) / 2.0, 100.0f, (256 * 12) / 2.0);
    shader.setVec3("viewPos", lens.GetPosition());
}

void OpenGL::SetShaderSkybox(Shader shader, View lens)
{
    glm::mat4 viewSky = glm::mat4(glm::mat3(lens.GetSkyview()));
    shader.use();
    shader.setMat4("view", viewSky);
    shader.setMat4("projection", lens.GetProjection());
}

void OpenGL::ExitScreenSetup(std::vector<glm::vec3> vertexData, std::vector<unsigned int> indices, unsigned int &VAO, unsigned int &VBO, unsigned int &EBO) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(glm::vec3), &vertexData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //postion attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void OpenGL::TerrainSetup(std::vector<glm::vec3> totalData, std::vector<unsigned int> Indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, totalData.size() * sizeof(glm::vec3), &totalData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

    //postion attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attributes
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //normal attributes
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);
}

void OpenGL::SkyboxSetup(std::vector <float> skyVerts, std::vector<std::string> faces, unsigned int& VAO, unsigned int& VBO, unsigned int& texture, Shader& skyShader)
{
    if(Debugger::GetInstance()->debugToConsole) std::cout << "renderer size: " << skyVerts.size() << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, skyVerts.size() * sizeof(float), &skyVerts[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data =
            stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,
                height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i]
                << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    skyShader.use();
    skyShader.setInt("skybox", 0);
}

unsigned int OpenGL::TextureFromFile(std::string path, const std::string& directory)//, bool gamma)
{
    std::string filename = path;

    if(Debugger::GetInstance()->debugToConsole) std::cout << "OpenGL.cpp::INFO::" << filename << std::endl; //debug

    filename = directory + '/' + filename;

    if(Debugger::GetInstance()->debugToConsole) std::cout << "OpenGL.cpp::INFO::" << filename << std::endl; //debug

    stbi_set_flip_vertically_on_load(false);
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, (int)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "OpenGL.cpp::ERROR::Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void OpenGL::SetupMesh(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}

unsigned int OpenGL::TextureFromFile(std::string path)
{
    //auto filename = directory + "//" + path;

    stbi_set_flip_vertically_on_load(false);
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, (int)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout << "Texture loaded" << std::endl;
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

int OpenGL::LoadModel(int numFrames, std::vector<int> commands, unsigned int& VAO, v3 anorms[162], std::vector<std::vector<glm::vec3>> vertices, std::vector<std::vector<int>> normals)
{
    ModelInfo tempBuffer;
    int num = vertexBuffer.size();
    int i = 0;
    int iTotalVertices = 0;

    //std::cout << "DEBUG - 4" << std::endl;
    tempBuffer.vboFrameVertices.resize(numFrames);
    for (int i = 0; i < numFrames; i++)
    {
        tempBuffer.vboFrameVertices[i].CreateBuffer();
    }
    tempBuffer.vboTextureCoords.CreateBuffer();

    if (commands.size() > 0)
    {
        while (1)
        {
            int action = commands[i];
            if (action == 0)
                break;

            int renderMode = action < 0 ? GL_TRIANGLE_FAN : GL_TRIANGLE_STRIP;
            int numVertices = action < 0 ? -action : action;
            i++;

            tempBuffer.renderModes.push_back(renderMode);
            tempBuffer.numRenderVertices.push_back(numVertices);

            for (int j = 0; j < numVertices; j++)
            {
                float s = *((float*)(&commands[i++]));
                float t = *((float*)(&commands[i++]));
                t = 1.0f - t;
                int vi = commands[i++];

                tempBuffer.vboTextureCoords.AddData(&s, 4);
                tempBuffer.vboTextureCoords.AddData(&t, 4);

                for (int k = 0; k < numFrames; k++)
                {
                    tempBuffer.vboFrameVertices[k].AddData(&vertices[k][vi], 12);
                    tempBuffer.vboFrameVertices[k].AddData(&anorms[normals[k][vi]], 12);
                }
            }
        }
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    for (int i = 0; i < numFrames; i++)
    {
        tempBuffer.vboFrameVertices[i].BindVBO();
        tempBuffer.vboFrameVertices[i].UploadData(GL_STATIC_DRAW);
    }

    tempBuffer.vboFrameVertices[0].BindVBO();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));

    tempBuffer.vboTextureCoords.BindVBO();
    tempBuffer.vboTextureCoords.UploadData(GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

    vertexBuffer.push_back(tempBuffer);
    return num;
}

void OpenGL::RenderModel(int number, Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::mat4 genFour, float direction, unsigned int& VAO, unsigned int &textureId, Shader& shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    shader.use();
    shader.setInt("texture0", 0);
    shader.setMat4("projection", proj);
    shader.setMat4("view", view);

    glm::mat4 model = genFour;
    model = glm::rotate(model, direction, glm::vec3(0, 0, 1));
    shader.setMat4("model", model);
    shader.setMat4("normal", model);

    glBindVertexArray(VAO);

    int iTotalOffset = 0;

    if (animState == NULL)
    {
        glEnableVertexAttribArray(0);
        vertexBuffer[number].vboFrameVertices[0].BindVBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
        shader.setFloat("fInterpolation", -1.0f);

        for (int i = 0; i < vertexBuffer[number].renderModes.size(); i++)
        {
            glDrawArrays(vertexBuffer[number].renderModes[i], iTotalOffset, vertexBuffer[number].numRenderVertices[i]);
            iTotalOffset += vertexBuffer[number].numRenderVertices[i];
        }
    }
    else
    {
        glEnableVertexAttribArray(0);
        vertexBuffer[number].vboFrameVertices[animState->currFrame].BindVBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(3);
        vertexBuffer[number].vboFrameVertices[animState->nextFrame].BindVBO();
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(2);
        vertexBuffer[number].vboFrameVertices[animState->currFrame].BindVBO();
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(4);
        vertexBuffer[number].vboFrameVertices[animState->nextFrame].BindVBO();
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        shader.setFloat("fInterpolation", animState->interpol);
        for (int i = 0; i < vertexBuffer[number].renderModes.size(); i++)
        {
            glDrawArrays(vertexBuffer[number].renderModes[i], iTotalOffset, vertexBuffer[number].numRenderVertices[i]);
            iTotalOffset += vertexBuffer[number].numRenderVertices[i];
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::RenderModel(int number, Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::vec3 position, glm::vec3 rotation, float direction, unsigned int& VAO, unsigned int &textureId, Shader& shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    shader.use();
    shader.setInt("texture0", 0);
    shader.setMat4("projection", proj);
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.05f));
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
    model = glm::rotate(model, direction, glm::vec3(0, 0, 1));
    shader.setMat4("model", model);
    shader.setMat4("normal", model);

    glBindVertexArray(VAO);

    int iTotalOffset = 0;

    if (animState == NULL)
    {
        glEnableVertexAttribArray(0);
        vertexBuffer[number].vboFrameVertices[0].BindVBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
        shader.setFloat("fInterpolation", -1.0f);

        for (int i = 0; i < vertexBuffer[number].renderModes.size(); i++)
        {
            glDrawArrays(vertexBuffer[number].renderModes[i], iTotalOffset, vertexBuffer[number].numRenderVertices[i]);
            iTotalOffset += vertexBuffer[number].numRenderVertices[i];
        }
    }
    else
    {
        glEnableVertexAttribArray(0);
        vertexBuffer[number].vboFrameVertices[animState->currFrame].BindVBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(3);
        vertexBuffer[number].vboFrameVertices[animState->nextFrame].BindVBO();
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(2);
        vertexBuffer[number].vboFrameVertices[animState->currFrame].BindVBO();
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(4);
        vertexBuffer[number].vboFrameVertices[animState->nextFrame].BindVBO();
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        shader.setFloat("fInterpolation", animState->interpol);
        for (int i = 0; i < vertexBuffer[number].renderModes.size(); i++)
        {
            glDrawArrays(vertexBuffer[number].renderModes[i], iTotalOffset, vertexBuffer[number].numRenderVertices[i]);
            iTotalOffset += vertexBuffer[number].numRenderVertices[i];
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*void OpenGL::SetupWater(Water* water)
{
    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    water->SetFBO(FBO);

    unsigned int DBO;
    glGenRenderbuffers(1, &DBO);
    glBindRenderbuffer(GL_RENDERBUFFER, DBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_ATTACHMENT, water->GetSize(), water->GetSize());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DBO);
    water->SetDBO(DBO);

    unsigned int colour;
    glGenTextures(1, &colour);
    glBindTexture(GL_TEXTURE_2D, colour);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, water->GetSize(), water->GetSize(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colour, 0);
    water->SetColourTextureID(colour);

    unsigned int depth;
    glGenTextures(1, &depth);
    glBindTexture(GL_TEXTURE_2D, depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, water->GetSize(), water->GetSize(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, depth, 0);
    water->SetDepthTextureID(depth);

    //Enable the clipping plane for the water
    glEnable(GL_CLIP_DISTANCE0);
}

void OpenGL::BindWater(Water* water)
{
    //bind framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, water->GetFBO());
    glViewport(0,0, water->GetSize(), water->GetSize());
}

void OpenGL::UnBindWater()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(0,0, viewport[2], viewport[3]);
}

void OpenGL::RenderWater(Water* water)
{



    // do stuff

    // unbind framebuffer and set the view port back to the default

}*/