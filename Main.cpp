#include<filesystem>
#include <memory>
namespace fs = std::filesystem;

#include "Mesh.h"
#include "FileReadWrite.h"
#include "BoundingBox.h"
#include <utility>

const unsigned int width = 1200;
const unsigned int height = 1200;

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{
	//---------------------------------------------------------------------//
	//----------------------- Filesystem to find folder -----------------------//
	//---------------------------------------------------------------------//
	std::string currentDir = (fs::current_path()).string();
	std::string TexturePath = "/Resources/Textures/";
	std::string ObjectPath = "/Resources/Objects/";


	//---------------------------------------------------------------------//
	//----------------------- Pointers -----------------------//
	//---------------------------------------------------------------------//
	std::shared_ptr<ReadWriteFiles> ReadWritePTR = std::make_shared<ReadWriteFiles>();


	//---------------------------------------------------------------------//
	//----------------------- Open GL Config -----------------------//
	//---------------------------------------------------------------------//
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Texture data
	Texture texturesBridge[]
	{
		Texture((currentDir + TexturePath + "planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((currentDir + TexturePath + "planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)

	};

	Texture texturesCastle[]
	{
		Texture((currentDir + TexturePath + "StoneWallSpec.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((currentDir + TexturePath + "StoneWallSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
		//Texture((currentDir + TexturePath + "StoneWallSpec.png").c_str(), "specular", 3, GL_RED, GL_UNSIGNED_BYTE)
	};

	Texture texturesGround[]
	{
		Texture((currentDir + TexturePath + "Grass.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((currentDir + TexturePath + "Grass.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture texturesGold[]
	{
		Texture((currentDir + TexturePath + "Gold.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((currentDir + TexturePath + "Gold.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
	};

	//---------------------------------------------------------------------//
	//----------------------- Creating objects and mesh data -----------------------//
	//---------------------------------------------------------------------//

	// Creating small trophies to pick up
    int ObjectAmount = 6;

	std::vector<Mesh> MeshVector;
    std::vector<std::vector<Vertex>> VertexVectorTrophy(ObjectAmount + 1);
    std::vector<std::vector<int>> IndicesVectorTrophy(ObjectAmount + 1);

    for (int i = 0; i <= ObjectAmount; i++)
    {
        std::string vertexFilePath = "Datafiles/3DProgTrophy" + std::to_string(i) + "Vertices.txt";
        std::string indicesFilePath = "Datafiles/3DProgTrophy" + std::to_string(i) + "Indices.txt";
        std::string textCoordsFilePath = "Datafiles/3DProgTrophy" + std::to_string(i) + "TextCoords.txt";

        ReadWritePTR->ReadFromFileWriteIntoNewFile(currentDir + ObjectPath + "3DProgTrophy" + std::to_string(i) + ".obj", vertexFilePath, textCoordsFilePath, indicesFilePath);
        ReadWritePTR->FromDataToVertexVector(vertexFilePath, textCoordsFilePath, VertexVectorTrophy[i]);
        ReadWritePTR->FromDataToIndicesVector(indicesFilePath, IndicesVectorTrophy[i]);

    	std::vector<Vertex> TrophyVertices(std::begin(VertexVectorTrophy[i]), std::end(VertexVectorTrophy[i]));
		std::vector<GLuint> TrophyIndices(std::begin(IndicesVectorTrophy[i]), std::end(IndicesVectorTrophy[i]));
		std::vector <Texture> TrophyTexture(texturesGold, texturesGold + sizeof(texturesGold) / sizeof(Texture));

		MeshVector.emplace_back(TrophyVertices, TrophyIndices, TrophyTexture);
    }

	// Castle
	std::vector<Vertex> VertexVectorSlott;
	std::vector<int> IndicesVectorSlott;
	ReadWritePTR->ReadFromFileWriteIntoNewFile(currentDir + ObjectPath + "3DProgSlott.obj", "Datafiles/SlottFileVert.txt", "Datafiles/SlottFileTextCoords.txt", "Datafiles/SlottFileIndices.txt");
	ReadWritePTR->FromDataToVertexVector("Datafiles/SlottFileVert.txt", "Datafiles/SlottFileTextCoords.txt", VertexVectorSlott);
	ReadWritePTR->FromDataToIndicesVector("Datafiles/SlottFileIndices.txt", IndicesVectorSlott);
	std::vector <Vertex> SlottVertices(std::begin(VertexVectorSlott), std::end(VertexVectorSlott));
	std::vector <GLuint> SlottIndices(std::begin(IndicesVectorSlott), std::end(IndicesVectorSlott));
	std::vector <Texture> SlottTexture(texturesCastle, texturesCastle + sizeof(texturesCastle) / sizeof(Texture));
	MeshVector.emplace_back(SlottVertices, SlottIndices, SlottTexture);

	// Bridge
	std::vector<Vertex> VertexVectorBru;
	std::vector<int> IndicesVectorBru;
	ReadWritePTR->ReadFromFileWriteIntoNewFile(currentDir + ObjectPath + "3DProgBru.obj", "Datafiles/BruFileVert.txt", "Datafiles/BruFileTextCoords.txt", "Datafiles/BruFileIndices.txt");
	ReadWritePTR->FromDataToVertexVector("Datafiles/BruFileVert.txt", "Datafiles/BruFileTextCoords.txt", VertexVectorBru);
	ReadWritePTR->FromDataToIndicesVector("Datafiles/BruFileIndices.txt", IndicesVectorBru);
	std::vector <Vertex> BruVertices(std::begin(VertexVectorBru), std::end(VertexVectorBru));
	std::vector <GLuint> BruIndices(std::begin(IndicesVectorBru), std::end(IndicesVectorBru));
	std::vector <Texture> BruTexture(texturesBridge, texturesBridge + sizeof(texturesBridge) / sizeof(Texture));
	MeshVector.emplace_back(BruVertices, BruIndices, BruTexture);

	// Ground
	std::vector<Vertex> VertexVectorBakke;
	std::vector<int> IndicesVectorBakke;
	ReadWritePTR->ReadFromFileWriteIntoNewFile(currentDir + ObjectPath + "3DProgBakke.obj", "Datafiles/BakkeByggFileVert.txt", "Datafiles/BakkeFileTextCoords.txt", "Datafiles/BakkeByggFileIndices.txt");
	ReadWritePTR->FromDataToVertexVector("Datafiles/BakkeByggFileVert.txt", "Datafiles/BakkeFileTextCoords.txt", VertexVectorBakke);
	ReadWritePTR->FromDataToIndicesVector("Datafiles/BakkeByggFileIndices.txt", IndicesVectorBakke);
	std::vector <Vertex> BakkeVertices(std::begin(VertexVectorBakke), std::end(VertexVectorBakke));
	std::vector <GLuint> BakkeIndices(std::begin(IndicesVectorBakke), std::end(IndicesVectorBakke));
	std::vector <Texture> BakkeTexture(texturesGround, texturesGround + sizeof(texturesGround) / sizeof(Texture));
	MeshVector.emplace_back(BakkeVertices, BakkeIndices, BakkeTexture);

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVerts, lightInd, BruTexture);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	///Collision Control
	BoundingBox A;
	BoundingBox B; 

	std::vector<glm::vec3> OrigoPointsVector = ReadWritePTR->getOrigoVector;
	std::vector<glm::vec3> trans;

	trans.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f)); 

	std::vector<std::vector<Vertex>> getMesh;
	getMesh.emplace_back(BakkeVertices);
	getMesh.emplace_back(lightVerts);


	glm::vec3 BBSize{ 5.0f,5.0f,5.0f };

	for (auto i = 0; i < getMesh.size(); i++)
	{
		for (auto j = i + 1; j < getMesh.size(); j++)
		{
			auto a = BoundingBox(getMesh[i], OrigoPointsVector[i], BBSize); 
			auto b = BoundingBox(getMesh[j], OrigoPointsVector[j], BBSize);   

			glm::vec3 mtv{};
			if (a.IntersectAABB(b, &mtv))
			{
				/*a.getVertex[i].position - mtv * 0.5f;
				b.getVertex[j].position + mtv * 0.5f;*/
			}
		}
	}




	//BB.IntersectObject(std::pair(VertexVectorBru, VertexVectorBakke), trans); 

	//BB.IntersectPlayer(OrigoPointsVector, trans); 
	

	//---------------------------------------------------------------------//
	//----------------------- Main While Loop -----------------------//
	//---------------------------------------------------------------------//
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Draws different meshes
		light.Draw(lightShader, camera);

		
		for (Mesh Objects : MeshVector)
		{

			Objects.Draw(shaderProgram, camera);
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}