#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);

    GLfloat vertices[] =
    {
         -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       // Esquina inferior izq
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        // Esquina inferior derecha
         0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   // Esquina superior
         -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,      // Interior izquierda
         0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    // Interior derecha
         0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f        // Interior abajo
    };

    GLfloat insideVertex[] =
    {
         -0.45f, -0.45f * float(sqrt(3)) / 3, 0.0f,       // Esquina inferior izq
         -0.5f / 2, 0.5f * float(sqrt(1.5f)) / 6, 0.0f,      // Interior izquierda
         -0.05f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Interior abajo


         0.05f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Interior abajo
         0.45f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Esquina inferior derecha
         0.5f / 2, 0.5f * float(sqrt(1.5f)) / 6, 0.0f,   // Esquina superior

         -0.4f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f,      // Interior izquierda
         0.0f, 0.45f * float(sqrt(3)) * 2 / 3, 0.0f,   // Esquina superior
         0.4f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f,    // Interior derecha
    };

    GLuint indices[] =
    {
    0, 3, 5, // Triangulo inferior izq
    3, 2, 4, // Triangulo inferior der
    5, 4, 1 // Triangulo superior
    };

    GLuint insideIndex[] =
    {
    0, 1, 2, // Triangulo inferior izq
    3, 4, 5, // Triangulo inferior der
    6, 7, 8 // Triangulo superior
    };

    glfwMakeContextCurrent(window);
    gladLoadGL();

    // creacion de shaders
    Shader outerTris("default.frag", "default.vert");
    Shader innterTris("inner.frag", "inner.vert");
    
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    EBO EBO1(indices, sizeof(indices));
    
    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glViewport(0, 0, 800, 800);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5255f, 0.8706f, 0.4471, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        outerTris.Activate();
        innterTris.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //limpia el buffer para liberar la gpu
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    innterTris.Delete();
    outerTris.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();
}