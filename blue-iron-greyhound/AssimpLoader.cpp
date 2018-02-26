#include "AssimpLoader.h"
using namespace std;
#include <iostream>
#include "OpenglUtils.h"
#include <glm/glm.hpp>




namespace AssimpLoader
{
	

	
	

	glm::vec4 AIQUATtoGLMVec4(aiQuaternion aiQuat)
	{
		glm::vec4 newVec;
		newVec.x = aiQuat.x;
		newVec.y = aiQuat.y;
		newVec.z = aiQuat.z;
		newVec.w = aiQuat.w;

		return newVec;
	}

	glm::vec3 AItoGLMVec3(aiVector3D aivec)
	{
		glm::vec3 newVec;
		newVec.x = aivec.x;
		newVec.y = aivec.y;
		newVec.z = aivec.z;

		return newVec;
	}






	void recursiveNodeProcess(aiNode* a_node, vector<node*>& nodes)
	{
		node* rootNode = new node();

		//init values off of aiNode param
		std::string parentName;
		std::vector<std::string> childrenNames;

		rootNode->name = a_node->mName.data;
		rootNode->transformation = AiToGLMMat4(a_node->mTransformation);

		if(a_node->mParent != NULL)
		rootNode->parentName = a_node->mParent->mName.data;

		rootNode->numOfChildren = a_node->mNumChildren;

		for(int i = 0; i <  a_node->mNumChildren; i++)
		rootNode->childrenNames.push_back(a_node->mChildren[i]->mName.data);

		rootNode->numOfMeshes = a_node->mNumMeshes;
		rootNode->numOfMeshes = (int)a_node->mMeshes;


		nodes.push_back(rootNode);

		for (int i = 0; i < a_node->mNumChildren; i++)
			recursiveNodeProcess(a_node->mChildren[i], nodes);
	}


	void AnimNodeProcess(const aiScene* m_scene, vector<animNode*>& ai_nodes_anim)
	{
		if (m_scene->mNumAnimations == 0)
			return;

	

		for (int i = 0; i < m_scene->mAnimations[0]->mNumChannels; i++)
		{
			aiNodeAnim* a_animNode = m_scene->mAnimations[0]->mChannels[i];
			animNode* animnode = new animNode();

		/*	
			int numPositionKeys;
			std::vector<glm::vec3> positionKeys;

			int numRotationKeys;
			std::vector<glm::vec3> rotationKeys;

			int numScalingKeys;
			std::vector<glm::vec3> scalingKeys;*/

			animnode->nodeName = a_animNode->mNodeName.data;
			animnode->numPositionKeys = a_animNode->mNumPositionKeys;
			animnode->numRotationKeys = a_animNode->mNumRotationKeys;
			animnode->numScalingKeys = a_animNode->mNumScalingKeys;

			for (int i = 0; i < a_animNode->mNumPositionKeys; i++)
			{
				animnode->positionKeysValues.push_back(AItoGLMVec3(a_animNode->mPositionKeys->mValue));
				animnode->positionKeysTimes.push_back(a_animNode->mPositionKeys->mTime);
			}
			
			
			for (int i = 0; i < a_animNode->mNumRotationKeys; i++)
			{
				animnode->rotationKeysValues.push_back(AIQUATtoGLMVec4(a_animNode->mRotationKeys->mValue));
				animnode->rotationKeysTimes.push_back(a_animNode->mRotationKeys->mTime);
			}
			
			
			for (int i = 0; i < a_animNode->mNumScalingKeys; i++)
			{
				animnode->scalingKeysValues.push_back(AItoGLMVec3(a_animNode->mScalingKeys->mValue));
			}
				




			ai_nodes_anim.push_back(animnode);
		}
			
	}




	//Extracts all the data we need and puts into into our parameters
	void loadObjectData(const std::string& file, vector<int>& meshIDs, vector<int>& indexCount, vector<glm::vec3>& maxmin)
	{
	
		// Create an instance of the Importer class for loading the object data
		//Assimp::Importer importer;
		// Create an instance of the Importer class for loading the object data
		Assimp::Importer importer;

		//loads our file into a scene object so its all accessible.
		const aiScene* scene = importer.ReadFile(file,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_SortByPType |
			aiProcess_GenSmoothNormals |
			aiProcess_GenNormals
			//aiProcess_FixInfacingNormals  
			//| aiProcess_FindInvalidData
			//| aiProcess_RemoveComponent
			//| aiProcess_FindDegenerates
			//| aiProcess_PreTransformVertices
			//| aiProcess_JoinIdenticalVertices		
			
		);

			

		if (!scene)
		{
			std::cout << "ERROR: Assimp file load failed." << std::endl;
			const char * 	GetErrorString();
		
		}

		//these store the minimum and maxium vertices for object
		glm::vec3 min(1000, 1000, 1000);
		glm::vec3 max(-1000, -1000, -1000);

		

		const aiMesh* mesh;
		//cout << "Number of meshes: " << scene->mNumMeshes << endl;


		//Temporary containers for object data
		std::vector<float> verts;
		std::vector<float> norms;
		std::vector<float> texCoords;
		std::vector<int>   indices;
		std::vector<float> colours;

		//will store the mesh ID of each scene mesh after they have been individually sent to openglUtils.
		//vector<int> meshIDs;
		
		int texCount = 0;

		for (unsigned int j = 0; j < scene->mNumMeshes; j++)
		{
			mesh = scene->mMeshes[j];
			int numOfFaces = mesh->mNumFaces;
			int numOfIndices = numOfFaces * 3;


			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
				const aiFace &face = mesh->mFaces[i];
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);		

			}

			int numOfVertices = mesh->mNumVertices;

			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
				if (mesh->HasPositions()) {
					verts.push_back(mesh->mVertices[i].x);
					verts.push_back(mesh->mVertices[i].y);
					verts.push_back(mesh->mVertices[i].z);

					//Stores the min and mex vertices
					if (mesh->mVertices[i].x < min.x)   min.x = mesh->mVertices[i].x;
					if (mesh->mVertices[i].y < min.y)   min.y = mesh->mVertices[i].y;
					if (mesh->mVertices[i].z < min.z) 	min.z = mesh->mVertices[i].z;
					
					if (mesh->mVertices[i].x > max.x) 	max.x = mesh->mVertices[i].x;
					if (mesh->mVertices[i].y > max.y) 	max.y = mesh->mVertices[i].y;
					if (mesh->mVertices[i].z > max.z)   max.z = mesh->mVertices[i].z;
							
				}

				if (mesh->HasNormals()) {
					norms.push_back(mesh->mNormals[i].x);
					norms.push_back(mesh->mNormals[i].x);
					norms.push_back(mesh->mNormals[i].x);

				}

				if (mesh->HasTextureCoords(0)) {
					texCoords.push_back(mesh->mTextureCoords[0][i].x);
					texCoords.push_back(mesh->mTextureCoords[0][i].y);

					texCount += 2;

				}

				if (mesh->HasVertexColors(0)) {
					//colours.push_back(mesh->mColors[j][i].r);
					//colours.push_back(mesh->mColors[j][i].g);
					//colours.push_back(mesh->mColors[j][i].b);

				}
			}

			//cout << texCount << endl;
			int ID = OpenglUtils::createMesh((GLuint)verts.size(), (GLfloat*)verts.data(), (GLfloat*)colours.data(), (GLfloat*)norms.data(), (GLfloat*)texCoords.data(), (GLuint)texCoords.size(), (GLuint)indices.size(), (GLuint*)indices.data());
			meshIDs.push_back(ID);
			indexCount.push_back(indices.size());

			

			colours.clear(); norms.clear(); texCoords.clear(); verts.clear(); indices.clear();

		}
		

		//Pass out min and max
		maxmin.push_back(min);
		maxmin.push_back(max);

		
	}


	


	//Extracts all the data we need and puts into into our parameters
	//includes data for animations
	void loadObjectDataAnimations(const std::string& file, vector<int>& meshIDs, vector<int>& indexCount, vector<glm::vec3>& maxmin, vector<node*>& nodes, vector<animNode*>& animNodes, std::vector<bone*>& bones)
	{

		// Create an instance of the Importer class for loading the object data
		Assimp::Importer importer;


		//loads our file into a scene object so its all accessible.
		const aiScene* scene = importer.ReadFile(file,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_SortByPType |
			aiProcess_GenSmoothNormals |
			aiProcess_GenNormals
		);



		if (!scene)
		{
			std::cout << "ERROR: Assimp file load failed." << std::endl;
			const char * 	GetErrorString();

		}

		//these store the minimum and maxium vertices for object
		glm::vec3 min(1000, 1000, 1000);
		glm::vec3 max(-1000, -1000, -1000);

		const aiMesh* mesh;
	
		//Temporary containers for object data
		std::vector<float> verts;
		std::vector<float> norms;
		std::vector<float> texCoords;
		std::vector<int>   indices;
		std::vector<float> colours;

		////////////
		

		int texCount = 0;


		//pull out the scenes aiNodes
		aiNode* m_rootNode = scene->mRootNode;
		//recursiveNodeProcess(m_rootNode, ai_nodes);
		recursiveNodeProcess(m_rootNode, nodes);

		//Pull out the scenes mAnimation
		//AnimNodeProcess(scene, ai_nodes_anim);
		AnimNodeProcess(scene, animNodes);


		for (unsigned int j = 0; j < scene->mNumMeshes; j++)
		{

			
			mesh = scene->mMeshes[j];
			int numOfFaces = mesh->mNumFaces;
			int numOfIndices = numOfFaces * 3;

			//Initialise bone related variable
			int WEIGHTS_PER_VERTEX = 4;
			int numOfBones = mesh->mNumVertices*WEIGHTS_PER_VERTEX;
			std::vector<int> boneIDs(numOfBones);
			std::vector<float> boneWeights(numOfBones);

		
		
		for (int i = 0; i < mesh->mNumBones; i++)
		{
				aiBone* currBone = mesh->mBones[i];

				//pull data to create a new boneobject with (meshID, boneID, name and matrix)
				std::string b_name = scene->mMeshes[j]->mBones[i]->mName.data;
				glm::mat4 b_mat = glm::transpose(AiToGLMMat4(scene->mMeshes[j]->mBones[i]->mOffsetMatrix));

				bone* boneObject = new bone(j, i, b_name, b_mat);
				bones.push_back(boneObject);

			
				//Find the corresponding node and animNode to the current bone and store them.
				//This searches through aiNodes and aiNodeAnims with the bone name.
				boneObject->node = FindAiNode(b_name, nodes);
				boneObject->animNode = FindAiNodeAnim(b_name, animNodes);


				if (boneObject->animNode == nullptr)
					std::cout << "No Animations were found for " + b_name << std::endl;
	

				// Pull per vertex bone related data (vertex ID's and Weights) which are used to make the mesh
				for (int j = 0; j < currBone->mNumWeights; j++)
				{
					aiVertexWeight weight = currBone->mWeights[j];
					unsigned int vertexStart = weight.mVertexId * WEIGHTS_PER_VERTEX;

					for (int k = 0; k < WEIGHTS_PER_VERTEX; k++)
					{
						if (boneWeights.at(vertexStart + k) == 0)
						{
							boneWeights.at(vertexStart + k) = weight.mWeight;

							//i == index of bone
							boneIDs.at(vertexStart + k) = i;
						}
					}
				}
		}



			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
				const aiFace &face = mesh->mFaces[i];
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);

			}

			int numOfVertices = mesh->mNumVertices;

			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

				


				if (mesh->HasPositions()) {
					verts.push_back(mesh->mVertices[i].x);
					verts.push_back(mesh->mVertices[i].y);
					verts.push_back(mesh->mVertices[i].z);

					//Stores the min and mex vertices
					if (mesh->mVertices[i].x < min.x)   min.x = mesh->mVertices[i].x;
					if (mesh->mVertices[i].y < min.y)   min.y = mesh->mVertices[i].y;
					if (mesh->mVertices[i].z < min.z) 	min.z = mesh->mVertices[i].z;

					if (mesh->mVertices[i].x > max.x) 	max.x = mesh->mVertices[i].x;
					if (mesh->mVertices[i].y > max.y) 	max.y = mesh->mVertices[i].y;
					if (mesh->mVertices[i].z > max.z)   max.z = mesh->mVertices[i].z;

				}

				if (mesh->HasNormals()) {
					norms.push_back(mesh->mNormals[i].x);
					norms.push_back(mesh->mNormals[i].x);
					norms.push_back(mesh->mNormals[i].x);

				}

				if (mesh->HasTextureCoords(0)) {
					texCoords.push_back(mesh->mTextureCoords[0][i].x);
					texCoords.push_back(mesh->mTextureCoords[0][i].y);

					texCount += 2;

				}

				if (mesh->HasVertexColors(0)) {
					//colours.push_back(mesh->mColors[j][i].r);
					//colours.push_back(mesh->mColors[j][i].g);
					//colours.push_back(mesh->mColors[j][i].b);

				}
			}

			
			//int ID = OpenglUtils::createMesh((GLuint)verts.size(), (GLfloat*)verts.data(), (GLfloat*)colours.data(), (GLfloat*)norms.data(), (GLfloat*)texCoords.data(), (GLuint)texCoords.size(), (GLuint)indices.size(), (GLuint*)indices.data());
			int ID = OpenglUtils::createAnimatedMesh((GLuint*)boneIDs.data(), (GLfloat*)boneWeights.data(), (GLuint)verts.size(), (GLfloat*)verts.data(), (GLfloat*)colours.data(), (GLfloat*)norms.data(), (GLfloat*)texCoords.data(), (GLuint)texCoords.size(), (GLuint)indices.size(), (GLuint*)indices.data());
			meshIDs.push_back(ID);
			indexCount.push_back(indices.size());

			//cout << "animated loading" << endl;



			colours.clear(); norms.clear(); texCoords.clear(); verts.clear(); indices.clear(); boneIDs.clear(); boneWeights.clear();

		}

		
		//Pass out min and max
		maxmin.push_back(min);
		maxmin.push_back(max);


		//nodes need to find their parents
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->parentName.size() != 0)
			{
				nodes[i]->parent = FindAiNode(nodes[i]->parentName, nodes);
			}
		}


		//filling in bone data
		for (int i = 0; i < bones.size(); i++)
		{
			std::string b_name = bones.at(i)->name;
			std::string parent_name = FindAiNode(b_name, nodes)->parent->name;

			bone* p_bone = FindBone(parent_name, bones);

			bones.at(i)->parent_bone = p_bone;

			if (p_bone == nullptr)
				std::cout << "Parent Bone for " << b_name << " does not exist (is nullptr)" << std::endl;
		}

		
	}

	

	/*void recursiveProcess(aiNode* m_rootNode, const aiScene* scene)
	{
		for (int i = 0; i < m_rootNode->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

		}

		for (int i = 0; i < m_rootNode->mNumChildren; i++)
			recursiveProcess(m_rootNode->mChildren[i], scene);
	}*/
	


	 aiMatrix4x4 GLMMat4ToAi(glm::mat4 mat)
	{
		return aiMatrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
			mat[1][0], mat[1][1], mat[1][2], mat[1][3],
			mat[2][0], mat[2][1], mat[2][2], mat[2][3],
			mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	}

	 glm::mat4 AiToGLMMat4(aiMatrix4x4& in_mat)
	{
		glm::mat4 tmp;
		tmp[0][0] = in_mat.a1;
		tmp[1][0] = in_mat.b1;
		tmp[2][0] = in_mat.c1;
		tmp[3][0] = in_mat.d1;

		tmp[0][1] = in_mat.a2;
		tmp[1][1] = in_mat.b2;
		tmp[2][1] = in_mat.c2;
		tmp[3][1] = in_mat.d2;

		tmp[0][2] = in_mat.a3;
		tmp[1][2] = in_mat.b3;
		tmp[2][2] = in_mat.c3;
		tmp[3][2] = in_mat.d3;

		tmp[0][3] = in_mat.a4;
		tmp[1][3] = in_mat.b4;
		tmp[2][3] = in_mat.c4;
		tmp[3][3] = in_mat.d4;
		return tmp;
	}





	 //Search and return a bone by name
	 bone* FindBone(std::string name, std::vector<bone*>& bones)
	 {
		 for (int i = 0; i < bones.size(); i++)
		 {
			 if (bones.at(i)->name == name)
				 return bones.at(i);
		 }

		 return nullptr;
	 }

	 //Search and return a node by name
	 node* FindAiNode(std::string name, vector<node*>& ai_nodes)
	 {
		 for (int i = 0; i < ai_nodes.size(); i++)
		 {
			 if (ai_nodes[i]->name == name)
			 {

				 return ai_nodes.at(i);
			 }

		 }
		 return nullptr;


	 }


	 animNode* FindAiNodeAnim(std::string name, vector<animNode*>& ai_nodes_anim)
	 {
		 for (int i = 0; i < ai_nodes_anim.size(); i++)
		 {
			 if (ai_nodes_anim.at(i)->nodeName == name)
				 return ai_nodes_anim.at(i);
		 }
		 return nullptr;
	 }

	 //return index of bone in our bones vector
	 int FindBoneIDByName(std::string name, std::vector<bone*>& bones)
	 {
		 for (int i = 0; i < bones.size(); i++)
		 {
			 if (bones.at(i)->name == name)
				 return i;
		 }
		 return -1;
	 }


}//Namspace AssimpLoader



//
//
//void loadBoneData(const std::string& file)
//{
//	// Create an instance of the Importer class for loading the object data
//	Assimp::Importer importer;
//
//
//	//loads our file into a scene object so its all accessible.
//	const aiScene* scene = importer.ReadFile(file,
//		aiProcess_CalcTangentSpace |
//		aiProcess_Triangulate |
//		aiProcess_FlipUVs |
//		aiProcess_SortByPType |
//		aiProcess_GenSmoothNormals |
//		aiProcess_GenNormals
//	);
//
//
//	for (int i = 0; i < scene->mNumAnimations; i++)
//	{
//		std::cout << scene->mAnimations[i]->mName.data << std::endl;
//		std::cout << scene->mAnimations[i]->mDuration << std::endl;
//		std::cout << scene->mAnimations[i]->mNumChannels << std::endl;
//
//		for (int j = 0; j < scene->mAnimations[i]->mNumChannels; j++)
//		{
//			std::cout << scene->mAnimations[i]->mChannels[j]->mNodeName.data << std::endl;
//			std::cout << scene->mAnimations[i]->mChannels[j]->mPositionKeys->mTime << std::endl;
//			std::cout << scene->mAnimations[i]->mChannels[j]->mPositionKeys->mValue.x << std::endl;
//			std::cout << scene->mAnimations[i]->mChannels[j]->mPositionKeys->mValue.y << std::endl;
//			std::cout << scene->mAnimations[i]->mChannels[j]->mPositionKeys->mValue.z << std::endl;
//		}
//	}
//
//}
//
//void loadAnimationData(aiScene* scene)
//{
//
//	for (unsigned int k = 0; k < scene->mNumMeshes; k++)
//	{
//		aiMesh* pMesh = scene->mMeshes[k];
//
//
//		/*for (int i = 0; i < pMesh->mNumBones; i++) {
//		int BoneIndex = 0;
//		string BoneName(pMesh->mBones[i]->mName.data);
//
//		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
//		BoneIndex = m_NumBones;
//		m_NumBones++;
//		BoneInfo bi;
//		m_BoneInfo.push_back(bi);
//		}
//		else {
//		BoneIndex = m_BoneMapping[BoneName];
//		}
//
//		m_BoneMapping[BoneName] = BoneIndex;
//		m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
//
//		for (int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
//		int VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
//		float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
//		Bones[VertexID].AddBoneData(BoneIndex, Weight);
//		}
//		}*/
//	}
//
//}
