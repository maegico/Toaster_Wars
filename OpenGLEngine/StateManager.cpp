#include "StateManager.h"


StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}


void StateManager::loadState(){
	// Uses switch statement to check currentState then act according
	switch (currentState)
	{
	case MainMenu:
		break;
	case GameScreen:
		break;
	case PauseScreen:
		break;
	case GameOver:
		break;
	default:
		cout << "Not in any state. Something broke.";
		break;
	}
}
