#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed) {
	Camera::position = position;
	Camera::worldUp = worldUp;
	Camera::yaw = yaw;
	Camera::pitch = pitch;
	Camera::moveSpeed = moveSpeed;
	Camera::turnSpeed = turnSpeed;

	update();
}

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::update() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::cross(front, worldUp);
	right = glm::normalize(right);

	up = glm::cross(right, front);
	up = glm::normalize(up);
}

void Camera::KeyControl(bool* keys) {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		position += front * moveSpeed;
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		position -= front * moveSpeed;
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		position += right * moveSpeed;
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		position -= right * moveSpeed;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange) {
	yaw += xChange;
	pitch += yChange;

	if (pitch >= 90.0f) {
		pitch = 90.0f;
	}
	else if (pitch <= -90.0f) {
		pitch = -90.0f;
	}

	update();
}

glm::mat4 Camera::calculateView() {
	return glm::lookAt(position, position + front, up);
}