/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com" (tutorial)
///////////////////////////////////////

#include "bone.h"


bone::bone(int in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat)
{
	id = in_id;
	name = in_name;
	offset_matrix = AssimpLoader::AiToGLMMat4(in_o_mat);

	meshID = in_mesh;

	parent_bone = nullptr;
	node = nullptr;
}


bone::bone(int in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat)
{
	id = in_id;
	name = in_name;
	offset_matrix = in_o_mat;

	meshID = in_mesh;

	parent_bone = nullptr;
	node = nullptr;
}

glm::mat4 bone::GetParentTransforms()
{
	bone* b = parent_bone;    //In order to recursively concatenate the transforms,
							  //we first start with this bone's parent.
	std::vector<glm::mat4> mats;    //Where we'll store the concatenated transforms.

	while (b != nullptr)    //As long as 'b' has a parent (see the end of the loop
	{                      //to avoid confusion).
		glm::mat4 tmp_mat = b->node->transformation; //This bone's transformation.
		mats.push_back(tmp_mat);

		b = b->parent_bone;    //We set b to its own parent so the loop can continue.
	}

	glm::mat4 concatenated_transforms(1);

	for (int i = mats.size() - 1; i >= 0; i--)
		concatenated_transforms *= mats.at(i);

	return concatenated_transforms;

}



unsigned int bone::FindPosition(float time)
{
	for (unsigned int i = 0; i < animNode->numPositionKeys -1 ; i++)		
	{
		//If the time passed in is less than the time of the next
		//keyframe, then this is the keyframe we want!
		if (time < (float)animNode->positionKeysTimes[i+1])				
			return i;
	}
	return 0;    //If we don't find anything, just return 0.
}


unsigned int bone::FindRotation(float time)
{
	for (unsigned int i = 0; i < animNode->numRotationKeys - 1; i++)
	{
		//Same as with the position.
		if (time < (float)animNode->rotationKeysTimes[i + 1])
			return i;
	}
	return 0;
}

float Factor = 0.00000001;

glm::vec3 bone::CalcInterpolatedPosition(float time)
{
	//If there's only one keyframe for the position, we return it.
	//This avoids any possible out of range errors later on in the function
	//as we're dealing with an array.
	if (animNode->numPositionKeys == 1)
	{
		glm::vec3 val = animNode->positionKeysValues[0];
		return val;
	}

	//The index of our current position, as well as the index that follows.
	//This will allow us to interpolate between the two values.
	unsigned int PositionIndex = FindPosition(time);
	unsigned int NextPositionIndex = (PositionIndex + 1);
	//DeltaTime is the amount of time between the two keyframes.
	float DeltaTime = animNode->positionKeysTimes[NextPositionIndex] - animNode->positionKeysTimes[PositionIndex];
	//The factor is simply how much time has passed since the last keyframe,
	//divided by the amount of time between the two keyframes (the DeltaTime)
	//to get the percentage, or how far along between the two keyframes we are.
	float Factor = (time - (float)animNode->positionKeysTimes[PositionIndex]) / DeltaTime;
	//Factor = 0.5;

	//The start and end positions (the position values of each of the keyframes)
	glm::vec3 p1 = animNode->positionKeysValues[PositionIndex];
	glm::vec3 p2 = animNode->positionKeysValues[NextPositionIndex];


	//and here we linearly interpolate between the two keyframes.
	glm::vec3 val = glm::mix(p1, p2, Factor);//, Factor

	return val;
}



glm::quat bone::CalcInterpolatedRotation(float time)
{
	if (animNode->numRotationKeys == 1)
	{
		glm::quat val = animNode->rotationKeysValues[0];
		return val;
	}

	unsigned int RotationIndex = FindRotation(time);
	unsigned int NextRotationIndex = (RotationIndex + 1);

	float DeltaTime = animNode->rotationKeysTimes[NextRotationIndex] - animNode->rotationKeysTimes[RotationIndex];
	float Factor = (time - (float)animNode->rotationKeysTimes[RotationIndex]) / DeltaTime;
	//Factor = 0.5;

	glm::quat r1 = animNode->rotationKeysValues[RotationIndex];
	glm::quat r2 = animNode->rotationKeysValues[NextRotationIndex];

	glm::quat val = glm::slerp(r1, r2, Factor);
	return val;
}



//This function will update our node's transformation to match that of
//our keyframes.
void bone::UpdateKeyframeTransform(float time)
{
	if (animNode == nullptr)
		return;

	pos = CalcInterpolatedPosition(time);
	rot = CalcInterpolatedRotation(time);
	scale = glm::vec3(1.0);    //You could add support for scaling, but that's
							   //beyond the scope of this tutorial series.


	//Modified - Originally mat *= glm::translate(pos)
	glm::mat4 mat(1);

	mat = glm::translate(mat, pos);
	mat *= glm::mat4_cast(rot);
	mat = glm::scale(mat, scale);


	glm::mat4 matrix = glm::mat4_cast(rot);

	node->transformation = mat;
}