#include "Window.h"

Window::Window() {
	width = 800;
	height = 600;
	Initialize();
}

Window::Window(GLint width, GLint height) {
	Window::width = width;
	Window::height = height;
	Initialize();
}

Window::~Window() {
	glfwDestroyWindow(window);
}

int Window::Initialize() {
	for (int i = 0; i < 1024; i++) {
		keys[i] = false;
	}

	if (!glfwInit()) {
		printf("GLFW: Não pode ser iniciado");
		return 1;
	};

	window = glfwCreateWindow(800, 600, "Ola Mundo!", NULL, NULL);
	if (!window) {
		printf("GLFW: Não foi possível criar janela");
		glfwTerminate;
		return 1;
	}

	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("Glew: Não pode ser iniciado!");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
		;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(window, this);

	CreateCallBacks();
}

void Window::CreateCallBacks() {
	glfwSetKeyCallback(window, handleKeys);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("APERTOU: %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("SOLTOU: %d\n", key);
		}
	}
}

