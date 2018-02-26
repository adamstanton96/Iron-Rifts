#pragma once
//credit to https://realitymultiplied.wordpress.com/2016/07/29/assimp-skeletal-animation-tutorial-4-finishing-up-oh-and-animation/

#include <glm/glm.hpp>
#include <string>

static float TimeToFrame(float time)
{
	float frame = 0.041666666667;
	return time / frame;
}

static glm::vec2 FramesToTime(glm::vec2 frames)
{
	float frame = 0.041666666667;
	return frames * frame;
}

class animation
{
public:
	animation()
	{
		start_time = 0;
		end_time = 0;
		priority = 0; 
	}

	animation(std::string in_name, glm::vec2 times, int in_priority)
	{
		name = in_name;
		start_time = times.x;
		end_time = times.y;
		priority = in_priority;
	}


	std::string name;
	float start_time;
	float end_time;

	int priority;
private:



};