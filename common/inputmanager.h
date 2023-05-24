#ifndef INPUTMANAGER_H 
#define INPUTMANAGER_H 

#include <GLFW/glfw3.h>

#include <map>

#include <iostream>

class InputManager 
{ 
public: 

    virtual ~InputManager();
	static InputManager* input();

	void update(GLFWwindow* w);

	bool getKey(int k);

	bool getKeyDown(int k);

	bool getKeyUp(int k);

private:
	InputManager();
	static InputManager* _instance;
	GLFWwindow* _window;

	void registerKey(int key, GLFWwindow* w);

	std::map<int, bool> _keys;
	std::map<int, bool> _keysDown;
	std::map<int, bool> _keysUp;
}; 
#endif // InputManager_H 
