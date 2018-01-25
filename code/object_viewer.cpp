#include <windows.h>
#include "Object.h"
#include "Renderer.h"

Object* object;
const int CLIENT_WIDTH = 720;
const int CLIENT_HEIGHT = 720;
const char WINDOW_NAME[] = "ObjectViewer";
bool running = true;
int scale = 10;
int xoff = 360;
int yoff = 360;


LRESULT CALLBACK windowProc(
	HWND window, 
	UINT message, 
	WPARAM wParam, 
	LPARAM lParam){
		
    switch(message){
		
        case WM_CLOSE:
            running = false;
			break;
        case WM_DESTROY:
            running = false;
			break;
		
		case WM_QUIT:
			running = false;
			break;
		case WM_KEYDOWN:
			
			switch(wParam){
				
				case VK_OEM_4://[ key
					scale--;
					break;
				case VK_OEM_6://] key
					scale++;
					break;
				case 'W':
					yoff++;
					break;
				case 'S':
					yoff--;
					break;
				case 'A':
					xoff--;
					break;
				case 'D':
					xoff++;
					break;
				case 'H':
					object->rotateX();
					break;
				case 'J':
					object->rotateY();
					break;
				case 'L':
					object->rotateZ();
			}
			
			break;
        default:
            return DefWindowProc(window, message, wParam, lParam);
    }
    return 0;
}


//Equivalent of main() for win32 apps
int CALLBACK WinMain(
	HINSTANCE instance,
	HINSTANCE prevInstance,
	LPSTR commandline,
	int showCode){
	
	//Define WindowClass
	WNDCLASS windowClass = {};
	windowClass.style = 0;
	windowClass.lpfnWndProc = windowProc;
	windowClass.hInstance = instance;
	windowClass.lpszClassName = WINDOW_NAME;
	
	//Try to register WindowClass
	if(!RegisterClass(&windowClass)){
		
		MessageBox(0,"Error Registering Windowclass",
					"Error", MB_OK);
		
		return 0;
	}
	
	//Create a window
	HWND window = CreateWindowEx(
		
		0,
		WINDOW_NAME,
		WINDOW_NAME,
		((WS_OVERLAPPEDWINDOW&~WS_THICKFRAME)&~ WS_MAXIMIZEBOX)|WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CLIENT_WIDTH,
		CLIENT_HEIGHT,
		0,
		0,
		instance,
		0
	);
	
	//Test if CreateWindowEx has failed
	if(!window)
    {
        MessageBox(NULL, "Window Creation Failed", "Error",
            MB_OK);
        return 0;
    }
	
	//Create buffer for graphics
	
	char* buffer = new char[4*CLIENT_WIDTH*CLIENT_HEIGHT];
	
	BITMAPINFO bufferInfo = {};
	bufferInfo.bmiHeader.biSize = sizeof(bufferInfo.bmiHeader);
	bufferInfo.bmiHeader.biWidth = CLIENT_WIDTH;
	bufferInfo.bmiHeader.biHeight = CLIENT_HEIGHT;
	bufferInfo.bmiHeader.biPlanes = 1;
	bufferInfo.bmiHeader.biBitCount = 32;
	bufferInfo.bmiHeader.biCompression = BI_RGB;
	
	object = new Object(commandline);
	Renderer* renderer = new Renderer(
		object, 
		buffer,
		CLIENT_HEIGHT, 
		CLIENT_WIDTH);
	
	MSG message;
	
	
	
	while(running){
		
		//Process message queue
		while(PeekMessage(&message, window, 0, 0, PM_REMOVE)){
			
			TranslateMessage(&message);
            DispatchMessage(&message); //WndProc is called here
			
		}
		
		HDC deviceContext = GetDC(window);
		
		
		renderer->render(scale,xoff,yoff);
		
		StretchDIBits(
			deviceContext,
			0,
			0,
			CLIENT_WIDTH,
			CLIENT_WIDTH,
			0,
			0,
			CLIENT_WIDTH,
			CLIENT_HEIGHT,
			buffer,
			&bufferInfo,
			DIB_RGB_COLORS,
			SRCCOPY
			
		);
		
		ReleaseDC(window, deviceContext);
		
	}
	return 0;
}