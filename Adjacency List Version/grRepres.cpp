// LABKA 2.5 v.2 List methods implementation
#include <iostream>
#include <fstream>
#include <algorithm>

#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\vList.h"
#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\grRepres.h"

GrL::~GrL() {
	_nB = _nMax = 0;
	delete[] A;
	delete[] B;
}

bool GrL::create(size_t _n) {
	_nA = _nB = 0;
	n = _nMax = _n;

	A = new(std::nothrow) size_t[_nMax];
	if (A == nullptr) {
		std::cerr << "FreeMem Problems due to A" << std::endl;
		return false;
	} else
		for (size_t i = 0; i < _nMax; ++i)
			A[i] = INT_MAX;

	B = new(std::nothrow) Node[_nMax];
	if (B == nullptr) {
		std::cerr << "FreeMem Problems due to B" << std::endl;
		return false;
	} else
		for (size_t i = 0; i < _nMax; ++i)
			B[i].v = B[i].next = INT_MAX;
	return true;
}

bool GrL::addArc(size_t i, size_t j) {
	while (true)
		if (_nB + 1 < _nMax) {
			if (A[i] == INT_MAX) { // vertex doesn't exist in A array -> add in A array
				A[i] = _nB; ++_nA;
				B[_nB++].v = j;
				break;
			} else { // vertex exist in A array -> add "new node" to adj list
				B[_nB].v = j;
				B[_nB].next = A[i];
				A[i] = _nB;
				++_nB;
				break;
			}
		} else 
			resizeB();
	if (!(isDir)) {
		while (true)
			if (_nB + 1 < _nMax) {
				if (A[j] == INT_MAX) { // vertex doesn't exist in A array -> add in A array
					A[j] = _nB; ++_nA;
					B[_nB++].v = i;
					break;
				} else { // vertex exist in A array -> add "new node" to adj list
					B[_nB].v = i;
					B[_nB].next = A[j];
					A[j] = _nB;
					++_nB;
					break;
				}
			} else
				resizeB();
	}
	++m;
	return true;
}

VList GrL::neighbors(size_t v) {
	VList L(77);
	size_t seek = A[v];
	if (seek != INT_MAX)
		while(true) {
			L.add(B[seek].v);
			seek = B[seek].next;
			if (seek >= INT_MAX)
				break;
		}
	return L;
}

void GrL::resizeB() {
	_nMax *= 2;
	Node* newB = new Node[_nMax];
	for (size_t i = 0; i < _nB; ++i)
		newB[i] = B[i];
	delete[] B;
	B = newB;
}

// The function to do DFS traversal. It uses SCCUtil() 
void GrA::SCC(std::vector <VList>& outVlist) {
	int* disc = new int[n];
	int* low = new int[n];
	bool* stackMember = new bool[n];
	VList st(n);

	for (size_t i = 0; i < n; ++i) {
		disc[i] = low[i] = -1; // default non-visited state
		stackMember[i] = false;
	}
	// Call the recursive helper function to find strongly 
	// connected components in DFS tree with vertex 'i' 
	for (size_t i = 0; i < n; ++i)
		if (disc[i] == -1)
			SCCUtil(i, disc, low, st, stackMember, outVlist);
}

void GrL::SCCUtil(size_t u, int disc[], int low[], VList& st, bool stackMember[], std::vector <VList>& outVlist) {
	// A recursive function that finds and prints strongly connected 
	// components using DFS traversal 
	// u -- >> The vertex to be visited next 
	// disc[] -- >> Stores discovery times of visited vertices 
	// low[] -- >> earliest visited vertex (the vertex with minimum 
	//             discovery time) that can be reached from subtree 
	//             rooted with current vertex 
	// &st -- >> To store all the connected ancestors (could be part 
	//           of SCC) 
	// stackMember[] --> bit/index array for faster check whether 
	//                   a node is in stack 
	static int time = 0;

	disc[u] = low[u] = ++time;
	st.add(u);
	stackMember[u] = true;

	for (size_t i = A[u], v = 0; ; ) {
		if (i >= INT_MAX)
			break;
		else {
			v = B[i].v;
			i = B[i].next;
		}
		// If v is not visited yet, then recur for it
		if (disc[v] == -1) {
			SCCUtil(v, disc, low, st, stackMember, outVlist);
			// Check if the subtree rooted with 'v' has a 
			// connection to one of the ancestors of 'u' 
			// Case 1  
			low[u] = std::min(low[u], low[v]);
		}
		// Update low value of 'u' only of 'v' is still in stack 
		// (i.e. it's a back edge, not cross edge). 
		// Case 2 
		else if (stackMember[v] == true)
			low[u] = std::min(low[u], disc[v]);
	}

	// head node found, pop the stack and print an SCC
	if (low[u] == disc[u])
		outVlist.push_back(st.createOutList(u, stackMember));
}
