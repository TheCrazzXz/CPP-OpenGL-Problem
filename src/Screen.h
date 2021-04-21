#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen
{
public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	Screen();
	bool init();

	void setParameters();
	//main loop
	void update();
	void newFrame();

	//window closing accessor and modifier
	bool ShouldClose();
	void setShouldClose(bool shouldClose);

	bool isKeyPressed(int key);

private:
	GLFWwindow* window;
};

#endif