#pragma once
template<typename T>
class Comparator
{
public:
	virtual int compare(const T& left, const T& right) {
		return (left > right) ? 1 : (left < right) ? -1 : 0;
	}
};
