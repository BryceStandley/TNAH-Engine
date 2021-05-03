#include "Md2.h"

Md2State Md2::animationList[21] =
{
	// first, last, fps
	{   0,  39,  9 },
	{  40,  45, 10 },
	{  40,  45,  5 },
	{  46,  53, 10 },
	{  54,  57,  7 },
	{  58,  61,  7 },
	{  62,  65,  7 },
	{  66,  71,  7 },
	{  72,  83,  7 },
	{  84,  94,  7 },
	{  95, 111, 10 },
	{ 112, 122,  7 },
	{ 123, 134,  6 },
	{ 135, 153, 10 },
	{ 154, 159,  7 },
	{ 160, 168, 10 },
	{ 196, 172,  7 },
	{ 173, 177,  5 },
	{ 178, 183,  7 },
	{ 184, 189,  7 },
	{ 190, 197,  7 },
};

std::string sMD2AnimationNames[MAX_ANIMATIONS] =
{
	"Stand",
	"Run",
	"Walk",
	"Attack",
	"Pain A",
	"Pain B",
	"Pain C",
	"Jump",
	"Flip",
	"Salute",
	"Fallback",
	"Wave",
	"Pointing",
	"Crouch Stand",
	"Crouch Walk",
	"Crouch Attack",
	"Crouch Pain",
	"Crouch Death",
	"Death Fallback",
	"Death Fall Forward",
	"Death Fallback Slow",
};

v3 anorms[162] =
{
{-0.525731, 0.000000, 0.850651},
{ -0.442863, 0.238856, 0.864188 },
{ -0.295242, 0.000000, 0.955423 },
{ -0.309017, 0.500000, 0.809017 },
{ -0.162460, 0.262866, 0.951056 },
{ 0.000000, 0.000000, 1.000000 },
{ 0.000000, 0.850651, 0.525731 },
{ -0.147621, 0.716567, 0.681718 },
{ 0.147621, 0.716567, 0.681718 },
{ 0.000000, 0.525731, 0.850651 },
{ 0.309017, 0.500000, 0.809017 },
{ 0.525731, 0.000000, 0.850651 },
{ 0.295242, 0.000000, 0.955423 },
{ 0.442863, 0.238856, 0.864188 },
{ 0.162460, 0.262866, 0.951056 },
{ -0.681718, 0.147621, 0.716567 },
{ -0.809017, 0.309017, 0.500000 },
{ -0.587785, 0.425325, 0.688191 },
{ -0.850651, 0.525731, 0.000000 },
{ -0.864188, 0.442863, 0.238856 },
{ -0.716567, 0.681718, 0.147621 },
{ -0.688191, 0.587785, 0.425325 },
{ -0.500000, 0.809017, 0.309017 },
{ -0.238856, 0.864188, 0.442863 },
{ -0.425325, 0.688191, 0.587785 },
{ -0.716567, 0.681718, -0.147621 },
{ -0.500000, 0.809017, -0.309017 },
{ -0.525731, 0.850651, 0.000000 },
{ 0.000000, 0.850651, -0.525731 },
{ -0.238856, 0.864188, -0.442863 },
{ 0.000000, 0.955423, -0.295242 },
{ -0.262866, 0.951056, -0.162460 },
{ 0.000000, 1.000000, 0.000000 },
{ 0.000000, 0.955423, 0.295242 },
{ -0.262866, 0.951056, 0.162460 },
{ 0.238856, 0.864188, 0.442863 },
{ 0.262866, 0.951056, 0.162460 },
{ 0.500000, 0.809017, 0.309017 },
{ 0.238856, 0.864188, -0.442863 },
{ 0.262866, 0.951056, -0.162460 },
{ 0.500000, 0.809017, -0.309017 },
{ 0.850651, 0.525731, 0.000000 },
{ 0.716567, 0.681718, 0.147621 },
{ 0.716567, 0.681718, -0.147621 },
{ 0.525731, 0.850651, 0.000000 },
{ 0.425325, 0.688191, 0.587785 },
{ 0.864188, 0.442863, 0.238856 },
{ 0.688191, 0.587785, 0.425325 },
{ 0.809017, 0.309017, 0.500000 },
{ 0.681718, 0.147621, 0.716567 },
{ 0.587785, 0.425325, 0.688191 },
{ 0.955423, 0.295242, 0.000000 },
{ 1.000000, 0.000000, 0.000000 },
{ 0.951056, 0.162460, 0.262866 },
{ 0.850651, -0.525731, 0.000000 },
{ 0.955423, -0.295242, 0.000000 },
{ 0.864188, -0.442863, 0.238856 },
{ 0.951056, -0.162460, 0.262866 },
{ 0.809017, -0.309017, 0.500000 },
{ 0.681718, -0.147621, 0.716567 },
{ 0.850651, 0.000000, 0.525731 },
{ 0.864188, 0.442863, -0.238856 },
{ 0.809017, 0.309017, -0.500000 },
{ 0.951056, 0.162460, -0.262866 },
{ 0.525731, 0.000000, -0.850651 },
{ 0.681718, 0.147621, -0.716567 },
{ 0.681718, -0.147621, -0.716567 },
{ 0.850651, 0.000000, -0.525731 },
{ 0.809017, -0.309017, -0.500000 },
{ 0.864188, -0.442863, -0.238856 },
{ 0.951056, -0.162460, -0.262866 },
{ 0.147621, 0.716567, -0.681718 },
{ 0.309017, 0.500000, -0.809017 },
{ 0.425325, 0.688191, -0.587785 },
{ 0.442863, 0.238856, -0.864188 },
{ 0.587785, 0.425325, -0.688191 },
{ 0.688191, 0.587785, -0.425325 },
{ -0.147621, 0.716567, -0.681718 },
{ -0.309017, 0.500000, -0.809017 },
{ 0.000000, 0.525731, -0.850651 },
{ -0.525731, 0.000000, -0.850651 },
{ -0.442863, 0.238856, -0.864188 },
{ -0.295242, 0.000000, -0.955423 },
{ -0.162460, 0.262866, -0.951056 },
{ 0.000000, 0.000000, -1.000000 },
{ 0.295242, 0.000000, -0.955423 },
{ 0.162460, 0.262866, -0.951056 },
{ -0.442863, -0.238856, -0.864188 },
{ -0.309017, -0.500000, -0.809017 },
{ -0.162460, -0.262866, -0.951056 },
{ 0.000000, -0.850651, -0.525731 },
{ -0.147621, -0.716567, -0.681718 },
{ 0.147621, -0.716567, -0.681718 },
{ 0.000000, -0.525731, -0.850651 },
{ 0.309017, -0.500000, -0.809017 },
{ 0.442863, -0.238856, -0.864188 },
{ 0.162460, -0.262866, -0.951056 },
{ 0.238856, -0.864188, -0.442863 },
{ 0.500000, -0.809017, -0.309017 },
{ 0.425325, -0.688191, -0.587785 },
{ 0.716567, -0.681718, -0.147621 },
{ 0.688191, -0.587785, -0.425325 },
{ 0.587785, -0.425325, -0.688191 },
{ 0.000000, -0.955423, -0.295242 },
{ 0.000000, -1.000000, 0.000000 },
{ 0.262866, -0.951056, -0.162460 },
{ 0.000000, -0.850651, 0.525731 },
{ 0.000000, -0.955423, 0.295242 },
{ 0.238856, -0.864188, 0.442863 },
{ 0.262866, -0.951056, 0.162460 },
{ 0.500000, -0.809017, 0.309017 },
{ 0.716567, -0.681718, 0.147621 },
{ 0.525731, -0.850651, 0.000000 },
{ -0.238856, -0.864188, -0.442863 },
{ -0.500000, -0.809017, -0.309017 },
{ -0.262866, -0.951056, -0.162460 },
{ -0.850651, -0.525731, 0.000000 },
{ -0.716567, -0.681718, -0.147621 },
{ -0.716567, -0.681718, 0.147621 },
{ -0.525731, -0.850651, 0.000000 },
{ -0.500000, -0.809017, 0.309017 },
{ -0.238856, -0.864188, 0.442863 },
{ -0.262866, -0.951056, 0.162460 },
{ -0.864188, -0.442863, 0.238856 },
{ -0.809017, -0.309017, 0.500000 },
{ -0.688191, -0.587785, 0.425325 },
{ -0.681718, -0.147621, 0.716567 },
{ -0.442863, -0.238856, 0.864188 },
{ -0.587785, -0.425325, 0.688191 },
{ -0.309017, -0.500000, 0.809017 },
{ -0.147621, -0.716567, 0.681718 },
{ -0.425325, -0.688191, 0.587785 },
{ -0.162460, -0.262866, 0.951056 },
{ 0.442863, -0.238856, 0.864188 },
{ 0.162460, -0.262866, 0.951056 },
{ 0.309017, -0.500000, 0.809017 },
{ 0.147621, -0.716567, 0.681718 },
{ 0.000000, -0.525731, 0.850651 },
{ 0.425325, -0.688191, 0.587785 },
{ 0.587785, -0.425325, 0.688191 },
{ 0.688191, -0.587785, 0.425325 },
{ -0.955423, 0.295242, 0.000000 },
{ -0.951056, 0.162460, 0.262866 },
{ -1.000000, 0.000000, 0.000000 },
{ -0.850651, 0.000000, 0.525731 },
{ -0.955423, -0.295242, 0.000000 },
{ -0.951056, -0.162460, 0.262866 },
{ -0.864188, 0.442863, -0.238856 },
{ -0.951056, 0.162460, -0.262866 },
{ -0.809017, 0.309017, -0.500000 },
{ -0.864188, -0.442863, -0.238856 },
{ -0.951056, -0.162460, -0.262866 },
{ -0.809017, -0.309017, -0.500000 },
{ -0.681718, 0.147621, -0.716567 },
{ -0.681718, -0.147621, -0.716567 },
{ -0.850651, 0.000000, -0.525731 },
{ -0.688191, 0.587785, -0.425325 },
{ -0.587785, 0.425325, -0.688191 },
{ -0.425325, 0.688191, -0.587785 },
{ -0.425325, -0.688191, -0.587785 },
{ -0.587785, -0.425325, -0.688191 },
{ -0.688191, -0.587785, -0.425325 } };

void Md2::LoadModel(const char* sFilename, const char* tFilename, const char* vShader, const char* fShader, Renderer * gameRenderer)
{
	FILE* fp;
	errno_t err;

	if ((err = fopen_s(&fp, sFilename, "rb") != 0))
	{
		//std::cout << "ERROR OPENING FILE -> " << sFilename << std::endl;
	}
	else
	{
		//std::cout << "DEBUG - 1" << std::endl;
		fread(&information, sizeof(Md2Values), 1, fp);

		char* buffer = new char[information.numFrames * information.frameSize];
		fseek(fp, information.ofsFrames, SEEK_SET);
		fread(buffer, sizeof(char), information.numFrames * information.frameSize, fp);

		//std::cout << "DEBUG - 2" << std::endl;
		vertices.resize(information.numFrames, std::vector<glm::vec3>(information.numVerts));
		normals.resize(information.numFrames, std::vector<int>(information.numVerts));

		for (int i = 0; i < information.numFrames; i++)
		{
			Md2Frame* frame_ptr = (Md2Frame*)&buffer[information.frameSize * i];

			for (int j = 0; j < information.numVerts; j++)
			{
				vertices[i][j].x = frame_ptr->translate[0] + (float(frame_ptr->verts[j].verts[0]) * frame_ptr->scale[0]);
				vertices[i][j].y = frame_ptr->translate[1] + (float(frame_ptr->verts[j].verts[1]) * frame_ptr->scale[1]);
				vertices[i][j].z = frame_ptr->translate[2] + (float(frame_ptr->verts[j].verts[2]) * frame_ptr->scale[2]);

				normals[i][j] = frame_ptr->verts[j].light;
			}
		}
		//std::cout << "DEBUG - 3" << std::endl;
		commands.resize(information.numCmds);
		fseek(fp, information.ofsCmds, SEEK_SET);
		fread(&commands[0], sizeof(int), information.numCmds, fp);

		int i = 0;
		int iTotalVertices = 0;

		//std::cout << "DEBUG - 4" << std::endl;
		vboFrameVertices.resize(information.numFrames);
		for (int i = 0; i < information.numFrames; i++)
		{
			vboFrameVertices[i].CreateBuffer();
		}
		vboTextureCoords.CreateBuffer();
		while (1)
		{
			int action = commands[i];
			if (action == 0)
				break;

			int renderMode = action < 0 ? GL_TRIANGLE_FAN : GL_TRIANGLE_STRIP;
			int numVertices = action < 0 ? -action : action;
			i++;

			renderModes.push_back(renderMode);
			numRenderVertices.push_back(numVertices);

			for (int j = 0; j < numVertices; j++)
			{
				float s = *((float*)(&commands[i++]));
				float t = *((float*)(&commands[i++]));
				t = 1.0f - t;
				int vi = commands[i++];

				vboTextureCoords.AddData(&s, 4);
				vboTextureCoords.AddData(&t, 4);

				for (int k = 0; k < information.numFrames; k++)
				{
					vboFrameVertices[k].AddData(&vertices[k][vi], 12);
					vboFrameVertices[k].AddData(&anorms[normals[k][vi]], 12);
				}
			}
		}
		
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		for (int i = 0; i < information.numFrames; i++)
		{
			vboFrameVertices[i].BindVBO();
			vboFrameVertices[i].UploadData(GL_STATIC_DRAW);
		}

		vboFrameVertices[0].BindVBO();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));

		vboTextureCoords.BindVBO();
		vboTextureCoords.UploadData(GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

		TextureLoader loader;
		textureId = TextureFromFile(tFilename);

		Shader s(vShader, fShader);
		shader = s;
	}
}


void Md2::RenderModel(Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::vec3 position, float rotation, float direction, Renderer * gameRenderer)
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
	model = glm::rotate(model, rotation, glm::vec3(1, 0, 0));
	model = glm::rotate(model, direction, glm::vec3(0, 0, 1));
	shader.setMat4("model", model);
	shader.setMat4("normal", model);

	glBindVertexArray(VAO);

	int iTotalOffset = 0;

	if (animState == NULL)
	{
		glEnableVertexAttribArray(0);
		vboFrameVertices[0].BindVBO();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
		shader.setFloat("fInterpolation", -1.0f);

		for (int i = 0; i < renderModes.size(); i++)
		{
			glDrawArrays(renderModes[i], iTotalOffset, numRenderVertices[i]);
			iTotalOffset += numRenderVertices[i];
		}
	}
	else
	{
		glEnableVertexAttribArray(0);
		vboFrameVertices[animState->currFrame].BindVBO();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

		glEnableVertexAttribArray(3);
		vboFrameVertices[animState->nextFrame].BindVBO();
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

		glEnableVertexAttribArray(2);
		vboFrameVertices[animState->currFrame].BindVBO();
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

		glEnableVertexAttribArray(4);
		vboFrameVertices[animState->nextFrame].BindVBO();
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

		shader.setFloat("fInterpolation", animState->interpol);
		for (int i = 0; i < renderModes.size(); i++)
		{
			glDrawArrays(renderModes[i], iTotalOffset, numRenderVertices[i]);
			iTotalOffset += numRenderVertices[i];
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Md2State Md2::StartAnimation(Md2Commands type)
{
	Md2State res;
	res.startFrame = animationList[type].startFrame;
	res.endFrame = animationList[type].endFrame;
	res.currFrame = animationList[type].startFrame;
	res.nextFrame = animationList[type].startFrame + 1;

	res.fps = animationList[type].fps;
	res.type = type;

	res.currTime = 0.0f;
	res.prevTime = 0.0f;

	res.interpol = 0.0f;

	return res;
}

void Md2::UpdateAnimation(Md2State* animState, float fTimePassed, Renderer* gameRenderer)
{
	animState->currTime += fTimePassed;

	if (animState->currTime - animState->prevTime > (1.0f / float(animState->fps)))
	{
		animState->prevTime = animState->currTime;

		animState->currFrame = animState->nextFrame;
		animState->nextFrame++;
		if (animState->nextFrame > animState->endFrame)
			animState->nextFrame = animState->startFrame;
	}

	animState->interpol = float(animState->fps) * (animState->currTime - animState->prevTime);
}

unsigned int Md2::TextureFromFile(std::string path)
{
	//auto filename = directory + "//" + path;

	stbi_set_flip_vertically_on_load(true);
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
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
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