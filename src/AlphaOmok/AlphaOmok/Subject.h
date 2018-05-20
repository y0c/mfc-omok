#pragma once
#include "Observer.h"
#include <vector>
#include <string>
using namespace std;

class Subject
{
	vector<Observer*> m_Observers;
public:
	void registerObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notifyAll(string eventType);
	Subject();
	~Subject();
};

