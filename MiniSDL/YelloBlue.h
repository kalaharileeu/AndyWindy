#pragma once
#include "PlayState.h"
class YelloBlue : public PlayState
{
public:
	~YelloBlue();
	void Update();
	void draw();
	bool onEnter();
	bool onExit();
	std::string getStateID() const { return yellowblueplayid; }
private:
	static const std::string yellowblueplayid;
};

