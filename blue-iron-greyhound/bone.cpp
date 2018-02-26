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

	glm::mat4 concatenated_transforms;

	for (int i = mats.size() - 1; i >= 0; i--)
		concatenated_transforms *= mats.at(i);

	return concatenated_transforms;

}