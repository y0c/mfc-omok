#include "stdafx.h"
#include "Subject.h"

void Subject::registerObserver(Observer* observer) {
	m_Observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {

}

void Subject::notifyAll(string eventType) {
	for (Observer* observer : m_Observers) {
		observer->notify(eventType);
	}
}
Subject::Subject()
{
}


Subject::~Subject()
{
}
