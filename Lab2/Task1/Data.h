#pragma once
class Data
{
	int key;
	int value;

public:
	bool operator>(const Data& right) const;
	bool operator<(const Data& right) const;
	bool operator==(const Data& right) const;
};

