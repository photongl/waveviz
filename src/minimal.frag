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

// fragment shader for coloring the pointcloud representation

// uniform vars
uniform vec3 eye_pos;

// varying vars
varying vec3 frag_wavefunc;

void main()
{	
	float red=0.0, green=0.0, blue=0.0;
	
	red = (atan(frag_wavefunc.y, frag_wavefunc.x)+3.14)/3.14;		
	
	
	// map phase onto red-blue spectrum	
	if (red>1.0) 
	{		
		red=2.0-red;
		if (red<0.5)
			green=red*2.0;
		else
			green=(1.0-red)*2.0;
	}
		
	blue=1.0-red;
	
	// write frag color
	gl_FragColor = vec4 (red, green, blue, frag_wavefunc.z);
	
}
