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

//////////////////////////////////////////////////////////
// renderer.C
//
// Contains an implementation of the renderer class
//////////////////////////////////////////////////////////


#include "includeall.h"
#include "renderer.h"

using namespace std;

// shader var pointers
int loc_time=0;		// time
int loc_eye=0;		// eye coordinates
int loc_compute=0;	// compute bool var



///////////////
// Constructor
///////////////
CRenderer::CRenderer()
{
	this->m_camera = new CCamera();
	this->p=this->v=0;
	this->f=0;
	this->theta=this->phi=0;
	this->compute=false;
	
	// set start and end density and compute region size
	m_startdensity=10.0f;
	m_enddensity=40.0f;
	m_cubesize=20;  
}



///////////////////////
// Main drawing method
///////////////////////
void CRenderer::Render()
{	
	// clear screen
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	/** start drawing **/		
	
	glPushMatrix();
	{
		
				
		glRotatef (theta, 0, 1, 0);
		glRotatef (phi, 1, 0, 0);
		// draw the axes
		glUseProgram (0);		
		glBegin (GL_LINES);
		{
			glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
			glVertex3i (0, 0, 0);
			glVertex3i (500, 0, 0);
			glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
			glVertex3i (0, 0, 0);
			glVertex3i (0, 500, 0);
			glColor4f (0.0f, 1.0f, 1.0f, 1.0f);
			glVertex3i (0, 0, 0);
			glVertex3i (0, 0, 500);
		}
		glEnd();
		glUseProgram (p);
		
		// draw the particle system
		m_scene->Display (-m_cubesize, m_cubesize, 
				   -m_cubesize, m_cubesize, 
				   -m_cubesize, m_cubesize, 
				   m_startdensity, m_enddensity);		
	}	
	glPopMatrix();
	this->UpdateCamera();
	
	/** end drawing **/
	
	glFlush();
	UpdateFPS();			
}


///////////
// Animate
///////////
void CRenderer::Animate()
{		
	// compute data
	if (compute)
	{
		t++;
		
		m_compute->Compute (-m_cubesize, m_cubesize, 
				     -m_cubesize, m_cubesize, 
				     -m_cubesize, m_cubesize, 
				     t, m_scene->m_data);
		
		glUniform1f (loc_time, t);			
	}	
}



////////////////////////////
// Initlialize the renderer
////////////////////////////
void CRenderer::InitRenderer(PCOMPFUNC ptr)
{  
	// set shaders
	setShaders("minimal2.vert", "ray.frag");
	
	// set var pointers
	loc_time=glGetUniformLocation (p, "time");
	loc_eye=glGetUniformLocation (p, "eye_pos");
	loc_compute=glGetUniformLocation (p, "compute_data");
	
	// set the compute var for the frag shader
	setPhaseCalcState (1);
	
	// set state vars
	glEnable (GL_DEPTH_TEST);
	//glEnable (GL_VERTEX_PROGRAM_TWO_SIDE);	
	glPointSize (1.2f);
	
	// set blending parameters
	
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	// set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (90.0, 1.0, 1.0, 2500.0);
	
	glClearColor (0.0, 0.0, 0.0, 0.0);	
	
	// set up scene
	m_scene = new CScene();
	m_scene->InitScene(p);
	m_compute = new CCompute(m_scene);
	m_compute->setComputeFunction (ptr);
	m_compute->Compute (-m_cubesize, m_cubesize, 
			     -m_cubesize, m_cubesize, 
			     -m_cubesize, m_cubesize, 
			     0, m_scene->m_data);
	
	// set camera
	this->UpdateCamera();  
}



///////////////////////////////////
// sets whether the phase will be 
// calculated on the GPU
// or will be provided by the CPU
///////////////////////////////////
void CRenderer::setPhaseCalcState (int compute)
{
	glUniform1i (loc_compute, compute);
}




///////////////////////////////////
// Sets the Modelview matrix
// according to the camera details
///////////////////////////////////
void CRenderer::UpdateCamera()
{
	if (m_camera->Eye.z>2000) m_camera->Eye.z=2000;
	if (m_camera->Eye.z<-500) m_camera->Eye.z=-500;
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();	
	gluLookAt (m_camera->Eye.x, m_camera->Eye.y, m_camera->Eye.z,
		m_camera->Target.x, m_camera->Target.y, m_camera->Target.z,
		m_camera->UpVector.x, m_camera->UpVector.y, m_camera->UpVector.z);  
	
	// pass eye coordinates to shader
	glUniform3f (loc_eye, m_camera->Eye.x, m_camera->Eye.y, m_camera->Eye.z);
}
  


///////////////
// Destructor
///////////////
CRenderer::~CRenderer()
{

	delete m_camera;
	delete m_compute;
	delete m_scene;

}



///////////////
// Update FPS
///////////////
void CRenderer::UpdateFPS()
{
	/*
	glUseProgram (0);
	
	static long frameBase=0;
	static long frameRate=0;
	static long frames=0;
	
	long now = glutGet(GLUT_ELAPSED_TIME);
	if((now - frameBase) >= 250)
	{
	frameBase = now;
	frameRate = 4*frames;
	frames = 0;
	}
	
	frames++;
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
	
	//invert the y axis
	glScalef(1, -1, 1);
	
	// actually move the origin to the top left corner
	glTranslatef(0, -glutGet(GLUT_WINDOW_HEIGHT), 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0, 0.7f, 0.7f);
	glRasterPos2f(10, 20);
	
	// concatenate
	string text = "Framerate: ";
	char number[10];
	sprintf(number, "%i fps t=%i", frameRate, t);
	text.append(number);	
	int i;
	
	// print framerate
	
	for(i=0; i<text.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	}  
	
		
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glUseProgram (p);
	
	glFlush();
	*/
}



/////////////////////////////
// print GL shader link log
/////////////////////////////
void CRenderer::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
	
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
		free(infoLog);
	}
}




////////////////////////////////
// print GL shader compile  log 
////////////////////////////////
void CRenderer::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
	
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
		free(infoLog);
	}
}



////////////////
// Set Shaders
////////////////
void CRenderer::setShaders(char* vsFileName, char* fsFileName)
{

	char *vs = NULL,*fs = NULL,*fs2 = NULL;
	
	printf ("Setting shaders...\n");
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
		
	vs = textFileRead(vsFileName);
	fs = textFileRead(fsFileName);
	
	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	printShaderInfoLog(v);
	printShaderInfoLog(f);
	
	p = glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);

	glLinkProgram(p);
	printProgramInfoLog(p);

	glUseProgram(p);
}
