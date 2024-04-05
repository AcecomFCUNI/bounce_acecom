#include <iostream>

const float IMAGE_SCALE = 0.05f;
const float VELOCITY_X = 0.15f;
const float VELOCITY_Y = 0.15f;

static int CalcVertices(float* x, float* y, float vertices[]){

	vertices[0]		= *x - 1.7f	*	IMAGE_SCALE;
	vertices[1]		= *y - 4.5f	*	IMAGE_SCALE; //bottom left

	vertices[8]		= *x + 1.7f	*	IMAGE_SCALE;
	vertices[9]		= *y - 4.5f	*	IMAGE_SCALE; //bottom right

	vertices[16]	= *x + 1.7f	*	IMAGE_SCALE;
	vertices[17]	= *y + 4.5f	*	IMAGE_SCALE; //top right

	vertices[24]	= *x - 1.7f	*	IMAGE_SCALE;
	vertices[25]	= *y + 4.5f	*	IMAGE_SCALE;//top left

	return 0;
}

static int CaclNewPosition(float* x, float* y, double fixedDeltaTime){

	*x += VELOCITY_X * fixedDeltaTime;
	*y += VELOCITY_Y * fixedDeltaTime;


	return 0;
}