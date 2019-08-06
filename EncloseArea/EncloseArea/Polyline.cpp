#include "stdafx.h"
#include "Polyline.h"

#include "Point.h"

#include <iostream>
#include <string>
#include <iosfwd>
#include <fstream> 

CPolyline::CPolyline()
{
}




CPolyline::~CPolyline()
{
}

void CPolyline::addPoint( Point point )
{
	m_PolyPointVector.push_back(point);
}

void CPolyline::ClearPolyPointVector()
{
	m_PolyPointVector.clear();
}

vector<Point> CPolyline::getPoints()
{
	vector<Point> point;
	for (auto i = m_PolyPointVector.begin(); i != m_PolyPointVector.end(); ++i)
		point.push_back(*i);
	return point;
}

Point CPolyline::getPoint(int nIdx)
{
	return m_PolyPointVector[nIdx];
}

//һ��polyline��ĸ���
int CPolyline::getPointNum()
{

	return m_PolyPointVector.size();
}

//���ƶ����
void CPolyline::draw(CDC* pDC)
{	 
		for (unsigned int i = 1; i < m_PolyPointVector.size();i++) //����һ��polyline��ÿһ����
		{
			pDC->MoveTo((int)m_PolyPointVector[i-1].x,(int)m_PolyPointVector[i-1].y);
			pDC->LineTo((int)m_PolyPointVector[i].x,(int)m_PolyPointVector[i].y);
		}
}

void CPolyline::read(ifstream* ReadFile)
{
	Point point;
	string readline;
	getline(*ReadFile,readline,'\n');
	ClearPolyPointVector();
	string linenum = readline;
	int nlinenum = stoi(linenum);
	for(int i = 0; i < nlinenum; i++)
	{	
		getline(*ReadFile,readline,'\n');
		point = ReadPoint(readline);
		addPoint(point); //����ȡ���ĵ���뵽����ߵ�������					
	}
	//throw std::logic_error("The method or operation is not implemented.");
}

