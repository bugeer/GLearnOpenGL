#ifndef __SHADER__
#define __SHADER__

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

const unsigned int LogLen = 1024;

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vShaderSource;
		std::string fShaderSource;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vss, fss;
			vss << vShaderFile.rdbuf();
			fss << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vShaderSource = vss.str();
			fShaderSource = fss.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		unsigned int vShader, fShader;
		const char* vShaderCode = vShaderSource.c_str();
		const char* fShaderCode = fShaderSource.c_str();

		std::cout << vShaderCode << std::endl;
		std::cout << std::endl;
		std::cout << fShaderCode << std::endl;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vShaderCode, NULL);
		glCompileShader(vShader);
		checkCompileError(vShader, "VERTEX");

		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fShaderCode, NULL);
		glCompileShader(fShader);
		checkCompileError(fShader, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vShader);
		glAttachShader(ID, fShader);
		glLinkProgram(ID);
		checkCompileError(ID, "PROGRAM");

		glDeleteShader(vShader);
		glDeleteShader(fShader);
	}
	void use() {
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool  value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setInt(const std::string& name, int   value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat2f(const std::string& name, float v1, float v2) const {
		glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2);
	}
	void setVec2(const std::string &name, const glm::vec2 & value) const  {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, const glm::vec3 & value) const  {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, const glm::vec4 & value) const  {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, float x, float y) const  {
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void setVec3(const std::string &name, float x, float y, float z) const  {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec4(const std::string &name, float x, float y, float z, float w) const  {
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void setMat2(const std::string &name, const glm::mat2 & value) const  {
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void setMat3(const std::string &name, const glm::mat3 & value) const  {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void setMat4(const std::string &name, const glm::mat4 & value) const  {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

private:
	void checkCompileError(unsigned int shader, std::string type) {
		int success;
		char infoLog[LogLen];

		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, LogLen, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR OF TYPE: " << type << std::endl
					<< infoLog << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, LogLen, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR OF TYPE" << type << std::endl
					<< infoLog << std::endl;
			}
		}
	}
};

#endif // !__SHADER__

