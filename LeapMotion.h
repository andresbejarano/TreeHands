/**
 *	LeapMotion.h
 *	Written by: Andres Bejarano
 *
 */

#ifndef _LEAPMOTION_H_
#define _LEAPMOTION_H_

#include "Leap.h"

/**
*	An interface for listening the events on the Leap Motion
*/
class LeapMotionListener : public Leap::Listener {

public:

	/**
	*	Function called when a Leap Motion is connected
	*/
	//virtual void onConnect(const Leap::Controller& controller);

	/**
	*	Function called when a new frame is generated
	*/
	//virtual void onFrame(const Leap::Controller& controller);

};


/**
*	An object representing a Leap Motion
*/
class LeapMotion {

public:

	/**
	*	The constructor of the class
	*/
	LeapMotion();

	/**
	*	Send the command to disconnect logically the Leap Motion
	*/
	void disconnect();

	/**
	*	Indicates if the Leap Motion is running
	*/
	bool isRunning();

	/**
	*	Indicates if the Leap Motion is connected
	*/
	bool isConnected();

	/**
	*	Returns the current frame on the Leap Motion
	*/
	Leap::Frame* getFrame();

	/**
	*	A listener to the events of the Leap Motion
	*/
	LeapMotionListener listener;

	/**
	*	The reference to the Leap Motion controller
	*/
	Leap::Controller controller;

	/**
	*	Indicates if the Leap Motion is running
	*/
	bool running;

};

#endif
