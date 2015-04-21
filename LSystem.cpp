/**
 *	LSystem.cpp
 *	Written by: Andres Bejarano
 */

#include <stack>
#include "LSystem.h"
#include "GL\freeglut.h"

/**
 *	Checks if two vec4 (actually vec3) vectors are the same
 */
bool equal(glm::vec4 v1, glm::vec4 v2) {

	/* Compares if the (x, y, z) values are the same */
	return(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);

}

/**
*	The constructor of the class
*/
Rule::Rule(const std::string l, const std::string p) {

	/* Stores the predecessor of the rule */
	letter = l;

	/* Stores tue successor of the rule */
	phrase = p;

}

/**
*	The constructor of the class
*/
LSystem::LSystem(const std::string g) {

	/* Sets the new grammar and build the system */
	setGrammar(g);

}

/**
*	Generates and return the next iteration
*/
std::string LSystem::generate() {

	/* Get the last iteration */
	std::string last = iterations.at(iterations.size() - 1);

	/* The length of the last iteration */
	int nLast = last.size();

	/* Where each token of the iteration will be stored */
	std::string token;

	/* The string where the current iteration will be stored */
	std::stringstream it;

	/* The size of the ruleset */
	int nRuleset = ruleset.size();

	/* For each one of the tokens of the last iteration */
	for(int j = 0; j < nLast; j += 1) {

		/* Get the current token */
		token = last.substr(j, 1);

		/* Where successors will be stored */
		std::string replace = token;

		/* For each one of the rules on the grammar */
		for(int r = 0; r < nRuleset; r += 1) {

			/* If the predecessor of the current rule is equal to the token */
			if(ruleset.at(r).letter.compare(token) == 0) {

				/* Store the successor of the rule */
				replace = ruleset.at(r).phrase;

				/* Break the for loop */
				break;

			}
		}

		/* Add the new element to the generated string */
		it << replace;

	}

	/* Get the generated iteration in string format */
	std::string generated = it.str();

	/* Stores the generated iteration */
	iterations.push_back(generated);

	/* Return the last generated iteration */
	return generated;

}

/**
*	Returns the current rotation angle of the grammar
*/
float LSystem::getAngle() {

	/* Return the current rotation angle */
	return angle;

}

/**
*	Return the n-th iteration of the grammar
*/
std::string LSystem::getIteration(int n) {

	/* The number of currently generated iterations of the grammar */
	int nIterations = iterations.size();

	/* If it is requested an already generated iteration */
	if(n < nIterations) {

		/* Return the requested generation */
		return iterations.at(n);

	}
	else {

		/* Where the requested iteration will be stored */
		std::string requested;

		/* For the last generated iteration until the requested one */
		for(int i = nIterations - 1; i < n; i += 1) {

			/* Generate a new iteration of the grammar */
			requested = generate();

		}

		/* Return the requested iteration */
		return requested;

	}
}

/**
*	Return the las generated iteration
*/
std::string LSystem::getLastIteration() {

	/* Return the last stored iteration */
	return iterations.at(iterations.size() - 1);

}

/**
*	Returns the number of iterations
*/
int LSystem::nIterations() {

	/* Return the number of iterations*/
	return iterations.size();

}

/**
*	Returns the number of rules
*/
int LSystem::nRules() {

	/* Return the number of rules */
	return ruleset.size();

}

/**
*	Set the rotation angle of the grammar
*/
void LSystem::setAngle(float a) {

	/* Sets the new rotation angle */
	angle = a;

}

/**
*	Sets a new grammar to the system
*	Previous values are updated to the new grammar
*/
void LSystem::setGrammar(std::string g) {

	/* Sets the new grammar */
	grammar = g;

	/* Makes an internal copy of the grammar */
	std::string gram = g;

	/* Clean the ruleset vector */
	ruleset.clear();

	/* Clean the generated iterations vector */
	iterations.clear();

	/* Supporting variables for traversing the grammar */
	size_t pos = 0;
	std::string token;

	/* Indicates if the first line of the grammar (rotation angle) has been read */
	bool firstLine = false;

	/* Traverse the grammar until the last semicolon */
	while((pos = gram.find(";")) != std::string::npos) {

		/* Get the line until the next semicolon */
		token = gram.substr(0, pos);

		/* If the first line has not been read */
		if(!firstLine) {

			std::cout << "Read angle = " << token << std::endl;

			/* Stores the rotation angle as float */
			angle = (float)std::atof(token.c_str());

			/* Indicates that the first line of the grammar (rotation angle) has been read */
			firstLine = true;

		}
		else {

			/* Gets the position of the blank space */
			size_t pos2 = token.find(">");

			/* Get the predecessor of the rule */
			std::string pred = token.substr(0, pos2);

			/* Removes the predecessor on the current line */
			token.erase(0, pos2 + 1);

			/* Get the successor of the rule */
			std::string suc = token;

			/* Stores the elements of the rule in the rules vector */
			ruleset.push_back(Rule(pred, suc));

		}

		/* Remove the read part of the grammar */
		gram.erase(0, pos + 1);

	}

	/* The first iteration is the predecessor of the first rule */
	iterations.push_back(ruleset.at(0).letter);

	writeGrammar();

}

/**
*	Write the iterations generated so far
*/
void LSystem::writeIterations() {

	/* The number of iterations so far */
	int n = iterations.size();

	/* For each one of the generated iterations */
	for(int i = 0; i < n; i += 1) {

		/* Write the iteration */
		std::cout << i << ": " << iterations.at(i) << std::endl;

	}

}

/**
*	Write the grammar on console/terminal
*/
void LSystem::writeGrammar() {

	/* Write the rotation angle of the grammar */
	std::cout << "angle: " << angle << std::endl;

	/* Get the number of rules of the grammar */
	int n = ruleset.size();

	/* For each rule on the grammar */
	for(int i = 0; i < n; i += 1) {

		/* Write the rule */
		std::cout << ruleset.at(i).letter << "->" << ruleset.at(i).phrase << std::endl;

	}

}

/**
*	The constructor of the class
*/
Turtle::Turtle(std::string s, float l, float t) {

	/* The sentence for generating the points */
	sentence = s;

	/* The length of the line segments */
	length = l;

	/* The number of generated points (0 by now) */
	nPoints = 0;

	/* The rotation angle */
	theta = t;

}

/**
*	Generate the points
*/
float* Turtle::generatePoints(GLfloat* srcPoints, int maxPoints) {

	/**/
	int addedPoints = 0;

	/* The vector of generated points */
	std::vector<glm::vec4> points;

	/* The stack of matrices */
	std::stack<glm::mat4> matrixStack;

	/* The transformation matrix translatedn to P */
	glm::mat4 matrix;

	/* The size of the sentence */
	int nSentence = sentence.size();

	/* For each token in the sentence */
	for(int i = 0; i < nSentence; i += 1) {

		/* Get the i-th token */
		std::string token = sentence.substr(i, 1);

		/* If token is '[' then push the current matrix */
		if(token.compare("[") == 0) {

			/* Push the matrix */
			matrixStack.push(glm::mat4(matrix));
		
		}

		/* If token is ']' then pop the last matrix */
		else if(token.compare("]") == 0) {

			/* Pop the matrix */
			matrix = matrixStack.top();
			matrixStack.pop();
		
		}

		/* If token is '+' then rotate +Z */
		else if(token.compare("+") == 0) {

			/* Rotate the matrix */
			matrix = glm::rotate(matrix, theta, glm::vec3(0.0f, 0.0f, 1.0f));
		
		}

		/* If token is '-' then rotate -Z */
		else if(token.compare("-") == 0) {

			/* Rotate the matrix */
			matrix = glm::rotate(matrix, -theta, glm::vec3(0.0f, 0.0f, 1.0f));
		
		}

		/* If token is '&' then rotate +Y */
		else if(token.compare("&") == 0) {

			/* Rotate the matrix */
			matrix = glm::rotate(matrix, theta, glm::vec3(0.0f, 1.0f, 0.0f));
		
		}

		/* If token is '%' then rotate -Y */
		else if(token.compare("%") == 0) {

			/* Rotate the matrix */
			matrix = glm::rotate(matrix, -theta, glm::vec3(0.0f, 1.0f, 0.0f));
		
		}

		/* If token is '#' then rotate +X */
		else if(token.compare("#") == 0) {

			/* Rotate the matrix */
			matrix = glm::rotate(matrix, theta, glm::vec3(1.0f, 0.0f, 0.0f));
		
		}

		/* If token is '/' then rotate -X */
		else if(token.compare("/") == 0) {

			/* Rotate the matrix */
			matrix = glm::rotate(matrix, -theta, glm::vec3(1.0f, 0.0f, 0.0f));
		
		}

		/* It is a letter, define a line */
		else {

			/* Generate the first point of the segment */
			glm::vec4 p1 = matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

			/* Generates the second point of the segment */
			glm::vec4 p2 = glm::translate(matrix, glm::vec3(0.0f, length, 0.0f)) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

			/* Indicates whether the points are in the vector */
			bool alreadyInVector = false;

			/* The size of the vector */
			int nVector = points.size();

			/* For each pair of points already in vector */
			for(int g = 0; g < nVector; g += 2) {

				/* Check the new points with the current pair of points */
				if(equal(points.at(g), p1) && equal(points.at(g + 1), p2)) {
					alreadyInVector = true;
					break;
				}
			}

			/* If points are not in vector */
			if(!alreadyInVector) {

				/* Add p1 to the vector */
				points.push_back(p1);
			
				/* Add p2 to the vector */
				points.push_back(p2);

				addedPoints += 6;

				/* Warn if maximum number of tree points reached */
				if(addedPoints >= maxPoints) {
					std::cout << "Generation stopped: max number of possible points reached" << std::endl;
					break;
				}

			}

			/* Translates the location */
			matrix = glm::translate(matrix, glm::vec3(0.0, length, 0.0f));
		
		}

	}
	
	/* Get the number of added vertices */
	nPoints = points.size();

	addedPoints = 0;
	
	/**/
	for(int i = 0; i < nPoints; i += 1) {

		/**/
		GLfloat vX = points.at(i).x;
		GLfloat vY = points.at(i).y;
		GLfloat vZ = points.at(i).z;

		/**/
		srcPoints[addedPoints] = vX;
		srcPoints[addedPoints + 1] = vY;
		srcPoints[addedPoints + 2] = vZ;
		addedPoints += 3;

		/* Break the loop if all possible positions are filled */
		if(addedPoints >= maxPoints) {break;}

	}

	std::cout << "Generated " << addedPoints << " tree points" << std::endl;
	
	/* Fill the remaining positions of the array */
	if(addedPoints < maxPoints) {
		
		for(int i = addedPoints; i < maxPoints; i += 1) {srcPoints[i] = (GLfloat)0.0f;}

	}

}

/**
*	Return the number of generated points from the last call to generatePoints function
*/
int Turtle::nGeneratedPoints() {

	/* Return the number of generated points */
	return nPoints;

}
