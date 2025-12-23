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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct textureCoordOfCell t1={0,0,0.0375,0,0.0375,0.06696428571,0,0.06696428571};
struct textureCoordOfCell t2={0,0,0,0,0,0,0,0};

float MatrixCoordniates[4]=
{
    2.0f,-2.0f,2.0f,2.0f
};

void moveTest(const struct Grid* grid,int* cell,int* prevCell,struct vertexContext* context)
{
    if(*prevCell != *cell)
    {
        SetCell(grid,t2,*prevCell);
        SetCell(grid,t1,*cell);
        gridUpdate(context,grid,*prevCell);
        gridUpdate(context,grid,*cell);
    };
    *prevCell = *cell;
}

int C;

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
    glfwSetKeyCallback(window, key_callback);

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
    struct vertexContext v1;
    const struct Grid * g1 = CreateGrid((float)SCR_WIDTH,(float)SCR_HEIGHT,100.0f,100.0f);
    
    for(int i=0;i<g1->numberOfCells;i++)
    {
        SetCell(g1,t1,i);
    }
    
   
    int size = sizeof(struct vertex)*4*(g1->numberOfCells);
    int numberOfIndices = 6*(g1->numberOfCells);
     //printf("the size of cells is %d/n",size);
    initiliseVertexContext(&v1,size,(g1->cells),GL_STATIC_DRAW,callback1,sizeof(unsigned int)*numberOfIndices,g1->indices);
    glFinish();
    glFlush();
    free(g1->cells);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    //Image and texture loading
    int width,height, nrChannels;
    stbi_set_flip_vertically_on_load(0);  
    unsigned char *data = stbi_load("data/image/GRASS+.png",&width,&height,&nrChannels,0 );
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    //glGenerateMipmap(GL_TEXTURE_2D);
    //printf("error %d",glGetError());
    useShaderContext(a);
    // render loop
    // -----------
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int r=0,b=1;


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
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
        if(C ==1)
        {
            moveTest(g1,&b,&r,&v1);
            b++;
            C=0;
        }

 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        gllog();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    deleteVertexContext(&v1);
    DeleteShaderContext(a);
    GridTerminate(g1);
    free(data);
    glDeleteTextures(1,&texture);
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
    // if(glfwGetKey(window,GLFW_KEY_D) && C!=1)
    // {
    //     printf("\nmoved\n");
    //     C=1;
    // }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_RELEASE)
    {
        if(key==GLFW_KEY_D)
        {
            C=1;
        }
    }
}