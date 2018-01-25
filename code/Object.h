#ifndef OBJECT_H
#define OBJECT_H

class Object{
	public:
		typedef struct{ double x,y,z;} Vertex;
		typedef struct{ Vertex start,end;} Line;
		Object(char*);
		Line getLine(int);
		int getLineNumber();
		void setRotationAngle(double);
		void rotateX();
		void rotateY();
		void rotateZ();
		
	private:
		typedef struct{ int start, end;} Edge;
		Vertex* vertices;
		Edge* edges;
		int vertexNumber, edgeNumber;
		float rotationAngle, sinResult, cosResult;
};



#endif