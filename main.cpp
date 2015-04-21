/**
 *	main.cpp
 *	Written by: Andres Bejarano
 *
 */

#include "TreeHands.h"

/**
 *	The TreeHands reference
 */
TreeHands* application;

/**
 *	The width of the window
 */
int windowWidth = 800;

/**
 *	The height of the window
 */
int windowHeight = 600;

/**
 *	Indicates if the window is fullscreen
 */
bool fullscreen = false;

bool drawHelp = true;

/**
 *	Function called in each loop of the OpenGL pipeline
 */
void onDraw(void)  {

	/* Updates the information of the program */
	application->update();

	/* Draws the information */
	application->draw();

}

/**
 *
 */
void onIdle() {

	/* Calls glutDisplayFunc callback function */
	glutPostRedisplay();

}

/**
 * Function called when the windows is reshaped
 */
void onReshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 600.0f);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Function called when a key is pressed
 */
void onKeyPressed(unsigned char key, int x, int y) {

	switch(key) {

		/* The ESC key */
		case 27:

			/* Exits the program */
			exit(0);

			break;

		/* Press 'f' or 'F' to toggle fullscreen mode */
		case 'f':
		case 'F':

			/* If it is right now on fullscreen mode */
			if(fullscreen) {

				/* Resize the window to its gridinal size */
				glutReshapeWindow(windowWidth, windowHeight);

			}
			else {

				/* Set the fullscreen mode */
				glutFullScreen();

			}

			/* Toggles the fullscreen state indicator */
			fullscreen = !fullscreen;

			break;

		/* Press 'g' or 'G' to toggle the rendering of the gridin and the grid */
		case 'g':
		case 'G':
			{
				/* Toggles the drawing of the origin and the grid */
				application->drawGrid = !application->drawGrid;

			}
			break;

		/* Press 't' or 'T' to toggle the rendering of the RGB triangle */
		case 't':
		case 'T':
			{
				/* Toggles the drawing of the RGB triangle */
				application->drawTriangle = !application->drawTriangle;

			}
			break;

		/* Press 'e' or 'E' to toggle the rendering of the tree */
		case 'e':
		case 'E':
			{

				/* Toggles the drawing of the rendering of the tree */
				application->drawTree = !application->drawTree;

			}
			break;

		/* Press '+' to increment by 1 the number of iterations of the grammar */
		case '+':
			{
				/* Generate the next iteration */
				application->nextIteration();

			}
			break;

		/* Press '-' to decrement by 1 the number of iterations of the grammar */
		case '-':
			{
				/* If there is at least one iteration */
				if(application->currentIteration > 0) {

					/* Return to the previous iteration */
					application->previousIteration();

				}
			}
			break;

		/* Press 'h' or 'H' to show the help */
		case 'h':
		case 'H':
			{
				system("cls");
				std::cout << "+-------------------------------------------------------+" << std::endl;
				std::cout << "| TreeHands - GUI controls                              |" << std::endl;
				std::cout << "|                                                       |" << std::endl;
				std::cout << "| -Press h to show the GUI control message              |" << std::endl;
				std::cout << "| -Press t to show/hide the reference triangle          |" << std::endl;
				std::cout << "| -Press g to show/hide the reference grid              |" << std::endl;
				std::cout << "| -Press e to show/hide the generated tree              |" << std::endl;
				std::cout << "| -Press f to toggle the fullscreen visualization       |" << std::endl;
				std::cout << "| -Press + to increment the iterations of the grammar   |" << std::endl;
				std::cout << "| -Press - to decrement the iterations of the grammar   |" << std::endl;
				std::cout << "| -Press LEFT or RIGHT to rotate the camera             |" << std::endl;
				std::cout << "| -Press UP to increment the distance of the camera     |" << std::endl;
				std::cout << "| -Press DOWN to decrement the distance of the camera   |" << std::endl;
				std::cout << "| -Press ESC to exit                                    |" << std::endl;
				std::cout << "+-------------------------------------------------------+" << std::endl;
			}

	}

}

/**
 * Function called when a special key is pressed
 */
void onSpecialKeyPressed(int key, int x, int y) {

	switch(key) {
	
	/* Press 'UP' to set the position of the visualization camera a little bit closer */
	case GLUT_KEY_UP:
		{
			/* Get the vector from the eye location to the target location, and normalize it */
			glm::vec3 d = glm::normalize(application->camEye - application->camTarget);

			/* Subtract the new vector to the eye location of the visualization camera */
			application->camEye = application->camEye - d;

		}
		break;

	/* Press 'DOWN' to set the position of the visualization camera a little bit farther */
	case GLUT_KEY_DOWN:
		{
			/* Get the vector from the eye location to the target location, and normalize it */
			glm::vec3 d = glm::normalize(application->camEye - application->camTarget);

			/* Add the new vector to the eye location of the visualization camera */
			application->camEye = application->camEye + d;

		}
		break;

	/* Press 'LEFT' to speed up the rotation to the left */
	case GLUT_KEY_LEFT:
		{
			/* Increment the left speed rotation to the left */
			application->camYawSpeed -= 0.1f;

		}
		break;

	/* Press 'RIGHT' to speed up the rotation to the left */
	case GLUT_KEY_RIGHT:
		{
			/* Increment the right speed rotation to the left */
			application->camYawSpeed += 0.1f;

		}
		break;

	}
}

/**
 *
 */
void onKeyUp(unsigned char key, int x, int y) {

	// TODO

}

/**
 *	Function called when the window is about to be closed
 */
void onClose() {

	/* Disconnects the Leap Motion */
	application->leapMotion->disconnect();

}

/**
 *	The main function of the program
 */
int main(int argc, char** argv) {

	/* Read the grammar (if any) from console */
	//std::string grammar = (argc > 0) ? argv[0] : "25.7;F F[+F][-F];";
	


	/* Define window position */
	HDC hdc = GetDC(NULL);
	int screenWidth = GetDeviceCaps(hdc, HORZRES);
	int screenHeight = GetDeviceCaps(hdc, VERTRES);
	int winXPos = (screenWidth >= windowWidth) ? (screenWidth - windowWidth) / 2 : 0;
	int winYPos = (screenHeight >= windowHeight) ? (screenHeight - windowHeight) / 2 : 0;

	/* Initialize window */
	glutInit(&argc, argv);

	std::string grammar;
	char* cGrammar;
	std::cout << "+------------------------------------------------------------------+" << std::endl;
	std::cout << "| TreeHands                                                        |" << std::endl;
	std::cout << "| By: Andres Bejarano                                              |" << std::endl;
	std::cout << "|                                                                  |" << std::endl;
	std::cout << "| Before starting the program, please insert a grammar. It must    |" << std::endl;
	std::cout << "| follow the next format:                                          |" << std::endl;
	std::cout << "|                                                                  |" << std::endl;
	std::cout << "| 1) Expressions must be separated by semicolons                   |" << std::endl;
	std::cout << "| 2) The first value is the rotation angle                         |" << std::endl;
	std::cout << "| 3) The next are the rotation symbols:                            |" << std::endl;
	std::cout << "|    + and - for +Z and -Z rotation                                |" << std::endl;
	std::cout << "|    & and % for +Y and -Y rotation                                |" << std::endl;
	std::cout << "|    # and / for +X and -X rotation                                |" << std::endl;
	std::cout << "|    [ and ] for push and pop operations                           |" << std::endl;
	std::cout << "| 4) Letter and derivations are separated by >                     |" << std::endl;
	std::cout << "|                                                                  |" << std::endl;
	std::cout << "|                                                                  |" << std::endl;
	std::cout << "| Example: 25.7;F>F[+A][-F];A>F;                                   |" << std::endl;
	std::cout << "|                                                                  |" << std::endl;
	std::cout << "+------------------------------------------------------------------+" << std::endl;
	std::cout << "Insert the grammar: ";
	std::cin >> cGrammar;
	grammar = cGrammar;
	std::cout << "Grammar is: " << grammar << std::endl;

	/* Initialize GLUT (actually Freeglut) */
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(winXPos, winYPos);
	glutCreateWindow("TreeHands");

	/* Set up freeglut callbacks */
	glutDisplayFunc(onDraw);
	glutCloseFunc(onClose);
	glutIdleFunc(onIdle);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyPressed);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialFunc(onSpecialKeyPressed);

	/* Set up GLEW */
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		return 0;
	}

	/* Initializes the application */
	application = new TreeHands(grammar);

	/* Shows the versions of OpenGL and GLEW */
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;

	/* Run loop */
	glutMainLoop();

	/* Exists the program (not reachable) */
	return 0;

}
