#ifndef GAME_H 
#define GAME_H

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <common/config.h>
#include <common/renderer.h>
#include <common/camera.h>

class Game 
{ 
public: 
    Game(); 
    virtual ~Game();

	void Run(Scene* scene);

	bool IsRunning() { return running; }

private:
	Renderer renderer;
	bool running;
}; 

#endif // game_H 
