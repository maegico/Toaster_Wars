#include <string>
#include <iostream>
#pragma once

using namespace std;

class StateManager
{
public:


	StateManager();
	~StateManager();

	enum State{ MainMenu, GameScreen, PauseScreen, GameOver };
	// Mutator
	void StateManager::setState(State state){ currentState = state;}

	// Getter
	State getState(){ return currentState;}

	void loadState();

private:
	State currentState;
};





