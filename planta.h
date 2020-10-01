#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.h"
#include <stdlib.h>
class planta
{
	GLMmodel* objmodel_ptr;
public:
	planta();
	void abrirMalla(char* path);
	void dibujarMalla(float x, float y, float z);
};

