#pragma once
#include <vector>
#include "Stack.h"
#include <iostream>

class Position {
public:
	Position();
	Position(std::vector<Stack> &position);

	void getParentNode();
	void addNode(Position* position);
	void setPosition(std::vector<Stack> position);
	std::vector<Stack> getPosition();
	Position* getParentPointer();
	std::vector<Position*> getChildPointers();
	void setParentPointer(Position* parent);
	void setChildPointers(Position* child);
	bool isFinal;
	int index;

private:
	Position* parentPointer_;
	std::vector<Position*> childPointers_;
	std::vector<Stack> position_;
};