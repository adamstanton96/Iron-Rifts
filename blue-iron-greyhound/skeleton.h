#pragma once

#include "bone.h"
#include <vector>

class skeleton
{
public:
	skeleton(){}

	skeleton(std::vector<bone*> bones, glm::mat4 globalInverseTransform)
	{
		init(bones, globalInverseTransform);
	}

	void init(std::vector<bone*> bones, glm::mat4 globalInverseTransform)
	{
		this->bones = bones;
		this->globalInverseTransform = globalInverseTransform;

		for (int i = 0; i < bones.size(); i++)
			bones.at(i)->parentSkeleton = this;
	}


	bone* FindBone(std::string name)
	{
		for (int i = 0; i < bones.size(); i++)
		{
			if (bones.at(i)->name == name)
				return bones.at(i);
		}
		return nullptr;
	}


	void UpdateBoneMatsVector()
	{

		if (bones.size() == 0)
			return;

		boneMats.clear();


		for (int i = 0; i < 100; i++)
		{
			if (i > bones.size() - 1)
				boneMats.push_back(glm::mat4(1.0));
			else
			{
				glm::mat4 concatenated_transformation = (bones.at(i)->GetParentTransforms() * bones.at(i)->node->transformation);
			}
		}

	}


	void update()
	{
		UpdateBoneMatsVector();


		glUniformMatrix4fv(glGetUniformLocation(6, "gBones"), //We find the location of the gBones uniform.
			boneMats.size(),
			GL_FALSE,    //We don't need to transpose the matrices.
			glm::value_ptr(boneMats[0]));
	}



	std::vector<bone*> bones;
	glm::mat4 globalInverseTransform;
	std::vector<glm::mat4> boneMats;

private:


};
