#ifndef MESHCOMPONENT
#define MESHCOMPONENT

#include <glm/glm.hpp>
#include <vector>
#include "Component.h"
#include "RenderingSystem.h"
using namespace std;


class MeshComponent : public Component
{
public:
	MeshComponent(std::string name);
	MeshComponent(){}
	~MeshComponent() {}

	void init();
	void update();

	
	void loadTexture(char * filename);
	void loadObject(const char * filename);

	//Gets
	glm::vec3 getTranslation();
	glm::vec3 getScaling();
	glm::vec3 getRotate();

	//Sets
	void addTexture(int ID) { textures.push_back(ID); }
	void setRenderer(RenderingSystem* rendersystem);
	void setTranslation(glm::vec3 tran);
	void setScaling(glm::vec3 scale);

	//If the user has a rigid body give it the meshes min and max
	void setMinMax(vector<glm::vec3> minmax);
	

	void setMeshes(vector<int> meshIDs);
	vector<int> getMeshes();

	vector<int> getTextures();

	float getRenderRotateDeg() { return deg; }

	void setIndexCounts(vector<int> indexCounts);
	vector<int> getIndexCounts();

	RenderingSystem *renderer;

	bool isAnimated;

protected:
	//transformation data for renderer
	glm::vec3 translation;
	glm::vec3 scaling;
	glm::vec3 rotate;
	float deg;


	vector<int> meshIDs;
	vector<int> indexCounts;
	vector<int> textures;	

	

};
#endif