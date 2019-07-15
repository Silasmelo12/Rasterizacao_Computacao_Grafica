#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

typedef struct{
    float R;
    float G;
    float B;
    float A;
}tColor;

tColor cor = {255, 0, 0, 255};
tColor cor1 = {0, 255, 0, 255};
tColor cor2 = {0, 0, 255, 255};

void PutPixel(int x, int y,tColor *c0){
    if(x<0||y<0||x>IMAGE_WIDTH||y>IMAGE_HEIGHT){
        return;
    }
    else{
        int offset = 4*(x+y*IMAGE_WIDTH);
        FBptr[offset]   = c0->R;
        FBptr[offset+1] = c0->G;
        FBptr[offset+2] = c0->B;
        FBptr[offset+3] = c0->A;
    }
}

void Troca(int *x0, int *y0, int *x1, int *y1){
    int aux;

    aux = *x0;
    *x0 = *x1;
    *x1 = aux;

    aux = *y0;
    *y0 = *y1;
    *y1 = aux;
}

void TrocaCoordenadas(int *x1, int *y1, int *x2, int *y2){

    int aux;
    aux = *x1;
    *x1 = *y1;
    *y1 = aux;

    aux = *x2;
    *x2 = *y2;
    *y2 = aux;
}

void DrawLine(int x0, int y0, int x1, int y1,tColor *c0, tColor *c1){
    int dx,dy;
    float a, b, c;
    float dr = c1->R - c0->R;
    float dg = c1->G - c0->G;
    float db = c1->B - c0->B;

    if(x0 > x1){
        Troca(&x0,&y0,&x1,&y1);
        dx = x1 - x0;
        dy = y1 - y0;
    }
    else{
        dx = x1 - x0;
        dy = y1 - y0;
    }
    if(dx==0 && dy==0){
        PutPixel(x0,y0,c0);
        return;
    }
    if(dx==0 && dy!=0){
        a = (float)dr/dy;
        b = (float)dg/dy;
        c = (float)db/dy;

        if(dy>0){
            for(y0;y0<=y1;y0++){
                c0->R +=a;
                c0->G +=b;
                c0->B +=c;

                PutPixel(x0,y0,c0);
            }
        }
        else{
            for(y0;y0>=y1;y0--){
                c0->R +=a;
                c0->G +=b;
                c0->B +=c;

                PutPixel(x0,y0,c0);
            }
        }
        return;
    }
    if(dy==0 && dx!=0){
        a = (float)dr/dx;
        b = (float)dg/dx;
        c = (float)db/dx;

        for(x0;x0<=x1;x0++){
            c0->R +=a;
            c0->G +=b;
            c0->B +=c;

            PutPixel(x0,y0,c0);
        }
        return;
    }
    if((dx!=0)&&(dy!=0)){
        int D,E,NE;
        bool cod;
        float m = (float)dy/dx;

        if(abs(dx)>=abs(dy)){
            if(dy<0){
                dy = -dy;
            }
            D = 2*dy - dx;
            E = 2*dy;
            NE = 2*dy - 2*dx;
        }
        else{
            cod = true;

            TrocaCoordenadas(&x0,&y0,&x1,&y1);
            if(x0>x1){
                Troca(&x0,&y0,&x1,&y1);
                dx = x1 - x0;
                dy = y1 - y0;
            }
            else{
                dx = x1 - x0;
                dy = y1 - y0;
            }
            if(dy<0){
                dy = -dy;
            }
            D = 2*dy - dx;
            E = 2*dy;
            NE = 2*dy - 2*dx;
        }
        a = (float)dr/dx;
        b = (float)dg/dx;
        c = (float)db/dx;

        while(x0<x1){
            c0->R +=a;
            c0->G +=b;
            c0->B +=c;

            if(D<=0){
                D+= E;
                x0++;
            }
            else{
                D+= NE;
                x0++;

                if(m<0){
                    y0--;
                }
                else
                    y0++;
            }
            if(cod){
                TrocaCoordenadas(&x0,&y0,&x1,&y1);
                PutPixel(x0,y0,c0);
                TrocaCoordenadas(&x0,&y0,&x1,&y1);
            }
            else{
                PutPixel(x0,y0,c0);
            }
        }
    }
}

void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, tColor *c0, tColor *c1, tColor *c2){
    tColor aux1 = {c0->R, c0->G, c0->B, c0->A};
    tColor aux2 = {c1->R, c1->G, c1->B, c1->A};
    tColor aux3 = {c2->R, c2->G, c2->B, c2->A};

    DrawLine(x0,y0,x1,y1,&aux1,&aux2);

    aux1.R = c0->R;
    aux1.G = c0->G;
    aux1.B = c0->B;
    aux1.A = c0->A;

    aux2.R = c1->R;
    aux2.G = c1->G;
    aux2.B = c1->B;
    aux2.A = c1->A;

    DrawLine(x1,y1,x2,y2,&aux2,&aux3);

    aux2.R = c1->R;
    aux2.G = c1->G;
    aux2.B = c1->B;
    aux2.A = c1->A;

    aux3.R = c2->R;
    aux3.G = c2->G;
    aux3.B = c2->B;
    aux3.A = c2->A;

    DrawLine(x2,y2,x0,y0,&aux3,&aux1);


}

#endif // _MYGL_H_


