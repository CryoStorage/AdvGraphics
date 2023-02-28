#include"VBO.h"

// Constructor de Vertex Buffer Object
VBO::VBO()
{
	glGenBuffers(1, &VBO);
}