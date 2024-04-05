#include <GLFW/glfw3.h>
#include <iostream>

class MainWindow{

	GLFWwindow* GLFWmainWindow;
	static MainWindow* mainWindow;

public:
	static unsigned int screenWidth;
	static unsigned int screenHeight;

private:
	MainWindow(){

		if(screenWidth * screenHeight == 0){
			std::cout<<"Invalid configuration data, first call ConfigWindow"<<std::endl;
			glfwTerminate();

		}

		GLFWmainWindow = glfwCreateWindow(
			screenWidth,
			screenHeight,
			"Patata", 
			nullptr,
			nullptr);
	}


public:
	static MainWindow* Get(){
		if(mainWindow != nullptr) return mainWindow;

		mainWindow = new MainWindow();
		return mainWindow;
	}

	static void ConfigWindow(
		unsigned int screenWidth, 
		unsigned int screenHeight){

		MainWindow::screenWidth = screenWidth;
		MainWindow::screenHeight = screenHeight;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);   
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}


	GLFWwindow* glfw(){
		return GLFWmainWindow;
	}

};

unsigned int MainWindow::screenHeight = 0;
unsigned int MainWindow::screenWidth = 0;
MainWindow* MainWindow::mainWindow = nullptr;