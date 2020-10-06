#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm.h"
#include <stdlib.h>
class jupiter
{
	GLMmodel* objmodel_ptr;
public:
	jupiter();
	void abrirMalla();
	void dibujarMalla(float x, float y, float z);
};

