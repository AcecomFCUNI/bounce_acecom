#include "base_object.hpp"

const float START_CENTER_X = 0.35f;
const float START_CENTER_Y = 0.1f;
const float OFFSET_X = 1.7f;
const float OFFSET_Y = 4.5f;
const float IMAGE_SCALE = 0.05;
const float VELOCITY_X = 2.f;
const float VELOCITY_Y = 2.f;

class lemur_object : public object_texture{

private:
	bool canMove;

public:
	
	lemur_object(bool _canMove):object_texture(
		START_CENTER_X, 
		START_CENTER_Y, 
		OFFSET_X, OFFSET_Y, 
		IMAGE_SCALE, 
		VELOCITY_X, 
		VELOCITY_Y){

		this->canMove = _canMove;
	}

	virtual void RenderObject() override{
		object_texture::RenderObject();
	}

	virtual void ProcessFrame(GLFWwindow *window, double delta) override{
		if(!canMove) return;
		centerX += velocityX * delta;
		centerY += velocityY * delta;
	}

	void InverseYVelocity(){ velocityY *=-1; }
	void InverseXVelocity(){ velocityX *=-1; }
};