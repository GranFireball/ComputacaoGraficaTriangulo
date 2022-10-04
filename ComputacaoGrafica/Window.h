#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Window
{
public:
	Window();

	Window(GLint width, GLint height);
	int Initialize();
	~Window();

	bool ShouldClose() { return glfwWindowShouldClose(window); }
	GLfloat GetBufferWidth() { return (GLfloat)bufferWidth; }
	GLfloat GetBufferHeight() { return (GLfloat)bufferHeight; }
	void SwapBuffers() { return glfwSwapBuffers(window); }

private:
	GLFWwindow* window;
	GLint width, height;
	int bufferWidth, bufferHeight;

	//Callbacks
	void CreateCallBacks();

	//teclas
	bool keys[1024];

	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);

};

