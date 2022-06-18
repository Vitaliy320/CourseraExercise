#include "Game.h"
#include "Solver.h"


Game::Game(int numberOfStacks, int startingStackIndex, int targetStackIndex, int numberOfCubes) {
	this->startingStackIndex = startingStackIndex;
	this->targetStackIndex = targetStackIndex;
	this->numberOfCubes = numberOfCubes;
	this->numberOfStacks = numberOfStacks;
	for (int i = 0; i < numberOfStacks; i++) {
		Stack stack = Stack(i);
		stacks.push_back(stack);
		Stack stackPointers = Stack(i);
		stacksPointers.push_back(stackPointers);
	}
}

void Game::initialiseCubes() {
	for (int i = numberOfCubes; i > 0; i--) {
		Cube cube = Cube(i);
		stacks[startingStackIndex].pushBack(cube);
		Cube* cubePointer = new Cube(i);
		stacksPointers[startingStackIndex].pushBackPointer(cubePointer);
		delete cubePointer;
		stacksPointers[startingStackIndex].cubesPointers.back()->size = 1;
	}

	Position startingPosition = Position(stacks);
	Position* positionsTree = &startingPosition;
	Solver solver = Solver(numberOfStacks, startingStackIndex, targetStackIndex, startingPosition);
	//solver.positionsTree = &startingPosition;
	positionsTree = solver.getPossiblePositions(positionsTree);
}
