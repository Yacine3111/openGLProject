#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>


using namespace std;

//vertex shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                 "}\0";
//fragment shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
                                   "}\n\0";

int main() {
    //Initialize GLFW
    glfwInit();

    //Tell GFLW what version of openGl we are using. Currently, the 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Tell GLFW witch profile of openGl function we are using.
    //We are currently using the CORE profile so only the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Vertices coordinates (x,y,z)
    GLfloat vertices[] =
            {
                    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,//lower left corner
                    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,//lower right corner
                    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f//Upper corner
            };

    int windowWidth = 800;
    int windowHeight = 800;

    //Creating a GLFW window object
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "My window", nullptr, nullptr);

    if (window == nullptr) {
        cout << "Failed to create the window";
        return -1;
    }

    //Put the object window into the current context of GLFW
    glfwMakeContextCurrent(window);

    //Loading glad to have access to openGL
    gladLoadGL();

    //Specifies the location of rendering of openGL. Currently, our hole window
    glViewport(0, 0, windowWidth, windowHeight);

    // Create Vertex Shader object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Attach vertex shader source to the vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // compile the vertex shader into machine code
    glCompileShader(vertexShader);

    // Create fragment Shader object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Attach fragment shader source to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    // compile the fragment shader into machine code
    glCompileShader(vertexShader);

    //create shader program object and get its reference
    GLuint shaderProgram = glCreateProgram();

    // Attach the vertex and fragment shaders to the shader program;
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/link all the shaders together into the shader program
    glLinkProgram(shaderProgram);

    //delete the now useless vertex and fragment shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Create reference container for the vertex array object and the vertex buffer object
    GLuint VAO, VBO;

    //Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Make the VAO the current vertex array object by binding it
    glBindVertexArray(VAO);

    // Bind the vbo specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the vertex attribute so that openGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    // Enable the vertex attribute so that openGL know to use it
    glEnableVertexAttribArray(0);

    //Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //specify the background color of the window
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //change the back buffer to the new color
    glClear(GL_COLOR_BUFFER_BIT);
    //swap the front buffer with the back buffer
    glfwSwapBuffers(window);

    //we show the window until an action close it
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell openGL which shader program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so openGL knows to use it
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        //To make the window response to the action that are made toward it
        glfwPollEvents();
    }

    //Delete all the object we created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //we delete the window
    glfwDestroyWindow(window);

    //we stop glfw
    glfwTerminate();
    return 0;
}