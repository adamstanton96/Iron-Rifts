#include "OBB.h"


OBB::OBB(glm::vec3 min, glm::vec3 max)
{
	objectSpaceMin = min;
	objectSpaceMax = max;


}


void OBB::calculateVertices()
{

	vertices.push_back(glm::vec3(objectSpaceMin));
	vertices.push_back(glm::vec3(objectSpaceMin.x, objectSpaceMax.y, objectSpaceMin.z));
	vertices.push_back(glm::vec3(objectSpaceMin.x, objectSpaceMin.y, objectSpaceMax.z));
	vertices.push_back(glm::vec3(objectSpaceMin.x, objectSpaceMax.y, objectSpaceMax.z));

	vertices.push_back(glm::vec3(objectSpaceMax));
	vertices.push_back(glm::vec3(objectSpaceMax.x, objectSpaceMin.y, objectSpaceMin.z));
	vertices.push_back(glm::vec3(objectSpaceMax.x, objectSpaceMax.y, objectSpaceMin.z));
	vertices.push_back(glm::vec3(objectSpaceMax.x, objectSpaceMin.y, objectSpaceMax.z));

	
}

void OBB::updateVertices()
{
	
	std::cout << vertices.size() << std::endl;
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = glm::vec4(vertices[i], 0) * rotation;
		vertices[i] = vertices[i] + position;

		/*std::cout << "X: " << vertices[i].x;
		std::cout << " Y: " << vertices[i].y;
		std::cout << " Z: " << vertices[i].z << std::endl;*/
	}

}


void OBB::update(glm::vec3 worldPos)
{
	worldSpaceMin = objectSpaceMin + worldPos;
	worldSpaceMax = objectSpaceMax + worldPos;
}

void OBB::setminmax(glm::vec3 min, glm::vec3 max)
{
	objectSpaceMin = min;
	objectSpaceMax = max;
}


void OBB::setGlobalPosition(glm::vec3 pos)
{
	position = pos;
	updateVertices();
}

void OBB::calculateSurfaceNormals()
{
	glm::vec3 faceNormal;
	
	//"min" normals (3)
	faceNormals.push_back( glm::cross((vertices[2] - vertices[0]), (vertices[1] - vertices[0])) );
	faceNormals.push_back( glm::cross((vertices[1] - vertices[0]), (vertices[5] - vertices[0])) );
	faceNormals.push_back( glm::cross((vertices[5] - vertices[0]), (vertices[2] - vertices[0])) );

	//"max" normals (3)
	faceNormals.push_back( glm::cross((vertices[2] - vertices[4]), (vertices[7] - vertices[4])) );
	faceNormals.push_back( glm::cross((vertices[7] - vertices[4]), (vertices[5] - vertices[4])) );
	faceNormals.push_back( glm::cross((vertices[6] - vertices[4]), (vertices[3] - vertices[4])) );


	std::cout << "Face Normals:   " << std::endl;
	std::cout << faceNormals.size() << std::endl;
	for (int i = 0; i < faceNormals.size(); i++)
	{
		//Do They Need Normalized?
		faceNormals[i] = glm::normalize(faceNormals[i]);

		std::cout << "X: " << faceNormals[i].x;
		std::cout << " Y: " << faceNormals[i].y;
		std::cout << " Z: " << faceNormals[i].z << std::endl;
	}

	
}

void OBB::setRotation(float degrees, glm::vec3 roatationAxis)
{

	glm::mat4 Identity(1.0);
	glm::mat4 stack = Identity;

	//stack = glm::translate(stack, position);
	rotation = glm::rotate(stack, float(degrees * DEG_TO_RADIAN), roatationAxis);

	rotatedMin = glm::vec4(objectSpaceMin, 1);
	rotatedMax = glm::vec4(objectSpaceMax, 1);

	rotatedMin = rotatedMin * rotation;
	rotatedMax = rotatedMax * rotation;


	worldSpaceMin = glm::vec3(rotatedMin) + position;
	worldSpaceMax = glm::vec3(rotatedMax) + position;


	
	updateVertices();
	calculateSurfaceNormals();
}



void OBB::printDetails()
{

	std::cout << "Object Space Non Rotated Values: " << std::endl;
	std::cout << "MinX: " << objectSpaceMin.x << std::endl;
	std::cout << "MaxX: " << objectSpaceMax.x << std::endl;
	std::cout << "MinY: " << objectSpaceMin.y << std::endl;
	std::cout << "MaxY: " << objectSpaceMax.y << std::endl;
	std::cout << "MinZ: " << objectSpaceMin.z << std::endl;
	std::cout << "MaxZ: " << objectSpaceMax.z << std::endl;

	std::cout << "World Space Rotated Values: " << std::endl;
	std::cout << "MinX: " << worldSpaceMin.x << std::endl;
	std::cout << "MaxX: " << worldSpaceMax.x << std::endl;
	std::cout << "MinY: " << worldSpaceMin.y << std::endl;
	std::cout << "MaxY: " << worldSpaceMax.y << std::endl;
	std::cout << "MinZ: " << worldSpaceMin.z << std::endl;
	std::cout << "MaxZ: " << worldSpaceMax.z << std::endl;


	std::cout << "Rotated Values: " << std::endl;
	std::cout << "MinX: " << rotatedMin.x << std::endl;
	std::cout << "MaxX: " << rotatedMax.x << std::endl;
	std::cout << "MinY: " << rotatedMin.y << std::endl;
	std::cout << "MaxY: " << rotatedMax.y << std::endl;
	std::cout << "MinZ: " << rotatedMin.z << std::endl;
	std::cout << "MaxZ: " << rotatedMax.z << std::endl;

	

	
	draw();

}


void OBB::draw()
{
	GLfloat lineCoordinates[] = { rotatedMin.x, rotatedMin.y,
		rotatedMin.z, rotatedMax.x, rotatedMax.y, rotatedMax.z };
	
	int mesh = OpenglUtils::createMesh(2, lineCoordinates, nullptr, nullptr, nullptr, NULL, NULL, nullptr);
	OpenglUtils::drawMesh(mesh, 2, GL_LINE);
}
