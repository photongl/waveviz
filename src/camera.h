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

////////////////////////////////////////////////////////
// camera.h
//
// Contains declaration of the camera class
// This class will be used to set the MODELVIEW matrix.
////////////////////////////////////////////////////////

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "datastructs.h"

class CCamera
{
 public:
  Vector3d Eye;
  Vector3d Target;
  Vector3d UpVector;

 public:
  CCamera();
  ~CCamera();
  void SetEye (float x, float y, float z);
  void SetTarget (float x, float y, float z);
  void SetUpVector (float x, float y, float z);
};

#endif
