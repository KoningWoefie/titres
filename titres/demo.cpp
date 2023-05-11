#include <common/game.h>

#include "MyScene.h"

int main( void )
{
	Game game;
	MyScene* scene = new MyScene();

	do 
	{
		game.Run(scene);
	} 
	// Check if the ESC key was pressed or the window was closed
	while( game.IsRunning() );

	delete scene;

	return 0;
}
