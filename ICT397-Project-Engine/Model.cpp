#include "Model.h"

void Model::LoadModel(std::string const& path, Renderer* gameRenderer, std::string pathTexture)
{
    if (fbx)
    {
        Fbx temp(path, gameRenderer);
        fbxModel = temp;
    }
    else if (md2)
    {
        md2Model.LoadModel(path.c_str(), pathTexture.c_str(), "./res/shader/md2vert.vert", "./res/shader/md2frag.frag", gameRenderer);
        currentState = md2Model.StartAnimation(WALK);
    }
}

void Model::Render(View lens, Shader &shader, glm::vec3 pos, glm::vec3 rot, float scale, bool rotate, float time, float direction, Renderer* gameRenderer, bool p)
{
    if (fbx)
    {
        gameRenderer->SetShader(shader, lens);
        for (int i = 0; i < fbxModel.meshes.size(); i++)
        {
            gameRenderer->RenderModel(shader, GenerateMatFour(pos, rot, scale, rotate) * fbxModel.meshes[i].transform, fbxModel.meshes[i]);
        }
    }
    else if (md2)
    {
        if (animations)
        {
            rot.x = 180.695f;
            if(p)
                md2Model.RenderModel(&currentState, lens.GetProjection(), lens.GetView(), GenerateMatFour(pos, rot, scale, rotate), direction, gameRenderer);
            else
                md2Model.RenderModel(&currentState, lens.GetProjection(), lens.GetView(), pos, rot, direction, gameRenderer);
            md2Model.UpdateAnimation(&currentState, time, gameRenderer);
        }
        else
        {
            md2Model.RenderModel(NULL, lens.GetProjection(), lens.GetView(), GenerateMatFour(pos, rot, scale, rotate), 0, gameRenderer);
        }
    }
}

glm::mat4 Model::GenerateMatFour(glm::vec3 pos, glm::vec3 rot, float scale, bool rotate)
{
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, pos); // translate it too the position on the screen we want it
    m = glm::scale(m, glm::vec3(scale, scale, scale));	// it's a bit too big for our scene, so scale it down

    if (rotate)
    {
        m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::rotate(m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    m = glm::rotate(m, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m = glm::rotate(m, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m = glm::rotate(m, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));

    return m;
}

