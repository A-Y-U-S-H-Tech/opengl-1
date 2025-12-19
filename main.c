#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <custom/shader.h>
#include <custom/loger.h>
#include <custom/vertex.h>
#include <string.h>
#include <stdio.h>
#include <custom/grid.h>
#define STB_IMAGE_IMPLEMENTATION
#include <external/stdb_image.h>//this library uses math.h as a dependency

void callback1(struct vertexContext*);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float MatrixCoordniates[4]=
{
    2.0f,-2.0f,2.0f,2.0f
};



int main()
{
    int SCR_HEIGHT = 600;
    int SCR_WIDTH = 600;  
    // glfw: initialize and configure
    // ------------------------------
    glfwInitHint(GLFW_PLATFORM,GLFW_PLATFORM_WAYLAND);
    glfwInitHint(GLFW_WAYLAND_LIBDECOR,GLFW_WAYLAND_DISABLE_LIBDECOR);//libedocr add lag resize that is why it is disabled
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD" );
        return -1;
    }
    int width1, height1;
    glfwGetFramebufferSize(window, &width1, &height1);

    glViewport(0, 0, width1,  height1);
    struct shaderContext* a = CreateContext();


    vShader(a,"data/shader/vertex.vs");
    fShader(a,"data/shader/fragment.fs");
    enableShaderContext(a);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    //  POSITION            TEXTURE CORDINATES
      -0.5f, 0.0f, 0.0f,    0.0f,  0.9330357143f,
      -0.5f, 0.5f, 0.0f,    0.0f,  1.0f,
      0.5f,  0.0f, 0.0f,    0.0375f, 0.9330357143f,
      0.5f,  0.0f, 0.0f,    0.0375f, 0.9330357143f,
      -0.5f, 0.5f, 0.0f,    0.0f,  1.0f,
      0.5f,  0.5f, 0.0f,    0.0375f, 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    struct vertexContext v1;
    struct Grid * g1 = CreateGrid((float)SCR_WIDTH,(float)SCR_HEIGHT,5.0f,5.0f);

   
    int size = sizeof(struct vertex)*4*(g1->numberOfCells);
    int size2 = 4*6*(g1->numberOfCells);
     //printf("the size of cells is %d/n",size);
    initiliseVertexContext(&v1,size,(g1->cells),GL_STATIC_DRAW,callback1,size2,g1->indices);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Image and texture loading
    //enableVertextContext(&v1);
    //printf("123 error  %d",glGetError());
    int width,height, nrChannels;
    stbi_set_flip_vertically_on_load(1);  
    unsigned char *data = stbi_load("data/image/GRASS+.png",&width,&height,&nrChannels,0 );
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    //glGenerateMipmap(GL_TEXTURE_2D);
    //printf("error %d",glGetError());
    useShaderContext(a);
    glUniform1i(glGetUniformLocation(a->program, "ourTexture"), 0);
    unsigned int transformLoc = glGetUniformLocation(a->program, "transform");
    glUniformMatrix2fv(transformLoc, 1, GL_FALSE,&(MatrixCoordniates[0]));
    // render loop
    // -----------
    useShaderContext(a);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        
        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        enableVertextContext(&v1);
        //glDrawArrays(GL_TRIANGLES, 0, g1->numberOfCells);
        glDrawElements(GL_TRIANGLES, size2, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        gllog();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    deleteVertexContext(&v1);
    DeleteShaderContext(a);
    free(g1->cells);
    free(g1->indices);
    free(g1);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void callback1(struct vertexContext* context)
{
    enableVertextContext(context);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(struct vertex),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(struct vertex),(void*)(sizeof(struct position)));
    glEnableVertexAttribArray(1);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

