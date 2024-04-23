#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../common/stb_image.h"
#include "../common/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum RenderMode {
	POLYGON  = 0,
	POLYLINE = 1,
};

static RenderMode rm = RenderMode::POLYGON;
static int WIDTH  = 800;
static int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	WIDTH  = width;
	HEIGHT = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_M:
			rm = rm == RenderMode::POLYGON ? RenderMode::POLYLINE : RenderMode::POLYGON;
			if (rm == RenderMode::POLYGON) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if (rm == RenderMode::POLYLINE) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			break;
		case GLFW_KEY_Q:
			glfwSetWindowShouldClose(window, true);
			break;
		default:
			break;
		}
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpengL-1.8 Coordinate systems", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader("../shaders/coordinate.vs", "../shaders/coordinate.fs");

	glm::vec3 cubePositions[] = {
		glm::vec3(+0.0f, +0.0f, +0.0f ),
		glm::vec3(+2.0f, +5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f ),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(+2.4f, -0.4f, -3.5f ),
		glm::vec3(-1.7f, +3.0f, -7.5f ),
		glm::vec3(+1.3f, -2.0f, -2.5f ),
		glm::vec3(+1.5f, +2.0f, -2.5f ),
		glm::vec3(+1.5f, +0.2f, -1.5f ),
		glm::vec3(-1.3f, +1.0f, -1.5f ),
	};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, +0.5f, -0.5f, -0.5f,  1.0f, 0.0f, +0.5f, +0.5f, -0.5f,  1.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,  1.0f, 1.0f, -0.5f, +0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f, +0.5f,  0.0f, 0.0f, +0.5f, -0.5f, +0.5f,  1.0f, 0.0f, +0.5f, +0.5f, +0.5f,  1.0f, 1.0f,
		+0.5f, +0.5f, +0.5f,  1.0f, 1.0f, -0.5f, +0.5f, +0.5f,  0.0f, 1.0f, -0.5f, -0.5f, +0.5f,  0.0f, 0.0f,

		-0.5f, +0.5f, +0.5f,  1.0f, 0.0f, -0.5f, +0.5f, -0.5f,  1.0f, 1.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -0.5f, -0.5f, +0.5f,  0.0f, 0.0f, -0.5f, +0.5f, +0.5f,  1.0f, 0.0f,

		+0.5f, +0.5f, +0.5f,  1.0f, 0.0f, +0.5f, +0.5f, -0.5f,  1.0f, 1.0f, +0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,  0.0f, 1.0f, +0.5f, -0.5f, +0.5f,  0.0f, 0.0f, +0.5f, +0.5f, +0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, +0.5f, -0.5f, -0.5f,  1.0f, 1.0f, +0.5f, -0.5f, +0.5f,  1.0f, 0.0f,
		+0.5f, -0.5f, +0.5f,  1.0f, 0.0f, -0.5f, -0.5f, +0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f, +0.5f, -0.5f,  0.0f, 1.0f, +0.5f, +0.5f, -0.5f,  1.0f, 1.0f, +0.5f, +0.5f, +0.5f,  1.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,  1.0f, 0.0f, -0.5f, +0.5f, +0.5f,  0.0f, 0.0f, -0.5f, +0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int VBO;
	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1;
	unsigned int texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../res/container.jpg", &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("../res/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader.use();
	shader.setInt("t2d01", 0);
	shader.setInt("t2d02", 1);

	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();

		glm::mat4 M = glm::mat4(1.0f);
		glm::mat4 T = glm::mat4(1.0f);
		glm::mat4 V = glm::mat4(1.0f);
		glm::mat4 P = glm::mat4(1.0f);
		V = glm::translate(V, glm::vec3(0.0f, 0.0f, -8.0f));
		P = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 1000.0f);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; ++i) {
			T = glm::translate(T, cubePositions[i]);
			M = glm::rotate(T, (float)(i+glfwGetTime()), glm::vec3(0.5f, 1.0f, 0.0f));
			shader.setMat4("model",      M);
			shader.setMat4("view",       V);
			shader.setMat4("projection", P);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}
