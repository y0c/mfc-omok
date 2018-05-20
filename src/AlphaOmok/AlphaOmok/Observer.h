#pragma once
#include <string>
#include <map>


using namespace std;

class Observer
{
public:
	virtual void notify(string eventType,map<string,void*> data) {};
	Observer();
	~Observer();
};


