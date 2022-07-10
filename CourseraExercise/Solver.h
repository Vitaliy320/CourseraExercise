#pragma once
#include "Stack.h"
#include "Cube.h"
#include "Position.h"
#include <string>
#include "knownPosition.h"

class Solver {
public:
	Position* positionsTree;
	int numberOfStacks, startingStackIndex, targetStackIndex, numberOfCubes, minBranchLength;
	Position startingPosition, currentPosition;
	
	Solver(int numberOfStacks, int startingStackIndex, int targetStackIndex, int numberOfCubes, Position &position);

	Position* getTree();
	Position* getPossiblePositions(Position* currentPosition, int* index);
	Stack getStackByIndexValue(std::vector<Stack> stacks, int index);

	bool positionInVectorOfPositions(Position * position);
	bool equalPositions(Position position1, Position position2);

	int getBranchLength(Position* position);

	void removeBranchUpToRoot(Position* position);

	std::vector<KnownPosition> knownPositions;

	bool currentPositionHasLongerBranchLength(Position* position, KnownPosition* knownPosition);

	void printBranch(Position* position);

	std::vector<Position*> finalPositions;

private:
	std::vector<Stack> getRemainingStacks(std::vector<Stack> stacksToFilter, Stack stackToExclude);
	bool compareVectorsOfCubes_(std::vector<Cube> vector1, std::vector<Cube> vector2);
	bool stackInVectorOfStacks_(std::vector<Stack> knownStacks, Stack positionStack);
	void printInfo_(Position currentPosition);
};