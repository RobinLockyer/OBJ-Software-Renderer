#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Object.h"
using namespace std;

Object::Object(char* fileLoc){
		
		//open file
		ifstream file(fileLoc);
		
		string line;
		string lineType;
		
		//count number of edges and vertices
		vertexNumber = 0;
		edgeNumber = 0;
		
		while(file.good()){
			
			//Get first token of line
			//This specifies what data is stored on the line
			
			file >> lineType;
			getline(file,line);
			
			if(!lineType.compare("v")){
				
				vertexNumber++;
				
			}
			else if(!lineType.compare("f")){
				
				edgeNumber += count(line.begin(), line.end(), ' ');
				
			}
			
		}
		
		//Reset file
		file.clear();
		file.seekg(0, ios::beg);
		
		//Allocate arrays
		vertices = new Vertex[vertexNumber];
		edges = new Edge[edgeNumber];
		
		int vertexCounter = 0;
		int edgeCounter = 0;
		
		while(file.good()){
			
			//Get the next line without advancing the stream position
			streampos position = file.tellg();
			getline(file,line);
			file.seekg(position);
			
			//Get first token of line
			//This specifies what data is stored on the line
			file >> lineType;
			
			string token;
			
			
			
			if(!lineType.compare("v")){
				
				file >> token;
				vertices[vertexCounter].x = atof(token.c_str());
				
				file >> token;
				vertices[vertexCounter].y = atof(token.c_str());
				
				file >> token;
				vertices[vertexCounter].z = atof(token.c_str());
				
				vertexCounter++;
				
			}
			else if(!lineType.compare("f")){
				//TODO: prevent repeated edges
				//Convert strings to integers
				int vertexNumber = count(line.begin(), line.end(), ' ');
				int* vertices = new int[vertexNumber];
				
				for(int i = 0; i < vertexNumber; i++){
					
					file >> token;
					vertices[i] = atoi(token.c_str()); 
					
				}
				
				//pair vertices to form edge
				
				for(int i = 0; i < vertexNumber; i++){
					
					edges[edgeCounter].start = vertices[i]-1;
					edges[edgeCounter].end = vertices[(i+1)%vertexNumber]-1;
					
					edgeCounter++;
					
				}
				delete vertices;
			}
			//Proceed to next line
			file.ignore(numeric_limits<streamsize>::max(),'\n');
		}
		
		file.close();
		
		//calculate sin/cos for the default angle
		setRotationAngle(M_PI/32.0);
	}

int Object::getLineNumber(){
	return edgeNumber;
}

Object::Line Object::getLine(int n){
	
	Edge edge = edges[n];
	
	return Line{
		vertices[edge.start],
		vertices[edge.end]
	};
	
}

void Object::setRotationAngle(double rotationAngle){
	
	this->rotationAngle = rotationAngle;
	sinResult = sin(rotationAngle);
	cosResult = cos(rotationAngle);
	
}

void Object::rotateX(){
	
	/* Matrix for rotation about X axis:
		1     0     0
		0     cos   -sin
		0     sin   cos
	*/
	
	for(int i = 0; i < vertexNumber; i++){
		
		Vertex initial = vertices[i];
		
		vertices[i].y = (initial.y * cosResult) - (initial.z * sinResult);
		vertices[i].z = (initial.y * sinResult) + (initial.z * cosResult);
		
	}
	
}

void Object::rotateY(){
	
	/* Matrix for rotation about Y axis:
		cos   0     sin
		0     1     0
		-sin  0     cos
	*/
	
	for(int i = 0; i < vertexNumber; i++){
		
		Vertex initial = vertices[i];
		
		vertices[i].x = (initial.x * cosResult) + (initial.z * sinResult);
		vertices[i].z = -(initial.x * sinResult) + (initial.z * cosResult);
		
	}
	
}

void Object::rotateZ(){
	
	/* Matrix for rotation about Z axis:
		cos   -sin  0
		sin   cos   0
		0     0     1
	*/
	
	for(int i = 0; i < vertexNumber; i++){
		
		Vertex initial = vertices[i];
		
		vertices[i].x = (initial.x * cosResult) - (initial.y * sinResult);
		vertices[i].y = (initial.x * sinResult) + (initial.y * cosResult);
		
	}
	
}