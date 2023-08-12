#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <common/config.h>
#include <common/camera.h>
#include <common/renderer.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Renderer::Renderer()
{
	// We get the camera from the scene later
	_camera = nullptr;

	_viewMatrix = glm::mat4(1.0f);
	_projectionMatrix = glm::mat4(1.0f);

	// Create window with OpenGL context
	this->init();
}

Renderer::~Renderer()
{
	// Cleanup VBO and shader
	glDeleteProgram(_programID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

int Renderer::init()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	// Set OpenGL version (2.1)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( WIDTH, HEIGHT, "Demo", NULL, NULL);
	if( _window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	_programID = this->loadShaders("shaders/sprite.vert", "shaders/sprite.frag");

	// Use our shader
	glUseProgram(_programID);

	return 0;
}

float Renderer::updateDeltaTime() {
	// lastTime is initialised only the first time this function is called
	static double lastTime = glfwGetTime();
	// get the current time
	double currentTime = glfwGetTime();

	// Compute time difference between current and last time
	float deltaTime = float(currentTime - lastTime);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
	return deltaTime;
}

void Renderer::renderScene(Scene* scene)
{
	// get camera from scene and update
	_camera = scene->camera();

	_viewMatrix = _camera->getViewMatrix();
	_projectionMatrix = _camera->getProjectionMatrix();

	glm::mat4 im = glm::mat4(1.0f);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//render the scene with all its children
	renderEntity(scene, im);

	// Swap buffers
	glfwSwapBuffers(this->window());
	glfwPollEvents();
}

void Renderer::renderEntity(Entity* entity, glm::mat4 PaMa)
{
	// Build the Model matrix from Entity transform
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(entity->position));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, entity->rotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(entity->scale.x, entity->scale.y, entity->scale.z));

	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	PaMa *= modelMatrix;

	if (entity->ESprite() != nullptr)
	{
		if(entity->ESprite()->Meshes().size() > 0)
		{
			this->renderNineSlices(entity->ESprite(), PaMa, entity->scale.x, entity->scale.y);
		}
		else
		{
			this->renderSprite(entity->ESprite(), PaMa);
		}
	}
	else if (entity->GetSpriteSheet().size() > 0)
	{
		this->renderSpriteSheet(entity->GetSpriteSheet(), PaMa);
	}
	for (int i = 0; i < entity->Children().size(); i++)
	{
		renderEntity(entity->Children()[i], PaMa);
	}
}

void Renderer::renderSprite(Sprite* sprite, glm::mat4 mm)
{
	// Build MVP matrix
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(sprite->spritePosition[0], sprite->spritePosition[1], 0));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, sprite->spriteRotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sprite->spriteScale[0], sprite->spriteScale[1], 1));
	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	glm::mat4 mdm = mm;
	mdm *= modelMatrix;
	glm::mat4 MVP = _projectionMatrix * _viewMatrix * mdm;

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	sprite = _resMan.GetTexture(sprite->TextureName());
	glBindTexture(GL_TEXTURE_2D, sprite->getTexture());
	Mesh* mesh = _resMan.GetMesh(sprite->width(), sprite->height(), sprite->GetUV().x, sprite->GetUV().y, sprite->pivot);
	// Set our "textureSampler" sampler to use Texture Unit 0
	GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
	glUniform1i(textureID, 0);

	GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
	glUniform2f(uvOffset, sprite->getUVOffset()[0], sprite->getUVOffset()[1]);

	GLuint colorID = glGetUniformLocation(_programID, "blendColor");
	glUniform4f(colorID, sprite->color.r/255, sprite->color.g/255, sprite->color.b/255, 1.0f);

	renderMesh(mesh, MVP);
}

void Renderer::renderSpriteSheet(std::vector<Sprite*> spriteSheet, glm::mat4 mm)
{
	for (int i = 0; i < spriteSheet.size(); i++)
	{
		//std::cout << std::to_string(spriteSheet[i]->getUVOffset()[0]) << " , " << std::to_string(spriteSheet[i]->getUVOffset()[1]) << std::endl;
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		Sprite* s = _resMan.GetTexture(spriteSheet[i]->TextureName(), true, spriteSheet[i]->GetUV()[1], spriteSheet[i]->GetUV()[0]);
		s->SetUpSize(64, 64, s->getTexture());
		//s = nullptr;
		glBindTexture(GL_TEXTURE_2D, s->getTexture()); //size

		Mesh* mesh = _resMan.GetMesh(s->width(), s->height(), s->GetUV().x, s->GetUV().y, s->pivot);

		// Set our "textureSampler" sampler to use Texture Unit 0
		GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
		glUniform1i(textureID, 0);

		GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
		glUniform2f(uvOffset, spriteSheet[i]->getUVOffset()[0], spriteSheet[i]->getUVOffset()[1]);

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(spriteSheet[i]->spritePosition[0], spriteSheet[i]->spritePosition[1], 0));
		glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, spriteSheet[i]->spriteRotation);
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(spriteSheet[i]->spriteScale[0], spriteSheet[i]->spriteScale[1], 1));

		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		glm::mat4 mdm = mm;

		mdm *= modelMatrix;

		glm::mat4 MVP = _projectionMatrix * _viewMatrix * mdm;

		GLuint colorID = glGetUniformLocation(_programID, "blendColor");
		glUniform4f(colorID, spriteSheet[i]->color.r/255, spriteSheet[i]->color.g/255, spriteSheet[i]->color.b/255, 1.0f);

		this->renderMesh(mesh, MVP);
	}
}

void Renderer::renderNineSlices(Sprite* sprite, glm::mat4 mm, float scaleX, float scaleY)
{
	for (int i = 0; i < 9; i++)
	{
		// Build MVP matrix

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		Sprite* s = _resMan.GetTexture(sprite->TextureName());
		glBindTexture(GL_TEXTURE_2D, s->getTexture());
		Mesh* mesh = _resMan.GetMesh(sprite->Meshes()[i]->Width(), sprite->Meshes()[i]->Height(), sprite->Meshes()[i]->GetUV().x, sprite->Meshes()[i]->GetUV().y, sprite->pivot, sprite->Meshes()[i]->GetUVOffset(), sprite->Meshes()[i]->Type(), sprite->Meshes()[i]->Corner());
		// Set our "textureSampler" sampler to use Texture Unit 0
		GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
		glUniform1i(textureID, 0);

		GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
		glUniform2f(uvOffset, sprite->Meshes()[i]->GetUVOffset()[0], sprite->Meshes()[i]->GetUVOffset()[1]);
		// std::cout << std::to_string(sprite->Meshes()[i]->GetUVOffset()[0]) << " , " << std::to_string(sprite->Meshes()[i]->GetUVOffset()[1]) << std::endl;

		GLuint colorID = glGetUniformLocation(_programID, "blendColor");
		glUniform4f(colorID, sprite->color.r/255, sprite->color.g/255, sprite->color.b/255, 1.0f);

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(sprite->spritePosition[0], sprite->spritePosition[1], 0));
		glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, sprite->spriteRotation);
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sprite->spriteScale[0], sprite->spriteScale[1], 1));

		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		glm::mat4 mdm = mm;

		mdm *= modelMatrix;

		glm::mat4 MVP = _projectionMatrix * _viewMatrix * mdm;

		float x = 0.0f;
		float y = 0.0f;
		switch (i)
		{
		case 0:
			break;
		case 1:
			x = -(((sprite->Meshes()[0]->Width())/2) + ((sprite->Meshes()[i]->Width() / 2) / scaleX));
			break;
		case 2:
			x = ((sprite->Meshes()[0]->Width())/2) + ((sprite->Meshes()[i]->Width() / 2) / scaleX);
			break;
		case 3:
			y = -(((sprite->Meshes()[0]->Height())/2) + ((sprite->Meshes()[i]->Height() / 2) / scaleY));
			break;
		case 4:
			y = ((sprite->Meshes()[0]->Height())/2) + ((sprite->Meshes()[i]->Height() / 2) / scaleY);
			break;
		case 5:
			x = -(((sprite->Meshes()[0]->Width())/2) + ((sprite->Meshes()[i]->Width() / 2) / scaleX));
			y = -(((sprite->Meshes()[0]->Height())/2) + ((sprite->Meshes()[i]->Height() / 2) / scaleY));
			break;
		case 6:
			x = ((sprite->Meshes()[0]->Width())/2) + ((sprite->Meshes()[i]->Width() / 2) / scaleX);
			y = -(((sprite->Meshes()[0]->Height())/2) + ((sprite->Meshes()[i]->Height() / 2) / scaleY));
			break;
		case 7:
			x = -(((sprite->Meshes()[0]->Width())/2) + ((sprite->Meshes()[i]->Width() / 2) / scaleX));
			y = ((sprite->Meshes()[0]->Height())/2) + ((sprite->Meshes()[i]->Height() / 2) / scaleY);
			break;
		case 8:
			x = ((sprite->Meshes()[0]->Width())/2) + ((sprite->Meshes()[i]->Width() / 2) / scaleX);
			y = ((sprite->Meshes()[0]->Height())/2) + ((sprite->Meshes()[i]->Height() / 2) / scaleY);
			break;
		default:
			break;
		}

		renderMesh(mesh, MVP, scaleX, scaleY, x, y);
		// renderMesh(mesh, MVP, scaleX, scaleY, sprite->Meshes()[i]->meshPos.x, sprite->Meshes()[i]->meshPos.y);
	}
	
}

void Renderer::renderMesh(Mesh* m, glm::mat4 mm, float scaleX, float scaleY, float x, float y)
{
	glm::mat4 mdm = mm;
	if(m->IsNineSlice())
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
		glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, 0.0f);
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		if(m->Corner())
		{
			scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f/scaleX, 1.0f/scaleY, 1));
		}
		else
		{
			switch (m->Type())
			{
				case 0:
					// std::cout << "middle" << std::endl;
					break;
				case 1:
					// std::cout << "edgeX" << std::endl;
					scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f/scaleX, 1.0f, 1));
					break;
				case 2:
					// std::cout << "edgeY" << std::endl;
					scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f/scaleY, 1));
					break;
				default:
					std::cout << "Error: Mesh type not found" << std::endl;
					break;
			}
		}
		
		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
		mdm *= modelMatrix;
	}

	GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mdm[0][0]);

	// 1st attribute buffer : vertices
	GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, m->vertexbuffer());
	glVertexAttribPointer(
		vertexPositionID, // The attribute we want to configure
		3,          // size : x,y,z => 3
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// 2nd attribute buffer : UVs
	GLuint vertexUVID = glGetAttribLocation(_programID, "vertexUV");
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, m->uvbuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U,V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2*3 indices starting at 0 -> 2 triangles

	// cleanup
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

GLuint Renderer::loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path.c_str(), std::ios::in);
	if (vertexShaderStream.is_open()){
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	} else {
		printf("Can't to open %s.\n", vertex_file_path.c_str());
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path.c_str(), std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	} else {
		printf("Can't to open %s.\n", fragment_file_path.c_str());
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path.c_str());
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path.c_str());
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
