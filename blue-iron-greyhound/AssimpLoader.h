#ifndef ASSIMPLOADER
#define ASSIMPLOADER

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla
#include <glm/glm.hpp>
#include <vector>
using namespace std;

namespace AssimpLoader
{
	void loadObjectData(const std::string& file, vector<int>& meshIDs, vector<int> &indexCount, vector<glm::vec3>& maxmin);
	void loadObjectDataAnimations(const std::string& file, vector<int>& meshIDs, vector<int>& indexCount, vector<glm::vec3>& maxmin);


	//void loadBoneData(const std::string& file);
}


#endif ASSIMPLOADER