#include <stdlib.h>
#include <math.h>
#include "Renderer.h"
#include "Object.h"



Renderer::Renderer(Object* object, Buffer buffer, int height, int width){
    
    this->object = object;
    this->buffer = buffer;
    this->height = height;
    this->width = width;
    
}

//Draws object to buffer
void Renderer::render(int scale, int xoff, int yoff){
    
    fillBuffer(BACKGROUND);
    
    //Draw each line in object
    for(int i = 0 ; i < object->getLineNumber(); i++){
        
        Object::Line line = object->getLine(i);
        
        int x0 = (line.start.x * scale) + xoff;
        int y0 = (line.start.y * scale) + yoff;
        int x1 = (line.end.x * scale) + xoff;
        int y1 = (line.end.y * scale) + yoff;
        
        drawLine(BLACK,x0,y0,x1,y1);
        
    }
    
}


//returns 1 if x>0, -1 if x<0, 0 otherwise
int sign(int x){
    
    return (0<x) - (0>x);
    
}

//Plots a line of specified colour from (x0, y0) to (x1, y1) using adaptation
// of Bresenham's line algorithm
void Renderer::drawLine(Colour colour, int x0, int y0, int x1, int y1){
    
    /*Algorithm only works for gradient magnitude of 1 or less
      To draw lines of gradient magnitude greater than 1, x and y must
      be swapped
     */
    bool flip = abs(x1 - x0) < abs(y1 -y0);
    
    if(flip){
        
        //swap x and y
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
        
    }
    
    //Get change in x and y
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    int xinc = sign(dx);
    int yinc = sign(dy);
    
    dx*=xinc;
    dy*=yinc;
    
    int d = 2*dy - dx;
    int y = y0;
    
    
    for(int x=x0;x!=x1;x+=xinc){
        
        if(!flip)
            plot(x, y, colour);
        else 
            plot(y,x,colour);
        if(d>0){
            y+=yinc;
            d -= dx;
        }
        
        d += dy;
        
    }
    
}

//Fills buffer with single colour
void Renderer::fillBuffer(Colour colour){
    
    Colour* pixel = (Colour*)buffer;
    
    for(int y = 0; y < height; y++){
        
        for(int x = 0; x < width; x++){
            
            *pixel = colour;
            pixel++;
            
        }
        
    }
    
}

//Sets the colour of pixel in buffer at (x,y)
void Renderer::plot(int x, int y, Colour colour){
    
    //TODO prevent memory access violation when plotting out of bounds
    
    Colour* pixel = (Colour*)buffer;
    pixel += x + (width * y);
    *pixel = colour;
    
}

void Renderer::drawTestPattern(){
    
    const double c = 2*3.141592653/32;
    for(int i = 0; i<32;++i){
        drawLine(BLACK, 360, 360, 100*cos(i*c)+360, 100*sin(i*c)+360 );
    }
    
}


