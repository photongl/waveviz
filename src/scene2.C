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
// scene2.C
//
// Contains the implementation of the scene class
// using 3D textures for rendering
//////////////////////////////////////////////////////


#include "includeall.h"
#include "scene.h"

int p=0;		// the current shader
GLuint vb_id=0;		// vertex buffer id
GLuint texid=0;		// texture id
GLuint texdataid=0;	// id for data texture

// shader var pointers
int pos_loc=0;		// 'abs_pos' var
int loc_cell_dims=0;	// 'cell_dims' var




///////////////
// Constructor
///////////////
CScene::CScene()
{
	SetSceneDivisions (100, 100, 100);
	SetSceneBounds (2000, 2000, 2000);
	SetSceneOrigin (50, 50, 50);	
}

//////////////
// Destructor
//////////////
CScene::~CScene()
{	
	// clean up the computed data
	delete [] m_data;
}


/////////////////////////
// Initialize the scene
/////////////////////////
void CScene::InitScene(int shader_id)
{	
	// allocate data space
	m_data = new complex[m_xdivs*m_ydivs*m_zdivs];	
	
	/** get shader var pointers **/
	m_shaderid=p=shader_id;
	
	// get 'abs_pos' location	
	pos_loc = glGetUniformLocation (m_shaderid, "abs_pos");	
	// get 'cell_dims' location
	loc_cell_dims = glGetUniformLocation (m_shaderid, "cell_dims");
	
	// set data texture
	glEnable (GL_TEXTURE_1D);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glGenTextures (1, &texdataid);
	glBindTexture (GL_TEXTURE_1D, texdataid);
	
	
	// set splat-texture
	glEnable (GL_TEXTURE_2D);
			
	
	printf ("Scene Init done...\n");	
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


///////////////////////////
// Generates space cells
// not required for scene2.C
/////////////////////////////
void CScene::GenSpaceCells()
{
	
	
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
	int x=0, y=0, z=0, index=0;
	float density=0;
	
	// get cell dimensions and send them to the shader
	int xlength = (m_xsize)/m_xdivs;
	int ylength = (m_ysize)/m_ydivs;
	int zlength = (m_zsize)/m_zdivs;
	
	glUniform1f (loc_cell_dims, (xend-xstart)*xlength);
	
	// convert coordinates to array indices
	xstart=xstart+m_xorg; xend=xend+m_xorg;
	ystart=ystart+m_yorg; yend=yend+m_yorg;
	zstart=zstart+m_zorg; zend=zend+m_zorg;
	
	/*
	for (int k=zstart; k<zend; k++)
	{
		for (int j=ystart; j<yend; j++)
		{
			for (int i=xstart; i<xend; i++)
			{
				// convert indices to coordinates :(
				x=(i-m_xorg)*xlength;
				y=(j-m_yorg)*ylength;
				z=(k-m_zorg)*zlength;
				
				
				// get the appropriate cell to represent
				// the PDF at the given point
				index=k*m_xdivs*m_ydivs+j*m_xdivs+i;
				
				density=((m_data[index].real*m_data[index].real
						+m_data[index].imag*m_data[index].imag)/max);
				
				
				if (density>=start_threshold && density<=end_threshold && density!=0)
				{	
					//printf ("density:%f\t", density);
					glColor4f (1.0f, 0, 0, density);						
					// render the cell
					glPushMatrix();
					glTranslatef (x, y, z);
					
					glBegin (GL_QUADS);
					{
						glTexCoord2f (-1.0f, -1.0f);						
						glVertex2i (-xlength/2, -ylength/2);
						glTexCoord2f (1.0f, -1.0f);
						glVertex2i (xlength/2, -ylength/2);
						glTexCoord2f (1.0f, 1.0f);
						glVertex2i (xlength/2, ylength/2);
						glTexCoord2f (-1.0f, 1.0f);
						glVertex2i (-xlength/2, ylength/2);						
					}
					glEnd();
							
					glPopMatrix();
					
					// pass abs_pos to shader
					glUniform3f (pos_loc, x, y, z);					
				}				
			}
		}
	}
	*/
	
	int half_diag = (int)sqrt (2.0f*(xend-xstart)*xlength
			*(xend-xstart)*xlength)/2.0f;
	glBegin(GL_QUADS);
	{
		glTexCoord2f (-1.0f, -1.0f);						
		glVertex2i (-half_diag, -half_diag);
		glTexCoord2f (1.0f, -1.0f);
		glVertex2i (half_diag, -half_diag);
		glTexCoord2f (1.0f, 1.0f);
		glVertex2i (half_diag, half_diag);
		glTexCoord2f (-1.0f, 1.0f);
		glVertex2i (-half_diag, half_diag);
	}
	glEnd();	
	//glUniform3f (pos_loc, 0, 0, 0);
}
