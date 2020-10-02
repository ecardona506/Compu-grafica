#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "glm.h"

class Maceta
{
	float x, y, z;
	GLMmodel* objmodel_ptr;
public:
	void abrirMalla();
	void dibujarMalla(float x, float y, float z);
};
