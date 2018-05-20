#pragma once
#include <string>
using namespace std;

class Observer
{
public:
	virtual void notify(string eventType) {};
	Observer();
	~Observer();
};


