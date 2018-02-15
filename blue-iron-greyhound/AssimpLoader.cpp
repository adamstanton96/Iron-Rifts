#include "AssimpLoader.h"
using namespace std;
#include <iostream>
#include "OpenglUtils.h"
#include <glm/glm.hpp>


namespace AssimpLoader
{
	

	void recursiveNodeProcess(aiNode* node, vector<aiNode*>& ai_nodes)
	{
		ai_nodes.push_back(node);

		for (int i = 0; i < node->mNumChildren; i++)
			recursiveNodeProcess(node->mChildren[i], ai_nodes);
	}


	void AnimNodeProcess(const aiScene* m_scene, vector<aiNodeAnim*>& ai_nodes_anim)
	{
		if (m_scene->mNumAnimations == 0)
			return;

		for (int i = 0; i < m_scene->mAnimations[0]->mNumChannels; i++)
			ai_nodes_anim.push_back(m_scene->mAnimations[0]->mChannels[i]);
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
		cout << "normal loading" << endl;

		//Pass out min and max
		maxmin.push_back(min);
		maxmin.push_back(max);

		
	}


	


	//Extracts all the data we need and puts into into our parameters
	//includes data for animations
	void loadObjectDataAnimations(const std::string& file, vector<int>& meshIDs, vector<int>& indexCount, vector<glm::vec3>& maxmin, vector<aiNode*>& ai_nodes, vector<aiNodeAnim*>& ai_nodes_anim)
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



	


		for (unsigned int j = 0; j < scene->mNumMeshes; j++)
		{


			mesh = scene->mMeshes[j];
			int numOfFaces = mesh->mNumFaces;
			int numOfIndices = numOfFaces * 3;


			int WEIGHTS_PER_VERTEX = 4;
			int size = mesh->mNumVertices*WEIGHTS_PER_VERTEX;

			std::vector<int> boneIDs(size);
			std::vector<float> boneWeights(size);

		
			// Pull per vertex bone related data (vertex ID's and Weights)
		for (int i = 0; i < mesh->mNumBones; i++)
		{
				aiBone* currBone = mesh->mBones[i];

				for (int j = 0; j < currBone->mNumWeights; j++)
				{
					aiVertexWeight weight = currBone->mWeights[j];
					

					unsigned int vertexStart = weight.mVertexId * WEIGHTS_PER_VERTEX;

					//cout << vertexStart << endl;

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

		cout << "animated loading" << endl;
		//Pass out min and max
		maxmin.push_back(min);
		maxmin.push_back(max);


		//Parse the scene nodes
		aiNode* m_rootNode = scene->mRootNode;
		recursiveNodeProcess(m_rootNode, ai_nodes);

		//Pull out the scenes mAnimation
		AnimNodeProcess(scene, ai_nodes_anim);

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
