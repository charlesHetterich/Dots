#pragma once
#include "globalVariablesAndIncludes.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Time.h"

class Animation
{
public:
	static int CANVAS_WIDTH;
	static int CANVAS_HEIGHT;

	Animation(int x = 0, int y = 0, int w = 0, int h = 0, int numFrames = 0, int frameTime = 0)
	{
		basePosX = x;
		basePosY = y;
		frameWidth = w;
		frameHeight = h;
		this->numFrames = numFrames;
		this->frameTime = frameTime;
		frameTimer = SDL_GetTicks();
		doOneCycle = false;
		firstDraw = true;
		currentFrame = 0;
	}
	bool shouldAnimate()
	{ 
		if (firstDraw)
		{
			firstDraw = false;
			return true;
		}

		return SDL_GetTicks() > frameTimer + frameTime;
	}
	Rect getAnimation()
	{
		//checks for next frame
		if (SDL_GetTicks() > frameTimer + frameTime)
		{
			currentFrame++;
			if (currentFrame >= numFrames)
			{
				currentFrame = 0;
				doOneCycle = false;
			}

			frameTimer = SDL_GetTicks();
		}

		return Rect((basePosX + frameWidth*currentFrame) / (float)CANVAS_WIDTH, basePosY / (float)CANVAS_HEIGHT, frameWidth / (float)CANVAS_WIDTH, frameHeight / (float)CANVAS_HEIGHT);
	}
	Rect getFirstAnimation()
	{
		return Rect((basePosX) / (float)CANVAS_WIDTH, basePosY / (float)CANVAS_HEIGHT, frameWidth / (float)CANVAS_WIDTH, frameHeight / (float)CANVAS_HEIGHT);
	}
	inline int getCurrentFrame() { return currentFrame; }

	//single cycle
	void cycleOnce()
	{
		doOneCycle = true;
		currentFrame = 0;
		frameTimer = SDL_GetTicks();
	}
	inline bool getOneCycle()
	{
		return doOneCycle;
	}

private:
	//position
	unsigned int basePosX;
	unsigned int basePosY;

	//frames
	unsigned int frameWidth;
	unsigned int frameHeight;
	unsigned int numFrames;

	//Timing
	unsigned int frameTime; //milliseconds
	unsigned int frameTimer;
	unsigned int currentFrame = 0;

	//flags
	bool doOneCycle;
	bool firstDraw;
};

class Sprite
{
public:
	Sprite(float x = 1, float y = 1, float w = 1, float h = 1, Shader* shader = nullptr);
	~Sprite();
	
	//core
	void draw(Animation* animation);
	void draw();
	glm::mat4 getTransform();

	//characteristics
	void setColor(float r, float g, float b) { color = { r, g, b, color.a }; };

	//transformations
	glm::vec4& getColor() { return color; }
	void setX(float x) { rect.x = x; }
	float getX() { return rect.x; }
	void setY(float y) { rect.y = y; }
	float getY() { return rect.y; }
	void setW(float w) { rect.w = w; }
	float getW() { return rect.w; }
	void setH(float h) { rect.h = h; }
	float getH() { return rect.h; }
	Rect getRect() { return rect; }
	void setAlpha(float a) { color.a = a; }
	float getAlpha() { return color.a; }

protected:

	//characteristics
	glm::vec4 color = { 1, 1, 1, 1 };

	//animation
	Animation idle = Animation(0, 32, 32, 32, 5, 75);
	Time time;

	//transformations
	Rect rect;

	Shader* shader;
	Mesh* mesh;
};
