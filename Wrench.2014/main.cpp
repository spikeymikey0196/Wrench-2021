#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GLee.h"

#include <gl/gl.h>
#include <gl/glu.h>

#include "SOIL.h"
#include "tinyxml.h"

#include "Scene.h"
#include "MainMenuScene.h"

#include "Wrench.h"

using namespace Wrench;

struct Globals
{
    HINSTANCE hInstance;
    HWND hwnd;
    HDC   hdc;
    HGLRC hglrc;
    int width, height;
};

Globals g;

unsigned int lastFrame = 0;



LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );
void shutdown();
void init(HINSTANCE hInstance);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{
	init(hInstance);
	Wrench::Init(800, 600);

	//temp
	lastFrame = timeGetTime();
	Wrench::PushScene(new MainMenuScene());
	//end temp

    MSG msg;

    while( 1 )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if( msg.message == WM_QUIT )
            {
                break;
            }
            
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			unsigned int currentTime = timeGetTime();
			
			if(currentTime >= lastFrame + 15)
			{
				Wrench::Update(currentTime - lastFrame);
				Wrench::Render();

				lastFrame = currentTime;
			}
        }
    }

	shutdown();
    return msg.wParam;
}



void Windows_SetWindowTitle(const char *text)
{
	SetWindowText(g.hwnd, text);
}



void init(HINSTANCE hInstance)
{
	g.hInstance = hInstance;
    WNDCLASS wc;
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );         
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );     
    wc.hInstance = hInstance;         
    wc.lpfnWndProc = WndProc;         
    wc.lpszClassName = TEXT("Wrench");
    wc.lpszMenuName = 0; 
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClass(&wc);
    
    RECT rect;
    SetRect( &rect, 50,
                    50,
                    850,
                    650 );
    
    g.width = rect.right - rect.left;
    g.height = rect.bottom - rect.top;
    
    AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );

    g.hwnd = CreateWindow(TEXT("Wrench"),
                          TEXT("GL WINDOW!"),
                          WS_OVERLAPPEDWINDOW,
                          rect.left, rect.top,  // adjusted x, y positions
                          rect.right - rect.left, rect.bottom - rect.top,  // adjusted width and height
                          NULL, NULL,
                          hInstance, NULL);

    if( g.hwnd == NULL )
    {
        FatalAppExit( NULL, TEXT("CreateWindow() failed!") );
    }

    ShowWindow( g.hwnd, 1 );

    g.hdc = GetDC( g.hwnd );

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
};


    int chosenPixelFormat = ChoosePixelFormat( g.hdc, &pfd );

    if( chosenPixelFormat == 0 )
    {
        FatalAppExit( NULL, TEXT("ChoosePixelFormat() failed!") );
    }

    int result = SetPixelFormat( g.hdc, chosenPixelFormat, &pfd );

    if (result == NULL)
    {
        FatalAppExit( NULL, TEXT("SetPixelFormat() failed!") );
    }

    g.hglrc = wglCreateContext( g.hdc );

    wglMakeCurrent( g.hdc, g.hglrc );

	glClearDepth(1.0f);									// Depth Buffer Setup
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void shutdown()
{
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( g.hglrc );
    ReleaseDC( g.hwnd, g.hdc );
    AnimateWindow( g.hwnd, 200, AW_HIDE | AW_BLEND );
}

//extern access from camera
void WinSwapBuffer()
{
	SwapBuffers(g.hdc);
}

LRESULT CALLBACK WndProc(   HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) 
{
	Scene *scene = Wrench::CurrentScene();

    switch( message )
    {
    case WM_CREATE:
        return 0;
        break;

    case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint( hwnd, &ps );
            EndPaint( hwnd, &ps );
        }
        return 0;
        break;

    case WM_KEYDOWN:
		if(!(lparam & (1 << 30)))
			if(scene) scene->KeyDown(wparam);
		return 0;
		break;

	case WM_LBUTTONDOWN:
		if (scene) scene->MouseButtonDown(LOWORD(lparam), g.height - HIWORD(lparam));
		break;

	case WM_LBUTTONUP:
		if (scene) scene->MouseButtonUp(LOWORD(lparam), g.height - HIWORD(lparam));
		break;

	case WM_MOUSEMOVE:
		if (scene) scene->MouseMotion(LOWORD(lparam), g.height - HIWORD(lparam));
		break;

    case WM_KEYUP:
		if(scene) scene->KeyUp(wparam);
		return 0;
		break;

    case WM_DESTROY:
        PostQuitMessage( 0 ) ;
        return 0;
        break;

	case WM_SIZE:
		g.width = LOWORD(lparam);
		g.height = HIWORD(lparam);

		if (scene) scene->Resize(g.width, g.height);
		break;

	default: break;
    }
 
    return DefWindowProc( hwnd, message, wparam, lparam );
}
