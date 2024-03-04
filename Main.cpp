#include<filesystem>
#include <memory>
namespace fs = std::filesystem;

#include"Mesh.h"
#include "FileReadWrite.h"

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
	std::shared_ptr<ReadWriteFiles> ReadWritePTR = std::make_shared<ReadWriteFiles>();

	std::vector<Vertex> VertexVectorSlott;
	std::vector<int> IndicesVectorSlott;
	ReadWritePTR->ReadFromFileWriteIntoNewFile("3DProgSlott.obj", "SlottFileVert.txt", "SlottFileFace.txt");
	ReadWritePTR->FromDataToVertexVector("SlottFileVert.txt", VertexVectorSlott);
	ReadWritePTR->FromDataToIndicesVector("SlottFileFace.txt", IndicesVectorSlott);

	std::vector<Vertex> VertexVectorBru;
	std::vector<int> IndicesVectorBru;
	ReadWritePTR->ReadFromFileWriteIntoNewFile("3DProgBru.obj", "BruFileVert.txt", "BruFileFace.txt");
	ReadWritePTR->FromDataToVertexVector("BruFileVert.txt", VertexVectorBru);
	ReadWritePTR->FromDataToIndicesVector("BruFileFace.txt", IndicesVectorBru);

	std::vector<Vertex> VertexVectorBakke;
	std::vector<int> IndicesVectorBakke;
	ReadWritePTR->ReadFromFileWriteIntoNewFile("3DProgBakke.obj", "BakkeByggFileVert.txt", "BakkeByggFileFace.txt");
	ReadWritePTR->FromDataToVertexVector("BakkeByggFileVert.txt", VertexVectorBakke);
	ReadWritePTR->FromDataToIndicesVector("BakkeByggFileFace.txt", IndicesVectorBakke);

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

	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	std::string currentDir = (fs::current_path()).string();
	std::string texPath = "/Resources/";

	// Texture data
	Texture textures[]
	{
		Texture((currentDir + texPath + "planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((currentDir + texPath + "planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// Original code from the tutorial
	/*Texture textures[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};*/

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Store mesh data in vectors for the mesh
	std::vector <Vertex> SlottVertices(std::begin(VertexVectorSlott), std::end(VertexVectorSlott));
	std::vector <GLuint> SlottIndices(std::begin(IndicesVectorSlott), std::end(IndicesVectorSlott));
	std::vector <Texture> SlottTexture(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create hus mesh
	Mesh Slott(SlottVertices, SlottIndices, SlottTexture);

	// Store mesh data in vectors for the mesh
	std::vector <Vertex> BruVertices(std::begin(VertexVectorBru), std::end(VertexVectorBru));
	std::vector <GLuint> BruIndices(std::begin(IndicesVectorBru), std::end(IndicesVectorBru));
	std::vector <Texture> BruTexture(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	Mesh Bru(BruVertices, BruIndices, BruTexture);

	// Store mesh data in vectors for the mesh
	std::vector <Vertex> BakkeVertices(std::begin(VertexVectorBakke), std::end(VertexVectorBakke));
	std::vector <GLuint> BakkeIndices(std::begin(IndicesVectorBakke), std::end(IndicesVectorBakke));
	std::vector <Texture> BakkeTexture(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	Mesh TestBygg(BakkeVertices, BakkeIndices, BakkeTexture);

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

	// Main while loop
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
		Slott.Draw(shaderProgram, camera);
		Bru.Draw(shaderProgram, camera);
		TestBygg.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

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

//// Vertices coordinates
//Vertex vertices[] =
//{ //               COORDINATES							   /				  COLORS					 /					NORMALS					/	       TEXTURE COORDINATES    //
//	////Vegg 1
//	//Vertex{glm::vec3(0.0f, 2.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, 0.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, 2.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//
//	////Vegg 2
//	//Vertex{glm::vec3(-5.0f, 2.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 2.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 0.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//
//	////Vegg 3
//	//Vertex{glm::vec3(-5.0f, 2.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 0.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 2.0f,  6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 0.0f,  6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//
//	////Vegg 4
//	//Vertex{glm::vec3(0.0f, 2.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, 0.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 2.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, -0.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//
//	////Vegg 5
//	//Vertex{glm::vec3(0.0f, 2.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 2.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, -0.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//
//	////Tak
//	//Vertex{glm::vec3(-5.0f, 2.0f,  8.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, 2.0f,  .0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(-5.0f, 2.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	//Vertex{glm::vec3(0.0f, -2.0f,  3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}
//
//
//	//HovedBygg
//	Vertex{glm::vec3(-3.0, 0.0,  0.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.625, 0.25)},
//	Vertex{glm::vec3(-3.0, 2.0,  0.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.375, 0.50)},
//	Vertex{glm::vec3(-3.0, 0.0, -1.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.375, 0.25)},
//	Vertex{glm::vec3(-3.0, 2.0, -1.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.625, 0.50)},
//	Vertex{glm::vec3(-1.0, 0.0,  0.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.375, 0.75)},
//	Vertex{glm::vec3(-1.0, 2.0,  0.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.625, 0.75)},
//	Vertex{glm::vec3(-1.0, 0.0, -1.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.375, 1.00)},
//	Vertex{glm::vec3(-1.0, 2.0, -1.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.125, 0.75)}
//
//	//Vertex{glm::vec3(-5.0, 2.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//	//Vertex{glm::vec3(0.0, 2.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(0.0, 2.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//	//Vertex{glm::vec3(0.0, 2.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(0.0, 0.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(0.0, 2.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//	//Vertex{glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 5.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//	//Vertex{glm::vec3(-5.0, 	0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	0.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 6.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//	//Vertex{glm::vec3(-5.0, 	0.0, 6.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(0.0, 2.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(0.0, 0.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//	//Vertex{glm::vec3(-5.0, -0.0, 8.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(0.0, 2.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//
//	//Vertex{glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0, 	2.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	//Vertex{glm::vec3(-5.0,   -0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//
//
//	/*Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
//	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
//	Vertex{glm::vec3(-2.0f, -1.0f,  2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
//	Vertex{glm::vec3(-2.0f, -1.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
//	Vertex{glm::vec3( 2.0f, -1.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
//	Vertex{glm::vec3( 2.0f, -1.0f,  2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}*/
//};

//// Indices for vertices order
//GLuint indices[] =
//{
//3, 6, 2,
//7, 4, 6,
//5, 0, 4,
//6, 0, 2,
//3, 5, 7,
//3, 7, 6,
//7, 5, 4,
//5, 1, 0,
//6, 4, 0,
//3, 1, 5
//
//};