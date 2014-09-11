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

/////////////////////////// 
// Ray tracing frag shader
///////////////////////////


// uniform vars
uniform float cell_dims;
uniform float time;


float psi_real=0.0;
float psi_imag=0.0;

// calculates alpha
float getAlpha (float x, float y, float z, bool compute)
{
	float retval=0.0;
	
	if (compute)
	{
		
		// wave functions and morphing time
		float psi_1_real=0.0, psi_2_real=0.0, psi_target_real=0.0;
		float psi_1_imag=0.0, psi_2_imag=0.0, psi_target_imag=0.0;
		float psi_1=0.0, psi_2=0.0, psi_target=0.0;
		int morph_time=1000;
		
		float t=0.0;
		int itime=time;
	
		// particel in a box
		float nx=2.0, ny=1.0, nz=3.0;	
		float E1=0.0, E2=0.0, Etarget=0.0;
		float Lx=600.0, Ly=400.0, Lz=200.0;
	
		if (abs(x)<Lx/2.0 && abs(y)<Ly/2.0 && abs(z)<Lz/2.0)
		{
			E1=1000.0*((nx/Lx)*(nx/Lx)+(ny/Ly)*(ny/Ly)+(nz/Lz)*(nz/Lz));
			E2=1000.0*((ny/Lx)*(ny/Lx)+(nx/Ly)*(nx/Ly)+(nz/Lz)*(nz/Lz));
			Etarget = 1000.0*((ny/Lx)*(ny/Lx)+(ny/Ly)*(ny/Ly)+(ny/Lz)*(ny/Lz));
		
			// calculate mrphin factor
			t=itime;//%morph_time;
			t/=morph_time;
			if (t>1.0) t=1.0;
		
				
			// compute the PDF at a given point
			psi_1 = sqrt (2.0/Lx)*cos (nx*3.141592*x/Lx)
					*sqrt (2.0/Ly)* cos (ny*3.141592*y/Ly)
					*sqrt (2.0/Lz)* cos (nz*3.141592*z/Lz);
			psi_1_imag = psi_1*sin(E1*time);
			psi_1_real = psi_1*cos(E1*time);
					
			psi_2 = sqrt (2.0/Lx)*cos (ny*3.141592*x/Lx)
					*sqrt (2.0/Ly)* cos (nx*3.141592*y/Ly)
					*sqrt (2.0/Lz)* cos (nz*3.141592*z/Lz);
			psi_2_imag = psi_2*sin(E2*time);
			psi_2_real = psi_2*cos(E2*time);
					
			psi_target=sqrt (2.0/Lx)*cos (ny*3.141592*x/Lx)
					*sqrt (2.0/Ly)* cos (ny*3.141592*y/Ly)
					*sqrt (2.0/Lz)* cos (ny*3.141592*z/Lz);
			psi_target_imag=psi_target*sin (Etarget*time);
			psi_target_real=psi_target*cos (Etarget*time); 
					
									
			psi_real = (1.0-t)*(psi_1_real+psi_2_real)
					+t*(psi_target_real);
			psi_imag = (1.0-t)*(psi_1_imag+psi_2_imag)
					+t*(psi_target_imag);
			
			retval=10000000.0*(psi_real*psi_real+psi_imag*psi_imag);
			
		}
		else
		{
			retval=0.0;
		}		
	}
	else
	{
		
	}	
	
	return retval;
}


void main()
{	
	// translation vector
	
	vec4 quad2model_trans = vec4(gl_ModelViewMatrix[3][0],
				     gl_ModelViewMatrix[3][1],
				     gl_ModelViewMatrix[3][2],
				     0.0);
						     
	
	// no of steps per ray
	float n=100.0, cell_size=cell_dims;
	
	
	// radius of cell-sphere and half-diagonal of face
	float radius = sqrt (3.0*cell_size*cell_size)/2.0;
	float half_diag = sqrt (2.0*cell_size*cell_size)/2.0;
	
	// get the eye-coordinates of the fragment
	vec2 quad_pos = vec2 (gl_TexCoord[0].s*half_diag,
			      gl_TexCoord[0].t*half_diag);
	float zi=sqrt (radius*radius-quad_pos.x*quad_pos.x);
	
	// get calc-space coords of ray start and ray end
	vec3 A = vec3(gl_ModelViewMatrixInverse*(vec4 (quad_pos, -zi, 1.0)+quad2model_trans));
	vec3 B = vec3(gl_ModelViewMatrixInverse*(vec4 (quad_pos, zi, 1.0)+quad2model_trans));
	
	// steps for incrementing the coordinates along the ray
	float xstep=(B.x-A.x)/n;
	float ystep=(B.y-A.y)/n;
	float zstep=(B.z-A.z)/n;
	
	float x=A.x, y=A.y, z=A.z;
	float alpha = 0.0;
	
	// start accumulating alpha along the ray
	for (int i=0; i<n; i++)
	{
		// stop calculating if the fragment becomes opaque
		if (alpha>=1.0) 
			break;
		// check whether the point lies within calc-space
		if (abs(x)>cell_size/2.0 || abs(y)>cell_size/2.0
				  || abs(z)>cell_size/2.0)
		{
			alpha+=0.0;			
		}
		else
		{
			// get alpha at the point
			alpha+=getAlpha (x, y, z, true);			
		}
		x+=xstep; 
		y+=ystep; 
		z+=zstep;
	}
	
	float red=0.5, green=0.2, blue=0.8;
	
	blue = (atan(psi_imag, psi_real)+3.14)/3.14;		
	
	
	// map phase onto red-blue spectrum
	if (blue>1.0) blue=2.0-blue;
	red=1.0-blue;	
	
	gl_FragColor = vec4 (red, green, blue, alpha);
}