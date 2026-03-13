#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <external/stdb_image.h>//this library uses math.h as a dependency

#include <custom/shader.h>
#include <custom/loger.h>
#include <custom/ui/color.h>
#include <custom/vertex.h>
#include <custom/grid.h>
#include <custom/Sprite.h>
#include <custom/Matrix.h>
#include <custom/ui/text.h>




void callback1(struct vertexContext*);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct spriteCordinates t1,t2;

float MatrixCoordniates[4]=
{
    2.0f,-2.0f,2.0f,2.0f
};
int SCR_HEIGHT = 32*20;
int SCR_WIDTH = 32*40;  

int C=0;

int main()
{

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
    const struct Grid * g1 = CreateGrid((float)width1,(float)height1,64.0f,64.0f);
  
    spriteParameter p1 ={16.00000000f,16.00000000f};
    SpriteSheetContext ss = SetSpriteSheet("data/image/GRASS+.png",p1);
    t1 = GetSprite(ss,0);
    t2 = GetSprite(ss,0);

    for(int i=0;i<g1->numberOfCells;i++)
    {
            SetCell(g1,t2,i);
    }
    t2 = GetSprite(ss,0);
    for(int i=0;i<g1->numberOfCells;i++)
    {
        if(i%2==0)
        {
            SetCell(g1,t2,i);
            continue;
        }
        if(i%5==0)
        {
            SetCell(g1,GetSprite(ss,0),i);
            continue;
        }
        SetCell(g1,t1,i);
    }
    
   
    int size = sizeof(struct vertex)*4*(g1->numberOfCells);
    int numberOfIndices = 6*(g1->numberOfCells);
     //printf("the size of cells is %d/n",size);
    initiliseVertexContext(&v1,size,(g1->cells),GL_STATIC_DRAW,callback1,sizeof(unsigned int)*numberOfIndices,g1->indices);

    useShaderContext(a);

    useSpriteSheet(ss,*a,"ourTexture");

    struct Matrix3x3 projMAtrix=ScreenProjection(SCR_WIDTH,SCR_HEIGHT);
    projMAtrix=ScreenProjection(width1,height1);
    glUniformMatrix3fv(glGetUniformLocation(a->program,"transform"),1,GL_FALSE,GetMatrix3x3Pointer(&projMAtrix));
    struct Matrix4x4 rot = Rotatez(0.0f/180.0f*22.0f/7.0f);
    glUniformMatrix4fv(glGetUniformLocation(a->program,"rotation"),1,GL_FALSE,GetMatrix4x4Pointer(&rot));
    // render loop
    // -----------
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    int r=0,b=1;
    

    useShaderContext(a);
    // glfwSetTime(0.00111);
    // double initalTime = glfwGetTime();
    // double finalTime = 0;
    // double frame=0;
    char s[] ="email:- ayush@gmail.com";
    char s2[] = "(!&**!)";
    struct CharectorCollection*  cc1 = CreateCharectorCollection(50,"data/shader/text.vs","data/shader/text.fs",1,"data/font/arial/ARIAL.TTF",120);
    RenderText(cc1);
    CreateStaticText(cc1,-500.0f,0.0f,s,sizeof(s),COLOR_PALE_PINK);
    CreateStaticText(cc1,-500.0f,200.0f,s2,sizeof(s2),COLOR_BLUE);
    RenderText(cc1);
    glUniformMatrix3fv(glGetUniformLocation(cc1->scontext->program,"transform"),1,GL_FALSE,GetMatrix3x3Pointer(&projMAtrix));
    glUniform1i(glGetUniformLocation(cc1->scontext->program,"ourTexture"),1);


    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----  
        if(C ==1)
        {
            projMAtrix=ScreenProjection(SCR_WIDTH,SCR_HEIGHT);
            glUniformMatrix3fv(glGetUniformLocation(a->program,"transform"),1,GL_FALSE,GetMatrix3x3Pointer(&projMAtrix));
            glUniformMatrix3fv(glGetUniformLocation(cc1->scontext->program,"transform"),1,GL_FALSE,GetMatrix3x3Pointer(&projMAtrix));
            C =0;
        }
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        
        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDisable(GL_BLEND);
        useShaderContext(a);
        enableVertextContext(&v1);
        //glPixelStorei(GL_UNPACK_ALIGNMENT,4);
        glActiveTexture(GL_TEXTURE0);
        //glDrawArrays(GL_TRIANGLES, 0, g1->numberOfCells);
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
        RenderText(cc1);
        glDrawElements(GL_TRIANGLES, cc1->size*6, GL_UNSIGNED_INT,0);
        // glBindVertexArray(0); // no need to unbind it every time 
        // if(C ==1)
        // {
        //     moveTest(g1,&b,&r,&v1);
        //     b++;
        //     C=0;
        // }
        // useShaderContext(s1);
        // enableVertextContext(&v1);
        // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

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
    DeleteSpriteSheet(ss);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    DeleteCollection(cc1);
    glfwTerminate();
    return 0;
}



void callback(struct vertexContext* context)
{
    enableVertextContext(context);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(struct charectorVertex),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(struct charectorVertex),(void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(struct charectorVertex),(void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);
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
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
    C = 1 ;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_RELEASE)
    {
        if(key==GLFW_KEY_D)
        {
            
        }
    }
}