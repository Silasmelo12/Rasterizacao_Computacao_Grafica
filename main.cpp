#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
    //*************************************************************************
    // Chame aqui as funções do mygl.h
    //*************************************************************************
    color c;
    for(int i = 0; i<IMAGE_HEIGHT; i+=10)
    {
        for(int j = 0; j<IMAGE_WIDTH; j+=10  )
        {
            c.R = j/2;
            c.G = i/2;
            c.B = i+j/4;
            c.A = i+j/1030;

            PutPixel(i,j,c);
        }
    }


}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // Inicializações.
    InitOpenGL(&argc, argv);
    InitCallBacks();
    InitDataStructures();

    // Ajusta a função que chama as funções do mygl.h
    DrawFunc = MyGlDraw;

    // Framebuffer scan loop.
    glutMainLoop();

    return 0;
}

