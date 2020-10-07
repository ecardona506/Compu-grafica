#include "planta.h"

void planta::abrirMalla() {
    objmodel_ptr = NULL;
    if (!objmodel_ptr)
    {
        objmodel_ptr = glmReadOBJ("./modelos/planta1.obj");
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
