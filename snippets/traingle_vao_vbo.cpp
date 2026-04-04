// Demonstrates: setting up a VAO, VBO and drawing a triangle
int main() {
    // 2 traingles side by side
    float vertices[] = {
        // 1st
        -0.9f, -0.5f, 0.0f, // left
        -0.15f, -0.5f, 0.0f, // right
        -0.25f,  0.5f, 0.0f,  // top
    };
    float vertices1[] = {
        // 2nd
        0.15f, -0.25f, 0.0f, // left
        0.7f, -0.25f, 0.0f, // right
        0.25f,  0.25f, 0.0f  // top
    };

    // setup buffer objects
    unsigned int VBO[2], VAO[2];
    //GLuint VBO, VAO, EBO;

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    //glGenBuffers(1, &EBO);

    // manipulate state for 1st triangle
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // manipulate state for 2nd triangle
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return 0;
}