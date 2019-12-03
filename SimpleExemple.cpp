#include <Core/Core.h>
#include <UltimateOpenGL_V3/UltimateOpenGL.h>
#include <GLFW/glfw3.h>

using namespace Upp;

const float screenWidth = 800.0f;
const float screenHeight = 600.0f;


UltimateOpenGL_Context context; //Context carrying all scene and object (Basicly context is a game)

CONSOLE_APP_MAIN
{
	/*****GLFW INITIALISATION AND OPENGL INITIALISATION USING GLAD ***/
	StdLogSetup(LOG_COUT|LOG_FILE);
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti alliasing 
    context.SetScreenSize(screenHeight,screenWidth);
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight,"Hello UltimateOpenGL V3", NULL, NULL);
    
    if (window == nullptr)
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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);   // Anti alliasing 
	
  //***All basic code to set Up glwf is coming before see my exemple or Readme of my GITHUB**/// 
    Scene& myScene = context.AddScene("main");
    myScene.AddCamera("main");
    myScene.SetBackGroundColor(context.TransformRGBToFloatColor(40,180,200));
    
	Object3D& modele =  myScene.CreateGameObject<Object3D>("modele");
	modele.LoadModel("C:\\Upp\\myapps\\ExempleUltimateOpenGL_V3\\obj upp\\upp.obj"); //Loading of model
	
	modele.GetTransform().SetNewPosition(glm::vec3(0,0,-5)); //Set new position 
	modele.GetTransform().ScaleNewValue(glm::vec3(0.05f,0.05f,0.05f)); //Scale the model
	
	modele.SetOnDrawFunction([](GameObject& gm){ //Bind event on draw
		double rotation = glm::cos(context.GetEllapsedTime())/100;
		gm.GetTransform().RotateFromEulerAngles(context.GetDeltaTime() * 2,glm::vec3(0,1,0) );
	});
	
	myScene.Load();
    while(!glfwWindowShouldClose(window)) {
        
		glfwSetWindowTitle(window, "UltimateOpenGL V3 - " +AsString(context.GetFPS()) +" FPS");
		try{
			context.Draw();  //Draw the context
		}catch(UGLException& e){
			LOG(e.what());	
		}
	
	    glfwSwapBuffers(window);
	    glfwPollEvents(); 
	}
	glfwTerminate();
}
