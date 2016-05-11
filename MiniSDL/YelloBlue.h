#pragma once
#include "PlayState.h"
class YelloBlue : public PlayState
{
public:
	~YelloBlue();
	bool onEnter();
	std::string getStateID() const { return yellowblueplayid; }
private:
	static const std::string yellowblueplayid;
};

