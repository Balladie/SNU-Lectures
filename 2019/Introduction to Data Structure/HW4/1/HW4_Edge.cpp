#include "HW4_Edge.h"

/* Constructor */

Edge::Edge() : idx(0), src(0), dest(0), dist(0) {}

Edge::Edge(int i, int s, int d, int w) : idx(i), src(s), dest(d), dist(w) {}

/* getter */

int Edge::getIdx() {
	return idx;
}

int Edge::getSrc() {
	return src;
}

int Edge::getDest() {
	return dest;
}

int Edge::getDist() {
	return dist;
}

/* setter */

void Edge::setIdx(int i) {
	idx = i;
}

void Edge::setSrc(int s) {
	src = s;
}

void Edge::setDest(int d) {
	dest = d;
}

void Edge::setDist(int w) {
	dist = w;
}

/* operators */

bool Edge::operator<(const Edge& e) {
	return dist < e.dist;
}

bool Edge::operator>(const Edge& e) {
	return dist > e.dist;
}

Edge& Edge::operator=(const Edge& e) {
	idx = e.idx;
	src = e.src;
	dest = e.dest;
	dist = e.dist;

	return *this;
}

/* functions */

void Edge::print() {
	cout << "[" << idx << "] " << src << " - " << dest << " (" << dist << ")";
}