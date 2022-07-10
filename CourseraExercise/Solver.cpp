#include "Solver.h"
#include "Position.h"

Solver::Solver(int numberOfStacks, int startingStackIndex, int targetStackIndex, int numberOfCubes, Position &position) {
	this->numberOfStacks = numberOfStacks;
	this->startingStackIndex = startingStackIndex;
	this->targetStackIndex = targetStackIndex;
	this->startingPosition = position;
	this->numberOfCubes = numberOfCubes;
	this->currentPosition = position;
	this->minBranchLength = 0;
}

bool Solver::compareVectorsOfCubes_(std::vector<Cube> vector1, std::vector<Cube> vector2) {
	if (vector1.size() != vector2.size()) {
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

bool Solver::stackInVectorOfStacks_(std::vector<Stack> knownStacks, Stack positionStack) {
	for (Stack knownStack : knownStacks) {
		if (compareVectorsOfCubes_(knownStack.getCubes(), positionStack.getCubes()) && knownStack.index == positionStack.index) {
			return true;
		}
	}
	return false;
}

bool Solver::equalPositions(Position position1, Position position2) {
	std::vector<Stack> stacks1 = position1.getPosition();
	std::vector<Stack> stacks2 = position2.getPosition();
	Stack stack1;
	Stack stack2;
	int equalStacks = 0;

	for (int i = 0; i < numberOfStacks; i++) {
		stack1 = getStackByIndexValue(stacks1, i);
		stack2 = getStackByIndexValue(stacks2, i);
		if (compareVectorsOfCubes_(stack1.getCubes(), stack2.getCubes())) {
			equalStacks++;
		}
	}
	return equalStacks == numberOfStacks;
}

bool Solver::currentPositionHasLongerBranchLength(Position* position, KnownPosition* knownPosition) {
	int currentBranchLength = getBranchLength(position);

	if (position->getParentPointer() == NULL || currentBranchLength > knownPosition->getBranchLength()) {
		return true;
	}

	knownPosition->setBranchLength(currentBranchLength);
	return false;
}

bool Solver::positionInVectorOfPositions(Position * position) {	
	Stack stack0 = getStackByIndexValue(position->getPosition(), 0);
	Stack stack2 = getStackByIndexValue(position->getPosition(), 2);

	for (KnownPosition knownPosition : knownPositions) {
		if (equalPositions(*knownPosition.getPosition(), *position) &&
			currentPositionHasLongerBranchLength(position, &knownPosition)) {
			return true;
		}
	}
	return false;
}

Stack Solver::getStackByIndexValue(std::vector<Stack> stacks, int index) {
	if (stacks.size() > index) {
		for (Stack stack : stacks) {
			if (stack.index == index) {
				return stack;
			}
		}
	}

	return Stack();
}

void Solver::printInfo_(Position currentPosition) {
	std::string stackCubes;
	std::cout << "Position: " << std::to_string(currentPosition.index) << "\n";

	if (currentPosition.getParentPointer() != NULL) {
		std::cout << "Parent position: " << std::to_string(currentPosition.getParentPointer()->index) << "\n";
	}

	for (int i = 0; i < numberOfStacks; i++) {
		Stack stack = getStackByIndexValue(currentPosition.getPosition(), i);
		std::cout << "Stack " << std::to_string(i) << " cubes:\n";

		stackCubes = "";
		for (Cube cube : stack.getCubes()) {
			stackCubes = stackCubes + std::to_string(cube.size) + " ";
		}
		std::cout << stackCubes << "\n";
	}
	std::cout << "\n\n";
}

int Solver::getBranchLength(Position* position) {
	int counter = 0;
	while (position->getParentPointer() != NULL) {
		position = position->getParentPointer();
		counter++;
	}

	return counter;
}

void Solver::removeBranchUpToRoot(Position* position) {
		while (Position * toDelete = position) {
			if (position->getParentPointer() == NULL) {
				break;
			}
			position = position->getParentPointer();
			delete toDelete;
		}
}

void Solver::printBranch(Position* position) {
	while (Position* currentPosition = position) {
		printInfo_(*currentPosition);
		position = position->getParentPointer();
	}
}

Position* Solver::getPossiblePositions(Position* currentPosition, int* index) {
	printInfo_(*currentPosition);

	if (getStackByIndexValue(currentPosition->getPosition(), targetStackIndex).getCubes().size() == numberOfCubes) {
		currentPosition->isFinal = true;
		int currentPositionLength = getBranchLength(currentPosition);
		if (minBranchLength == 0 || currentPositionLength < minBranchLength) {
			minBranchLength = currentPositionLength;
		}
		finalPositions.push_back(currentPosition);
		return currentPosition;
	}

	std::vector<Stack> possibleStacks;
	Stack remainingStack, initialStack;
	Position* position;
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

					*index = *index + 1;
					position->index = *index;

					position->setParentPointer(currentPosition);
					
					if (positionInVectorOfPositions(position) || (getBranchLength(position) > minBranchLength && minBranchLength > 0 && position->isFinal == false)) {
						delete position;
						break;
					}

					currentPosition->setChildPointers(position);

					knownPositions.push_back(KnownPosition(position, getBranchLength(position)));
				}
			}
		}
	}

	for (Position* position : currentPosition->getChildPointers()) {
		currentPosition = this->getPossiblePositions(position, index);
	}
	
	return currentPosition;
}

Position* Solver::getTree() {
	Position* positionsTree = &startingPosition;
	startingPosition.index = 0;
	int* index = new int(0);
	*index = 0;
	Position* currPosition = getPossiblePositions(&startingPosition, index);
	return positionsTree;
}
