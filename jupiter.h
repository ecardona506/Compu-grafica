#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.h"
#include <stdlib.h>
class jupiter
{
	GLMmodel* objmodel_ptr;
public:
	jupiter();
	void abrirMalla(char* path);
	void dibujarMalla(float x, float y, float z);
};

