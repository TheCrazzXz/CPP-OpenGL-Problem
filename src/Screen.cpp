#include "Screen.h"

unsigned int Screen::SCR_WIDTH = 800;
unsigned int Screen::SCR_HEIGHT = 600;

void Screen::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	Screen::SCR_WIDTH = width;
	Screen::SCR_HEIGHT = height;
}
Screen::Screen() : window(nullptr)
{
}
bool Screen::init()
{
	window = glfwCreateWindow(Screen::SCR_WIDTH, Screen::SCR_HEIGHT, "Game", NULL, NULL);
	if (!window)
	{
		//Window not created
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}
void Screen::setParameters()
{
	glViewport(0, 0, Screen::SCR_WIDTH, Screen::SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, Screen::framebufferSizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glEnable(GL_DEPTH_TEST);
}
void Screen::update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Screen::newFrame()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
bool Screen::ShouldClose()
{
	return glfwWindowShouldClose(window);
}
void Screen::setShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}
bool Screen::isKeyPressed(int key)
{
	if (glfwGetKey(window, key) == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}