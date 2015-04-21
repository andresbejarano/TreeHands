/**
 *	TreeHands.cpp
 *	Written by: Andres Bejarano
 *
 */

#include "TreeHands.h"

/**
 *	Source code for the grid vertex shader
 */
const char* gridVertexShaderSource = 
	"#version 400\n"
	"layout(location = 0) in vec3 position;"
	"void main () {"
	"  gl_Position = vec4(position, 1.0);"
	"}";

/**
 *	Source code for the grid geometry shader
 */
const char* gridGeometryShaderSource = 
	"#version 400\n"
	"layout(points) in;"
	"layout(line_strip, max_vertices = 406) out;"
	"uniform mat4 MVP;"
	"void main () {"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-20.0, 0.0, 0.0, 0.0));"
	"  EmitVertex();"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(20.0, 0.0, 0.0, 0.0));"
	"  EmitVertex();"
	"  EndPrimitive();"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(0.0, -20.0, 0.0, 0.0));"
	"  EmitVertex();"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(0.0, 20.0, 0.0, 0.0));"
	"  EmitVertex();"
	"  EndPrimitive();"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(0.0, 0.0, -20.0, 0.0));"
	"  EmitVertex();"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(0.0, 0.0, 20.0, 0.0));"
	"  EmitVertex();"
	"  EndPrimitive();"
	"  for(float i = 0.0; i <= 100.0; i += 10.0) {"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(-100.0, i, -100.0, 0.0));"
	"    EmitVertex();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(100.0, i, -100.0, 0.0));"
	"    EmitVertex();"
	"    EndPrimitive();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(i, 100.0, -100.0, 0.0));"
	"    EmitVertex();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(i, 0.0, -100.0, 0.0));"
	"    EmitVertex();"
	"    EndPrimitive();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(-i, 100.0, -100.0, 0.0));"
	"    EmitVertex();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(-i, 0.0, -100.0, 0.0));"
	"    EmitVertex();"
	"    EndPrimitive();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(-100.0, 0.0, -i, 0.0));"
	"    EmitVertex();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(100.0, 0.0, -i, 0.0));"
	"    EmitVertex();"
	"    EndPrimitive();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(i, 0.0, 0.0, 0.0));"
	"    EmitVertex();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(i, 0.0, -100.0, 0.0));"
	"    EmitVertex();"
	"    EndPrimitive();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(-i, 0.0, 0.0, 0.0));"
	"    EmitVertex();"
	"    gl_Position = MVP * (gl_in[0].gl_Position + vec4(-i, 0.0, -100.0, 0.0));"
	"    EmitVertex();"
	"    EndPrimitive();"
	"  }"
	"}";

/**
 *	Source code for the grid fragment shader
 */
const char* gridFragmentShaderSource = 
	"#version 400\n"
	"out vec4 color;"
	"void main () {"
	"  color = vec4(0.0, 1.0, 0.0, 1.0);"
	"}";

//-----------------------------------------------------------------------------------------

/**
 *	Source code for the triangle's vertex shader
 */
const char* triangleVertexShaderSource = 
	"#version 400\n"
	"layout(location = 0) in vec3 vertexPosition;"
	"layout(location = 1) in vec3 vertexColor;"
	"uniform mat4 MVP;"
	"out vec3 color;"
	"void main () {"
	"  color = vertexColor;"
	"  gl_Position = MVP * vec4(vertexPosition, 1.0);"
	"}";

/**
 *	Source code for the triangle's fragment shader
 */
const char* triangleFragmentShaderSource = 
	"#version 400\n"
	"in vec3 color;"
	"out vec4 frag_color;"
	"void main () {"
	"  frag_color = vec4(color, 1.0);"
	"}";

//--------------------------------------------------------------------------------------------

/**
 *	Source code for the hand's vertex shader
 */
const char* handVertexShaderSource = 
	"#version 400\n"
	"layout(location = 0) in vec3 vertexPosition;"
	"void main () {"
	"  gl_Position = vec4(vertexPosition, 1.0);"
	"}";

const char* handGeometryShaderSource = 
	"#version 400\n"
	"layout(lines) in;"
	"layout(line_strip, max_vertices = 2) out;"
	"uniform mat4 MVP;"
	"void main () {"
	"  gl_Position = MVP * (gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 1.0));"
	"  EmitVertex();"
	"  gl_Position = MVP * (gl_in[1].gl_Position + vec4(0.0, 0.0, 0.0, 1.0));"
	"  EmitVertex();"
	"  EndPrimitive();"
	"}";


/**
 *	Source code for the hand's fragment shader
 */
const char* handFragmentShaderSource = 
	"#version 400\n"
	"out vec4 frag_color;"
	"void main () {"
	"  frag_color = vec4(1.0, 0.0, 0.0, 1.0);"
	"}";

//--------------------------------------------------------------------------------------------

/**
 *	Source code for the tree's vertex shader
 */
const char* treeVertexShaderSource = 
	"#version 400\n"
	"layout(location = 0) in vec3 vertexPosition;"
	"uniform mat4 MVP;"
	"void main () {"
	"  gl_Position = MVP * vec4(vertexPosition, 1.0);"
	"}";

/**
 *	Source code for the tree's fragment shader
 */
const char* treeFragmentShaderSource = 
	"#version 400\n"
	"out vec4 frag_color;"
	"void main () {"
	"  frag_color = vec4(0.0, 0.0, 1.0, 1.0);"
	"}";

//---------------------------------------------------------------------------------------------

/**
 *	For tracking OpenGL errors
 */
GLenum glError;
GLint infoLogLength;
GLchar* strInfoLog;

/**
 *	The name of the fingers according to its type on the Leap Motion
 *	Code line from <Leap Motion SDK dir location>\LeapSDK\samples\Sample.cpp
 */
//const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};

/**
 *	The name of the bones of the fingers according to its type on the Leap Motion
 *	Code line from <Leap Motion SDK dir location>\LeapSDK\samples\Sample.cpp
 */
//const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};



/**
*	The location of the origin
*/
const GLfloat gridPoint[] = {
	  0.0f,  0.0f, 0.0f
};

/**
*	The location of the triangle's vertices
*/
const GLfloat trianglePoints[] = {
	  0.0f,  10.0f, 0.0f,
	 10.0f, -10.0f, 0.0f,
	-10.0f, -10.0f, 0.0f
};

/**
*	The color of the verties of the triangle
*/
const GLfloat triangleColors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

/**
 *	The maximum number of points for the tree
 */
const int maxTreePoints = 6240;

/**
 *	Number of points to draw
 */
const int pointsToDraw = maxTreePoints / 3;

/**
 *	The points of the generated model
 */
GLfloat treePoints[maxTreePoints];

/**
 *	The height if the generated tree
 */
GLfloat treeHeight;

/**
 *	The location of the left hand's vertices
 */
GLfloat leftHandPoints[156];
//GLfloat leftTreeHandPoints[3126];
GLfloat leftTreeHandPoints[maxTreePoints];

/**
 *	The location of the right hand's vertices
 */
GLfloat rightHandPoints[156];
//GLfloat rightTreeHandPoints[3126];
GLfloat rightTreeHandPoints[maxTreePoints];

/**
 *	Check any error thrown by OpenGL
 */
void checkError(char *message)  {

	/* Get the code of the error */
	glError = glGetError();

	/* If there is an error */
	if(glError != GL_NO_ERROR) {

		/* Write the error message */
		std::cout << "Error in " << message << ": " << glError << " - " << gluErrorString(glError) << std::endl;

	}

}

/**
*	The constructor of the class
*/
TreeHands::TreeHands(std::string inputGrammar) {

	/* Define clear color */
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	/* Get the reference to the Leap Motion controller */
	leapMotion = new LeapMotion();

	/* Get the reference to the L-System */
	lSystem = new LSystem(inputGrammar);
	
	/* Indicates the iteration on which the system is */
	currentIteration = 0;

	/* Initiates the rotation angle of the triangle */
	triangleRotationAngle = 0.0f;

	/* Init the grid and grid shaders */
	initGridShaders();

	/* Init the triangle shaders */
	initTriangleShaders();

	/* Init the hand shaders */
	initHandShaders();

	/* Init the tree shader */
	initTreeShaders();

	/* Enable 3D */
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	/* Indicates the culling method */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	/* Initialize the visualization camera vectors */
	camEye = glm::vec3(0, 200, 280);
	camTarget = glm::vec3(0, 100, 0);
	camUp = glm::vec3(0, 1, 0);

	/* Initialize the yaw rotation parameters of the visualization camera */
	camYawRotation = 0.0f;
	camYawSpeed = 0.0f;
	camYawStep = 0.1f;

	/* Initialize the yaw rotation matrix of the visualization camera */
	camYaw = glm::mat4x4();

	/* Indicates that the gridin and the grid should be drawn */
	drawGrid = true;

	/* Indicates that the RGB triangle should be drawn */
	drawTriangle = false;

	/* Indicates that the tree of the grammar should not be drawn */
	drawTree = true;
	
}

/**
*	Updates the information of the hands using the Leap Motion
*/
void TreeHands::updateHands() {

	/* If the Leap Motion is connected then get the information of the hand's vertices */
	if(leapMotion->isConnected()) {

		/* Indicates that the left hand has not been updated */
		bool leftHandUpdated = false;

		/* Indicates that the right hand has not been updated */
		bool rightHandUpdated = false;

		/* Indicates that the left hand should not be rendered (so far) */
		drawLeftHand = false;

		/* Indicates that the right hand should not be rendered (so far) */
		drawRightHand = false;
	
		/* Get the current frame */
		const Leap::Frame frame = leapMotion->controller.frame();

		/* Get the hand's list */
		Leap::HandList handList = frame.hands();

		/* Get the number of detected hands */
		int nHands = handList.count();

		/* For each detected hand */
		for(int h = 0; h < nHands; h += 1) {

			/* Get the current hand */
			Leap::Hand hand = handList[h];

			/* If the current hand is the left hand */
			if(hand.isLeft()) {

				/* If left hand has not been read */
				if(!leftHandUpdated) {

					/* Update the information of the left hand */
					updateLeftHandPoints(hand);

					/* Update the information of the left hand's VBO and VAO */
					updateLeftHandVertexObjects();

					/* The left hand has been read */
					leftHandUpdated = true;

					/**
					 *	Indicates that the left hand should be drawn
					 */
					drawLeftHand = true;

				}
				else {

					/* Go to the next hand */
					continue;

				}

			}
			else {

				/* If right hand has not been updated */
				if(!rightHandUpdated) {

					/* Update the information of the right hand */
					updateRightHandPoints(hand);

					/* Update the information of the right hand's VBO and VAO */
					updateRightHandVertexObjects();

					/* The left hand has been read */
					rightHandUpdated = true;

					/**
					 *	Indicates that the right hand should be drawn
					 */
					drawRightHand = true;

				}
				else {

					/* Go to the next hand */
					continue;

				}

			}

		}
	
	}

}

/**
*	Updates the information of the application
*/
void TreeHands::update() {
	
	/* Update the information of the hands using the Leap Motion */
	updateHands();

	/* If left hand was detected */
	if(drawLeftHand) {

		/* Place the original vertices on the new set */
		for(int i = 0; i < 156; i += 1) {
			leftTreeHandPoints[i] = leftHandPoints[i];
		}

		/* Keep the number of added vertices (must not be greater than maxTreePoints */
		int addedVertices = 156;

		/* Traverse again the original vertices, always starting with the first vertex of the bone */
		for(int i = 0; i < 156; i += 6) {

			/* Get the first vertex of the bone */
			glm::vec3 p0(leftHandPoints[i], leftHandPoints[i + 1], leftHandPoints[i + 2]);

			/* Get the second vertex of the bone */
			glm::vec3 p1(leftHandPoints[i + 3], leftHandPoints[i + 4], leftHandPoints[i + 5]);

			/* Get the vector that represents the bone */
			glm::vec3 bone = p1 - p0;

			/* Bone normalized */
			glm::vec3 normalizedBone = glm::normalize(bone);

			/* Get the angle between the bone and the X axis */
			float angle = glm::acos( glm::dot(normalizedBone,glm::vec3(1.0, 0.0, 0.0)  ));

			/* Set a quaternion pointing at the same direction than the bone and rotated by angle */
			glm::quat quaternion(angle, normalizedBone.x, normalizedBone.y, normalizedBone.z);

			/* Get the rotation matrix from the quaternion */
			glm::mat4 rM = glm::mat4_cast(quaternion);

			/* Set a translation matrix on p0 */
			glm::mat4 tM = glm::translate(glm::mat4(), p0);

			/* For each point in the tree */
			for(int t = 0; t < nTreePoints; t += 3) {

				/* Get the i-th vertex of the tree */
				glm::vec4 treePoint = glm::vec4(treePoints[t], treePoints[t + 1], treePoints[t + 2], 1.0f);

				/* Translate the vertex by using tM */
				treePoint = tM * rM * treePoint;

				/* Transform the (x, y, z) components of the points to GLfloat (avoid future errors with graphics card) */
				GLfloat x = treePoint.x;
				GLfloat y = treePoint.y;
				GLfloat z = treePoint.z;

				/* Place the point on the array */
				leftTreeHandPoints[addedVertices] = x;
				leftTreeHandPoints[addedVertices + 1] = y;
				leftTreeHandPoints[addedVertices + 2] = z;
				addedVertices += 3;

				/* If max number of vertices reached, then break all cycles */
				if(addedVertices >= maxTreePoints) {break;}

			}

			/* If max number of vertices reached, then break all cycles */
			if(addedVertices >= maxTreePoints) {
				break;
			}
			else {

				/* Clean the remaining spaces */
				for(int i = addedVertices; i < maxTreePoints; i += 1) {leftTreeHandPoints[i] = 0.0f;}

			}

		}

		/* Update the left hand's VBO and VAO */
		updateLeftHandVertexObjects();

	}

	/* If right hand was detected */
	if(drawRightHand) {

		/* Place the original vertices on the new set */
		for(int i = 0; i < 156; i += 1) {
			rightTreeHandPoints[i] = rightHandPoints[i];
		}

		/* Keep the number of added vertices (must not be greater than maxTreePoints */
		int addedVertices = 156;

		/* Traverse again the original vertices, always starting with the first vertex of the bone */
		for(int i = 0; i < 156; i += 6) {

			/* Get the first vertex of the bone */
			glm::vec3 p0(rightHandPoints[i], rightHandPoints[i + 1], rightHandPoints[i + 2]);

			/* Set a translation matrix on p0 */
			glm::mat4 tM = glm::translate(glm::mat4(), p0);

			/* For each point in the tree */
			for(int t = 0; t < nTreePoints; t += 3) {

				/* Get the i-th vertex of the tree */
				glm::vec4 treePoint = glm::vec4(treePoints[t], treePoints[t + 1], treePoints[t + 2], 1.0f);

				/* Translate the vertex by using tM */
				treePoint = tM * treePoint;

				/* Transform the (x, y, z) components of the points to GLfloat (avoid future errors with graphics card) */
				GLfloat x = treePoint.x;
				GLfloat y = treePoint.y;
				GLfloat z = treePoint.z;

				/* Place the point on the array */
				rightTreeHandPoints[addedVertices] = x;
				rightTreeHandPoints[addedVertices + 1] = y;
				rightTreeHandPoints[addedVertices + 2] = z;
				addedVertices += 3;

				/* If max number of vertices reached, then break all cycles */
				if(addedVertices >= maxTreePoints) {break;}

			}

			/* If max number of vertices reached, then break all cycles */
			if(addedVertices >= maxTreePoints) {
				break;
			}
			else {

				/* Clean the remaining spaces */
				for(int i = addedVertices; i < maxTreePoints; i += 1) {rightTreeHandPoints[i] = 0.0f;}

			}

		}

		/* Update the right hand's VBO and VAO */
		updateRightHandVertexObjects();

	}

}

/**
*	Draw the content of the application
*/
void TreeHands::draw() {
	
	/* Clear the window */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Set the viewMatrix with the parameters of the camera */
	camYawRotation += camYawSpeed * camYawStep;
	camYaw = glm::rotate(glm::mat4x4(), camYawRotation, glm::vec3(0.0, 1.0, 0.0));
	viewMatrix = glm::lookAt(camEye, camTarget, camUp) * camYaw;

	/* Set the projection matrix */
	projMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 600.0f);

	/* Set a matrix for the model, visualization and projection multiplication */
	glm::mat4x4 MVP = glm::mat4x4();

	/**
	 *	+-----------------------------------------------+
	 *	| Draw the triangle                             |
	 *	+-----------------------------------------------+
	 */

	/* If the RGB triangle should be drawn */
	if(drawTriangle) {

		/* Updates the triangle's rotation angle for the current frame */
		triangleRotationAngle += 0.1f;

		/* Set the modelMatrix with a z-rotation */
		modelMatrix = glm::rotate(glm::mat4x4(), triangleRotationAngle, glm::vec3(0.0, 0.0, 1.0));

		/* Calculates the MVP matrix */
		MVP = projMatrix * viewMatrix * modelMatrix;

		/* Indicates that the shader program will be used */
		glUseProgram(triangleShaderProgram);

		/* Set the MVP matrix on the shader */
		glUniformMatrix4fv(triangleMVPMatrixLocation, 1, GL_FALSE, &MVP[0][0]);

		/* Binds the VAO with the object */
		glBindVertexArray(triangleVAO);

		/* Draws the triangle */
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

	/**
	 *	+-----------------------------------------------+
	 *	| Draw the origin and grids                      |
	 *	+-----------------------------------------------+
	 */

	/* If the origin and the grid should be drawn */
	if(drawGrid) {

		/* Calculates the MVP matrix for the grid */
		MVP = projMatrix * viewMatrix * glm::mat4x4();

		/* Indicates that the origin and grid shader program will be used */
		glUseProgram(gridShaderProgram);

		/* Set the MVP matrix to the origin and grid shader program */
		glUniformMatrix4fv(gridMVPMatrixLocation, 1, GL_FALSE, &MVP[0][0]);

		/* Binds the VAO with the information of the grid's location */
		glBindVertexArray(gridVAO);

		/* Indicates the width of the lines for the grid */
		glLineWidth(1.0f);

		/* Draws the origin and grid */
		glDrawArrays(GL_POINTS, 0, 1);

	}

	/**
	 *	+-----------------------------------------------+
	 *	| Draw the left hand                             |
	 *	+-----------------------------------------------+
	 */

	/* If the left hand should be drawn */
	if(drawLeftHand) {

		/* Calculates the MVP matrix for the left hand */
		MVP = projMatrix * viewMatrix * glm::mat4x4();

		/* Indicates that the hand shader program will be used */
		glUseProgram(handShaderProgram);

		/* Set the MVP matrix on the shader */
		glUniformMatrix4fv(handMVPMatrixLocation, 1, GL_FALSE, &MVP[0][0]);

		/* Bind the left hand's VAO */
		glBindVertexArray(leftHandVAO);

		/* Indicates the width of the lines for the left hand */
		glLineWidth(3.0f);

		/* Draws the lines of the left hand */
		glDrawArrays(GL_LINES, 0, pointsToDraw);

	}

	/**
	 *	+-----------------------------------------------+
	 *	| Draw the right hand                            |
	 *	+-----------------------------------------------+
	 */

	/* If the right hand should be drawn */
	if(drawRightHand) {

		/* Calculates the MVP matrix for the right hand */
		MVP = projMatrix * viewMatrix * glm::mat4();

		/* Indicates that the hand shader program will be used */
		glUseProgram(handShaderProgram);

		/* Set the MVP matrix on the shader */
		glUniformMatrix4fv(handMVPMatrixLocation, 1, GL_FALSE, &MVP[0][0]);

		/* Bind the right hand's VAO */
		glBindVertexArray(rightHandVAO);

		/* Indicates the width of the lines for the right hand */
		glLineWidth(3.0f);

		/* Draws the lines of the left hand */
		glDrawArrays(GL_LINES, 0, pointsToDraw);

	}


	/**
	 *	+-----------------------------------------------+
	 *	| Draw the tree of the grammar                  |
	 *	+-----------------------------------------------+
	 */

	/* If the tree should be drawn */
	if(drawTree) {

		/* Calculates the MVP matrix for the right hand */
		MVP = projMatrix * viewMatrix * glm::mat4();

		/* Indicates that the hand shader program will be used */
		glUseProgram(treeShaderProgram);

		/* Set the MVP matrix on the shader */
		glUniformMatrix4fv(treeMVPMatrixLocation, 1, GL_FALSE, &MVP[0][0]);

		/* Bind the right tree's VAO */
		glBindVertexArray(treeVAO);

		/* Indicates the width of the lines for the right hand */
		glLineWidth(3.0f);

		/* Draws the lines of the left hand */
		glDrawArrays(GL_LINES, 0, pointsToDraw);

	}

	/* Swap the buffers */
	glutSwapBuffers();

}

/**
*	Releases the resources taken by the application
*/
void TreeHands::close() {

	/* Disconnect the Leap Motion */
	leapMotion->disconnect();

}

/**
*	Initialized the shaders and shader program of the origin and grid
*/
void TreeHands::initGridShaders() {

	/* Define the vertex buffer object for the gridin */
	glGenBuffers(1, &gridVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridPoint), gridPoint, GL_STATIC_DRAW);

	/* Define the vertex attribute object for the gridin */
	glGenVertexArrays(1, &gridVAO);
	glBindVertexArray(gridVAO);
	glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	/* Set up the grid's vertex shader */
	gridVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gridVertexShader, 1, &gridVertexShaderSource, NULL);
	glCompileShader(gridVertexShader);

	/* Set up the grid's geometry shader */
	gridGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gridGeometryShader, 1, &gridGeometryShaderSource, NULL);
	glCompileShader(gridGeometryShader);

	/* Set up the grid's fragment shader */
	gridFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gridFragmentShader, 1, &gridFragmentShaderSource, NULL);
	glCompileShader(gridFragmentShader);

	/* Set up the grid's shader program */
	gridShaderProgram = glCreateProgram();
	glAttachShader(gridShaderProgram, gridVertexShader);
	glAttachShader(gridShaderProgram, gridGeometryShader);
	glAttachShader(gridShaderProgram, gridFragmentShader);
	glLinkProgram(gridShaderProgram);

	/* Get the location of the matrices on the gridin's geometry shader */
	gridMVPMatrixLocation = glGetUniformLocation(gridShaderProgram, "MVP");

}

/**
*	Initializes the shaders and shader program of the triangle
*/
void TreeHands::initTriangleShaders() {

	/* Define the triangle's points vertex buffer object */
	glGenBuffers(1, &trianglePointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, trianglePointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trianglePoints), trianglePoints, GL_STATIC_DRAW);

	/* Define the triangle's colors vertex buffer object */
	glGenBuffers(1, &triangleColorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleColorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors), triangleColors, GL_STATIC_DRAW);

	/* Define the triangle's vertex attribute object */
	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, trianglePointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, triangleColorsVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	/* Set up the triangle's vertex shader */
	triangleVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(triangleVertexShader, 1, &triangleVertexShaderSource, NULL);
	glCompileShader(triangleVertexShader);

	/* Set up the triangle's fragment shader */
	triangleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(triangleFragmentShader, 1, &triangleFragmentShaderSource, NULL);
	glCompileShader(triangleFragmentShader);

	/* Set up the triangle's shaders program */
	triangleShaderProgram = glCreateProgram();
	glAttachShader(triangleShaderProgram, triangleVertexShader);
	glAttachShader(triangleShaderProgram, triangleFragmentShader);
	glLinkProgram(triangleShaderProgram);

	/* Get the location of the matrices on the triangle's shader program */
	triangleMVPMatrixLocation = glGetUniformLocation(triangleShaderProgram, "MVP");

}

/**
*	Initializes the hand shaders and the hand shader program
*/
void TreeHands::initHandShaders() {

	/* Define the left Hand's points vertex buffer object */
	glGenBuffers(1, &leftHandPointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, leftHandPointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftHandPoints), leftHandPoints, GL_STREAM_DRAW);

	/* Define the left hand's vertex attribute object */
	glGenVertexArrays(1, &leftHandVAO);
	glBindVertexArray(leftHandVAO);
	glBindBuffer(GL_ARRAY_BUFFER, leftHandPointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	/* Define the right Hand's points vertex buffer object */
	glGenBuffers(1, &rightHandPointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rightHandPointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightHandPoints), rightHandPoints, GL_STREAM_DRAW);

	/* Define the right hand's vertex attribute object */
	glGenVertexArrays(1, &rightHandVAO);
	glBindVertexArray(rightHandVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rightHandPointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	/* Set up the hand's vertex shader */
	handVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(handVertexShader, 1, &handVertexShaderSource, NULL);
	glCompileShader(handVertexShader);

	/* Set up the hand's geometry shader */
	handGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(handGeometryShader, 1, &handGeometryShaderSource, NULL);
	glCompileShader(handGeometryShader);

	/* Set up the hand's fragment shader */
	handFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(handFragmentShader, 1, &handFragmentShaderSource, NULL);
	glCompileShader(handFragmentShader);

	/* Set up the hand's shaders program */
	handShaderProgram = glCreateProgram();
	glAttachShader(handShaderProgram, handVertexShader);
	glAttachShader(handShaderProgram, handGeometryShader);
	glAttachShader(handShaderProgram, handFragmentShader);
	glLinkProgram(handShaderProgram);

	/* Get the location of the matrices on the hand's shader program */
	handMVPMatrixLocation = glGetUniformLocation(handShaderProgram, "MVP");

}

/**
*	Initializes the shader and shader program of the tree of the grammar
*/
void TreeHands::initTreeShaders() {

	/* Define the tree's points vertex buffer object */
	glGenBuffers(1, &treePointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, treePointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treePoints), treePoints, GL_STREAM_DRAW);

	/* Define the tree's vertex attribute object */
	glGenVertexArrays(1, &treeVAO);
	glBindVertexArray(treeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, treePointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	/* Set up the tree's vertex shader */
	treeVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(treeVertexShader, 1, &treeVertexShaderSource, NULL);
	glCompileShader(treeVertexShader);

	/* Set up the tree's fragment shader */
	treeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(treeFragmentShader, 1, &treeFragmentShaderSource, NULL);
	glCompileShader(treeFragmentShader);

	/* Set up the tree's shaders program */
	treeShaderProgram = glCreateProgram();
	glAttachShader(treeShaderProgram, treeVertexShader);
	glAttachShader(treeShaderProgram, treeFragmentShader);
	glLinkProgram(treeShaderProgram);

	/* Get the location of the matrices on the tree's shader program */
	treeMVPMatrixLocation = glGetUniformLocation(treeShaderProgram, "MVP");

}

/**
*	Updates the information of the VBO and VAO of the left hand
*/
void TreeHands::updateLeftHandVertexObjects() {

	/* Define the left Hand's points vertex buffer object */
	glBindBuffer(GL_ARRAY_BUFFER, leftHandPointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftTreeHandPoints), leftTreeHandPoints, GL_STREAM_DRAW);

	/* Define the left hand's vertex attribute object */
	glGenVertexArrays(1, &leftHandVAO);
	glBindVertexArray(leftHandVAO);
	glBindBuffer(GL_ARRAY_BUFFER, leftHandPointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

}

/**
*	Updates the information of the VBO and VAO of the right hand
*/
void TreeHands::updateRightHandVertexObjects() {

	/* Define the right Hand's points vertex buffer object */
	glBindBuffer(GL_ARRAY_BUFFER, rightHandPointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightTreeHandPoints), rightTreeHandPoints, GL_STREAM_DRAW);

	/* Define the right hand's vertex attribute object */
	glGenVertexArrays(1, &rightHandVAO);
	glBindVertexArray(rightHandVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rightHandPointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

}

/**
*	Updates the points of the left hand
*/
void TreeHands::updateLeftHandPoints(Leap::Hand hand) {

	/* Set the position of the elbow */
	leftHandPoints[0] = hand.arm().elbowPosition().x;
	leftHandPoints[1] = hand.arm().elbowPosition().y;
	leftHandPoints[2] = hand.arm().elbowPosition().z;

	/* Set the position of the wrist */
	leftHandPoints[3] = hand.arm().wristPosition().x;
	leftHandPoints[4] = hand.arm().wristPosition().y;
	leftHandPoints[5] = hand.arm().wristPosition().z;

	/* Get the list of finger of the current hand */
	Leap::FingerList fingerList = hand.fingers();

	/* Get the number of detected fingers of the current hand */
	int nFingers = fingerList.count();

	/**/
	int currentIndex = 5;

	/* For each detected finger on the current hand */
	for(int f = 0; f < nFingers; f += 1) {

		/* Set the position of the wrist (again) */
		leftHandPoints[currentIndex + 1] = hand.wristPosition().x;
		leftHandPoints[currentIndex + 2] = hand.wristPosition().y;
		leftHandPoints[currentIndex + 3] = hand.wristPosition().z;
		currentIndex += 3;

		/* Get the current finger */
		Leap::Finger finger = fingerList[f];

		/* For each one of the bones of the finger */
		for(int b = 0; b < 4; b += 1) {

			/* Get the current bone */
			Leap::Bone::Type boneType = static_cast<Leap::Bone::Type>(b);
			Leap::Bone bone = fingerList[f].bone(boneType);

			/* Set the position of the current bone */
			leftHandPoints[currentIndex + 1] = bone.prevJoint().x;
			leftHandPoints[currentIndex + 2] = bone.prevJoint().y;
			leftHandPoints[currentIndex + 3] = bone.prevJoint().z;
			currentIndex += 3;

			/* Set the position of the current bone (again) */
			leftHandPoints[currentIndex + 1] = bone.prevJoint().x;
			leftHandPoints[currentIndex + 2] = bone.prevJoint().y;
			leftHandPoints[currentIndex + 3] = bone.prevJoint().z;
			currentIndex += 3;

		}

		/* Set the position of the finger tip */
		leftHandPoints[currentIndex + 1] = finger.tipPosition().x;
		leftHandPoints[currentIndex + 2] = finger.tipPosition().y;
		leftHandPoints[currentIndex + 3] = finger.tipPosition().z;
		currentIndex += 3;

	}
}

/**
*	Updates the points of the right hand
*/
void TreeHands::updateRightHandPoints(Leap::Hand hand) {

	/* Set the position of the elbow */
	rightHandPoints[0] = hand.arm().elbowPosition().x;
	rightHandPoints[1] = hand.arm().elbowPosition().y;
	rightHandPoints[2] = hand.arm().elbowPosition().z;

	/* Set the position of the wrist */
	rightHandPoints[3] = hand.arm().wristPosition().x;
	rightHandPoints[4] = hand.arm().wristPosition().y;
	rightHandPoints[5] = hand.arm().wristPosition().z;

	/* Get the list of finger of the current hand */
	Leap::FingerList fingerList = hand.fingers();

	/* Get the number of detected fingers of the current hand */
	int nFingers = fingerList.count();

	/**/
	int currentIndex = 5;

	/* For each detected finger on the current hand */
	for(int f = 0; f < nFingers; f += 1) {

		/* Set the position of the hand palm (again) */
		rightHandPoints[currentIndex + 1] = hand.wristPosition().x;
		rightHandPoints[currentIndex + 2] = hand.wristPosition().y;
		rightHandPoints[currentIndex + 3] = hand.wristPosition().z;
		currentIndex += 3;

		/* Get the current finger */
		Leap::Finger finger = fingerList[f];

		/* For each one of the bones of the finger */
		for(int b = 0; b < 4; b += 1) {

			/* Get the current bone */
			Leap::Bone::Type boneType = static_cast<Leap::Bone::Type>(b);
			Leap::Bone bone = fingerList[f].bone(boneType);

			/* Set the position of the current bone */
			rightHandPoints[currentIndex + 1] = bone.prevJoint().x;
			rightHandPoints[currentIndex + 2] = bone.prevJoint().y;
			rightHandPoints[currentIndex + 3] = bone.prevJoint().z;
			currentIndex += 3;

			/* Set the position of the current bone (again) */
			rightHandPoints[currentIndex + 1] = bone.prevJoint().x;
			rightHandPoints[currentIndex + 2] = bone.prevJoint().y;
			rightHandPoints[currentIndex + 3] = bone.prevJoint().z;
			currentIndex += 3;

		}

		/* Set the position of the finger tip */
		rightHandPoints[currentIndex + 1] = finger.tipPosition().x;
		rightHandPoints[currentIndex + 2] = finger.tipPosition().y;
		rightHandPoints[currentIndex + 3] = finger.tipPosition().z;
		currentIndex += 3;

	}

}

/**
*	Updates the points of the tree of the grammar
*/
void TreeHands::updateTreePoints() {

	/* Get the sentence for the requested iteration */
		std::string sentence = lSystem->getIteration(currentIteration);

		/* The turtle that generates the points */
		Turtle turtle(sentence, 20.0f, lSystem->getAngle());

		/* Get the generated points */
		turtle.generatePoints(treePoints, maxTreePoints);

		/* Get the number of generated points */
		nTreePoints = turtle.nGeneratedPoints() * 3;

		/* Update the VBO and VAO of the tree points */
		updateTreePointsVertexObjects();

		/* The current min and max Y values of the generated tree */
		float minY = treePoints[1];
		float maxY = treePoints[1];
	
		/* Traverse the Y-points of the tree */
		for(int y = 4; y < nTreePoints; y += 3) {

			/* Check for the Y-min value */
			if(y < maxTreePoints && treePoints[y] < minY) {

				/* Replace the value */
				minY = treePoints[y];

			}

			/* Check for the Y-max value */
			else if(y < maxTreePoints && treePoints[y] > maxY) {

				/* Replace the value */
				maxY = treePoints[y];

			}

		}

		/* Calculates the height of the tree */
		treeHeight = maxY - minY;

}

/**
 *	Updates the information of the VBO and VAO of the tree points
 */
void TreeHands::updateTreePointsVertexObjects() {

	/* Define the tree's points vertex buffer object */
	glBindBuffer(GL_ARRAY_BUFFER, treePointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treePoints), treePoints, GL_STREAM_DRAW);

	/* Define the tree's vertex attribute object */
	glGenVertexArrays(1, &treeVAO);
	glBindVertexArray(treeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, treePointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

}

/**
*	Generates the next iteration of the grammar
*/
void TreeHands::nextIteration() {

	/* Increment to the next iteration */
	currentIteration += 1;

	/* Update the tree points */
	updateTreePoints();

}

/**
*	Returns to a previous iteration of the grammar
*/
void TreeHands::previousIteration() {

	/* Decrement to the previous iteration */
	currentIteration -= 1;
	
	/* Update the tree points */
	updateTreePoints();

}
