#include <Core/Core.h>
#include <UltimateOpenGL_V2/UltimateOpenGL.h>
#include <GLFW/glfw3.h>

using namespace Upp;

UltimateOpenGL_Context context; //Context carrying all scene and object (Basicly context is a game)

Vector<float> CubeVertices{
    -0.2f, -0.2f, -0.2f, 0.0f,0.0f,-0.4f, 0.0f, 0.0f,
     0.2f, -0.2f, -0.2f, 0.0f,0.0f,-0.4f, 1.0f, 0.0f,
     0.2f,  0.2f, -0.2f, 0.0f,0.0f,-0.4f, 1.0f, 1.0f,
     0.2f,  0.2f, -0.2f, 0.0f,0.0f,-0.4f, 1.0f, 1.0f,
    -0.2f,  0.2f, -0.2f, 0.0f,0.0f,-0.4f, 0.0f, 1.0f,
    -0.2f, -0.2f, -0.2f, 0.0f,0.0f,-0.4f, 0.0f, 0.0f,

    -0.2f, -0.2f,  0.2f, 0.0f,0.0f, 0.4f, 0.0f, 0.0f,
     0.2f, -0.2f,  0.2f, 0.0f,0.0f, 0.4f, 1.0f, 0.0f,
     0.2f,  0.2f,  0.2f, 0.0f,0.0f, 0.4f, 1.0f, 1.0f,
     0.2f,  0.2f,  0.2f, 0.0f,0.0f, 0.4f, 1.0f, 1.0f,
    -0.2f,  0.2f,  0.2f, 0.0f,0.0f, 0.4f, 0.0f, 1.0f,
    -0.2f, -0.2f,  0.2f, 0.0f,0.0f, 0.4f, 0.0f, 0.0f, 

    -0.2f,  0.2f,  0.2f,  -0.4f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.2f,  0.2f, -0.2f,   -0.4f,  0.0f,  0.0f,1.0f, 1.0f,
    -0.2f, -0.2f, -0.2f,   -0.4f,  0.0f,  0.0f,0.0f, 1.0f,
    -0.2f, -0.2f, -0.2f,   -0.4f,  0.0f,  0.0f,0.0f, 1.0f,
    -0.2f, -0.2f,  0.2f,   -0.4f,  0.0f,  0.0f,0.0f, 0.0f,
    -0.2f,  0.2f,  0.2f,   -0.4f,  0.0f,  0.0f,1.0f, 0.0f,

     0.2f,  0.2f,  0.2f,   0.4f,  0.0f,  0.0f,1.0f, 0.0f,
     0.2f,  0.2f, -0.2f,   0.4f,  0.0f,  0.0f,1.0f, 1.0f,
     0.2f, -0.2f, -0.2f,   0.4f,  0.0f,  0.0f,0.0f, 1.0f,
     0.2f, -0.2f, -0.2f,   0.4f,  0.0f,  0.0f,0.0f, 1.0f,
     0.2f, -0.2f,  0.2f,   0.4f,  0.0f,  0.0f,0.0f, 0.0f,
     0.2f,  0.2f,  0.2f,   0.4f,  0.0f,  0.0f,1.0f, 0.0f,

    -0.2f, -0.2f, -0.2f,    0.0f, -0.4f,  0.0f,0.0f, 1.0f,
     0.2f, -0.2f, -0.2f,    0.0f, -0.4f,  0.0f,1.0f, 1.0f,
     0.2f, -0.2f,  0.2f,    0.0f, -0.4f,  0.0f,1.0f, 0.0f,
     0.2f, -0.2f,  0.2f,    0.0f, -0.4f,  0.0f,1.0f, 0.0f,
    -0.2f, -0.2f,  0.2f,    0.0f, -0.4f,  0.0f,0.0f, 0.0f,
    -0.2f, -0.2f, -0.2f,    0.0f, -0.4f,  0.0f,0.0f, 1.0f,

    -0.2f,  0.2f, -0.2f,    0.0f,  0.4f,  0.0f,0.0f, 1.0f,
     0.2f,  0.2f, -0.2f,    0.0f,  0.4f,  0.0f,1.0f, 1.0f,
     0.2f,  0.2f,  0.2f,   0.0f,  0.4f,  0.0f,1.0f, 0.0f, 
     0.2f,  0.2f,  0.2f,   0.0f,  0.4f,  0.0f, 1.0f, 0.0f,
    -0.2f,  0.2f,  0.2f,    0.0f,  0.4f,  0.0f,0.0f, 0.0f,
    -0.2f,  0.2f, -0.2f,    0.0f,  0.4f,  0.0f,0.0f, 1.0f
};

CONSOLE_APP_MAIN
{
	/*****GLFW INITIALISATION AND OPENGL INITIALISATION USING GLAD ***/
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    context.SetSceneSize(800.0f,600.0f);
    GLFWwindow* window = glfwCreateWindow(800.0f, 600.0f,"Hello UltimateOpenGL", NULL, NULL);
    if (window == NULL)
    {
        Cout() << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        Exit(-1);
    }
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        Cout()  << "Failed to initialize GLAD" << "\n";;
        Exit(-1);
    }
    
    
    //************New code ***********//
    Scene& presentation = context.AddScene("presentation"); //Create Scene 
    unsigned int camera = presentation.AddCamera(); //Adding camera to the scene
    Object3D& cube = presentation.CreateGameObject<Object3D>("cube",CubeVertices); //Adding the cube
    cube.GetTransform().SetNewPosition(glm::vec3(0.0f,0.0f,-1.0f)); // move the cube forward the camera

    presentation.Load(); //Loading the scene
    
    
    //***Adding event on Draw to the cube
    cube.SetOnDrawFunction([](GameObject& myGameObject){
    	myGameObject.GetTransform().RotateFromEulerAngles(0.001f,glm::vec3(1.0f,1.0f,1.0f)); // rotating of 0.001 degree every frame
    });
    

    while(!glfwWindowShouldClose(window)) {
        
        glClearColor(0.4f,0.5f,0.8f, 1.0f); //set Window background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the window
		
		context.Draw(); //Drawing the context (active scene)
	
	    glfwSwapBuffers(window); 
	    glfwPollEvents(); 
	}
	
	glfwTerminate();
	
}
