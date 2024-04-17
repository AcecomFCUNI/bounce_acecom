#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../utilities/render/buffer_generation.hpp"

class base_object{

protected:
	float centerX;
	float centerY;

	float offsetX;
	float offsetY;

	float scale;

public:
	base_object(
		float _centerX, 
		float _centerY, 
		float _offsetX, 
		float _offsetY,
		float _scale){

		this->centerX = _centerX;
		this->centerY = _centerY;
		this->offsetX = _offsetX;
		this->offsetY = _offsetY;
		this->scale = _scale;
	}

public:
	virtual void CalcVertices(float imageScale){};
	virtual void RenderObject(){};
	virtual void ProcessFrame(GLFWwindow* window, double delta){};


	virtual float GetCenterX(){ return centerX; }
	virtual float GetCenterY(){ return centerY; }
	virtual float GetOffsetX(){ return offsetX * scale; }
	virtual float GetOffsetY(){ return offsetY * scale; }
	
};


class object_color : public base_object{

protected:

	static int PlayerNumber;

	int playerID;

	float velocityX;
	float velocityY;

	float vertices[24];
	unsigned int indices[6]; 

	unsigned int VAO, VBO, EBO;

public:

	object_color(
		float _centerX, 
		float _centerY, 
		float _offsetX, 
		float _offsetY, 
		float _imageScale = 1.0f, 
		float _velocityX = 0.0f,
		float _velocityY = 0.0f) 

		:base_object(
			_centerX, 
			_centerY, 
			_offsetX, 
			_offsetY,
			_imageScale){

		this->velocityX = _velocityX;
		this->velocityY = _velocityY;
		this->playerID = PlayerNumber;
		this->PlayerNumber++;

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 3;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;

		CalcVertices(scale);
		CalcColor();

		generateBuffers(
    		&VAO, 
    		&VBO, 
    		&EBO, 
    		vertices, 
    		sizeof(vertices)/sizeof(float), 
    		indices, 
    		sizeof(indices)/sizeof(unsigned int),
    		false
    	);

	};

private:

	virtual void CalcVertices(float imageScale) override{
		vertices[0]		= centerX - offsetX * imageScale;
		vertices[1]		= centerY - offsetY * imageScale; //bottom left
		vertices[2]		= 0.f;	

		vertices[6]		= centerX + offsetX * imageScale;
		vertices[7]		= centerY - offsetY * imageScale; //bottom right
		vertices[8]		= 0.f;

		vertices[12]	= centerX + offsetX * imageScale;
		vertices[13]	= centerY + offsetY * imageScale; //top right
		vertices[14]	= 0.f;

		vertices[18]	= centerX - offsetX * imageScale;
		vertices[19]	= centerY + offsetY * imageScale;//top left
		vertices[20]	= 0.0f;
	}

	//only white for the moment
	void CalcColor(){
		vertices[3] = 1.0f;
		vertices[4] = 1.0f;
		vertices[5] = 1.0f;
		vertices[9] = 1.0f;
		vertices[10] = 1.0f;
		vertices[11] = 1.0f;
		vertices[15] = 1.0f;
		vertices[16] = 1.0f;
		vertices[17] = 1.0f;
		vertices[21] = 1.0f;
		vertices[22] = 1.0f;
		vertices[23] = 1.0f;
	}

public:

	virtual void RenderObject() override {
		CalcVertices(scale);
		UpdateVertex(&VAO, &VBO, vertices, sizeof(vertices)/sizeof(float) );
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}


	virtual void ProcessFrame(GLFWwindow* window, double delta) override{

		switch (playerID) {
			case 0:
				if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
					centerX -= velocityX * delta;
				}

				if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
					centerX += velocityX * delta;
				}
				break;

			case 1:
				if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
					centerX -= velocityX * delta;
				}

				if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
					centerX += velocityX * delta;
				}
				break;

			default:
				break;
		}

	}

};

inline int object_color::PlayerNumber = 0;


class object_texture : public base_object{

protected:

	float velocityX;
	float velocityY;

	float vertices[32];
	unsigned int indices[6]; 

	unsigned int VAO, VBO, EBO;

public:

	object_texture(
		float _centerX, 
		float _centerY, 
		float _offsetX, 
		float _offsetY, 
		float _imageScale = 1.0f,  
		float _velocityX = 0.0f,
		float _velocityY = 0.0f)

		:base_object(
			_centerX,
			_centerY,
			_offsetX,
			_offsetY,
			_imageScale){

		this->velocityX = _velocityX;
		this->velocityY = _velocityY;


		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 3;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;

		CalcVertices(scale);
		CalcColor();
		CalcTexturePosition();

		generateBuffers(
    		&VAO, 
    		&VBO, 
    		&EBO, 
    		vertices, 
    		sizeof(vertices)/sizeof(float), 
    		indices, 
    		sizeof(indices)/sizeof(unsigned int),
    		true
    	);

	};

private:

	virtual void CalcVertices( float imageScale) override{
		vertices[0]		= centerX - offsetX * imageScale;
		vertices[1]		= centerY - offsetY * imageScale; //bottom left
		vertices[2]		= 0.f;	

		vertices[8]		= centerX + offsetX * imageScale;
		vertices[9]		= centerY - offsetY * imageScale; //bottom right
		vertices[10]	= 0.f;

		vertices[16]	= centerX + offsetX * imageScale;
		vertices[17]	= centerY + offsetY * imageScale; //top right
		vertices[18]	= 0.f;

		vertices[24]	= centerX - offsetX * imageScale;
		vertices[25]	= centerY + offsetY * imageScale;//top left
		vertices[26]	= 0.0f;
	}

	//white for the moment
	virtual void CalcColor(){
		vertices[3] = 1.0f;
		vertices[4] = 1.0f;
		vertices[5] = 1.0f; //BL
		
		vertices[11] = 1.0f;
		vertices[12] = 1.0f;
		vertices[13] = 1.0f;//BR
		
		vertices[19] = 1.0f;
		vertices[20] = 1.0f;
		vertices[21] = 1.0f;//TR
		
		vertices[27] = 1.0f;
		vertices[28] = 1.0f;
		vertices[29] = 1.0f;//TL
	}

	virtual void CalcTexturePosition(){
		vertices[6] = 0.0f;
		vertices[7] = 0.0f;//BL
		
		vertices[14] = 1.0f;
		vertices[15] = 0.0f;//BR
		
		vertices[22] = 1.0f;
		vertices[23] = 1.0f;//TR
		
		vertices[30] = 0.0f;
		vertices[31] = 1.0f;//TL
		

	}

public:

	virtual void RenderObject() override {
		CalcVertices(scale);
		UpdateVertex(&VAO, &VBO, vertices, sizeof(vertices)/sizeof(float) );
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual void ProcessFrame() {};
	
};