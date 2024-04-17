#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <vector>

#include "render/shader_loading.hpp"
#include "render/2D_figure_renderization.hpp"
#include "../utilities/render/texture_loading.hpp"
#include "colisions/check_colisions.hpp"
#include "window/main_window.hpp"

const double FIXED_DELTA_TIME = 0.0033;

inline ShaderLoader* shaderLoader = ShaderLoader::GetInstance();

const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

inline lemur_object* lemur;
inline std::vector<object_color> colorObjects;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processFrame(GLFWwindow* window, double delta);

int main_game();
void start_configuration();
void game_loop();
void exit_configuration();

inline int main_game(){

	start_configuration();
	game_loop();
	exit_configuration();

	return 0;
}

inline void start_configuration(){
	std::cout<<"config"<<std::endl;
	glfwInit();
	MainWindow::ConfigWindow(SCR_WIDTH, SCR_HEIGHT);

	std::cout<<"Window Size: " << MainWindow::screenHeight << "X" << MainWindow::screenWidth << std::endl;

	if(MainWindow::Get()->glfw() == nullptr) return;

	glfwMakeContextCurrent(MainWindow::Get()->glfw());
    glfwSetFramebufferSizeCallback(MainWindow::Get()->glfw(), frameBufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    	std::cout<<"Failed to initialize GLAD"<<std::endl;
    }

    //charge shader
    std::cout<<"chargingShader"<<std::endl;
    shaderLoader->LoadShader(
    	"../assets/shaders/TextureRenderization/TextureShader.vert", 
    	"../assets/shaders/TextureRenderization/TextureShader.frag");

    shaderLoader->LoadShader(
    	"../assets/shaders/ColorRenderization/ColorRenderization.vert", 
    	"../assets/shaders/ColorRenderization/ColorRenderization.frag");

    //charge texture
	std::cout<<"charging texture"<<std::endl;
    UploadTexture("../assets/textures/lemur.png");

    //GenerateObjects
	lemur = new lemur_object(true);
    object_color player1 = object_color(0.f, -0.7f, 0.3f, 0.05f, 1.0f, 10.f);
    object_color player2 = object_color(0.f, 0.7f, 0.3f, 0.05f, 1.0f, 10.f);
    colorObjects.push_back(player1);
    colorObjects.push_back(player2);

}


inline void game_loop(){
	while(!glfwWindowShouldClose(MainWindow::Get()->glfw())){
		processFrame(MainWindow::Get()->glfw(), FIXED_DELTA_TIME);

		//render ACECOM texture
		glClear(GL_COLOR_BUFFER_BIT);
		shaderLoader->GetShader(0).use();
		lemur->RenderObject();

		shaderLoader->GetShader(1).use();
		for(int i = 0; i < colorObjects.size(); i++){
			colorObjects.at(i).RenderObject();
		}
		
		glfwSwapBuffers(MainWindow::Get()->glfw());
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds((long)(FIXED_DELTA_TIME * 1000)));
	}
}

inline void exit_configuration(){
	glfwTerminate();
}

inline void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

inline void processFrame(GLFWwindow* window, double delta){
	
	for(int i = 0; i < colorObjects.size(); i++){
		colorObjects.at(i).ProcessFrame(window, delta);
	}

	lemur->ProcessFrame(window, delta);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    CheckLemurColisions(colorObjects, lemur);
}

