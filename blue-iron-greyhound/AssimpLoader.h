#ifndef ASSIMPLOADER
#define ASSIMPLOADER

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "bone.h"
class bone;
using namespace std;

namespace AssimpLoader
{
	void loadObjectData(const std::string& file, vector<int>& meshIDs, vector<int> &indexCount, vector<glm::vec3>& maxmin);
	void loadObjectDataAnimations(const std::string& file, vector<int>& meshIDs, vector<int>& indexCount, vector<glm::vec3>& maxmin, vector<aiNode*>& ai_nodes, vector<aiNodeAnim*>& ai_nodes_anim, std::vector<bone*>& bones);



	void recursiveNodeProcess(aiNode* node, vector<aiNode*>& ai_nodes);
	void AnimNodeProcess(const aiScene* m_scene, vector<aiNodeAnim*>& ai_nodes_anim);

	//transform utilities
	 aiMatrix4x4 GLMMat4ToAi(glm::mat4 mat);
	 glm::mat4 AiToGLMMat4(aiMatrix4x4& in_mat);
	 //Search and return a bone by name
	 bone* FindBone(std::string name, std::vector<bone*>& bones);

	 //Search and return a node by name
	 aiNode* FindAiNode(std::string name, vector<aiNode*>& ai_nodes);
	 
	 aiNodeAnim* FindAiNodeAnim(std::string name, vector<aiNodeAnim*>& ai_nodes_anim);

	 //return index of bone in our bones vector
	 int FindBoneIDByName(std::string name, std::vector<bone*>& bones);





	
}


#endif ASSIMPLOADER