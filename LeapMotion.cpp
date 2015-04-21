/**
 *	LeapMotion.cpp
 *	Written by: Andres Bejarano
 *
 */

#include "LeapMotion.h"

/**
*	The constructor of the class
*/
LeapMotion::LeapMotion() {

	/* Indicates that no Leap Motion is running */
	running = false;

	/* Add the listener to the controller */
	//controller.addListener(listener);

}

/**
*	Indicates if the Leap Motion is running
*/
bool LeapMotion::isRunning() {

	/* Return if the Leap Motion is running */
	return running;

}

/**
*	Indicates if the Leap Motion is connected
*/
bool LeapMotion::isConnected() {

	/* Return if the Leap Motion is connected */
	return controller.isConnected();

}

/**
*	Send the command to disconnect logically the Leap Motion
*/
void LeapMotion::disconnect() {

	/* Removes the listener from the controller */
	//controller.removeListener(listener);

}

/**
*	Returns the current frame on the Leap Motion
*/
Leap::Frame* LeapMotion::getFrame() {

	/* Returns the current frame on the Leap Motion */
	return &controller.frame();

}

