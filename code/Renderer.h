#ifndef RENDERER_H
#define RENDERER_H
#include <stdint.h>
#include "Object.h"

typedef void* Buffer;
typedef int32_t Colour;
const Colour BACKGROUND = 0xf0f0f0;
const Colour BLACK = 0;

class Renderer{
	
public:
	Renderer(Object*, Buffer, int, int);
	void render(int,int,int);
private:
	Buffer buffer;
	Object* object;
	int height, width;
	void plot(int, int, Colour);
	void fillBuffer(Colour);
	void drawLine(Colour, int, int, int, int);
	void drawTestPattern();
};

#endif