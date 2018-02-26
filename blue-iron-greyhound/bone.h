#pragma once
/////////////////////////////////////
///Credit to "realitymultiplied.wordpress.com" (tutorial)
///////////////////////////////////////


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
using namespace std;


#include <iostream>    
#include "AssimpLoader.h"

#include "node.h"
#include "animNode.h"

//#include frametime
class skeleton;

class bone
{
public:
	 bone() { name = ""; id = -2; }

	 bone(int in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
	 bone(int in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);

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
	
private:



};
