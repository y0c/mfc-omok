#pragma once


class CanvasElement
{
protected:
	CPoint m_Point;
	CDC* m_pDC;
	int m_Size;
public:
	CanvasElement();
	CanvasElement(CPoint point, int size);
	~CanvasElement();
	CPoint GetPoint();
	int GetSize();

	void SetPoint(CPoint point);
	void SetSize(int size);

	void setDC(CDC* pDC);
	virtual void Render() {}
	virtual void OnClick(CPoint point) {}
	//Event Handler
	//void OnClick(CPoint clickPosition);
	
};



