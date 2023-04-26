#include <DxLib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Controller.h"

Controller::RingBuf* Controller::RingBuf::Create(int no)
{
	auto beginBuf = new RingBuf{0,0.0,nullptr,nullptr};
	auto beforeBuf = beginBuf;
	auto nowBuf = beginBuf;
	for (int j = 1; j < no; j++)
	{
		nowBuf = new RingBuf{ 0,0.0,beforeBuf,nullptr };
		beforeBuf->next = nowBuf;
		beforeBuf = nowBuf;
	}
	beginBuf->before = nowBuf;
	nowBuf->next = beginBuf;
	return beginBuf;
}

void Controller::RingBuf::Destroy(RingBuf* beginBuf)
{
	if (beginBuf->before == nullptr)
	{
		return;
	}
	beginBuf->before->next = nullptr;
	while (beginBuf->next != nullptr)
	{
		beginBuf = beginBuf->next;
		delete beginBuf->before;
	}
	delete beginBuf;
}


