#include "stdafx.h"
#include "Line.h"
#include "Point.h"
#include "Base.h"
#include "InputAndOutput.h"

#include <iostream>
#include <string>
#include <iosfwd>
#include <fstream> 

//Ĭ�Ϲ��캯��
CLine::CLine()
{

}

//���캯��
CLine::CLine(Point p1, Point p2)
{
	m_p1 = p1;
	m_p2 = p2;
}

//�������캯��
CLine::CLine(const CLine& src)
{
	m_p1 = src.m_p1;
	m_p2 = src.m_p2;
}

//��ֵ���캯��
CLine& CLine::operator=(const CLine& src)
{
	if (this != &src)
	{
		this->m_p1 = src.m_p1;
		this->m_p2 = src.m_p2;
	}
	return *this;
}


CLine::~CLine()
{

}


Point CLine::getStartPoint()
{
	return m_p1;
}

Point CLine::getEndPoint()
{
	return m_p2;
}

void CLine::setStartPoint(const Point& pt)
{
	m_p1 = pt;
}

void CLine::setEndPoint(const Point& pt)
{
	m_p2 = pt;
}

void CLine::setPoints(const Point &p1, const Point &p2)
{
	setStartPoint(p1);
	setEndPoint(p2);
}

void CLine::draw(CDC* pDC)
{
	Point startPoint = getStartPoint();
	Point endPoint = getEndPoint();
	pDC->MoveTo((int)startPoint.x,(int)startPoint.y);
	pDC->LineTo((int)endPoint.x,(int)endPoint.y);
}


void CLine::read(ifstream* ReadFile)
{
	Point StartPoint;
	Point EndPoint;
	string readline;
	//�ƶ�����һ��
	getline(*ReadFile,readline,'\n');
	//��ȡ��һ����
	StartPoint = ReadPoint(readline);
	//�ƶ�����һ��
	getline(*ReadFile,readline,'\n');
	//��ȡ�ڶ�����
	EndPoint = ReadPoint(readline);			

	setPoints(StartPoint,EndPoint);
}
