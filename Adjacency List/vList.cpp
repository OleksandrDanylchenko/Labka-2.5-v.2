#pragma once

#include <fstream>
#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\vList.h"
#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\grRepres.h"

VList::VList(size_t _n) : vList{ new size_t[_n] }, nmax{ _n }, n{ 0 } {}

VList::VList(VList&& r) noexcept : nmax{ 0 }, n{ 0 }, vList{ nullptr } {
	nmax = r.nmax;
	n = r.n;
	vList = r.vList;

	r.nmax = r.n = 0;
	r.vList = nullptr;
}

VList::~VList() {
	delete[]vList;
}

void VList::add(size_t v) {
	while (true) {
		if (n + 1 < nmax) {
			vList[n++] = v;
			break;
		} else
			resize();
	}
}

bool VList::notEmpty() const { return n > 0; }

void VList::output(std::ofstream& f) {
	for (size_t i = 0; i < n; ++i)
		f << vList[i] << ' ';
	f << std::endl;
}

void VList::resize() {
	nmax *= 3;
	size_t* newVlist = new size_t[nmax];
	for (size_t i = 0; i < n; ++i)
		newVlist[i] = vList[i];
	delete[] vList;
	vList = newVlist;
}

VList VList::createOutList(const size_t& u, bool stackMember[]) {
	if (notEmpty()) {
		VList result(77);
		size_t w = 0;
		while (vList[n - 1] != u) {
			w = vList[n - 1];
			result.add(w);
			stackMember[w] = false;
			vList[--n] = 0;
		}
		w = vList[n - 1];
		result.add(w);
		stackMember[w] = false;
		vList[--n] = 0;
		return result;
	}
	return VList(0);
}