/***********************************************************************************
	Copyright 2006. Akshay Mishra	

	This file is part of WaveVIZ.

	WaveVIZ is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	WaveVIZ is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with WaveVIZ; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
************************************************************************************/	

//////////////////////////////////////////////////////////////////
// application.C
//
// Contains the implementation of CApplication
//////////////////////////////////////////////////////////////////


#include "includeall.h"
#include "application.h"


// GLOBAL VARS
CRenderer* global_renderer=0;
CApplication* global_app=0;
double fps=75.0;


/*
//////////////////
// KeyBoardHandler
//////////////////
void KeyBoardFunc(unsigned char key, int x, int y)
{
	if (key==27)
		exit(0);
	if (key=='W' || key=='w')
	{
		global_renderer->m_camera->Eye.z-=3;
	}
	if (key=='S' || key=='s')
	{
		global_renderer->m_camera->Eye.z+=3;
	}  
	if (key=='P' || key=='p')
	{
		play=!play;
	}
	if (key=='C' || key=='c')
	{
		compute=!compute;
	}
	
	global_renderer->UpdateCamera();
	glutPostRedisplay();
}
*/

////////////////////////
// Handles timer event
///////////////////////
void TimerCallback (void* dummy)
{
	global_renderer->Animate ();
	Fl::repeat_timeout(1.0/fps, TimerCallback);	
}


//////////
// Render
//////////
void IdleFunc (void* dummy)
{
	global_app->make_current();
	global_renderer->Render();
	global_app->flush();		
}

///////////////////////
// Repaint method
///////////////////////
void CApplication::draw()
{	
	valid();
	m_renderer->Render();
}


//////////////////
// Event handler
//////////////////
int CApplication::handle(int event) 
{
	switch(event) 
	{
		default:
			return Fl_Gl_Window::handle(event);
	}
}


///////////////
// Constructor
///////////////
CApplication::CApplication(int X, int Y, int W, int H, const char *L)
	: Fl_Gl_Window(X, Y, W, H, L)
{
	global_app=this;
	m_ready=false;
}


/////////////////////////
// Conrtuctor (overload)
/////////////////////////
CApplication::CApplication(int X, int Y, int W, int H)
	: Fl_Gl_Window(X, Y, W, H)
{
	global_app=this;
	m_ready=false;
}


///////////////
// Init OpenGL
///////////////
void CApplication::InitApplication (PCOMPFUNC ptr)
{
	// set window parameters
	global_renderer=this->m_renderer=new CRenderer();  
	
	// check for GL extensions
	glewInit();
	if (GLEW_VERSION_2_0)
		printf("OpenGL 2.0 available...using shaders\n");
	else
	{
		printf("OpenGL 2.0 not supported...Quitting\n");
		exit(1);
	}   
	
	// init renderer and other classes
	this->m_renderer->InitRenderer(ptr);	
	m_ready=true;
	
	// start timer and idle loop
	Fl::add_idle (IdleFunc);
	Fl::add_timeout(1.0/fps, TimerCallback);	
}


/////////////////////////////////////////////
// Set the compute function for the renderer
/////////////////////////////////////////////
void CApplication::setComputeFunc (PCOMPFUNC ptr)
{
	m_renderer->m_compute->setComputeFunction (ptr);	
}


//////////////
// Destructor
//////////////
CApplication::~CApplication()
{
 	delete m_renderer;
}


