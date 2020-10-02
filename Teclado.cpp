#include "Teclado.h"

void Teclado::abrirMalla() {
    this->objmodel_ptr = NULL;
    if (!this->objmodel_ptr)
    {
        this->objmodel_ptr = glmReadOBJ("./modelos/paneles.obj");
        if (!objmodel_ptr)
            exit(0);
        glmUnitize(this->objmodel_ptr);
        glmFacetNormals(this->objmodel_ptr);
        glmVertexNormals(this->objmodel_ptr, 90.0);
    }
}

void Teclado::dibujarMalla(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    glPushMatrix();
    glTranslatef(x, y, z);
    glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}