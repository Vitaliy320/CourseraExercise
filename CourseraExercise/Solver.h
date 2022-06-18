#pragma once
#include "Stack.h"
#include "Cube.h"
#include "Position.h"

class Solver {
public:
	Position* positionsTree;
	int numberOfStacks, startingStackIndex, targetStackIndex;
	Position startingPosition, currentPosition;
	
	Solver(int numberOfStacks, int startingStackIndex, int targetStackIndex, Position &position);

	Position* getPossiblePositions(Position* currentPosition);

private:
	std::vector<Stack> getRemainingStacks(std::vector<Stack> stacksToFilter, Stack stackToExclude);
	bool compareVectors_(std::vector<Cube> vector1, std::vector<Cube> vector2);
};