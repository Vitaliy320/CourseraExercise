#include "Solver.h"
#include "Position.h"

Solver::Solver(int numberOfStacks, int startingStackIndex, int targetStackIndex, Position &position) {
	this->numberOfStacks = numberOfStacks;
	this->startingStackIndex = startingStackIndex;
	this->targetStackIndex = targetStackIndex;
	this->startingPosition = position;
	this->currentPosition = position;
	this->positionsTree = &this->startingPosition;
}

bool Solver::compareVectors_(std::vector<Cube> vector1, std::vector<Cube> vector2) {
	if (vector1.size() != vector2.size() || vector1.size() == 0 || vector2.size() == 0) {
		return false;
	}

	for (int i = 0; i < vector1.size(); i++) {
		if (!vector1[i].compareWithCube(vector2[i])) {
			return false;
		}
	}
	return true;
}

std::vector<Stack> Solver::getRemainingStacks(std::vector<Stack> stacksToFilter, Stack stackToExclude) {
	std::vector<Stack> possibleStacks;

	for (Stack stack : stacksToFilter) {
		if (stack.index != stackToExclude.index) {
			possibleStacks.push_back(stack);
		}
	}
	return possibleStacks;
}

Position* Solver::getPossiblePositions(Position* currentPosition) {
	std::vector<Stack> possibleStacks;
	Stack remainingStack, initialStack;
	Position* position;
	Position* test;
	Cube currentCube;
	for (Stack stack : currentPosition->getPosition()) {
		if (stack.getCubes().size() > 0) {
			possibleStacks = getRemainingStacks(currentPosition->getPosition(), stack);

			for (Stack possibleStack : possibleStacks) {
				initialStack = stack;
				if (possibleStack.getCubes().size() == 0 || possibleStack.getCubes().back().size > initialStack.getCubes().back().size) {
					currentCube = initialStack.popBack();
					possibleStack.pushBack(currentCube);
					remainingStack = getRemainingStacks(possibleStacks, possibleStack).back();
					std::vector<Stack> currentStacks = { initialStack, possibleStack, remainingStack };
					position = new Position(currentStacks);
					position->setParentPointer(currentPosition);
					currentPosition->setChildPointers(position);
				}
			}
		}
	}
	return currentPosition;
}
