/*

NAME: Geometry.h
DESC:

DATE: February 2 2015
AUTH: Jonatan H Sundqvist

===============================================================================================

SPEC |

TODO | - 

*/



//-------------------------------------------------------------------------------------------------
// We'll need these
//-------------------------------------------------------------------------------------------------
# pragma once

#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <map>
#include <vector>

// My headers
#include "Texture.h"



//-------------------------------------------------------------------------------------------------
// Forward declarations
//-------------------------------------------------------------------------------------------------
namespace Geometry {

// Functions
int cube(int, int, int, int, int, int);
int prism(int, float);
int axes(float, float, float, float, float);
int building();

// Classes
struct GeometryState;
struct Camera;
struct Vector;
struct Polygon;

}


//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
int Geometry::cube(int left, int right, int front, int back, int top, int bottom) {

	//
	using namespace Texture;

	glEnable(GL_TEXTURE_2D);

	// Front
	glBindTexture(GL_TEXTURE_2D, textureIDs[front]);

	glBegin(GL_QUADS);
	glNormal3d(0.0, 0.0, 1.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// Back
	glBindTexture(GL_TEXTURE_2D, textureIDs[back]);

	glBegin(GL_QUADS);
	glNormal3d(0.0, 0.0, -1.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();

	// Left
	glBindTexture(GL_TEXTURE_2D, textureIDs[left]);

	glBegin(GL_QUADS);
	glNormal3d(-1.0, 0.0, 0.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// Right
	glBindTexture(GL_TEXTURE_2D, textureIDs[right]);

	glBegin(GL_QUADS);
	glNormal3d(1.0, 0.0, 0.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureIDs[6]);

	// Top
	glBindTexture(GL_TEXTURE_2D, textureIDs[top]);

	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 1.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// Bottom
	glBindTexture(GL_TEXTURE_2D, textureIDs[bottom]);

	glBegin(GL_QUADS);
	glNormal3d(0.0, -1.0, 0.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	return 0;

}


int Geometry::prism(int sides, float height) {

	for (int dAngle = 0, next = 360 / sides; dAngle < 360; (dAngle += 360 / sides), (next += 360 / sides)) {
		glBegin(GL_TRIANGLES);
		//glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, dCentre);
		glVertex3f(cosine(dAngle), sine(dAngle), 0.0f);
		glVertex3f(cosine(next), sine(next), 0.0f);
		glEnd();
	}

	return 0;

}


int Geometry::axes(float X, float Y, float Z, float length, float width) {

	glDisable(GL_LIGHTING);
	glLineWidth(width);
	glTranslatef(X, Y, Z);

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f-length, 0.0f, 0.0f); glVertex3f(0.0f+length, 0.0f, 0.0f); // X-axis (red)
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f-length, 0.0f); glVertex3f(0.0f, 0.0f+length, 0.0f); // Y-axis (green)
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f-length); glVertex3f(0.0f, 0.0f, 0.0f+length); // Z-axis (blue)
	glEnd();

	glTranslatef(-X, -Y, -Z);
	glEnable(GL_LIGHTING);

	return 0;

}


int Geometry::building() {

	float dX = 2.0f, dZ = 0.0f;
	float dXList[] = { 2.0f, 0.0f, -2.0f, 0.0f };
	float dZList[] = { 0.0f, -2.0f, 0.0f, 2.0f };

	int sdeIndex, topIndex, btmIndex;

	glTranslatef(6.0f, 16.0f, -4.0f);

	for (int i = 0; i < 40; ++i) {

		glTranslatef(dX, -16.0f, dZ);

		if (i % 10 == 0) {
			dX = dXList[i / 10];
			dZ = dZList[i / 10];
			glTranslatef(0.0f, 2.0f, 0.0f);
			sdeIndex = Texture::Indices::crackedbrick;
			cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex);
			glTranslatef(0.0f, 4.0f, 0.0f);
			cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex);
			glTranslatef(0.0f, 4.0f, 0.0f);
			cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex);
			glTranslatef(0.0f, 4.0f, 0.0f);
			cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex, sdeIndex);
			glTranslatef(0.0f, -4.0f * 3 - 2.0f, 0.0f);
		}

		sdeIndex = (i % 2 == 0) ? Texture::Indices::sidegrass : Texture::Indices::crackedbrick;
		topIndex = (i % 2 == 0) ? Texture::Indices::topgrass : sdeIndex;
		btmIndex = (i % 2 == 0) ? Texture::Indices::dirt : sdeIndex;

		cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, topIndex, btmIndex);
		glTranslatef(0.0f, 4.0f, 0.0f);
		cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, topIndex, btmIndex);
		glTranslatef(0.0f, 4.0f, 0.0f);
		cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, topIndex, btmIndex);
		glTranslatef(0.0f, 4.0f, 0.0f);
		cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, topIndex, btmIndex);
		glTranslatef(0.0f, 4.0f, 0.0f);
		cube(sdeIndex, sdeIndex, sdeIndex, sdeIndex, topIndex, btmIndex);

	}

	return 0;

}



//-------------------------------------------------------------------------------------------------
// Classes
//-------------------------------------------------------------------------------------------------
struct Geometry::GeometryState {
	// TODO: Use vectors (?)
	float X, Y, Z;		// Position
	float rX, rY, rZ;	// Rotation (degrees)
	int sides;

	GeometryState(int sides, float X, float Y, float Z, float rX, float rY, float rZ) {
		this->sides = sides;

		this->X = X;
		this->Y = Y;
		this->Z = Z;

		this->rX = rX;
		this->rY = rY;
		this->rZ = rZ;
	}

	int applyTransformations() {
		//glLoadIdentity();
		glTranslatef(this->X, this->Y, this->Z);
		glRotatef(this->rX, 1.0f, 0.0f, 0.0f);
		glRotatef(this->rY, 0.0f, 1.0f, 0.0f);
		glRotatef(this->rZ, 0.0f, 0.0f, 1.0f);
		return 0;
	}

};


struct Geometry::Camera {

	// TODO: Inherit from Geometry state (?)
	float X, Y, Z;
	float rX, rY, rZ;

	Camera() {
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;

		this->rX = 0.0f;
		this->rX = 0.0f;
		this->rX = 0.0f;
	}

	Camera(float X, float Y, float Z, float rX, float rY, float rZ) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;

		this->rX = rX;
		this->rY = rY;
		this->rZ = rZ;
	}

	int applyTransformations() {
		glLoadIdentity();
		glTranslatef(this->X, this->Y, this->Z);
		glRotatef(this->rX, 1.0f, 0.0f, 0.0f);
		glRotatef(this->rY, 0.0f, 1.0f, 0.0f);
		glRotatef(this->rZ, 0.0f, 0.0f, 1.0f);
		return 0;
	}

};


struct Geometry::Vector {
	// TODO: Find pre-existing type instead
	GLfloat x, y, z;
};


struct Geometry::Polygon {

	// An interactive polygon

	Polygon(std::vector<Vector> vertices) {
		//
		this->vertices = vertices;
	}


	void render() {

		//
		if (vertices.size() < 3) {
			return;
		}

		OutputDebugString(L"Rendering polygon.\n");
		glBegin(GL_POLYGON);

		for (Vector vertex : this->vertices) {
			glColor3f(1.0f, 0.8f, 0.0f);
			glVertex3f(vertex.x, vertex.y, vertex.z);
			OutputDebugLine("Vertex (X=%f, Y=%f, Z=%f)", vertex.x, vertex.y, vertex.z);
		}

		glEnd();

	}

	std::vector<Vector> vertices;

};

