#pragma once

#include "bone.h"
#include <vector>


#include <GL/glew.h>

class skeleton
{
public:
	skeleton();

	skeleton(std::vector<bone*> bones, glm::mat4 globalInverseTransform);
	

	void init(std::vector<bone*> bones, glm::mat4 globalInverseTransform);
	void UpdateBoneMatsVector();
	void update();



	bone* FindBone(std::string name);
	std::vector<glm::mat4> getBoneMats();


	void PlayAnimation(animation& anim, bool loop, bool reset_to_start);
	void StopAnimating();
	void SetIdleAnimation(animation* in_anim);




	std::vector<bone*> bones;
	glm::mat4 globalInverseTransform;
	std::vector<glm::mat4> boneMats;




	void giveDeltaTime(double time);

	float time;

	float start_time;
	float end_time;

	animation* active_animation;
	animation* idle_animation;

	bool anim_play;
	bool anim_loop;

	double deltaTime;


private:


};
