#pragma once
#include "Controller.h"
class KeyInput :
	public Controller
{
public:
	KeyInput() ;
	~KeyInput() ;

	void Update(void) override;
private:
	std::array<char, 256U> keyData_;
	std::map<InputID, unsigned int> inputTbl_;
	InputID oldid;
};

