#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "Shader.h"
#include "Quadcopter.h"
#include "Circle.h"
#include "Camera.h"
#include "Axes.h"
#include "Fluid.h"
#include <Windows.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const float ASPECT_RATIO = SCR_WIDTH / SCR_HEIGHT;

Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.01667f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Basic Quadcopter Variables
float k = 0.12265f;
float b = 0.01f;

//Fluid Simulation Variables
const int F_W_SIZE = SCR_WIDTH;
const int F_H_SIZE = SCR_HEIGHT;

vector<splatPointer> sB;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    //glEnable(GL_DEPTH_TEST);
    //glLineWidth(5.0);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------

    /*glm::vec3 start{ 0, 0, 0 };
    glm::vec3 end{ 5, 5, 5 };

    Quadcopter q = Quadcopter(k, b);
    q.setColor(glm::vec3{ 0.0, 0.0, 0.0 });

    Axes a = Axes();

    Circle c = Circle();*/

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    Fluid f = Fluid(F_W_SIZE, F_H_SIZE, 1, SCR_WIDTH, SCR_HEIGHT);

    float frameRate = 0.01667;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

         // bind textures on corresponding texture units

        // activate shader
        //glm::mat4 view = camera.GetViewMatrix(); // make sure to initialize matrix to identity matrix first
        //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        //glm::mat4 model = q.update(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, deltaTime);
        //
        //a.setMVP(projection * view);
        //a.draw();

        //q.setMVP(projection * view * model);
        //q.drawQuadcopter();

        //c.setColor(glm::vec3{ 0.0, 0.0, 0.0 });
        //c.setMVP(projection * view);
        //c.draw();

        /*f.advectionShader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);*/

        if (!sB.empty() && !sB[0].down)
        {
            sB.pop_back();
        }
        else if (!sB.empty())
        {
            if (sB[0].moved) {
                sB[0].moved = false;
                f.splat(sB[0]);
            }
        }

        f.step(frameRate);
        f.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);

    int pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (pressed == GLFW_PRESS && !sB.empty())
    {
        sB[0].prevTexcoordX = sB[0].texcoordX;
        sB[0].prevTexcoordY = sB[0].texcoordY;
        sB[0].texcoordX = xpos / SCR_WIDTH;
        sB[0].texcoordY = 1.0f - ypos / SCR_HEIGHT;
        sB[0].deltaX = (sB[0].texcoordX - sB[0].prevTexcoordX) * ASPECT_RATIO;
        sB[0].deltaY = (sB[0].texcoordY - sB[0].prevTexcoordY) * ASPECT_RATIO;
        sB[0].moved = abs(sB[0].deltaX) > 0 || abs(sB[0].deltaY) > 0;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    struct find_id : std::unary_function<splatPointer, bool> {
        DWORD id;
        find_id(DWORD id) :id(id) { }
        bool operator()(splatPointer const& m) const {
            return m.id == id;
        }
    };

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        auto it = std::find_if(sB.begin(), sB.end(), find_id(-1));
        if (it == sB.end())
        { 
            splatPointer p;
            p.down = true;
            p.texcoordX = xpos / SCR_WIDTH;
            p.texcoordY = 1.0f - ypos / SCR_HEIGHT;            
            sB.push_back(p);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && !sB.empty()) {
        sB[0].down = false;
    }
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}