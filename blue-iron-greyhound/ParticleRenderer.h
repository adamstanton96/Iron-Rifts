#pragma once
#include "System.h"
#include "OpenglUtils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "CameraComponent.h"


#define DEG_TO_RADIAN 0.017453293

class ParticleRenderer : public System
{
public:
	ParticleRenderer(Camera* camera);
	~ParticleRenderer();

	void init();
	void draw(glm::vec3 pos, glm::vec3 colour);

	void update();

private:
	int shaderID;

	Camera* camera;

	GLfloat r;
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::mat4 projection;
	std::stack<glm::mat4> mvStack;


	char* particleVert =
	{
	"	#version 330					\n"
	"									\n"
	"uniform vec4 spotLightPosition; \n"
	"out vec4 Vposition;				\n"

	"in  vec3 in_Position;				\n"
	"in  vec4 in_Color;					\n"
	"out vec4 ex_Color;					\n"

	"uniform mat4 modelview;			\n"
	"uniform mat4 projection;			\n"
	"uniform float pointSize;			\n"

	"void main(void)					\n"
	"{									\n"
	"	ex_Color = in_Color;			\n"

	"	vec4 vertexPosition = modelview * vec4(in_Position,1.0);		\n"

	"	//Calculate distance from point to camera and					\n"
	"	//scale point size so size is consistent at varying distances	\n"
	"	float distance = distance(vec3(vertexPosition), vec3(0,0,0));	\n"
	"	gl_PointSize = pointSize / distance;							\n"

	"	gl_Position = projection * vertexPosition;						\n"

	"	//spotlight														\n"
	"	Vposition = vertexPosition;										\n"
	"} \n"
	};


	char* particleFrag =
	{
	"	#version 330				\n"

	"	precision highp float;		\n"

	"struct lightStruct				\n"
	"{								\n"
	"	vec4 ambient;				\n"
	"	vec4 diffuse;				\n"
	"	vec4 specular;				\n"
	"};								\n"

	"uniform lightStruct spotLight;															\n"
	"uniform	vec4 spotLightPosition;				// Position in eye coords.				\n"
	"uniform vec3 spotlightDirection;			// Normalized direction of the spotlight	\n"
	"uniform int angle1;							// Angle of outer cone					\n"
	"uniform	int angle2;							// Angle of inner cone					\n"
	"in vec4 Vposition;							// Vertex position							\n"


	"uniform float attConst;			\n"
	"uniform float attLinear;			\n"
	"uniform float attQuadratic;		\n"

	"in  vec4 ex_Color;					\n"
	"out vec4 out_Color;				\n"
	"uniform sampler2D textureUnit0;	\n"


	"void main(void)								\n"
	"{												\n"
	"	float DEG_TO_RADIANS = 0.017453293;			\n"

	"	float ang1 = angle1 * DEG_TO_RADIANS;		\n"
	"	float ang2 = angle2 * DEG_TO_RADIANS;		\n"

	"	//Spotlight calculations					\n"
	"	vec4 totalLight;							\n"

	"	//Finds the vector from the spotlight to the vertex		\n"
	"	vec3 L = spotLightPosition.xyz - Vposition.xyz;			\n"
	"	float distToLight = length(L);									//this could be used for attenuation \n"
	"	L = normalize(L);										\n"

	"	//The angle between spotlight direction and vertex				\n"
	"	float cosDir = dot(L, -spotlightDirection);						\n"

	"	//Compare vector to frag from light to the cones angles			\n"
	"	float spotEffect = smoothstep(cos(ang2) , cos(ang1) ,cosDir);	\n"

	"	//Add the spotlight light values and times by spoteffect.		\n"
	"	//Spoteffect will be zero if the current fragment is not in the spotlights light cone\n"
	"	vec4 lightSpot = vec4(spotEffect) * (spotLight.diffuse + spotLight.specular);\n"

	"	totalLight = vec4(lightSpot);									\n"


	"	//Ditch low values of transparency								\n"
	"	if (texture(textureUnit0, gl_PointCoord).a < 0.5) discard;		\n"

	"	out_Color = (ex_Color + totalLight) * vec4(ex_Color.a);			\n"


	"}																	\n"
	};
};