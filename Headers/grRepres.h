#pragma once
#include <vector>

class GrA {
public:
	GrA() {}; //: isDir(0), n(0), m(0) {}
	virtual bool create(size_t n) = 0;
	virtual bool addArc(size_t i, size_t j) = 0;
	virtual VList neighbors(size_t v) = 0;
	size_t getN() const { return n; }
	size_t getM() const { return m; }
	bool getIsDir() { return isDir; }
	void setisDir(bool d) { isDir = d; }
	// Tarjan’s Algorithm to find and print Strongly Connected Components
	void SCC(std::vector <VList>& outVlist);
protected:
	bool isDir{ false };
	size_t n{ 0 }, m{ 0 };
	// A Recursive DFS based function used by SCC() 
	virtual void SCCUtil(size_t u, int disc[], int low[], VList& st, bool stackMember[], std::vector <VList>& outVlist) = 0;
};

class GrMA : public GrA {
public:
	~GrMA();
	bool create(size_t n);
	bool addArc(size_t i, size_t j);
	VList neighbors(size_t v);
protected:
	bool** E{ nullptr };
	void SCCUtil(size_t u, int disc[], int low[], VList& st, bool stackMember[], std::vector <VList>& outVlist);
};

class GrL : public GrA {
public:
	~GrL();
	bool create(size_t n);
	bool addArc(size_t, size_t);
	VList neighbors(size_t v);
protected:
	size_t _nA{ 0 }, _nB{ 0 }, _nMax{ 0 };
	size_t* A{ nullptr };
	struct Node { size_t v; size_t next; };
	Node* B{ nullptr };
	void resizeB();

	void SCCUtil(size_t u, int disc[], int low[], VList& st, bool stackMember[], std::vector <VList>& outVlist);
};