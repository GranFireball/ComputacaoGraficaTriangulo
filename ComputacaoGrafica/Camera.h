#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera
{
public:
	Camera();
	~Camera();
	Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

	void KeyControl(bool* keys);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	glm::mat4 calculateView();
	

private:
	glm::vec3 position;
	glm::vec3 worldUp;
	GLfloat yaw, pitch;
	GLfloat moveSpeed, turnSpeed;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	void update();
};

