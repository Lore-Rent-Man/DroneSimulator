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
#include "Shader.h"

using namespace std;
using namespace glm;

class Circle : public Object {
    unsigned int VBO, VAO;
    Shader s = Shader("circlevertexshader.glsl", "circlefragmentshader.glsl");
public:
    Circle() {

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        float right = 0.5;
        float bottom = -0.5;
        float left = -0.5;
        float top = 0.5;
        vertices = {
            //x y z
            right, 0.0f, bottom, 1.0, -1.0,
            right, 0.0f, top, 1.0, 1.0,
            left, 0.0f, top, -1.0, 1.0,
            left, 0.0f, bottom, -1.0, -1.0,
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
        s.use();
        s.setMat4("MVP", MVP);
        s.setVec3("color", color);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    ~Circle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};