#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>

#include "render/shader_loading.hpp"
#include "render/2D_figure_renderization.hpp"
#include "../utilities/render/texture_loading.hpp"
#include "../utilities/render/buffer_generation.hpp"
#include "colisions/image_position.hpp"
#include "window/main_window.hpp"

const double FIXED_DELTA_TIME = 0.01;

inline ShaderLoader* shaderLoader = ShaderLoader::GetInstance();

const float START_CENTER_POSITION_X = 0.3f;
const float START_CENTER_POSITION_Y = 0.0f;

const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

float center_position_x = 0.1f;
float center_position_y = 0.0f;

inline float vertices[] = {
	// positions          // colors           // texture coords
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left 
};

inline unsigned int indices[]{
	0, 1, 3,
	1, 2, 3,
};

inline unsigned int VAO, VBO, EBO;


void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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

    //generate buffers
    std::cout<<"generate buffers"<<std::endl;
    generateBuffers(
    	&VAO, 
    	&VBO, 
    	&EBO, 
    	vertices, 
    	sizeof(vertices)/sizeof(float), 
    	indices, 
    	sizeof(indices)/sizeof(unsigned int)
    	);
	
	//charge texture
	std::cout<<"charging texture"<<std::endl;
    UploadTexture("../assets/textures/lemur.png");
}

inline void game_loop(){
	while(!glfwWindowShouldClose(MainWindow::Get()->glfw())){
		processInput(MainWindow::Get()->glfw());

		//calc new position
		CaclNewPosition(&center_position_x, &center_position_y, FIXED_DELTA_TIME);
		CalcVertices(&center_position_x, &center_position_y, vertices);

		//render image
		UpdateVertex(&VAO, &VBO, vertices, sizeof(vertices)/sizeof(float));
		glClear(GL_COLOR_BUFFER_BIT);
		shaderLoader->GetShader(0).use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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

inline void processInput(GLFWwindow* window){
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}