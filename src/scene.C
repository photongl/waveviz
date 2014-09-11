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

//////////////////////////////////////////////////////
// scene.C
//
// Contains the implementation of the scene class
//////////////////////////////////////////////////////


#include "includeall.h"
#include "scene.h"

// max space cell resolution
#define CELL_RESOLUTION m_cellresolution
#define CELL_DENSITY m_celldensity
#define CELL_OVERLAP m_celloverlap

// global vars
int pos_loc=0;		// location of 'abs_pos' register
int loc_wavefunc=0;	// location of 'wavfunc' register
GLuint vb_id=0;		// vertex buffer id
float phase=0;


///////////////
// Constructor
///////////////
CScene::CScene()
{
	SetSceneDivisions (100, 100, 100);
	SetSceneBounds (2000, 2000, 2000);
	SetSceneOrigin (50, 50, 50);
	m_vertices=0;
	m_data=0;
	m_cellresolution=40;
	m_celldensity=10;
	m_celloverlap=20;
}

//////////////
// Destructor
//////////////
CScene::~CScene()
{
	if (m_vertices==0) return;
	
	// clean up the space cells	
	delete [] m_vertices;
	
	// clean up the computed data
	if (m_data==0) return;
	
	delete [] m_data;
}


/////////////////////////
// Initialize the scene
/////////////////////////
void CScene::InitScene(int shader_id)
{
	// generate space cells
	this->GenSpaceCells();
	
	// allocate data space
	m_data = new complex[m_xdivs*m_ydivs*m_zdivs];
	
	printf ("Scene Init done...\n");	
	
	// get 'abs_pos' location
	m_shaderid=shader_id;
	pos_loc = glGetUniformLocation (m_shaderid, "abs_pos");
	loc_wavefunc=glGetAttribLocation (m_shaderid, "wavefunc");
}


/////////////////////
// Sets scene bounds
/////////////////////
void CScene::SetSceneBounds (int xsize,
			     int ysize,
			     int zsize)
{
	m_xsize=xsize;
	m_ysize=ysize;
	m_zsize=zsize;
}


////////////////////////////
// Sets number of divisions
// for each axis
////////////////////////////
void CScene::SetSceneDivisions (int x, int y, int z)
{
	m_xdivs=x;
	m_ydivs=y;
	m_zdivs=z;
}


////////////////////////////////
// sets the scene's origin cell
////////////////////////////////
void CScene::SetSceneOrigin (int x, int y, int z)
{
	m_xorg=x;
	m_yorg=y;
	m_zorg=z;
}


/////////////////////////
// Generates space cells
// to be used for showing
// probability densities
/////////////////////////
void CScene::GenSpaceCells()
{
	// seed rand()
	srand ((unsigned) time (NULL));
	
	// some vars
	int x=0, y=0, z=0;
	
	// get cell dimensions
	int xlength = (m_xsize)/m_xdivs;
	int ylength = (m_ysize)/m_ydivs;
	int zlength = (m_zsize)/m_zdivs;
	printf ("Cell dims:%d %d %d...\n", xlength, ylength, zlength);
	
	// tell GL about these arrays
	glEnableClientState (GL_VERTEX_ARRAY);	
	
	// allocate vertex space
	m_vertices = new Vector3d [CELL_DENSITY*CELL_RESOLUTION*(CELL_RESOLUTION-1)/2];
	
	for (int i=0; i<CELL_RESOLUTION; i++)
	{
		//m_spacecells[i].points = new Vector3d [CELL_DENSITY*i];
		for (int j=0; j<CELL_DENSITY*i; j++)
		{
			x=rand()%(xlength+CELL_OVERLAP)-xlength/2;
			z=rand()%(zlength+CELL_OVERLAP)-zlength/2;
			y=rand()%(ylength+CELL_OVERLAP)-ylength/2;
			
			m_vertices[i*(i-1)*CELL_DENSITY/2+j].x=x;
			m_vertices[i*(i-1)*CELL_DENSITY/2+j].y=y;
			m_vertices[i*(i-1)*CELL_DENSITY/2+j].z=z;
		}
	}
	
	// write vertices to video memory
	glGenBuffers (1, &vb_id);
	glBindBuffer (GL_ARRAY_BUFFER, vb_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3d)*CELL_DENSITY*CELL_RESOLUTION
			*(CELL_RESOLUTION-1)/2, 
		      m_vertices, GL_STATIC_DRAW);
	glVertexPointer (3, GL_FLOAT, 0, 0);	
}




///////////////////////////////////////
// Displays the PDF for a given region
///////////////////////////////////////
void CScene::Display (int xstart, int xend,
		      int ystart, int yend,
		      int zstart, int zend,
		      float start_threshold, float end_threshold)
{
	// physical coordinates
	int x=0, y=0, z=0;
	
	// get cell dimensions
	int xlength = (m_xsize)/m_xdivs;
	int ylength = (m_ysize)/m_ydivs;
	int zlength = (m_zsize)/m_zdivs;
	
	// space-cell index
	int index=0; int data_index=0;
	float alpha=1.0f, density=0.0f;
	
	// convert coordinates to array indices
	xstart=xstart+m_xorg; xend=xend+m_xorg;
	ystart=ystart+m_yorg; yend=yend+m_yorg;
	zstart=zstart+m_zorg; zend=zend+m_zorg;
	
	// display the PDF for the region
	for (int k=zstart; k<zend; k++)
	{
		for (int j=ystart; j<yend; j++)
		{
			for (int i=xstart; i<xend; i++)
			{
				data_index=k*m_xdivs*m_ydivs+j*m_xdivs+i;
				
				// convert indices to coordinates :(
				x=(i-m_xorg)*xlength;
				y=(j-m_yorg)*ylength;
				z=(k-m_zorg)*zlength;
				
				// get the appropriate cell to represent
				// the PDF at the given point
				density=m_data[data_index].real*m_data[data_index].real
					+m_data[data_index].imag*m_data[data_index].imag;
				
				index=(int)(density/max*CELL_RESOLUTION)-1;
				
				
				if (index<0) index=0;
				
				if (index>=start_threshold && index <=end_threshold && index!=0)
				{
					alpha=(float)index/CELL_RESOLUTION;
				
					
					// render the cell
					glPushMatrix();
					glTranslatef (x, y, z);
					
					glDrawArrays (GL_POINTS, index*(index-1)*CELL_DENSITY/2,
							index*CELL_DENSITY);
					glPopMatrix();
					
					// pass abs_pos to shader
					//glUniform3f (pos_loc, x, y, z);
					glVertexAttrib3f (loc_wavefunc, 
							m_data[data_index].real,
							m_data[data_index].imag,
							 alpha);
				}				
			}
		}
	}	
}
