#include "puerta.h"

puerta::puerta() {}

void puerta::abrirMalla() {
    objmodel_ptr = NULL;
    if (!objmodel_ptr)
    {
        objmodel_ptr = glmReadOBJ("./modelos/D3 Alpha Lab door.obj");
        if (!objmodel_ptr)
            exit(0);

        glmUnitize(objmodel_ptr);
        glmFacetNormals(objmodel_ptr);
        glmVertexNormals(objmodel_ptr, 90.0);
    }
}
void puerta::dibujarMalla(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glmDraw(objmodel_ptr, GLM_SMOOTH);
    glPopMatrix();

}
