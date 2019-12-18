#include "HW4_Node.h"

/* Constructor */

Node::Node() : idx(0), dist(0) {}

Node::Node(int i, int d) : idx(i), dist(d) {}

/* getter */

int Node::getIdx() {
	return idx;
}

int Node::getDist() {
	return dist;
}

/* setter */

void Node::setIdx(int i) {
	idx = i;
}

void Node::setDist(int d) {
	dist = d;
}

/* operators */

bool Node::operator<(const Node& n) {
	return dist < n.dist;
}

bool Node::operator>(const Node& n) {
	return dist > n.dist;
}

Node& Node::operator=(const Node& n) {
	idx = n.idx;
	dist = n.dist;

	return *this;
}

/* functions */

void Node::print() {
	cout << "[" << idx << "] (" << dist << ")";
}