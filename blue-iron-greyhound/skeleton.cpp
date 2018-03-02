#include "skeleton.h"


skeleton::skeleton()
{
	time = start_time = end_time = 0;
	active_animation = nullptr;

	anim_loop = false;
}

skeleton::skeleton(std::vector<bone*> bones, glm::mat4 globalInverseTransform)
{
	init(bones, globalInverseTransform);
	
}

void skeleton::init(std::vector<bone*> bones, glm::mat4 globalInverseTransform)
{
	this->bones = bones;
	this->globalInverseTransform = globalInverseTransform;

	time = 0;
	start_time = 0;
	end_time = 0;

	active_animation = nullptr;
	idle_animation = nullptr;

	anim_loop = false;

	for (int i = 0; i < bones.size(); i++)
		bones.at(i)->parentSkeleton = this;
}


bone* skeleton::FindBone(std::string name)
{
	for (int i = 0; i < bones.size(); i++)
	{
		if (bones.at(i)->name == name)
			return bones.at(i);
	}
	return nullptr;
}


void skeleton::UpdateBoneMatsVector()
{

	if (bones.size() == 0)
		return;

	boneMats.clear();


	for (int i = 0; i < 100; i++)
	{
		if (i > bones.size() - 1)
		{
			boneMats.push_back(glm::mat4(1.0));
		}
		else
		{

				glm::mat4 concatenated_transformation = (bones.at(i)->GetParentTransforms() * bones.at(i)->node->transformation);
				boneMats.push_back(globalInverseTransform * concatenated_transformation * bones.at(i)->offset_matrix);
				


				glm::mat4 pTrans = (bones.at(i)->GetParentTransforms());
				glm::mat4 nodeTrans = (bones.at(i)->node->transformation);


				glm::mat4 total = globalInverseTransform * concatenated_transformation * bones.at(i)->offset_matrix;
				glm::mat4 offset = bones.at(i)->offset_matrix;
				glm::mat4 globalTransform = globalInverseTransform;
		
		}
	}

}


void skeleton::giveDeltaTime(double deltaT)
{
	deltaTime = deltaT;
}

std::vector<glm::mat4> skeleton::getBoneMats()
{
	return boneMats;
}


void skeleton::update()
{
	UpdateBoneMatsVector();

	if (boneMats.size() > 0)
	{
		//Update the shaders bone data
		glUseProgram(6);

		int uniformIndex = glGetUniformLocation(6, "gBones");
		glUniformMatrix4fv(uniformIndex, boneMats.size(), GL_FALSE,
			glm::value_ptr(boneMats[0]));

		/*int uniformIndex = glGetUniformLocation(program, uniformName);
		glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, data);

		OpenglUtils::setUniformMatrix4fv(currShader, "gBones", mesh->getBoneMats());*/

	}
	else
		std::cout << " Skeleton::Update - std vec BoneMats is empty." << std::endl;
	



	//If we're not playing an animation, then just give up, do nothing.
	if (!anim_play)
		return;

	//Update the time variable by adding the delta time of the last frame
	//It's * 0.001f because the delta time is in milliseconds, and we 
	//need it in seconds.
	time += deltaTime *0.001f;

	//Make sure the time can't be less than our animation's start time.
	if (time < start_time)
		time = start_time;

	//Make sure the time can't be greater than our animation's end time.
	if (time > end_time)
	{
		if (anim_loop)
		{
			//If looping is set, then loop!
			time = start_time;
		}	
		else
		{
			//Else, give up.
			StopAnimating();
		}
			
	}

	for (int i = 0; i < bones.size(); i++)
		bones.at(i)->UpdateKeyframeTransform(time);
}



void skeleton::PlayAnimation(animation& anim, bool loop, bool reset_to_start)
{
	//If there's an animation currently playing
	if (active_animation != nullptr)
	{
		//And this animation is more important than the current one
		if (anim.priority < active_animation->priority) //Set the current animation to the one passed in.
			active_animation = &anim;
		else
		{
			//Do nothing.
			return;
		}
	}
	else
		//Set the current animation to the one passed in.
		active_animation = &anim;

	start_time = active_animation->start_time;
	end_time = active_animation->end_time;

	anim_play = true;
	anim_loop = loop;

	//The reset_to_start variable determines whether or not the animation
	//should restart upon playing.
	if (reset_to_start)
		time = active_animation->start_time;
}


//This function stops animating
void skeleton::StopAnimating()
{
	time = end_time;
	active_animation = nullptr;
	anim_play = false;
}

void skeleton::SetIdleAnimation(animation* in_anim)
{
	idle_animation = in_anim;
}