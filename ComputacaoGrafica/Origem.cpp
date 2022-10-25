#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

std::vector<Mesh*> listMesh;
std::vector<Shader*> listShader;
Window * window;
Camera camera;
Texture brickTexture;
Texture groundTexture;


//Vertex Shader
static const char* VertexLocation = "VertexShader.glsl";
static const char* FragmenetLocation = "FragmentShader.glsl";

void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y	, z	
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f,    //Vertice 0 (x,y,z,u,v)
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  //Vertice 1 (x,y,z,u,v)
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   //Vertice 2 (x,y,z,u,v)
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f    //Vertice 3 (x,y,z,u,v)
	};

	GLuint indice[] = {
		0, 1, 3,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//CreateMesh
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, sizeof(vertices), indice, sizeof(indice));
	listMesh.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, sizeof(vertices), indice, sizeof(indice));
	listMesh.push_back(obj2);

	GLfloat verticesChao[] = {
		-10.0f, 0.0f, -10.0f, 0.0f, 0.0f,  // 1 - x,y,z,u,v
		-10.0f, 0.0f, 10.0f, 0.0f, 10.0f,  // 2 - x,y,z,u,v
		10.0f, 0.0f, 10.0f, 10.0f, 10.0f,  // 3 - x,y,z,u,v
		10.0f, 0.0f, -10.0f, 10.0f, 0.0f,  // 4 - x,y,z,u,v
	};

	GLuint indiceChao[] = {
		0, 1, 3,
		1, 2, 3
	};

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(verticesChao, sizeof(verticesChao), indiceChao, sizeof(indiceChao));
	listMesh.push_back(obj3);

}


void CriaShader() {
	Shader* shader = new Shader();
	shader->CreateFromFile(VertexLocation, FragmenetLocation);
	listShader.push_back(shader);
}


int main() {
	window = new Window(1024, 768);

	CriaTriangulos();
	CriaShader();

	//Camera
	camera = Camera(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture((char*)"Texture/brick.png");
	brickTexture.loadTexture();
	groundTexture = Texture((char*)"Texture/ground.png");
	groundTexture.loadTexture();

	float triangleOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.05f;
	bool direction = true;

	float rotationOffset = 0.0f, maxRotation = 360.0f, minRotation = -0.1f, incRotation = 0.5f;
	bool rotation = true;

	float scaleOffset = 0.4f, maxScale = 0.7f, minScale = 0.3f, incScale = 0.005f;
	bool scale = true;

	while (!window->ShouldClose()) {
		
		//Habilitar os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.KeyControl(window->GetKeys());
		camera.MouseControl(window->GetXChange(), window->GetYChange());

		//Desenha o triangulo
		Shader* shader = listShader[0];
		shader->UseProgram();
			
				//Mover o triangulo
				triangleOffset += direction ? incOffset : incOffset * -1;
				if (triangleOffset >= maxOffset || triangleOffset <= minOffset)
					direction = !direction;

				//Rotação do triangulo
				rotationOffset += rotation ? incRotation : incRotation * -1;
				if (rotationOffset >= maxRotation || rotationOffset <= minRotation)
					rotation = !rotation;

				//Scale do triangulo
				scaleOffset += scale ? incScale : incScale * -1;
				if (scaleOffset >= maxScale || scaleOffset <= minScale)
					scale = !scale;
				
				/*
				* Triangulo 1
				*/
				brickTexture.useTexture();												
				glm::mat4 model(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
				glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
				listMesh[0]->RenderMesh();

				/*
				* Triangulo 2
				*/
				brickTexture.useTexture();				
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));				
				glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
				listMesh[1]->RenderMesh();

				/*
				* Chao
				*/
				groundTexture.useTexture();
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));				
				glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
				listMesh[2]->RenderMesh();

				//Projeção de perspectiva 3D
				glm::mat4 projection = glm::perspective(1.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);
				glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));

				glUniformMatrix4fv(shader->GetUniformView(), 1, GL_FALSE, glm::value_ptr(camera.calculateView()));
				
		glUseProgram(0);

		window->SwapBuffers();
	}

	window->~Window();
	return 0;
}