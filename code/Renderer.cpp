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

void Renderer::render(int scale, int xoff, int yoff){
	
	fillBuffer(BACKGROUND);
	
	for(int i = 0 ; i < object->getLineNumber(); i++){
		
		Object::Line line = object->getLine(i);
		
		int x0 = (line.start.x * scale) + xoff;
		int y0 = (line.start.y * scale) + yoff;
		int x1 = (line.end.x * scale) + xoff;
		int y1 = (line.end.y * scale) + yoff;
		
		drawLine(BLACK,x0,y0,x1,y1);
		
	}
	
}

int sign(int x){
	
	return (0<x) - (0>x);
	
}

void Renderer::drawLine(Colour colour, int x0, int y0, int x1, int y1){
	
	bool flip = abs(x1 - x0) < abs(y1 -y0);
	
	if(flip){
		
		int temp = x0;
		x0 = y0;
		y0 = temp;
		temp = x1;
		x1 = y1;
		y1 = temp;
		
	}
	
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

void Renderer::fillBuffer(Colour colour){
	
	Colour* pixel = (Colour*)buffer;
	
	for(int y = 0; y < height; y++){
		
		for(int x = 0; x < width; x++){
			
			*pixel = colour;
			pixel++;
			
		}
		
	}
	
}

//TODO prevent memeory access violation
void Renderer::plot(int x, int y, Colour colour){
	
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


