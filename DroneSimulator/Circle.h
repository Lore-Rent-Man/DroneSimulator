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
    unsigned int texture;
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

        const int SIZE = 100;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float x[SIZE][SIZE][3];
        /*for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                x[i][j][0] = 1.0f;
                x[i][j][1] = 1.0f;
                x[i][j][2] = 1.0f;
            }
        }*/
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SIZE, SIZE, 0, GL_RGB, GL_FLOAT, x);
        glGenerateMipmap(GL_TEXTURE_2D);
        s.use();
        glUniform1i(glGetUniformLocation(s.ID, "texture1"), 0);
    }

    void draw() {
        s.use();
        s.setMat4("MVP", MVP);
        s.setVec3("color", color);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    ~Circle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};