#include "stdafx.h"
#include "CanvasElement.h"


CanvasElement::CanvasElement()
{
}


CanvasElement::CanvasElement(CPoint point, int size)
{
	m_Point = point;
	m_Size = size;
}

CanvasElement::~CanvasElement()
{}


CPoint CanvasElement::GetPoint() {
	return m_Point;
}

int CanvasElement::GetSize() {
	return m_Size;
}

void CanvasElement::SetPoint(CPoint point) {
	m_Point = point;
}

void CanvasElement::SetSize(int size) {
	m_Size = size;
}