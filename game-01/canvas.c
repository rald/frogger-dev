#include "canvas.h"

extern gl2dRGBA palette[];

Canvas* CanvasLoad(char *filename) {
    Canvas* canvas=malloc(sizeof(*canvas));

    int ch,i,j,k;
    FILE *fp = fopen(filename,"r");
    
    char *hex="0123456789ABCDEF";

    fscanf(fp,"%d %d %d %d",&canvas->w,&canvas->h,&canvas->frames,&canvas->transparent);
    canvas->pixels=malloc(sizeof(*canvas->pixels)*canvas->frames*canvas->w*canvas->h);
    
    i=0;
    while((ch=fgetc(fp))!=EOF) {
        j=-1;
        for(k=0;k<16;k++) {
            if(ch==hex[k]) {
                j=k;
                break;
            }
        }
        if(j!=-1) {
            canvas->pixels[i++]=j;
        }
    }
    
    fclose(fp);
    
    return canvas;
}

void CanvasDraw(Canvas *canvas,int x,int y,int frame,int size) {
    int i,j,k;
    for(j=0;j<canvas->h;j++) {
        for(i=0;i<canvas->w;i++) {
            k=canvas->pixels[frame*canvas->w*canvas->h+j*canvas->w+i];
            if(k!=canvas->transparent) {
                gl2dSetColor(palette[k]);
                gl2dSetPixel(x+i*size,y+j*size,size);
            }
        }
    }
}

