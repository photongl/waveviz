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
// compute.C
// contains the implementation of the compute class
//////////////////////////////////////////////////////////////

#include "compute.h"
#include <cstdlib>
#include <math.h>
#include <cstdio>

//////////////////////////////////////////////////
// Computes the PDF for a given region
// returns-the max value obtained for the region
// m_data is the data array in which the results
// will be written
//////////////////////////////////////////////////
float CCompute::Compute (int xstart, int xend,
		      int ystart, int yend,
		      int zstart, int zend,
		      int time, complex *m_data)
{
	int index=0;
	
	// physical coordinates
	int x=0, y=0, z=0;
	
	// density
	float density=0.0f;
	
	// reset max
	m_scene->max=0.0f;
	
	// get cell dimensions
	int xlength = (m_scene->m_xsize)/m_scene->m_xdivs;
	int ylength = (m_scene->m_ysize)/m_scene->m_ydivs;
	int zlength = (m_scene->m_zsize)/m_scene->m_zdivs;
		
	// convert coordinates to array indices
	xstart=xstart+m_scene->m_xorg; xend=xend+m_scene->m_xorg;
	ystart=ystart+m_scene->m_yorg; yend=yend+m_scene->m_yorg;
	zstart=zstart+m_scene->m_zorg; zend=zend+m_scene->m_zorg;		
	
	// compute the PDF for the region
	for (int k=zstart; k<zend; k++)
	{
		for (int j=ystart; j<yend; j++)
		{
			for (int i=xstart; i<xend; i++)
			{
				index=k*m_scene->m_xdivs*m_scene->m_ydivs
						+j*m_scene->m_xdivs+i;
				
				// convert indices to coordinates :(
				x=(i-m_scene->m_xorg)*xlength;
				y=(j-m_scene->m_yorg)*ylength;
				z=(k-m_scene->m_zorg)*zlength;
				
				// get data from function evaluator
				if (m_ptr!=0)
				{
					m_data[index]=m_ptr (x, y, z, time);
				}
				else
				{
					m_data[index] = FuncDef (x, y, z, time);
				}
				
				density=m_data[index].real*m_data[index].real
						+m_data[index].imag*m_data[index].imag;
						
				// get max(PDF) for this region
				if (density>m_scene->max)
					m_scene->max=density;
			}			
		}
	}
	
	return m_scene->max;		
}


/////////////////////////////
// sets the compute function
/////////////////////////////
void CCompute::setComputeFunction (PCOMPFUNC ptr)
{
	m_ptr=ptr;
}


///////////////
// Constructor
///////////////
CCompute::CCompute(CScene *scene)
{
	m_scene = scene;
	m_ptr=0;
}






/****************************************************************************/
//////////////////////////////////////
// Write your function evaluator here
//////////////////////////////////////
complex CCompute::FuncDef (int x, int y, int z, int time)
{
	complex psi={0.0f, 0.0f};
	static int old_time=0;
	
	
	
	// write any code required for your 
	// function evaluation below
	/**********************************************************************/
	
	// define your variables here
	// (variables that are not dependent on space
	// should be defined as "static")
	
	
	//// SAMPLE CODE FOR MORPHING \\\\
	
	// non-static vars
	
	// wave functions
	float psi_1_real=0.0f, psi_2_real=0.0f, psi_target_real=0.0f, psi_real=0.0f;
	float psi_1_imag=0.0f, psi_2_imag=0.0f, psi_target_imag=0.0f, psi_imag=0.0f;
	float psi_1=0.0f, psi_2=0.0f, psi_target=0.0f;
	
	// static vars
	static int morph_time=2000;	// morphing time
	static float t=0.0f;		// blending factor
	static int Lx = 600, Ly = 400, Lz = 200;		// box size
	static float nx=2.0f, ny=1.0f, nz=1.0f;			// quantum nos.
	static float E1=0.0f, E2=0.0f, Etarget=0.0f;		// energies	
	
	
	if (old_time!=time)
	{
		// evaluate variables not dependent on space here
		
		// calculate morphing factor
		t=time;
		t/=morph_time;
		if (t>1.0f) t=1.0f;
		
		// calculate energies
		E1=1000*((nx/Lx)*(nx/Lx)+(ny/Ly)*(ny/Ly)+(nz/Lz)*(nz/Lz));
		E2=1000*((ny/Lx)*(ny/Lx)+(nx/Ly)*(nx/Ly)+(nz/Lz)*(nz/Lz));
		Etarget = 1000*((ny/Lx)*(ny/Lx)+(nx/Ly)*(nx/Ly)+(ny/Lz)*(ny/Lz));		
	}
	
	// do space-varying calculations here
		
	if (abs(x)<Lx/2 && abs(y)<Ly/2 && abs(z)<Lz/2)
	{
					
		// initial wave function
		if (t<1.0f)
		{
			psi_1 = sqrt (2.0f/Lx)*cos (nx*3.141592f*x/Lx)
					*sqrt (2.0f/Ly)* cos (ny*3.141592f*y/Ly)
					*sqrt (2.0f/Lz)* cos (nz*3.141592f*z/Lz);
			psi_1_imag = psi_1*sin(E1*time);
			psi_1_real = psi_1*cos(E1*time);
						
			psi_2 = sqrt (2.0f/Lx)*cos (ny*3.141592f*x/Lx)
					*sqrt (2.0f/Ly)* cos (nx*3.141592f*y/Ly)
					*sqrt (2.0f/Lz)* cos (nz*3.141592f*z/Lz);
			psi_2_imag = psi_2*sin(E2*time);
			psi_2_real = psi_2*cos(E2*time);
		}
		else
		{
			// don't keep computing psi_1 and psi_2
			// once morphing is over
			psi_1_imag = 0;
			psi_1_real = 0;
					
			psi_2_imag = 0;
			psi_2_real = 0;
		}
					
			
		// target wave function
		psi_target=sqrt (2.0f/Lx)*cos (ny*3.141592f*x/Lx)
				*sqrt (2.0f/Ly)* cos (nx*3.141592f*y/Ly)
				*sqrt (2.0f/Lz)* cos (ny*3.141592f*z/Lz);
		psi_target_imag=psi_target*sin (Etarget*time);
		psi_target_real=psi_target*cos (Etarget*time); 
					
			
		// blend the initial and target wave functions
		psi_real = (1.0f-t)*(psi_1_real+psi_2_real)
				+t*psi_target_real;
		psi_imag = (1.0f-t)*(psi_1_imag+psi_2_imag)
				+t*psi_target_imag;			
	}
	else
	{
		psi_real=0;
		psi_imag=0;
	}		
		
	
	
	// always assign the values you have computed
	// to the real and imaginary parts of psi like this
	psi.real=psi_real;
	psi.imag=psi_imag;
	
	
	/**********************************************************************/
	// end function evaluation
	old_time=time;
	return psi;
}
