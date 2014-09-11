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

/////////////////////////////////////////////////////////
// camera.C
//
// Contains the implementation of the camera class.
/////////////////////////////////////////////////////////

#include "camera.h"


//////////////
// Constructor
//////////////
CCamera::CCamera()
{
  this->SetEye (0, 0, 0);
  this->SetTarget (0, 0, -1000);
  this->SetUpVector (0, 1, 0);

}


//////////////
// Destructor
//////////////
CCamera::~CCamera()
{




}


////////////////////////////
// Sets the eye coordinates
////////////////////////////
void CCamera::SetEye (float x, float y, float z)
{
  this->Eye.x=x;
  this->Eye.y=y;
  this->Eye.z=z;
}

///////////////////////////////
// Sets the target coordinates
///////////////////////////////
void CCamera::SetTarget (float x, float y, float z)
{
  this->Target.x=x;
  this->Target.y=y;
  this->Target.z=z;
}

/////////////////////////////////
// Sets the up-vector components
/////////////////////////////////
void CCamera::SetUpVector (float x, float y, float z)
{
  this->UpVector.x=x;
  this->UpVector.y=y;
  this->UpVector.z=z;
}
  
