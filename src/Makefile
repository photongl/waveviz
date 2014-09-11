#***********************************************************************************
#	Copyright 2006. Akshay Mishra	
#
#	This file is part of WaveVIZ.
#
#	WaveVIZ is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.
#	
#	WaveVIZ is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#	
#	You should have received a copy of the GNU General Public License
#	along with WaveVIZ; if not, write to the Free Software
#	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#************************************************************************************

# set compiler
CC=g++

# edit include paths as necessary for your system - in particular for FLTK and GLEW (most probably /usr/include)
INCLUDE=-I/home/akshay/dev/include -I/usr/X11R6/include

# edit lib paths as necessary for your system - in particular for FLTK and GLEW (most probably /usr/lib)
LIB=-L/home/akshay/dev/lib -L/usr/X11R6/lib
LSTD=-lX11 -lXext -lXi -lXmu -lm -lGLEW -lfltk_gl -lfltk -lGL -lGLU

# executable compiler flags
EF=-c
# library compiler flags
LF=-fPIC -c

# linking executable
visapp: main.o application.o renderer.o camera.o scene.o textfile.o compute.o WaveVizUI.o
	$(CC) main.o application.o renderer.o camera.o scene.o textfile.o compute.o WaveVizUI.o -o visapp $(INCLUDE) $(LIB) $(LSTD)
	rm *.o

visfog: main.o application.o renderer2.o camera.o scene2.o textfile.o compute.o WaveVizUI.o
	$(CC) main.o application.o renderer2.o camera.o scene2.o textfile.o compute.o WaveVizUI.o -o visfog $(INCLUDE) $(LIB) $(LSTD)
	rm *.o

# linking shared object libraries
libvis: lapplication.o lrenderer.o lcamera.o lscene.o ltextfile.o lcompute.o
	$(CC) -shared -o libvis.so lapplication.o lrenderer.o lcamera.o lscene.o ltextfile.o lcompute.o $(INCLUDE) $(LIB) $(LSTD)
	rm *.o

libvisfog: lapplication.o lrenderer2.o lcamera.o lscene2.o ltextfile.o lcompute.o
	$(CC) -shared -o libvisfog.so lapplication.o lrenderer2.o lcamera.o lscene2.o ltextfile.o $(INCLUDE) $(LIB) $(LSTD)
	rm *.o

# object files for executable
main.o: application.h includeall.h
	$(CC) $(INCLUDE) $(EF) main.C	

application.o: includeall.h
	$(CC) $(INCLUDE) $(EF) application.C

renderer.o: includeall.h camera.h scene.h textfile.h
	$(CC) $(INCLUDE) $(EF) renderer.C

renderer2.o: includeall.h camera.h scene.h textfile.h
	$(CC) $(INCLUDE) $(EF) renderer2.C

camera.o: includeall.h
	$(CC) $(EF) camera.C

scene.o: includeall.h
	$(CC) $(INCLUDE) $(EF) scene.C

textfile.o:

scene2.o: includeall.h scene.h includeall.h
	$(CC) $(INCLUDE) $(EF) scene2.C

compute.o: scene.h includeall.h
	$(CC) $(INCLUDE) $(EF) compute.C

WaveVizUI.o:
	$(CC) $(INCLUDE) $(EF) WaveVizUI.C


# object files for shared library
lapplication.o: includeall.h
	$(CC) $(INCLUDE) $(LF) -o lapplication.o application.C

lrenderer.o: includeall.h camera.h scene.h textfile.h
	$(CC) $(INCLUDE) $(LF) -o lrenderer.o renderer.C

lrenderer2.o: includeall.h camera.h scene.h textfile.h
	$(CC) $(INCLUDE) $(LF) -o lrenderer2.o renderer2.C

lcamera.o: includeall.h
	$(CC) $(INCLUDE) $(LF) -o lcamera.o camera.C

lscene.o: includeall.h
	$(CC) $(INCLUDE) $(LF) -o lscene.o scene.C

ltextfile.o:
	$(CC) $(INCLUDE) $(LF) -o ltextfile.o textfile.cpp

lscene2.o: includeall.h scene.h
	$(CC) $(INCLUDE) $(LF) -o lscene2.o scene2.C

lcompute.o: scene.h includeall.h
	$(CC) $(INCLUDE) $(LF) -o lcompute.o compute.C

lWaveVizUI.o:
	$(CC) $(INCLUDE) $(EF) WaveVizUI.C

# clean-up
clean:
	rm *.o
