/**
 *	LSystem.h
 *	Written by: Andres Bejarano
 *
 *	Adapted ideas from: The Nature of Code, by Daniel Shiffman
 *	http://natureofcode.com/book/chapter-8-fractals/
 */

#ifndef _LSYSTEM_H_
#define _LSYSTEM_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

/**/
#include "GL\freeglut.h"

/* Include the OpenGL Math header */
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

/**
 *	The representation of a rule for a L-System
 */
class Rule {

public:

	/**
	 *	The letter of the rule
	 */
	std::string letter;

	/**
	 *	The phrase of the rule
	 */
	std::string phrase;

	/**
	 *	The constructor of the class
	 */
	Rule(const std::string l, const std::string p);

};

/**
 *	A class representing a L-System
 */
class LSystem {

public:

	/**
	 *	The constructor of the class
	 */
	LSystem(const std::string g);

	/**
	 *	Generates and return the next iterarion
	 */
	std::string generate();

	/**
	 *	Returns the current rotation angle of the grammar
	 */
	float getAngle();

	/**
	 *	Returns the n iteration over the grammar
	 */
	std::string getIteration(int n);

	/**
	 *	Return the las generated iteration
	 */
	std::string getLastIteration();

	/**
	 *	Returns the number of iterations
	 */
	int nIterations();

	/**
	 *	Returns the number of rules
	 */
	int nRules();

	/**
	 *	Set the rotation angle of the grammar
	 */
	void setAngle(float a);

	/**
	 *	Sets a new grammar to the system
	 */
	void setGrammar(std::string g);

	/**
	 *	Write the grammar on console/terminal
	 */
	void writeGrammar();

	/**
	 *	Write the iterations generated so far
	 */
	void writeIterations();

private:

	/**
	 *	The grammar of the system
	 */
	std::string grammar;

	/**
	 *	The initial sentence (axiom)
	 */
	std::string sentence;

	/**
	 *	The ruleset (array of Rule objects)
	 */
	std::vector<Rule> ruleset;

	/**
	 *	The set of generated iterations
	 */
	std::vector<std::string> iterations;

	/**
	 *	Keep track of the number of the last generated iteration
	 */
	int lastGeneratedIteration;

	/**
	 *	The rotation angle of the system
	 */
	float angle;

};

/**
 *	The class representing the turtle rendering for L-Systems
 */
class Turtle {

public:

	/**
	 *	The constructor of the class
	 */
	Turtle(std::string s, float l, float t);

	/**
	 *	Generate the points
	 */
	float* generatePoints(GLfloat* points, int maxPoints);

	/**
	 *	Return the number of generated points from the last call to generatePoints function
	 */
	int nGeneratedPoints();

private:

	/**
	 *	The sentence to generate the points
	 */
	std::string sentence;

	/**
	 *	The length of each line segment
	 */
	float length;

	/**
	 *	The number of generated points
	 */
	int nPoints;

	/**
	 *	The rotation angle
	 */
	float theta;

};

#endif
