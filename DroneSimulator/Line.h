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

class Line : public Object {
    unsigned int VBO, VAO;
    Shader s = Shader("objectvertexshader.glsl", "objectfragmentshader.glsl");
    vec3 startPoint;
    vec3 endPoint;
public:
    Line(vec3 start, vec3 end) {

        startPoint = start;
        endPoint = end;

        vertices = {
             start.x, start.y, start.z,
             end.x, end.y, end.z,
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void draw() {
        s.use();
        s.setMat4("MVP", MVP);
        s.setVec3("color", color);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
    }

    ~Line() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};