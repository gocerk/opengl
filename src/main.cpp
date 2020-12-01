#include <iostream> 
#include <glad/glad.h> 
#include "library.hpp"
#include <GLFW/glfw3.h> 
#include <glm/mat4x4.hpp> 

using namespace std ; 

// vertex shader 
char* vssource = 
"#version 330 core\n                    \
layout (location = 0) in vec3 inPoisiton;\ 
void main()\
{                                       \
    gl_Position = vec4(inPosition , 1.0) \
}" ; 

// fragment shader 
char* fssource = 
"#version 330 core\n                \
 out vec4 fragColor ;               \
 void main()                        \
 {                                  \
    fragColor = vec4(1.0f , 0.0f , 0.0f , 1.0f) \  
}";
float vertices[] = {
    -0.6f , -0.6f , 0.0f , 
     0.5f , 0.5f , 0.0f , 
     0.0f , 0.5f , 0.0  
};

unsigned int programid ; 
int main(int argc , char**argv)
{
    if (!glfwInit())
        return -1; 
    
    GLFWwindow* window = glfwCreateWindow(700 , 700 , "First app" , NULL , NULL) ;
    

    if (window == NULL)
    {
        cout << "Pencere olusturulamadi" << endl ; 
        glfwTerminate() ; 

        return -1 ; 
    }
    glfwMakeContextCurrent(window) ;

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Glad yuklenemedi" << endl ;
        return -1 ; 
    }

    programid = glCreateProgram() ; 

    unsigned int vertexShaderid = glCreateShader(GL_VERTEX_SHADER) ; 
    glShaderSource(vertexShaderid , 1, &vssource , NULL) ; 
    glCompileShader(vertexShaderid) ; 
    // fssource object  

    unsigned int fragmentshaerid = glCreateShader(GL_FRAGMENT_SHADER) ; 
    glShaderSource(fragmentshaerid , 1 , &fssource , NULL) ; 
    glCompileShader(fragmentshaerid) ; 

    glAttachShader(programid , vertexShaderid) ; 
    glAttachShader(programid , fragmentshaerid) ; 

    glLinkProgram(programid) ; 

    // buffer 
    unsigned int vbo ; 
    glGenBuffers(1 , &vbo) ;    
    glBindBuffer(GL_ARRAY_BUFFER , vbo) ; 
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW) ; 
    
    unsigned int vao ; 
    glGenVertexArrays(1 , &vao) ; 
    glBindVertexArray(vao) ; 
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , sizeof(float)*3 , (void*)0) ; 

    glEnableVertexAttribArray(0) ; 



    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f , 0.12f , 0.2f , 0.1f) ; 
        glClear(GL_COLOR_BUFFER_BIT) ; 
        glUseProgram(programid) ; 
        glBindVertexArray(vao) ; 
        glDrawArrays(GL_TRIANGLES , 0 , 3) ; 

        glfwSwapBuffers(window) ;
        glfwPollEvents() ; 

    } 
    return 0 ; 
}