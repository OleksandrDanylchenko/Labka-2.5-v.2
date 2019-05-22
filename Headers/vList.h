#pragma once

class VList {
public:
	VList() = delete;
	VList(size_t);
	VList(const VList&) = delete;
	VList(VList&&) noexcept;
	~VList();
	void add(size_t v);
	bool notEmpty() const;
	void output(std::ofstream& f);
	VList createOutList(const size_t& vertex, bool stackMember[]);
	void resize();
protected:
	size_t nmax, n;
	size_t* vList;
};