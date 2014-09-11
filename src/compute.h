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

//////////////////////////////////////////////////////////////
// compute.h
// Computes the data for the volume to be rendered.
//////////////////////////////////////////////////////////////

#ifndef __COMPUTE_H__
#define __COMPUTE_H__


#include "scene.h"

typedef complex (*PCOMPFUNC) (int, int, int, int);

class CCompute
{

public:
	CScene *m_scene;
	PCOMPFUNC m_ptr;
	
	CCompute (CScene *scene);
	
	float Compute (int xstart, int xend,
			int ystart, int yend,
			int zstart, int zend,
			int time, complex *m_data);
	complex FuncDef (int x, int y, int z, int t);
	void setComputeFunction (PCOMPFUNC ptr);
};

#endif
