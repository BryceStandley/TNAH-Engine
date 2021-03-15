#include "Model.h"
Model::Model(std::string modelName, std::string vertShader, std::string fragShader)
{
	buffer = new GlewBuffer();
	shader = new GlewShader("Hi", "hi");
}
Model::~Model()
{

}