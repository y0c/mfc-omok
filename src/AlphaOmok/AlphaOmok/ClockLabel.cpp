#include "stdafx.h"
#include "ClockLabel.h"


ClockLabel::ClockLabel()
{

}
ClockLabel::ClockLabel(CPoint point, int size)
{
	m_Point = point;
	m_Size = size;
	m_S = 0;
	
}

ClockLabel::~ClockLabel()
{
}

void ClockLabel::Render() {
	CString str1;
	CFont m_font;
	m_font.CreateFont(40, 30, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("±¼¸²Ã¼"));
	CFont *p_old_font = m_pDC->SelectObject(&m_font);
	str1.Format(_T("%d"), m_S);
	m_pDC->DrawText(str1, CRect(m_Point.x, m_Point.y, m_Point.x + m_Size, m_Point.y + m_Size), DT_VCENTER | DT_SINGLELINE);
	m_pDC->SelectObject(p_old_font);
}