#include "Position.h"

Position::Position() {}

Position::Position(std::vector<Stack>& position) {
	position_ = position;
	parentPointer_ = nullptr;
	//childPointers_ = std::vector<Position*>;
	is_final = false;
}

void Position::setPosition(std::vector<Stack> position) {
	position_ = position;
}

std::vector<Stack> Position::getPosition() {
	return position_;
}

Position* Position::getParentPointer() {
	return parentPointer_;
}

std::vector<Position*> Position::getChildPointers() {
	return childPointers_;
}

void Position::setParentPointer(Position* parent) {
	parentPointer_ = parent;
}

void Position::setChildPointers(Position* child) {
	childPointers_.push_back(child);
}

void Position::addNode(Position* position) {
	Position* node = this;
	/*while (node->getChildPointers() != nullptr) {
		node = node->getChildPointers();
	}
	position->setParentPointer(node);
	node->setChildPointers(position);*/
}