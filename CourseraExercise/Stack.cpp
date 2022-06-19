#include "Stack.h"
#include <iostream>
using namespace std;

Stack::Stack(){}

Stack::Stack(int i) {
	index = i;
}

void Stack::pushBack(Cube& cube) {
	//cube.size = 0;
	cubes_.push_back(cube);
}

void Stack::pushBackPointer(Cube* cube) {
	cubesPointers.push_back(cube);
	(*cube).size = 0;
}

std::vector<Cube> Stack::getCubes() {
	return cubes_;
}

Cube &Stack::popBack() {
	Cube topCube = cubes_.back();
	cubes_.pop_back();
	return topCube;
}

