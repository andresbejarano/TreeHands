/**
 *	TreeHands.h
 *	Writen by: Andres Bejarano
 */

#ifndef _TREEHANDS_H_
#define _TREEHANDS_H_

/* Required by GLM in order to improve some calculations */
#define GLM_FORCE_RADIANS

/* Include basic input/output and string management headers */
#include <string>
#include <iostream>
#include <sstream>

/* Include the GLEW header (must go before any other OpenGL support library */
#include "GL\glew.h"

/* Include the Freeglut header */
#include "GL\freeglut.h"

/* Include the OpenGL Math header */
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"

/* Include the Leap Motion header */
#include "LeapMotion.h"

/* Include the LSystem header */
#include "LSystem.h"



/**
 *	The class that represents the application
 */
class TreeHands {

public:

	/**
	 *	The constructor of the class
	 */
	TreeHands(std::string inputGrammar);

	/**
	 *	Updates the information of the application
	 */
	void update();

	/**
	 *	Draw the content of the application
	 */
	void draw();

	/**
	 *	Updates the points of the tree of the grammar
	 */
	void updateTreePoints();

	/**
	 *	Releases the resources taken by the application
	 */
	void close();

	/**
	 *	Generates the next iteration of the grammar
	 */
	void nextIteration();

	/**
	 *	Returns to a previous iteration of the grammar
	 */
	void previousIteration();

	/**
	 *	The reference to the L-System
	 */
	LSystem* lSystem;

	/**
	 *	The reference to the Leap Motion object
	 */
	LeapMotion* leapMotion;

	/**
	 *	The model matrix
	 */
	glm::mat4x4 modelMatrix;

	/**
	 *	The visualization matrix
	 */
	glm::mat4x4 viewMatrix;

	/**
	 *	The projection matrix
	 */
	glm::mat4x4 projMatrix;

	/**
	 *	The vertex buffer object for the left hand
	 */
	GLuint leftHandPointsVBO;

	/**
	 *	The vertex attribute object for the left hand
	 */
	GLuint leftHandVAO;

	/**
	 *	The vertex buffer object for the right hand
	 */
	GLuint rightHandPointsVBO;

	/**
	 *	The vertex attribute object for the right hand
	 */
	GLuint rightHandVAO;

	/**
	 *	The vertex shader for the hands
	 */
	GLuint handVertexShader;

	/**
	 *	The geometry shader for the hands
	 */
	GLuint handGeometryShader;

	/**
	 *	The fragment shader for the hands
	 */
	GLuint handFragmentShader;

	/**
	 *	The shader program for the hands
	 */
	GLuint handShaderProgram;
	
	/**
	 *	The location of the MVP for the hand's geometry shader
	 */
	GLint handMVPMatrixLocation;

	/**
	 *	Indicates if there is a left hand to be drawn
	 */
	bool drawLeftHand;

	/**
	 *	Indicates if there is a right hand to be drawn
	 */
	bool drawRightHand;

	/**
	 *	The vertex buffer object for the grid
	 */
	GLuint gridVBO;

	/**
	 *	The vertex attribute object for the grid
	 */
	GLuint gridVAO;

	/**
	 *	The vertex shader for the grid
	 */
	GLuint gridVertexShader;

	/**
	 *	The geometry shader for the grid
	 */
	GLuint gridGeometryShader;

	/**
	 *	The fragment shader for the grid
	 */
	GLuint gridFragmentShader;

	/**
	 *	The shader program for the grid
	 */
	GLuint gridShaderProgram;
	
	/**
	 *	The location of the MVP for the grid's geometry shader
	 */
	GLint gridMVPMatrixLocation;

	/**
	 *	Indicates if the origin and the grid should be drawn
	 */
	bool drawGrid;

	/**
	 *	The vertex buffer object for the triangle
	 */
	GLuint trianglePointsVBO;

	/**
	 *	The vertex buffer object for the triangle colors
	 */
	GLuint triangleColorsVBO;

	/**
	 *	The vertex attribute object for the triangle
	 */
	GLuint triangleVAO;

	/**
	 *	The vertex shader for the triangle
	 */
	GLuint triangleVertexShader;

	/**
	 *	The fragment shader for the triangle
	 */
	GLuint triangleFragmentShader;

	/**
	 *	The shader program for the triangle
	 */
	GLuint triangleShaderProgram;
	
	/**
	 *	The location of the MVP for the triangle's vertex shader
	 */
	GLint triangleMVPMatrixLocation;

	/**
	 *	Indicates if the RGB triangle should be drawn
	 */
	bool drawTriangle;

	/**
	 *	The rotation angle of the triangle
	 */
	GLfloat triangleRotationAngle;

	/**
	 *
	 */
	GLuint treePointsVBO;

	/**
	 *
	 */
	GLuint treeVAO;

	/**
	 *
	 */
	GLuint treeVertexShader;

	/**
	 *
	 */
	GLuint treeGeometryShader;

	/**
	 *
	 */
	GLuint treeFragmentShader;

	/**
	 *
	 */
	GLuint treeShaderProgram;

	/**
	 *
	 */
	GLuint treeMVPMatrixLocation;

	/**
	 *	The number of points on the tree
	 */
	int nTreePoints;

	/**
	 *	The number of points fo the tree for arms
	 */
	int nArmTreePoints;

	/**
	 *	The number of points of the tree for fingers
	 */
	int nFingerTreePoints;

	/**
	 *	Indicates the current number of iterations of the grammar
	 */
	int currentIteration;

	/**
	 *
	 */
	bool drawTree;

	/**
	 *	The location of the visualization camera
	 */
	glm::vec3 camEye;

	/**
	 *	The location of the target of the visualization camera
	 */
	glm::vec3 camTarget;

	/**
	 *	The up vector of the visualization camera
	 */
	glm::vec3 camUp;

	/**
	 *	The yaw rotation angle of the visualization camera
	 */
	GLfloat camYawRotation;

	/**
	 *	The yaw rotation speed of the visualization camera
	 */
	GLfloat camYawSpeed;

	/**
	 *	The yaw rotation angle step of the visualiation cameara
	 */
	GLfloat camYawStep;

	/**
	 *	The yaw rotation matrix of the visualization camera
	 */
	glm::mat4x4 camYaw;

private:

	/**
	 *	Initializes the shaders and shader program of the grid and grid
	 */
	void initGridShaders();

	/**
	 *	Initializes the shader and shader program of the hands
	 */
	void initHandShaders();

	/**
	 *	Initializes the shader and shader program of the tree of the grammar
	 */
	void initTreeShaders();

	/**
	 *	Initializes the shaders and shader program of the triangle
	 */
	void initTriangleShaders();

	/**
	 *	Updates the information of the hands using the Leap Motion
	 */
	void updateHands();

	/**
	 *	Updates the points of the left hand
	 */
	void updateLeftHandPoints(Leap::Hand hand);

	/**
	 *	Updates the points of the right hand
	 */
	void updateRightHandPoints(Leap::Hand hand);

	/**
	 *	Updates the information of the VBO and VAO of the left hand
	 */
	void updateLeftHandVertexObjects();

	/**
	 *	Updates the information of the VBO and VAO of the right hand
	 */
	void updateRightHandVertexObjects();

	/**
	 *	Updates the information of the VBO and VAO of the tree points
	 */
	void updateTreePointsVertexObjects();

};

#endif
