#pragma once
/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com" (tutorial)
///////////////////////////////////////


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
using namespace std;


#include <iostream>    
#include "AssimpLoader.h"

#include "node.h"
#include "animNode.h"
#include "animation.h"

//#include frametime
class skeleton;

class bone
{
public:
	 bone() { name = ""; id = -2; }

	 bone(int in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
	 bone(int in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);

	 unsigned int FindPosition(float time);
	 glm::vec3 CalcInterpolatedPosition(float time);
	 unsigned int FindRotation(float time);
	 glm::quat CalcInterpolatedRotation(float time);

	 void UpdateKeyframeTransform(float time);

	 glm::mat4 GetParentTransforms();


	string name;
	int meshID;
	int id;

	node* node;
	animNode* animNode;
	bone* parent_bone;

	glm::mat4 parent_transforms;

	glm::mat4 offset_matrix;

	skeleton* parentSkeleton;

	//Keyframe Data
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;
	glm::vec3 p1;
	glm::vec3 p2;
	
private:
};
