// LABKA 2.5 v.2 Matrix methods implementation
#include <iostream>
#include <fstream>
#include <algorithm>

#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\vList.h"
#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\grRepres.h"

GrMA::~GrMA() {
	if (E != nullptr) {
		for (size_t l = 0; l < n; ++l) {
			delete[] E[l];
			E[l] = nullptr;
		}
		delete[] E;
		E = nullptr;
	}
}

bool GrMA::create(size_t _n) {
	// deletes all the information in previous 2D array
	if (E != nullptr) {
		for (size_t l = 0; l < n; ++l) {
			delete[] E[l];
			E[l] = nullptr;
		}
		delete[] E;
		E = nullptr;
	}

	// creates new 2D bool matrix
	n = _n;
	E = new(std::nothrow) bool* [n] {};
	if (E != nullptr) {
		for (size_t i = 0; i < n; ++i) {
			E[i] = new(std::nothrow) bool [n] {};
			if (E[i] == nullptr)
				return false;
		}
	}
	return (E != nullptr);
}

bool GrMA::addArc(size_t v, size_t w) {
	E[v][w] = 1;
	if (!isDir)
		E[w][v] = 1;
	++m;
	return true;
}

VList GrMA::neighbors(size_t i) {
	VList L(77);
	for (size_t j = 0; j < n; ++j) // check entire matrix
		if (E[i][j] != false)
			L.add(j);
	return L;
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

void GrMA::SCCUtil(size_t u, int disc[], int low[], VList& st, bool stackMember[], std::vector <VList>& outVlist) {
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

	for (size_t i = 0; i < n; ++i) {
		// checks only adjacent vertices
		if (E[u][i] != 1)
			continue;
		// If v is not visited yet, then recur for it
		if (disc[i] == -1) {
			SCCUtil(i, disc, low, st, stackMember, outVlist);
			// Check if the subtree rooted with 'v' has a 
			// connection to one of the ancestors of 'u' 
			// Case 1  
			low[u] = std::min(low[u], low[i]);
		}
		// Update low value of 'u' only of 'v' is still in stack 
		// (i.e. it's a back edge, not cross edge). 
		// Case 2 
		else if (stackMember[i] == true)
			low[u] = std::min(low[u], disc[i]);
	}

	// head node found, pop the stack and print an SCC 
	if (low[u] == disc[u])
		outVlist.push_back(st.createOutList(u, stackMember));
}