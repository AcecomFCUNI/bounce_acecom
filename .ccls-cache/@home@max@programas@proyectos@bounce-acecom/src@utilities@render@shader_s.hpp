#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// program ID
	unsigned int ID;

	// constructor
	Shader(const char* vertexPath, const char* fragmentPath){
		// 1 leyendo los datos de los archivos
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//* ensure ifstream objects can throw exceptions:
    	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    	try{
    		//abriendo archivos
    		vShaderFile.open(vertexPath);
    		fShaderFile.open(fragmentPath);
    		std::stringstream vShaderStream, fShaderStream;

    		//pasando los buffers al stream
    		vShaderStream << vShaderFile.rdbuf();
    		fShaderStream << fShaderFile.rdbuf();

    		//cerrando archivos
    		vShaderFile.close();
    		fShaderFile.close();

    		//convirtiendo el stream en strings
    		vertexCode = vShaderStream.str();
    		fragmentCode = fShaderStream.str();
    	}
    	catch(std::ifstream::failure e){
    		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    	}
    	//string to char pointer
    	const char* vShaderCode = vertexCode.c_str();
    	const char* fShaderCode = fragmentCode.c_str();
    	
    	//2 construyendo el programa
    	unsigned int vertex, fragment;
    	int sucess;
    	char infoLog[512];

    	//vertex shader
    	vertex = glCreateShader(GL_VERTEX_SHADER);
    	glShaderSource(vertex, 1, &vShaderCode, NULL);
    	glCompileShader(vertex);
    	glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);
    	if(!sucess){
    		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}

    	//fragment shader
    	fragment = glCreateShader(GL_FRAGMENT_SHADER);
    	glShaderSource(fragment, 1, &fShaderCode, NULL);
    	glCompileShader(fragment);
    	glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);
    	if(!sucess){
    		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}

    	//shader program
    	ID = glCreateProgram();
    	glAttachShader(ID, vertex);
    	glAttachShader(ID, fragment);
    	glLinkProgram(ID);
    	glGetProgramiv(ID, GL_LINK_STATUS, &sucess);
    	if(!sucess){
    		glGetProgramInfoLog(ID, 512, NULL, infoLog);
    		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    	}

    	//delete shaders
    	glDeleteShader(vertex);
    	glDeleteShader(fragment);
	}
	//* usar/activar el shader
	void use(){
		glUseProgram(ID);
	}
	//* funciones para setear uniform
	void setBool(const std::string &name, bool value) const{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}  
    void setInt(const std::string &name, int value) const{
    	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }   
    void setFloat(const std::string &name, float value) const{
    	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    //agregar setTexture
    
};

#endif