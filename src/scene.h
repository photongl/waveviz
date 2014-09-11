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

///////////////////////////////////////////////////////
// scene.h
//
// Contains the scene class declaration to be used for
// defining the scene along with its spatial structure
///////////////////////////////////////////////////////


#ifndef __SCENE_H__
#define __SCENE_H__

#include "datastructs.h"

class CScene
{
 public:
  // space-cell array
  Vector3d *m_vertices;
  
  // scene-cube divisions
  int m_xdivs;
  int m_ydivs;
  int m_zdivs;  

  // scene bounds
  int m_xsize;
  int m_ysize;
  int m_zsize;  
  
  // scene origin
  int m_xorg;
  int m_yorg;
  int m_zorg;
  
  // shader id
  int m_shaderid;
  
  // pdf data
  complex *m_data;
  
  float max;
  
  // cell parameters
  int m_cellresolution;
  int m_celldensity;
  int m_celloverlap;
  
  
 public:
	
	
	CScene();
	~CScene();
	void SetSceneBounds (int xsize,
			int ysize,
			int zsize);
	void SetSceneDivisions (int x, int y, int z);
	void SetSceneOrigin (int x, int y, int z);
	
	void InitScene (int shader_id);  
	void GenSpaceCells ();  
	
	void Display (int xstart, int xend,
		int ystart, int yend,
		int zstart, int zend,
		float start_threshold, float end_threshold);	

};

#endif
