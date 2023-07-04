#include <common/game.h>

#include "BattleScene.h"

int main( void )
{
	Game game;
	BattleScene* scene = new BattleScene();

	do 
	{
		game.Run(scene);
	} 
	// Check if the ESC key was pressed or the window was closed
	while( game.IsRunning() );

	delete scene;

	return 0;
}