
#include "Shader.h"
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>





    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        
        std::cout << "Vertex Shader Path: " << vertexPath << std::endl;
        std::cout << "Fragment Shader Path: " << fragmentPath << std::endl;

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

           
            if (!vShaderFile.is_open()) {
                std::cout << "ERROR: Could not open vertex shader file: " << vertexPath << std::endl;
            }

           
            if (!fShaderFile.is_open()) {
                std::cout << "ERROR: Could not open fragment shader file: " << fragmentPath << std::endl;
            }

            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            if (vShaderStream.str().empty()) {
                std::cout << "ERROR: Vertex shader file is empty or failed to load." << std::endl;
            }
            if (fShaderStream.str().empty()) {
                std::cout << "ERROR: Fragment shader file is empty or failed to load." << std::endl;
            }
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" <<e.what()<< std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
       

         // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        // print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
   
    void Shader::use()
    {
        glUseProgram(ID);
    }
    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);      

    }
    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setTransform(const std::string& name, glm::mat4 trans) const
    {
        unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    }

    void Shader::setModel(const std::string& model_name, glm::mat4 model, const std::string& view_name, glm::mat4 view, const std::string& projection_name, glm::mat4 projection) const
    {
        int modelLoc = glGetUniformLocation(ID, model_name.c_str());
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(ID, view_name.c_str());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(ID, projection_name.c_str());
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }


