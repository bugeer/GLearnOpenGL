#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../common/stb_image.h"
#include "../common/Shader.h"
#include "../common/camera.h"

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

Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));
float lastX      = WIDTH  / 2.0f;
float lastY      = HEIGHT / 2.0f;
bool  firstMouse = true;
float deltaTime  = 0.0f;
float lastFrame  = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	WIDTH  = width;
	HEIGHT = height;
}

void mouse_callback(GLFWwindow* window, double xp, double yp) {
	float xpos = static_cast<float>(xp);
	float ypos = static_cast<float>(yp);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		std::cout << camera.Position.x << ", "
			<< camera.Position.y << ", "
			<< camera.Position.z << std::endl;
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback      (window, mouse_callback);
    glfwSetScrollCallback         (window, scroll_callback);

	Shader shader("../shaders/camera.vs", "../shaders/camera.fs");

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

	shader.setInt("t2d01", 0);
	shader.setInt("t2d02", 1);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)(WIDTH / HEIGHT), 0.1f, 1000.0f);
		shader.setMat4("projection", projection);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

		glBindVertexArray(VAO);

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);

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
