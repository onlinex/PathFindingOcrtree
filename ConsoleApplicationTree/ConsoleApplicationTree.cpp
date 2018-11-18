// ConsoleApplicationTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "window.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <SDL.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class point {
public:
	float x;
	float y;
	float z;
	point(int x, int y, int z) :x((float)x), y((float)y), z((float)z) {

	}
};

class pointCloud {
private:
	int length = 0;
	const int* size = new const int(100);
	point** cloud = new point*[*size];
public:
	void append(point* p) {
		if (length+1 > *size) {
			resize();
		}
		cloud[length] = p;
		length++;
	}
	void remove() {
		if (length > 0) {
			length--;
		}
	}
	int getLength() {
		return length;
	}
	point* getElement(int n) {
		return cloud[n];
	}
private:
	void resize() {
		delete size;
		size = new const int(length+(int)(length/2));
		point** newcloud = new point*[*size];
		for (int i = 0; i < length; i++) {
			newcloud[i] = cloud[i];
		}
		delete cloud;
		cloud = newcloud;
	}
};

class node {
public:
	float x, y, z;
	node* first = nullptr;
	node* second = nullptr;
	node* third = nullptr;
	node* forth = nullptr;
	node* fifth = nullptr;
	node* sixth = nullptr;
	node* seventh = nullptr;
	node* eighth = nullptr;

	node* parent = nullptr;

	pointCloud* pc = new pointCloud;

	float g = 0;
	float h = 0;
	float f = 0;
	node* previous = nullptr;

	node(int level, float x, float y, float z, node* parent = NULL):level(level), x(x), y(y), z(z), parent(parent) {
		size = (int) 512 / (int)(pow(2, level));
	}
	int getLevel() {
		return level;
	}
	int getSize() {
		return size;
	}
private:
	int level;
	int size;


	int length = 0;
	const int* scale = new const int(10);
	node** nCloud = new node*[*scale];
	void resize() {
		delete scale;
		scale = new const int(length + (int)(length / 2));
		node** newcloud = new node*[*scale];
		for (int i = 0; i < length; i++) {
			newcloud[i] = nCloud[i];
		}
		delete nCloud;
		nCloud = newcloud;
	}
public:
	void addConnection(node* p) {
		if (length + 1 > *scale) {
			resize();
		}
		nCloud[length] = p;
		length++;
	}
	void removeConnection(node* p) {
		for (int i = 0; i < length; i++) {
			if (nCloud[i] == p) {
				for (int ix = i; ix < length - 1; ix++) {
					nCloud[ix] = nCloud[ix + 1];
				}
				length--;
				break;
			}
		}
	}
	void rearrangeConnections() {
		for (int i = 0; i < parent->length; i++) {
			if (((size + parent->nCloud[i]->size == abs(x - parent->nCloud[i]->x)) && (abs(y - parent->nCloud[i]->y) <= parent->nCloud[i]->size) && (abs(z - parent->nCloud[i]->z) <= parent->nCloud[i]->size)) ||
			   ((size + parent->nCloud[i]->size == abs(y - parent->nCloud[i]->y)) && (abs(x - parent->nCloud[i]->x) <= parent->nCloud[i]->size) && (abs(z - parent->nCloud[i]->z) <= parent->nCloud[i]->size)) ||
				((size + parent->nCloud[i]->size == abs(z - parent->nCloud[i]->z)) && (abs(x - parent->nCloud[i]->x) <= parent->nCloud[i]->size) && (abs(y - parent->nCloud[i]->y) <= parent->nCloud[i]->size))) {

				addConnection(parent->nCloud[i]);
				parent->nCloud[i]->addConnection(this);

			}
		}
	}

	int getLength() {
		return length;
	}
	node* getElement(int n) {
		return nCloud[n];
	}

	~node() {
		for (int i = 0; i < length; i++) {
			nCloud[i]->removeConnection(this);
		}
	}
};

bool coordInNode(node* pointer, float x, float y, float z) {
	return abs(pointer->x - x) <= pointer->getSize() && abs(pointer->y - y) <= pointer->getSize() && abs(pointer->z - z) <= pointer->getSize();
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

class manager {
public:
	int maxDepth;
	node* root = new node(0, 0.0, 0.0, 0.0);
	float t_size;
	manager(int depth):maxDepth(depth) {

	}

	void addConnection(node* n1, node* n2) {
		n1->addConnection(n2);
		n2->addConnection(n1);
	}

	void removeConnection(node* n1, node* n2) {
		n1->removeConnection(n2);
		n2->removeConnection(n1);
	}

	void split(node* pointer, int level) {
		level++;
		t_size = (float) 512.0 / (float)(pow(2, level));

		pointer->first = new node(level, pointer->x + t_size, pointer->y + t_size, pointer->z + t_size, pointer);
		pointer->second = new node(level, pointer->x - t_size, pointer->y + t_size, pointer->z + t_size, pointer);
		pointer->third = new node(level, pointer->x - t_size, pointer->y - t_size, pointer->z + t_size, pointer);
		pointer->forth = new node(level, pointer->x + t_size, pointer->y - t_size, pointer->z + t_size, pointer);
		/////////
		pointer->fifth = new node(level, pointer->x + t_size, pointer->y + t_size, pointer->z - t_size, pointer);
		pointer->sixth = new node(level, pointer->x - t_size, pointer->y + t_size, pointer->z - t_size, pointer);
		pointer->seventh = new node(level, pointer->x - t_size, pointer->y - t_size, pointer->z - t_size, pointer);
		pointer->eighth = new node(level, pointer->x + t_size, pointer->y - t_size, pointer->z - t_size, pointer);

		addConnection(pointer->first, pointer->second);
		addConnection(pointer->second, pointer->third);
		addConnection(pointer->third, pointer->forth);
		addConnection(pointer->forth, pointer->first);
		//////////
		addConnection(pointer->fifth, pointer->sixth);
		addConnection(pointer->sixth, pointer->seventh);
		addConnection(pointer->seventh, pointer->eighth);
		addConnection(pointer->eighth, pointer->fifth);

		addConnection(pointer->first, pointer->fifth);
		addConnection(pointer->second, pointer->sixth);
		addConnection(pointer->third, pointer->seventh);
		addConnection(pointer->forth, pointer->eighth);

		if (pointer->parent != nullptr) {
			pointer->first->rearrangeConnections();
			pointer->second->rearrangeConnections();
			pointer->third->rearrangeConnections();
			pointer->forth->rearrangeConnections();
			////////
			pointer->fifth->rearrangeConnections();
			pointer->sixth->rearrangeConnections();
			pointer->seventh->rearrangeConnections();
			pointer->eighth->rearrangeConnections();
		}
		
		for (int i = 0; i < pointer->pc->getLength(); i++) {
			point* p = pointer->pc->getElement(i);


			if (coordInNode(pointer->first, p->x, p->y, p->z)) {
				addpoint(pointer->first, p);
			}
			else if (coordInNode(pointer->second, p->x, p->y, p->z)) {
				addpoint(pointer->second, p);
			}
			else if (coordInNode(pointer->third, p->x, p->y, p->z)) {
				addpoint(pointer->third, p);
			}
			else if (coordInNode(pointer->forth, p->x, p->y, p->z)) {
				addpoint(pointer->forth, p);
			}
			//////////////
			else if (coordInNode(pointer->fifth, p->x, p->y, p->z)) {
				addpoint(pointer->fifth, p);
			}
			else if (coordInNode(pointer->sixth, p->x, p->y, p->z)) {
				addpoint(pointer->sixth, p);
			}
			else if (coordInNode(pointer->seventh, p->x, p->y, p->z)) {
				addpoint(pointer->seventh, p);
			}
			else if (coordInNode(pointer->eighth, p->x, p->y, p->z)) {
				addpoint(pointer->eighth, p);
			}
		}


	}

	void addpoint(node* pointer, point* p) {
		if (pointer->first == nullptr && pointer->getLevel() < maxDepth) {
			split(pointer, pointer->getLevel());
		}
		if (pointer->first != nullptr) {
			if (coordInNode(pointer->first, p->x, p->y, p->z)) {
				addpoint(pointer->first, p);
			}
			else if (coordInNode(pointer->second, p->x, p->y, p->z)) {
				addpoint(pointer->second, p);
			}
			else if (coordInNode(pointer->third, p->x, p->y, p->z)) {
				addpoint(pointer->third, p);
			}
			else if (coordInNode(pointer->forth, p->x, p->y, p->z)) {
				addpoint(pointer->forth, p);
			}
			//////////////
			else if (coordInNode(pointer->fifth, p->x, p->y, p->z)) {
				addpoint(pointer->fifth, p);
			}
			else if (coordInNode(pointer->sixth, p->x, p->y, p->z)) {
				addpoint(pointer->sixth, p);
			}
			else if (coordInNode(pointer->seventh, p->x, p->y, p->z)) {
				addpoint(pointer->seventh, p);
			}
			else if (coordInNode(pointer->eighth, p->x, p->y, p->z)) {
				addpoint(pointer->eighth, p);
			}
		}
		else {
			pointer->pc->append(p);
		}

	}

	void unite(node* pointer) {
		if (pointer != nullptr) { // parent is not nullptr
			if (pointer->first->pc->getLength() + pointer->second->pc->getLength() + pointer->third->pc->getLength() + pointer->forth->pc->getLength() +
				pointer->fifth->pc->getLength() + pointer->sixth->pc->getLength() + pointer->seventh->pc->getLength() + pointer->eighth->pc->getLength() == 0) {
				if (pointer->first->first == nullptr && pointer->second->first == nullptr && pointer->third->first == nullptr && pointer->forth->first == nullptr &&
					pointer->fifth->first == nullptr && pointer->sixth->first == nullptr && pointer->seventh->first == nullptr && pointer->eighth->first == nullptr) {
					delete pointer->first;
					delete pointer->second;
					delete pointer->third;
					delete pointer->forth;
					//////////////
					delete pointer->fifth;
					delete pointer->sixth;
					delete pointer->seventh;
					delete pointer->eighth;
					pointer->first = nullptr; pointer->second = nullptr; pointer->third = nullptr; pointer->forth = nullptr;
					pointer->fifth = nullptr; pointer->sixth = nullptr; pointer->seventh = nullptr; pointer->eighth = nullptr;
				}

				unite(pointer->parent);
			}
		}
	}

	void removePoint(node* pointer, point* p) {
		if (pointer->first == nullptr) {
			pointer->pc->remove();
			unite(pointer->parent);
		}
		else {
			if (coordInNode(pointer->first, p->x, p->y, p->z)) {
				removePoint(pointer->first, p);
			}
			else if (coordInNode(pointer->second, p->x, p->y, p->z)) {
				removePoint(pointer->second, p);
			}
			else if (coordInNode(pointer->third, p->x, p->y, p->z)) {
				removePoint(pointer->third, p);
			}
			else if (coordInNode(pointer->forth, p->x, p->y, p->z)) {
				removePoint(pointer->forth, p);
			}
			//////////////
			else if (coordInNode(pointer->fifth, p->x, p->y, p->z)) {
				removePoint(pointer->fifth, p);
			}
			else if (coordInNode(pointer->sixth, p->x, p->y, p->z)) {
				removePoint(pointer->sixth, p);
			}
			else if (coordInNode(pointer->seventh, p->x, p->y, p->z)) {
				removePoint(pointer->seventh, p);
			}
			else if (coordInNode(pointer->eighth, p->x, p->y, p->z)) {
				removePoint(pointer->eighth, p);
			}
		}
	}

};

node* findClosest(node* pointer, float x, float y, float z) {
	
	if (pointer->first == nullptr) {
		return pointer;
	}
	else {
		if (coordInNode(pointer->first, x, y, z)) {
			findClosest(pointer->first, x, y, z);
		}
		else if (coordInNode(pointer->second, x, y, z)) {
			findClosest(pointer->second, x, y, z);
		}
		else if (coordInNode(pointer->third, x, y, z)) {
			findClosest(pointer->third, x, y, z);
		}
		else if (coordInNode(pointer->forth, x, y, z)) {
			findClosest(pointer->forth, x, y, z);
		}
		//////////////
		else if (coordInNode(pointer->fifth, x, y, z)) {
			findClosest(pointer->fifth, x, y, z);
		}
		else if (coordInNode(pointer->sixth, x, y, z)) {
			findClosest(pointer->sixth, x, y, z);
		}
		else if (coordInNode(pointer->seventh, x, y, z)) {
			findClosest(pointer->seventh, x, y, z);
		}
		else if (coordInNode(pointer->eighth, x, y, z)) {
			findClosest(pointer->eighth, x, y, z);
		}
		else {
			return pointer;
		}
	}
}

class AStar {
public:
	node* root;
	int sizeSearch;
	int depth;
	int minsize;


	AStar(node* root, int depth, int minsize):root(root), depth(depth), minsize(minsize) {
		sizeSearch = (int)512 / (int)(pow(2, depth-minsize));
	}

	int openset_length = 0;
	int closedset_length = 0;
	const int* openset_scale = new const int(10);
	const int* closedset_scale = new const int(10);
	node** openset = new node*[*openset_scale];
	node** closedset = new node*[*closedset_scale];

	int pathset_length = 0;
	const int* pathset_scale = new const int(100);
	node** pathset = new node*[*pathset_scale];

	void refreshGValues() {
		for (int i = 0; i < closedset_length; i++) {
			closedset[i]->g = 0;
			closedset[i]->h = 0;
			closedset[i]->f = 0;
			closedset[i]->previous = nullptr;
		}
		closedset_length = 0;
		resizeClosedSet();
		for (int i = 0; i < openset_length; i++) {
			openset[i]->g = 0;
			openset[i]->h = 0;
			openset[i]->f = 0;
			openset[i]->previous = nullptr;
		}
		openset_length = 0;
		resizeOpenSet();
	}

	void setStartPoint(float start_x, float start_y, float start_z, float in_end_x, float in_end_y, float in_end_z) {
		endNode = findClosest(root, in_end_x, in_end_y, in_end_z);
		end_x = endNode->x;
		end_y = endNode->y;
		end_z = endNode->z;
		refreshGValues();
		addElement(&openset_scale, &openset_length, findClosest(root, start_x, start_y, start_z), openset);
		pathset_length = 0;
		resizePathSet();
	}

	int search() {
		if (openset_length > 0) {
			lowestIndEl = openset[0];
			for (int i = 0; i < openset_length; i++) {
				if (openset[i]->f < lowestIndEl->f) {
					lowestIndEl = openset[i];
				}
			}

			if (distance(lowestIndEl->x, lowestIndEl->y, lowestIndEl->z, end_x, end_y, end_z) <= 1) {

				if (pathset_length != 0) {
					return 1;
				}

				tempLowestIndEl = lowestIndEl;
				addElement(&pathset_scale, &pathset_length, tempLowestIndEl, pathset);
				while (tempLowestIndEl->previous != nullptr) {
					tempLowestIndEl = tempLowestIndEl->previous;
					addElement(&pathset_scale, &pathset_length, tempLowestIndEl, pathset);
				}
				cout << "path found! length:" << pathset_length << endl;
				cout << "Time: " << tempTime << ", inter: " << tempIter << endl;
				tempTime = 0; tempIter = 0;
				return 1;

			}

			clock_t pStart = clock();

			removeElement(lowestIndEl, &openset_length, openset);
			addElement(&closedset_scale, &closedset_length, lowestIndEl, closedset);


			for (int ix = 0; ix < lowestIndEl->getLength(); ix++) {
				if (lowestIndEl->getElement(ix)->first == nullptr && lowestIndEl->getElement(ix)->pc->getLength() == 0 && lowestIndEl->getElement(ix)->getSize()>= sizeSearch) {
					if (!elementInArray(lowestIndEl->getElement(ix), &closedset_length, closedset)) {
						temp_g = lowestIndEl->g + distance(lowestIndEl->getElement(ix)->x, lowestIndEl->getElement(ix)->y, lowestIndEl->getElement(ix)->z, lowestIndEl->x, lowestIndEl->y, lowestIndEl->z);
						temp_g *= (lowestIndEl->getElement(ix)->getLevel() - lowestIndEl->getLevel() + depth)/(2*(depth)); //////////////

						newPath = false;
						if (elementInArray(lowestIndEl->getElement(ix), &openset_length, openset)) {
							if (temp_g < lowestIndEl->getElement(ix)->g) {
								lowestIndEl->getElement(ix)->g = temp_g;
								newPath = true;
							}
						}
						else {
							lowestIndEl->getElement(ix)->g = temp_g;
							addElement(&openset_scale, &openset_length, lowestIndEl->getElement(ix), openset);
							newPath = true;
						}
						if (newPath == true) {
							lowestIndEl->getElement(ix)->h = distance(lowestIndEl->getElement(ix)->x, lowestIndEl->getElement(ix)->y, lowestIndEl->getElement(ix)->z, end_x, end_y, end_z);
							lowestIndEl->getElement(ix)->f = lowestIndEl->getElement(ix)->g + lowestIndEl->getElement(ix)->h;
							lowestIndEl->getElement(ix)->previous = lowestIndEl;
						}

					}

				}
			}
			tempTime += (long double)(clock() - pStart) / CLOCKS_PER_SEC;
			tempIter += 1;

			//search();
			return 2;

		}
		else {
			cout << "no solution" << endl;
			tempTime = 0; tempIter = 0;
			return 0;
		}
	}

	bool getEndNode() {
		if (endNode == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

private:
	int temp_g = 0;
	bool newPath = false;
	node* lowestIndEl;

	long double tempTime = 0;
	int tempIter = 0;

	node* tempLowestIndEl;

	float end_x;
	float end_y;
	float end_z;
	node* endNode = nullptr;

	void removeElement(node* p, int* in_length, node** arr) {
		for (int i = 0; i < *in_length; i++) {
			if (arr[i] == p) {
				for (int ix = i; ix < *in_length - 1; ix++) {
					arr[ix] = arr[ix + 1];
				}
				*in_length = *in_length - 1;
				break;
			}
		}
	}

	void resizeOpenSet() {
		delete openset_scale;
		openset_scale = new const int(100 + openset_length + (int)(openset_length / 2));

		node** newarr = new node*[*openset_scale];
		for (int i = 0; i < openset_length; i++) {
			newarr[i] = openset[i];
		}
		delete openset;
		openset = newarr;
	}

	void resizeClosedSet() {
		delete closedset_scale;
		closedset_scale = new const int(100 + closedset_length + (int)(closedset_length / 2));

		node** newarr = new node*[*closedset_scale];
		for (int i = 0; i < closedset_length; i++) {
			newarr[i] = closedset[i];
		}
		delete closedset;
		closedset = newarr;
	}

	void resizePathSet() {
		delete pathset_scale;
		pathset_scale = new const int(100 + pathset_length + (int)(pathset_length / 2));

		node** newarr = new node*[*pathset_scale];
		for (int i = 0; i < pathset_length; i++) {
			newarr[i] = pathset[i];
		}
		delete pathset;
		pathset = newarr;
	}


	void addElement(const int** scale, int* in_length, node* el, node** arr) {
		arr[*in_length] = el;
		*in_length = *in_length + 1;
		if (*in_length + 1 > **scale) {
			if (arr == openset) {
				resizeOpenSet();
			}
			else if (arr == closedset) {
				resizeClosedSet();
			}
			else if (arr == pathset) {
				resizePathSet();
			}
		}
	}

	bool elementInArray(node* el, int* in_length, node** arr) {
		for (int i = 0; i < *in_length; i++) {
			if (arr[i] == el) {
				return true;
				break;
			}
		}
		return false;
	}
};

void drawTree(window* window, node* root) {

	int px = (int) root->x;
	int py = (int) root->y;

	if (root->first != nullptr) {
		drawTree(window, root->first);
		drawTree(window, root->second);
		drawTree(window, root->third);
		drawTree(window, root->forth);
		////////
		drawTree(window, root->fifth);
		drawTree(window, root->sixth);
		drawTree(window, root->seventh);
		drawTree(window, root->eighth);

		//window->DrawPoint(px + 512, py + 512, root->getSize(), root->pc->getLength());
	}
	else {
		window->DrawPoint(px + 512, py + 512, root->getSize(), root->pc->getLength());
	}
}

void drawPath(window* window, AStar* a) {
	/*for (int i = 0; i < a->openset_length; i++) {
		for (int ix = 0; ix < a->openset[i]->getLength(); ix++) {
			window->DrawPathPoint(a->openset[i]->getElement(ix)->x + 512, a->openset[i]->getElement(ix)->y + 512, 3);
		}
	}
	for (int i = 0; i < a->openset_length; i++) {
		window->DrawPathPoint(a->openset[i]->x + 512, a->openset[i]->y + 512, 1);
	}
	for (int i = 0; i < a->closedset_length; i++) {
		window->DrawPathPoint(a->closedset [i]->x + 512, a->closedset[i]->y + 512, 2);
	}*/
	for (int i = 0; i < a->pathset_length; i++) {
		window->DrawPathPoint(a->pathset[i]->x + 512, a->pathset[i]->y + 512, 0, a->pathset[i]->z);
	}
}

long double addRandomPoints(manager* manager, int n) {
	long double timeTaken = 0;
	for (int i = 0; i < n; i++) {
		int min = -256;
		int max = 256;
		try {
			srand(clock()*i*i);
			int x = (min + (rand() % (int)(max - min + 1)));
			srand(clock()*i);
			int y = (min + (rand() % (int)(max - min + 1)));
			srand(clock());
			int z = (min + (rand() % (int)(max - min + 1)));

			clock_t eStart = clock();
			point* p = new point(x, y, z);
			manager->addpoint(manager->root, p);
			timeTaken +=(long double)(clock() - eStart) / CLOCKS_PER_SEC;
		}
		catch(...) {
			cout << "we have a problem here!" << endl;
		}
	}
	return timeTaken;
}


int main(int argc, char** argv)
{
	int ret = 0;

	manager m(10);
	AStar A(m.root, 10, 3);

	window window("SDL", 1024, 1024);

	string returnString;
	while (!window.isClosed()) {
		returnString = window.pollEvents();
		if (returnString == "a") {
			//point* p = new point(window.mouse.x-512, -window.mouse.y+512, 10);
			//clock_t tStart = clock();
			//m.addpoint(m.root, p);
			
			cout << addRandomPoints(&m, 300) << endl;
			//cout << "Time taken: " << (long double)(clock() - tStart) / CLOCKS_PER_SEC << endl;
		}
		else if (returnString == "d") {
			point* p = new point(window.mouse.x - 512, -window.mouse.y+512, 1);
			m.removePoint(m.root, p);
		}
		else if (returnString == "s") {
			A.setStartPoint((float)(window.mouse.x - 512), (float)(-window.mouse.y+512), 500.0, 500.0, 500.0, -500.0);
		}
		else if (returnString == "f") {
			A.search();
		}
		else if (returnString == "o") {
			point* p = new point(window.mouse.x - 512, -window.mouse.y + 512, 10);
			m.addpoint(m.root, p);
		}
		if (A.getEndNode() == true) {
			do {
				ret = A.search();
			} while (ret == 2);
		}
		window.clear();
		drawTree(&window, m.root);
		drawPath(&window, &A);
		window.present();
	}

	cin.get();
	return 0;
}

