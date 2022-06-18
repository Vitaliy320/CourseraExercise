#pragma once
#include <vector>
#include "Stack.h"

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
	bool is_final;

private:
	Position* parentPointer_;
	std::vector<Position*> childPointers_;
	std::vector<Stack> position_;
};