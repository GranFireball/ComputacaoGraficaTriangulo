#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

std::vector<Mesh*> listMesh;
std::vector<Shader*> listShader;
Window* window;
Camera camera;

//Vertex Array
static const char* VertexLocation = "VertexShader.glsl";

static const char* FragmentLocation = "FragmentShader.glsl";


void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y
		0.0f, 1.0f, 0.0f, //vertice 0 (verde)
		-1.0f, -0.7f, 0.0f, //vertice 1 (preto)
		0.0f, -0.7f, 0.0f, //vertice 2 (vermelho)
		0.0f, -0.7f, 1.0f //vertice 3 (azul)
	};

	GLfloat vertices2[] = {
		//x , y
		0.0f, 1.0f, 0.0f, //vertice 0 (verde)
		0.0f, -0.7f, 0.0f, //vertice 1 (preto)
		1.0f, -0.7f, 0.0f, //vertice 2 (vermelho)
		0.0f, -0.7f, -1.0f //vertice 3 (azul)
	};

	GLuint indice[] = {
		0, 1, 3,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//CreateMesh
	Mesh* obj1 = new Mesh();
	obj1->CrateMesh(vertices, sizeof(vertices), indice, sizeof(indice));
	listMesh.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CrateMesh(vertices2, sizeof(vertices2), indice, sizeof(indice));
	listMesh.push_back(obj2);

}

void CriaShader() {
	Shader* shader = new Shader();
	shader->CreateFromFile(VertexLocation, FragmentLocation);
	listShader.push_back(shader);
}


int main() {
	window = new Window(1024, 768);
	CriaTriangulos();
	CriaShader();

	//Camera
	camera = Camera(glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.5f, 0.5f);

	float triangleOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.05f;
	bool direction = true;

	float rotationOffset = 0.0f, maxRotation = 360.0f, minRotation = -0.1f, incRotation = 0.5f;
	bool rotation = true;

	float scaleOffset = 0.4f, maxScale = 0.7f, minScale = 0.3f, incScale = 0.005f;
	bool scale = true;

	while (!window->ShouldClose()) {

		//Habilitar os eventos do usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.KeyControl(window->GetKeys());
		camera.MouseControl(window->GetXChange(), window->GetYChange());

		//Desenha o triangulo
		Shader* shader = listShader[0];
		shader->UseProgram();

		//Mover o triangulo
		//triangleOffset += direction ? incOffset : incOffset * -1;
		//if (triangleOffset >= maxOffset || triangleOffset <= minOffset) direction = !direction;				

		//Rotacao do triangulo
		rotationOffset += rotation ? incRotation : incRotation * 0.05;
		if (rotationOffset >= maxRotation || rotationOffset <= minRotation) rotation = !rotation;

		//Scale do triangulo
		//scaleOffset += scale ? incScale: incScale * -1;
		//if (scaleOffset >= maxScale || scaleOffset <= minScale) scale = !scale;

		//Triangulo 1
		listMesh[0]->RenderMesh();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

		//Triangulo 2
		listMesh[1]->RenderMesh();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -5.0f));
		model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

		//Proje��o de perspectiva 3D
		glm::mat4 projection = glm::perspective(1.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);
		glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));
		
		glUniformMatrix4fv(shader->GetUniformView(), 1, GL_FALSE, glm::value_ptr(camera.calculateView()));

		glUseProgram(0);

		window->SwapBuffers();
	}

	window->~Window();
	glfwTerminate();
	return 0;
}