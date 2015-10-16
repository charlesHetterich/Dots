#pragma once
#include "globalVariablesAndIncludes.h"
#include "Sprite.h"

class Entity
{
public:
	Entity(){}
	virtual void draw(){};
	
	Rect getRect() { return image.getRect(); }

protected:

	Sprite image;
};

class Ornament : public Entity
{
public:
	Ornament() : Entity(){}

private:


};

class Dust : public Ornament
{
public:
	Dust(){}
	Dust(Shader *shader) : Ornament()
	{
		image = Sprite(0.0f, 0.0f, 250.0f, 250.0f, shader);
	};
	void createDust(float x, float y)
	{
		animation.cycleOnce();
		image.setX(x - (image.getW() / 2));
		image.setY(y - (image.getH() / 2));
	}

protected:

	Animation animation;
};

class TapDust : public Dust
{
public:
	TapDust(){}
	TapDust(Shader *shader) : Dust(shader)
	{
		animation = Animation(0, 64, 32, 32, 5, 100);
	}

	void draw()
	{
		if (animation.getOneCycle())
		{
			image.draw(&animation);
		}
	}

private:

};

class TrailDust : public Dust
{
public:
	TrailDust(){}
	TrailDust(Shader *shader) : Dust(shader)
	{
		animation = Animation(0, 96, 32, 32, 5, 120);
	}
	
	void draw()
	{
		if (animation.getOneCycle())
		{
			image.draw(&animation);
		}
	}

private:

};

class Mob : public Entity
{
public:
	Mob(){}
	Mob(float velocity, float angle) : Entity(), velocity(velocity), travelAngle(angle){}
	virtual void move()
	{
		image.setX(image.getX() + velocity * cos((travelAngle / 180.0f) * M_PI));
		image.setY(image.getY() + velocity * sin((travelAngle / 180.0f) * M_PI));
	}

protected:

	float velocity;
	float travelAngle;
};

class Disk : public Mob
{
public:
	Disk(){}
	Disk(float velocity, float angle, Shader* shader) : Mob(velocity, angle), currentDust(0), dustTimer(SDL_GetTicks()), dustTime(150)
	{
		for (unsigned int i = 0; i < 5; i++)
			trailDust[i] = TrailDust(shader);
	}

	//draw
	virtual void draw()
	{
		for (unsigned int i = 0; i < 5; i++)
			trailDust[i].draw();
	}

	//movement
	void move()
	{
		//create dust
		if (dustTimer + dustTime < SDL_GetTicks())
		{
			trailDust[currentDust].createDust(image.getX() + (image.getW() / 2), image.getY() + (image.getH() / 2));

			dustTimer = SDL_GetTicks();

			//cycle dust
			currentDust++;
			if (currentDust == 5)
				currentDust = 0;
		}
		
		//move
		Mob::move();
	}

	//kill disk
	virtual void killDisk(std::vector<std::shared_ptr<Disk>>* disks){}

protected:

	//dust particle
	TrailDust trailDust[5];
	unsigned int currentDust;
	unsigned int dustTime; //milliseconds
	unsigned int dustTimer;

};

class SmallDisk : public Disk
{
public:
	SmallDisk(float x, float y, float velocity, float angle, Shader* shader) : Disk(velocity, angle, shader), animation(1, 27, 4, 3)
	{
		image = Sprite(x, y, 40, 30, shader);
	}

	void draw()
	{
		image.draw(&animation);
		Disk::draw();
	}

private:

	Animation animation;
};

class BigDisk : public Disk
{
public:
	BigDisk(){}
	BigDisk(float x, float y, float velocity, float angle, Shader* shader) : Disk(velocity, angle, shader), animation(1, 17, 9, 8), shader(shader)
	{
		image = Sprite(x, y, 108, 96, shader);

		this->velocity = velocity;
		travelAngle = angle;
	}

	void draw()
	{
		image.draw(&animation);
		Disk::draw();
	}

protected:

	Animation animation;
	Shader* shader;
};

class ThreeSplitDisk : public BigDisk
{
public:
	ThreeSplitDisk(float x, float y, float velocity, float angle, Shader* shader) : BigDisk(x, y, velocity, angle, shader){}

	//kill disk
	void killDisk(std::vector<std::shared_ptr<Disk>>* disks)
	{
		float angle = rand() % 360;
		disks->push_back(std::shared_ptr<Disk>(new SmallDisk(image.getX() + (image.getW() / 2) - 20, image.getY() + (image.getH() / 2) - 15, 0.05, angle, shader)));
		disks->push_back(std::shared_ptr<Disk>(new SmallDisk(image.getX() + (image.getW() / 2) - 20, image.getY() + (image.getH() / 2) - 15, 0.05, angle + 30, shader)));
		disks->push_back(std::shared_ptr<Disk>(new SmallDisk(image.getX() + (image.getW() / 2) - 20, image.getY() + (image.getH() / 2) - 15, 0.05, angle + 60, shader)));
	}

private:

};

class TwoSplitDisk : public BigDisk
{
public:
	TwoSplitDisk(float x, float y, float velocity, float angle, Shader* shader) : BigDisk(x, y, velocity, angle, shader){}

	//kill disk
	void killDisk(std::vector<std::shared_ptr<Disk>>* disks)
	{
		disks->push_back(std::shared_ptr<Disk>(new TwoSplitDisk(image.getX(), image.getY(), 0.05, rand() % 360, shader)));
		disks->push_back(std::shared_ptr<Disk>(new ThreeSplitDisk(image.getX(), image.getY(), 0.05, rand() % 360, shader)));
	}

private:

};