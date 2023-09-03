#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Object.h"

using namespace std;
using namespace glm;

class Circle : public Object {
    int shaderProgram;
    unsigned int VBO, VAO;
public:
    Circle() {

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 pos;\n"
            "layout (location = 1) in vec2 value;\n"
            "uniform mat4 MVP;\n"
            "varying vec2 val;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = MVP * vec4(pos.x, pos.y, pos.z, 1.0);\n"
            "   val = value;\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "varying vec2 val;\n"
            "void main()\n"
            "{\n"
            "   float R = 1.0;\n" 
            "   float R2 = 0.9;\n"
            "   float dist = sqrt(dot(val, val));\n"
            "   if (dist >= R || dist <= R2)\n"
            "{\n"
            "   discard;\n"
            "}\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\n\0";

        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors

        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors


        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        float right = 0.5;
        float bottom = -0.5;
        float left = -0.5;
        float top = 0.5;
        vertices = {
            //x y z
            right, bottom, 0, 1.0, -1.0,
            right, top, 0, 1.0, 1.0,
            left, top, 0, -1.0, 1.0,
            left, bottom, 0, -1.0, -1.0,
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void draw() {
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &color[0]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    ~Circle() {

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }
};