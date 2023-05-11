#include "game.h" 
Game::Game() 
{

} 
Game::~Game() 
{ 
}

void Game::Run(Scene* scene)
{
	// get deltaTime and update camera
	float dt = renderer.updateDeltaTime();
	scene->camera()->computeViewMatrixFromInput(renderer.window(), dt);

	// Update the scene
	scene->update(dt); //(and make Scene abstract?)

	// Render the scene
	renderer.renderScene(scene);

	if (glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window()) == 0)
	{
		running = true;
	}
	else
	{
		running = false;
	}
}
