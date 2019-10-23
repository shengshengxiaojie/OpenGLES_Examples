﻿#include <examplebase.h>
#include <mesh.h>
#include <material.h>
using namespace es;

class Example final : public ExampleBase
{
public:
	std::vector<std::shared_ptr<Mesh>> cubes;

	Example()
	{
		title = "blinn phong lighting";
		settings.vsync = true;
		defaultClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		shadersDirectory = getResourcesPath(ResourceType::Shader) + "/13.blinn_phong_lighting/";
		texturesDirectory = getResourcesPath(ResourceType::Texture) + "/13.blinn_phong_lighting/";
	}
	~Example()
	{

	}
public:
	virtual void prepare() override
	{
		ExampleBase::prepare();

		// enable depth test
		glEnable(GL_DEPTH_TEST);

		// all positions of cubes
		std::array<glm::vec3, 10> cubePositions = {
			glm::vec3(0.0f,  3.0f,  -3.0f),
			glm::vec3(0.8f,  3.0f, -4.0f),
			glm::vec3(-2.5f, 2.2f, -3.2f),
			glm::vec3(-3.5f, -2.0f, -3.3f),
			glm::vec3(2.0f, -0.4f, -2.0f),
			glm::vec3(-1.7f,  3.0f, -3.5f),
			glm::vec3(1.3f, -3.0f, -2.8f),
			glm::vec3(1.8f,  2.0f, 0.5f),
			glm::vec3(2.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		std::vector<float> vertexAttribs = {
			// positions          // normals           // texture coordinates
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};

		std::vector<Vertex> vertices = {};
		for (uint32_t i = 0; i < static_cast<uint32_t>(vertexAttribs.size() / 8); i++)
		{
			Vertex vertex;
			vertex.vPosition = glm::vec3(vertexAttribs[i * 8], vertexAttribs[i * 8 + 1], vertexAttribs[i * 8 + 2]);
			vertex.vTexcoord = glm::vec2(vertexAttribs[i * 8 + 6], vertexAttribs[i * 8 + 7]);
			vertex.vNormal = glm::vec3(vertexAttribs[i * 8 + 3], vertexAttribs[i * 8 + 4], vertexAttribs[i * 8 + 5]);
			vertices.push_back(vertex);
		}

		std::unordered_map<Material::ShaderType, std::string> shaderPaths =
		{
			{ Material::ShaderType::VERTEX, shadersDirectory + "cube.vert" },
			{ Material::ShaderType::FRAGMENT, shadersDirectory + "cube.frag" }
		};

		std::vector<std::pair<Texture::Type, std::string>> texturePaths =
		{
			std::make_pair(Texture::Type::DIFFUSE, texturesDirectory + "cube_diffuse.png"),
			std::make_pair(Texture::Type::SPECULAR, texturesDirectory + "cube_specular.png")
		};

		// create cube material
	    material = std::make_shared<Material>(shaderPaths, texturePaths);

		for (unsigned int i = 0; i < cubePositions.size(); i++)
		{
			Mesh* cube = Mesh::createWithData(vertices, {}, material, Mesh::DrawType::ARRAYS);
			cube->setPosition(cubePositions[i]);
			cube->setRotation(glm::vec3(20.0f * i, 12.0f * i, 7.0f * i));
			cube->setScale(glm::vec3(0.7f));
			cubes.push_back(cube);
		}
	}

	virtual void render(float deltaTime) override
	{
		SDL_GetWindowSize(window, &destWidth, &destHeight);
		glViewport(0, 0, destWidth, destHeight);
		glClearColor(defaultClearColor.r, defaultClearColor.g, defaultClearColor.b, defaultClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		material->setVector3("viewPos", camera->getPosition());
		material->setFloat("shininess", 32.0f);
		// directional light
		material->setVector3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		material->setVector3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		material->setVector3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		material->setVector3("dirLight.specular", glm::vec3(0.4f, 0.4f, 0.4f));
		// point light
		material->setVector3("pointLight.position", glm::vec3(0.0f, 0.0f, 0.0f));
		material->setVector3("pointLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		material->setVector3("pointLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		material->setVector3("pointLight.specular", glm::vec3(0.8f, 0.8f, 0.8f));
		material->setFloat("pointLight.constant", 1.0f);
		material->setFloat("pointLight.linear", 0.022f);
		material->setFloat("pointLight.quadratic", 0.0019f);
		// spot light
		material->setVector3("spotLight.position", camera->getPosition());
		material->setVector3("spotLight.direction", camera->getFrontVector());
		material->setVector3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		material->setVector3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		material->setVector3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		material->setFloat("spotLight.constant", 1.0f);
		material->setFloat("spotLight.linear", 0.09f);
		material->setFloat("spotLight.quadratic", 0.032f);
		material->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		material->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		for (unsigned int i = 0; i < cubes.size(); i++)
		{
			cubes[i]->render(deltaTime);
		}
	}
};

Example* example;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	example = new Example();
	example->setupValidation();
	if (!example->setupSDL() ||
		!example->loadGLESFunctions() ||
		!example->setupImGui())
	{
		return 0;
	}
	example->prepare();
	example->renderLoop();
	delete(example);
	return 0;
}