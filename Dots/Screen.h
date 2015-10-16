#pragma once
#include "globalVariablesAndIncludes.h"
#include "Entities.h"
#include "Input.h"

class Screen
{
public:
	Screen(){}
	Screen(Shader* shader) : shader(shader){}

	static unsigned int CURRENT_SCREEN;

	virtual void input(Input input){}
	virtual void update(){}
	virtual void render(){}

protected:

	Shader* shader;
};

class HomeScreen : public Screen
{
public:
	HomeScreen(Shader* shader) : Screen(shader){}

	void input(Input input)
	{

	}
	void update()
	{

	}
	void render()
	{

	}

private:

};

class GameScreen : public Screen
{
public:
	GameScreen(Shader* shader) : Screen(shader)
	{
		for (unsigned int i = 0; i < 10; i++)
			dust[i] = TapDust(shader);
		currentDust = 0;

		disk.push_back(std::shared_ptr<Disk>(new TwoSplitDisk(-54, -48, 0, 0, shader)));
	}

	void input(Input input)
	{
		//if mouse is clicked
		if (input.getMouseButtonDown(0))
		{
			//create dust
			dust[currentDust].createDust(input.getMouseX(), input.getMouseY());

			//cycle dust
			currentDust++;
			if (currentDust == 10)
				currentDust = 0;

			

			//check for collision with dot
			float hitX = input.getMouseX();
			float hitY = input.getMouseY();
			//brute force cycle through all disks
			unsigned int size = disk.size();
			for (unsigned int i = 0; i < size; i++)
			{
				//check collision
				Rect rect = disk[i]->getRect();
				if (hitX >= rect.x && hitX <= rect.x + rect.w && hitY >= rect.y && hitY <= rect.y + rect.h)
				{

					//create new disks
					disk[i]->killDisk(&disk);

					//remove disk
					disk.erase(std::remove(disk.begin(), disk.end(), disk[i]), disk.end());

					//dont skip over any after erasing
					i--;
					size--;
				}
			}
		}

		//reset
		if (input.getKeyDown(SDL_SCANCODE_R))
		{
			disk.clear();
			disk.push_back(std::shared_ptr<Disk>(new TwoSplitDisk(-54, -48, 0, 0, shader)));
			std::cout << "arg";
		}
	}
	void update()
	{
		for (unsigned int i = 0; i < disk.size(); i++)
			disk[i]->move();
	}
	void render()
	{
		//draw tap dust
		for (unsigned int i = 0; i < 10; i++)
			dust[i].draw();

		//draw disks
		for (unsigned int i = 0; i < disk.size(); i++)
			disk[i]->draw();
	}

private:

	//tap dust effect
	TapDust dust[10];
	unsigned int currentDust;

	//game disks
	std::vector<std::shared_ptr<Disk>> disk;
};