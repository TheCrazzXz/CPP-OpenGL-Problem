#include <iostream>
//include glad before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "graphics/Shader.h"
#include "Camera.h"
#include "Screen.h"
#include "graphics/Texture.h"
#include "object/models/Cube.hpp"

unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;

Screen screen;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(double dt);

int main()
{
	glfwInit();

	//OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__
	
	if (!screen.init())
	{
		std::cerr << "Error : Failed to create GLFW Window :(" << std::endl;
		glfwTerminate();
		return -1;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//If GLAD initialization has failed
		std::cerr << "Error : Failed to initialize GLAD :(" << std::endl;
		glfwTerminate();
		return -1;
	}
	screen.setParameters();

	Shader shader("assets/object.vs", "assets/object.frag");

	Cube cube(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f), "assets/image.png");
	Cube cube2(glm::vec3(2.0f, 0.0f, -1.0f), glm::vec3(1.0f), "assets/image.png");
	cube.init();
	cube2.init();
	
	//Textures
	shader.activate();

	while (!screen.ShouldClose())
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		//Process Key input
		processInput(deltaTime);

		//Render
		screen.update();

		shader.activate();
		//Update :
		cube.pos = glm::vec3(cube.pos.x, cube.pos.y, cube.pos.z + currentTime / 10000);
		cube.setRotation(glm::vec3(0.5f), (float)glfwGetTime()* glm::radians(-55.0f));
		cube2.setRotation(glm::vec3(0.5f), (float)glfwGetTime() * glm::radians(-55.0f));
		//create transformation for screen
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.activate();
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		cube.render(shader);
		cube2.render(shader);

		//sends new frame to window
		screen.newFrame();
	}
	cube.cleanUp();
	cube2.cleanUp();

	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}
void processInput(double dt)
{
	float dx = 0;
	float dy = 0;

	if (screen.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		screen.setShouldClose(true);
	}
	if (screen.isKeyPressed(GLFW_KEY_UP))
	{
		camera.updateCameraPos(CameraDirection::FORWARD, dt);
	}
	if (screen.isKeyPressed(GLFW_KEY_DOWN))
	{
		camera.updateCameraPos(CameraDirection::BACKWARD, dt);
	}
	if (screen.isKeyPressed(GLFW_KEY_LEFT))
	{
		camera.updateCameraPos(CameraDirection::LEFT, dt);
	}
	if (screen.isKeyPressed(GLFW_KEY_RIGHT))
	{
		camera.updateCameraPos(CameraDirection::RIGHT, dt);
	}
	if (screen.isKeyPressed(GLFW_KEY_W))
	{
		std::cout << "A" << std::endl;
		dx += 0.1f;
	}
	if (screen.isKeyPressed(GLFW_KEY_Q))
	{
		std::cout << "Z" << std::endl;
		dx -= 0.1f;
	}
	if (screen.isKeyPressed(GLFW_KEY_E))
	{
		std::cout << "E" << std::endl;
		dy += 0.1f;
	}
	if (screen.isKeyPressed(GLFW_KEY_R))
	{
		std::cout << "R" << std::endl;
		dy -= 0.1f;
	}
	camera.updateCameraDirection(dx, dy);
}