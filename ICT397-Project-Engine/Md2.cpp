#include "Md2.h"

Md2State Md2::animationList[21] =
{
	// first, last, fps
	{   0,  39,  9 },
	{  40,  45, 10 },
	{  40,  45,  7 },
	{  46,  53,  8 },
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
	{ 183, 183,  7 },
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
	"Death",
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

#if _WIN32
    if((err = fopen_s(&fp, sFilename, "rb") != 0))
    {
        std::cout << "ERROR OPENING FILE -> " << sFilename << std::endl;
    }
#elif __APPLE__

    fp = fopen(sFilename, "rb");
    if (fp == nullptr)
    {
        std::cout << "ERROR OPENING FILE -> " << sFilename << std::endl;
    }
#endif
	else
	{
		fread(&information, sizeof(Md2Values), 1, fp);
		char* buffer = new char[information.numFrames * information.frameSize];
		fseek(fp, information.ofsFrames, SEEK_SET);
		fread(buffer, sizeof(char), information.numFrames * information.frameSize, fp);
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
			}
		}
		commands.resize(information.numCmds);
		fseek(fp, information.ofsCmds, SEEK_SET);
		fread(&commands[0], sizeof(int), information.numCmds, fp);

		number = gameRenderer->LoadModel(information.numFrames, commands, VAO, anorms, vertices, normals);
		TextureLoader loader;
		textureId = TextureFromFile(tFilename);

		Shader s(vShader, fShader);
		shader = s;

		delete[]buffer;
	}
}


void Md2::RenderModel(Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::vec3 position, glm::vec3 rotation, float direction, Renderer * gameRenderer)
{
	gameRenderer->RenderModel(number, animState, proj, view, position, rotation, direction, VAO, textureId, shader);
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
        if(Debugger::GetInstance()->debugToConsole) std::cout << "Texture loaded" << std::endl;
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}