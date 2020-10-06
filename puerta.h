#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm.h"
#include <stdlib.h>
class puerta
{
	GLMmodel* objmodel_ptr;
public:
	puerta();
	void abrirMalla();
	void dibujarMalla(float x, float y, float z);
};

