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

// vertex shader for coloring/billboarding fog representation

uniform vec3 abs_pos;
uniform vec3 eye_pos;
uniform int compute_data;


// varying vars
varying vec3 vabs_pos;


void main()
{	
	// transfer pos data to frag shader
	vabs_pos=abs_pos;
	
	// billboard rotation
	mat4 mat_billboard = gl_ModelViewMatrix;
	
	// remove previous rotations/scalings
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			if (i==j) 
				mat_billboard[i][j]=1.0;
			else
				mat_billboard[i][j]=0.0;
		}
	}
	
	
	
	// write vertex position
	gl_TexCoord[0] = gl_MultiTexCoord0;	
	gl_Position=gl_ProjectionMatrix*mat_billboard*gl_Vertex;
	//gl_Position=ftransform();
	
	// pass color data to frag shader
	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;
	
	
	
}
