#include "shader.h"

#include <glad/glad.h> // glad manages function pointers for OpenGL
#include <GLFW/glfw3.h>

#include <iostream>

// handle window resize
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const GLuint windowHeight = 800;
const GLuint windowWidth = 600;

int main()
{
    // initialize glfw
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window object
    GLFWwindow* window = glfwCreateWindow(windowHeight, windowWidth, "HelloOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    // inittialize glad before calling any opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    // configure the size of the rendering window for opengl
    glViewport(0, 0, fbWidth, fbHeight);

    // compile shaders and link shader program for star vertices
    Shader starShader("./shaders/star.vert", "./shaders/star.frag");
    
    // star vertices
    GLfloat vertices[] = {
        // position         // color
        0.0f, 0.9f, 0.0f,   1.0f, 0.0f, 0.0f, // 0, top
        -0.5f, 0.3f, 0.0f,  0.0f, 1.0f, 0.0f,// 1, outer left 2nd level
        -0.13f, 0.3f, 0.0f, 0.5f, 0.5f, 0.0f,// 2, inner left 2nd level
        0.13f, 0.3f, 0.0f,  0.0f, 0.5f, 0.5f,// 3, inner right 2nd level
        0.5f, 0.3f, 0.0f,   1.0f, 0.0f, 1.0f,// 4, outer right 2nd level
        -0.25f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f,// 5, left 3rd level
        0.1f, 0.0f, 0.0f,   0.0f, 0.5f, 0.5f,// 6, right 3rd level
        0.0f, -0.15f, 0.0f, 0.0f, 1.0f, 0.0f,// 7, bottom
        -0.3f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,// 8, bottom left
        0.3f, -0.4f, 0.0f,  0.0f, 0.0f, 1.0f,// 9, bottom right
    };

    GLint indices[] = {
        0, 5, 9,   // 1st triangle
        1, 2, 5,    // 2nd triangle
        3, 4, 6,   // 3rd triangle
        5, 8, 7    // 4th triangle
    };

    // setup buffer objects
    GLuint VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute for vertex attribute on attribute location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // handle input
        processInput(window);

        // rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // get and set uniform variable location for redColor
        starShader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optionally deallocate resources
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();
    return 0;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // close window if escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}