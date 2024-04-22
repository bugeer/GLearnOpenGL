#ifndef __SHADER__
#define __SHADER__

#include <glad/glad.h>

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

