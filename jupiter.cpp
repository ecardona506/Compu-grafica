#include "jupiter.h"


jupiter::jupiter() {}

void jupiter::abrirMalla() {
    objmodel_ptr = NULL;
    if (!objmodel_ptr)
    {
        objmodel_ptr = glmReadOBJ("./modelos/jupiter1.obj");
        if (!objmodel_ptr)
            exit(0);

        glmUnitize(objmodel_ptr);
        glmFacetNormals(objmodel_ptr);
        glmVertexNormals(objmodel_ptr, 90.0);
    }
}
void jupiter::dibujarMalla(float x, float y, float z, GLuint texid) {
        glPushMatrix();
        glTranslatef(x, y, z);
        glBindTexture(GL_TEXTURE_2D, texid);
        glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

}