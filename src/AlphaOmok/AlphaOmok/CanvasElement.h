#pragma once


class CanvasElement
{
protected:
	CPoint m_Point;
	int m_Size;
public:
	CanvasElement();
	CanvasElement(CPoint point, int size);
	~CanvasElement();
	CPoint GetPoint();
	int GetSize();

	void SetPoint(CPoint point);
	void SetSize(int size);

	virtual void Render(CDC* pDC) {}
	virtual void OnClick(CPoint point) {}
	//Event Handler
	//void OnClick(CPoint clickPosition);
	
};



