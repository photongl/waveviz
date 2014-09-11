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

///////////////////////////////////////////////////////////////
// renderer.h
//
// Contains declaration for the Renderer class
///////////////////////////////////////////////////////////////


#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "includeall.h"
#include "camera.h"
#include "scene.h"
#include "compute.h"
#include "textfile.h"


class CRenderer
{

 private:

 public:
	CCamera* m_camera;
	CScene* m_scene;
	CCompute* m_compute;
	GLuint v, f, p;
	float m_startdensity, m_enddensity;
	int m_cubesize;

 public:
	int t;
	float theta, phi;
	bool compute;	
	CRenderer();
	~CRenderer();
	void Render();
	void Animate();
	void InitRenderer(PCOMPFUNC);
	void UpdateCamera();
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog (GLuint obj);
	void setShaders(char* vsFileName, char* fsFileName);
	void UpdateFPS();
	void setPhaseCalcState (int compute);
};



#endif
