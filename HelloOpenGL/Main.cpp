#include <glad/glad.h> // glad manages function pointers for OpenGL
#include <GLFW/glfw3.h>

#include <iostream>

// handle window resize
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const GLuint windowHeight = 800;
const GLuint windowWidth = 600;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const GLchar* yelowFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

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

    // configure the size of the rendering window for opengl
    glViewport(0, 0, windowWidth, windowHeight);

    // setup for object buffers and shader programs
    // compile shaders and link shader program before setting up buffer objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    GLuint yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(yellowFragmentShader, 1, &yelowFragmentShaderSource, NULL);
    glCompileShader(yellowFragmentShader);

    glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKER_FAILED\n" << infoLog << std::endl;
    }

    GLuint yellowShaderProgram;
    yellowShaderProgram = glCreateProgram();

    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowFragmentShader);
    glLinkProgram(yellowShaderProgram);

    glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::YELLO_SHADER::PROGRAM::LINKER_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(yellowFragmentShader);

    // traingle
    //GLfloat vertices[] = {
    //    -0.5f, -0.5f, 0.0f, // left
    //     0.5f, -0.5f, 0.0f, // right
    //     0.0f,  0.5f, 0.0f  // top
    //};

    // 2 traingles side by side
    GLfloat vertices[] = {
        // 1st
        -0.9f, -0.5f, 0.0f, // left
        -0.15f, -0.5f, 0.0f, // right
        -0.25f,  0.5f, 0.0f,  // top
    };
    GLfloat vertices1[] = {
        // 2nd
        0.15f, -0.25f, 0.0f, // left
        0.7f, -0.25f, 0.0f, // right
        0.25f,  0.25f, 0.0f  // top
    };

    // square
    //GLfloat vertices[] = {
    //    0.5f,  0.5f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};

    //GLint indices[] = {
    //    0, 1, 3,   // first triangle, starts from 0!
    //    1, 2, 3    // second triangle
    //};

    // setup buffer objects
    GLuint VBO, VAO;
    GLuint VBO1, VAO1;
    //GLuint VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    //glGenBuffers(1, &EBO);
    
    // bind the Vertex Array Object first
    // manipulate state for 1st triangle
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glBindVertexArray(0); // no need to unbind, 2nd triangle will bind another vao

    // manipulate state for 2nd triangle
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // registers VBO as the vertex attribute's bound vertex buffer object
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); // not necessary: there are no other vao to bind and no function calls that could affect currently binded vao is used

    // bind and copy indices for ebo
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // can unbind vbo safely
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind vao
    //glBindVertexArray(0); // 

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

        // use shader program
        glUseProgram(shaderProgram);
        // render 1st triangle using first vao data, "VAO"
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // use second shader program for 2nd triangle
        // render 2nd triangle using 2nd vao data "VAO1"
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optionally deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteProgram(shaderProgram);

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