#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    int width = 800;
    int height = 800;
    
    GLfloat vertices[] =
    {
         -0.5f, 0.5f * float(sqrt(3)) / 3, 0.0f,
         0.5f, 0.5f * float(sqrt(3)) / 3, 0.0f,
         0.0f, -0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };
    
    //memory pointer for window object denoted with * 
    GLFWwindow* window = glfwCreateWindow(width, height, "window", NULL, NULL);
    //creates current context
    glfwMakeContextCurrent(window);
    //loads glad for gl language
    gladLoadGL();

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos; \n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
        "}\n\0";

    //compiling vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //compiling fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader;
    //building shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //deleting uncompiled shaders to save memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //sets viewport position, and size
    glViewport(0, 0, width, height );
    //sets the color that overrides cleared areas
    glClearColor(0.102f,0.1059f,0.1451f,1.0f);
    //clears buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //replaces front buffer with back buffer
    glfwSwapBuffers(window);


    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.102f, 0.1059f, 0.1451f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    return(0);

    glfwTerminate();
}