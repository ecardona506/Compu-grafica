#include "planta.h"

planta::planta() {}

void planta::abrirMalla(char* path) {
    objmodel_ptr = NULL;
    if (!objmodel_ptr)
    {
        objmodel_ptr = glmReadOBJ(path);
        if (!objmodel_ptr)
            exit(0);

        glmUnitize(objmodel_ptr);
        glmFacetNormals(objmodel_ptr);
        glmVertexNormals(objmodel_ptr, 90.0);
    }
}
void planta::dibujarMalla(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();

}
