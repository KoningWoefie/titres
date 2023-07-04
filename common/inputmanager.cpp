#include "inputmanager.h" 

//Copyright 2023 Sander Hoving (Fuck you Gideon)

InputManager::InputManager() 
{
	_window = nullptr;
	std::cout << "creating inputmanager" << std::endl;
} 
InputManager::~InputManager() 
{
}   

void InputManager::update(GLFWwindow* w)
{
	_window = w;

	for (int i = 32; i < 96; i++)
	{
		registerKey(i, w);
	}

	for (unsigned int i = 256; i < GLFW_KEY_LAST; i++)
	{
		registerKey(i, w);
	}
}

bool InputManager::getKey(int k)
{
	return _keys[k];
}
bool InputManager::getKeyDown(int k)
{
	return _keysDown[k];
}
bool InputManager::getKeyUp(int k)
{
	return _keysUp[k];
}

void InputManager::registerKey(int key, GLFWwindow* w)
{
	if (glfwGetKey(w, key) == GLFW_PRESS)
	{
		if (_keys[key] == false)
		{
			_keys[key] = true;
			_keysDown[key] = true;
		}
		else
		{
			_keysDown[key] = false;
		}
	}
	else
	{
		_keys[key] = false;
		_keysDown[key] = false;
		_keysUp[key] = false;
	}
	if (glfwGetKey(w, key) == GLFW_RELEASE)
	{
		if (_keys[key] == true)
		{
			_keys[key] = false;
			_keysUp[key] = true;
		}
		else
		{
			_keysUp[key] = false;
		}
	}
}

InputManager* InputManager::input()
{
	if (InputManager::_instance == nullptr)
	{
		_instance = new InputManager();
	}
	return _instance;
}

InputManager* InputManager::_instance = nullptr;
