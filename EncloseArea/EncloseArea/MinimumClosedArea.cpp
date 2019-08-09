#include "stdafx.h"
#include "MinimumClosedArea.h"

/*-------------------����˼·------------------------*/
/*
	�٣��õ��߶μ���S���߶εļ���Ϊline��polyline��

	�ڣ��Ƴ��������߶Σ����˵ĵ㶼�ǹ����ģ���

	�ۣ�������е��߶Σ����ǽ����е��ཻ���߶β�ֿ�,�õ��µ��߶μ���S��

	�ܣ��Ƴ�һ���˵�������߶Σ�һ���˵�������߶��ǲ����ɶ���εģ�

	�ݣ��ҳ����еĴ������߶μ���M,M���߶μ��ϵļ���,��ά���飻
	������Ĵ�����ָ���ǣ�������һ����Ϊ����ҵ������ཻ�������߶�,���ҵ�����Щ�߶��ཻ�������߶�,
	  ֱ���Ҳ����ཻ�߶�,��ô��Щ�߶εļ��Ͼ���һ��������Mi.Ȼ���������еĴ�����

	�ޣ��ֱ��ÿһ����������з���������ȡ��
*/

CMinimumClosedArea::CMinimumClosedArea(void)
{
}


CMinimumClosedArea::~CMinimumClosedArea(void)
{
}

/*--------------------����˼·�٣����߶����ǵ��߶μ���S��������ĿΪline��polyline)-----------------*/
//����line��polyline���鲢תΪ�߶�
vector<CLine> CMinimumClosedArea::get_line(vector<CLine> LineVector,vector<CPolyline> PolylineVector)
{
	vector<CLine> AllLineSegment;
	for (unsigned int i = 0; i < LineVector.size();i++)
	{
		AllLineSegment.push_back(LineVector[i]);
	}

	//��polylineת����line��Ȼ����ӵ�AllLineSegment
	for (unsigned int i = 0; i < PolylineVector.size();i++)
	{
		CPolyline polyline;
		polyline = PolylineVector[i];
		for(int i = 1; i<polyline.getPointNum(); i++) //����polyline��ÿһ����
		{
			CLine line;
			line.setPoints(polyline.getPoint(i-1),polyline.getPoint(i));
			AllLineSegment.push_back(line);
		}	
	}
	return AllLineSegment;
}


/*-----------------------����˼·�ڣ��Ƴ��������߶Σ����˵ĵ㶼�ǹ����ģ�----------------------------*/

//�Ƴ����еĹ����߶Σ��������߶ζ����ཻ���߶Ρ�
vector<CLine> CMinimumClosedArea::remove_isolated_line(vector<CLine> input)
{
	vector<CLine> lines;
	lines = input;
	vector<CLine> output;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		vector<CLine> M;
		M = lines;

		for (unsigned int j = 0; j < M.size(); j++)
		{
			if (doselinecross(lines[i], M[j]))
			{
				output.push_back(lines[i]);
				break;
			}
		}
	}
	return output;
}

//�ж��߶��Ƿ��ཻ
bool CMinimumClosedArea::doselinecross(CLine L1, CLine L2)
{
	double x1 = L1.getStartPoint().x;
	double y1 = L1.getStartPoint().y;
	double x2 = L1.getEndPoint().x;
	double y2 = L1.getEndPoint().y;

	double x3 = L2.getStartPoint().x;
	double y3 = L2.getStartPoint().y;
    double x4 = L2.getEndPoint().x;
	double y4 = L2.getEndPoint().y;
	//����ֱ���غ�
	if ((Be_equal_to(L1.getStartPoint(), L2.getStartPoint()) && Be_equal_to(L1.getEndPoint(), L2.getEndPoint())) || (Be_equal_to(L1.getStartPoint(), L2.getEndPoint()) && Be_equal_to(L1.getEndPoint() ,L2.getStartPoint()))) //����line�Ķ˵���ͬ
	{
		return false;
	}
	if (Be_equal_to((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4), 0.f) || Be_equal_to((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4), 0.f))//б�����
	{
		if (Be_equal_to(L1.getStartPoint(), L2.getStartPoint()) || Be_equal_to(L1.getEndPoint(), L2.getEndPoint()) || Be_equal_to(L1.getEndPoint(), L2.getStartPoint()) || Be_equal_to(L1.getStartPoint(), L2.getEndPoint()))
		{
			return true;
		}
		else  //���ཻ
		{
			return false;
		}
	}
	double X = ((x1 - x2) * (x3 * y4 - x4 * y3) - (x3 - x4) * (x1 * y2 - x2 * y1)) / ((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4));
	double Y = ((y1 - y2) * (x3 * y4 - x4 * y3) - (x1 * y2 - x2 * y1) * (y3 - y4)) / ((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4));
	Point Q;
	Q.x = X;
	Q.y = Y;
	//�жϽ����Ƿ�ͬʱ��L1��L2��
	if (isonline(L1.getStartPoint(), L1.getEndPoint(), Q) && isonline(L2.getStartPoint(), L2.getEndPoint(), Q))
	{
		return true;
	}
	else//�������ӳ�����
	{
		return false;
	}
}

//�ж������������Ƿ����
bool CMinimumClosedArea::Be_equal_to(double A, double B)
{
	if (((A - B) < 0.1) && ((A - B) > -0.1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�жϵ�A�͵�B�Ƿ����
bool CMinimumClosedArea::Be_equal_to(Point A, Point B)
{
	if (Be_equal_to(A.x, B.x) && Be_equal_to(A.y, B.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}


//�жϵ��Ƿ�������
bool CMinimumClosedArea::isonline(Point P1, Point P2, Point Q) //FVector��ʾ��,�ж�Q�Ƿ���line(p1,p2)��
{
	if (Be_equal_to(Q, P1) || Be_equal_to(Q, P2)) //��Q���߶εĶ˵�
	{
		return true;
	}
	if (Be_equal_to(Q.Distance(P1) + Q.Distance(P2), P1.Distance(P2)))//��Q��line�����˵�֮��
	{
		return true;
	}
	return false;
}


/*-------------����˼·�ۣ�������е��߶Σ����ǽ����е��ཻ���߶β�ֿ����õ��µ��߶μ���S��--------------*/

//�ָ����е��߶Σ��õ��µ��߶�����
vector<CLine> CMinimumClosedArea::breaklines(vector<CLine> input)
{
	vector<CLine> lines;
	lines.clear();
	lines = input;
	vector<CLine> output;
	output.clear();
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		vector<Point> crosspointVec;
		for (unsigned int j = 0; j < lines.size(); j++)
		{
			if (doselinecross(lines[i], lines[j])) //����line�ཻ
			{ 
				//���㲻��lines[i]�������յ�
				Point crosspoint;
				crosspoint = getcrosspoint(lines[i], lines[j]);
				if ((!Be_equal_to(crosspoint, lines[i].getStartPoint()))  
					&& (!Be_equal_to(crosspoint, lines[i].getEndPoint())))
				{
					crosspointVec.push_back(crosspoint);
				}
			}
		}

		crosspointVec.insert(crosspointVec.begin(),lines[i].getStartPoint());
		crosspointVec.push_back(lines[i].getEndPoint());
		//����ÿһ��������line�������룬����������
	    for (unsigned int m = 0;m < crosspointVec.size() - 1; m++)
	    {
			for (unsigned int n = 0; n < crosspointVec.size()-m-1; n++ )
			{
				double Distm = lines[i].getStartPoint().Distance(crosspointVec[n]);
				double Distn = lines[i].getStartPoint().Distance(crosspointVec[n+1]);
				if (Distm > Distn)
				{
					swap(crosspointVec[n],crosspointVec[n+1]);
				}
			}
		
	    }


		//��line[i]���ضϵ��߶η���output��

		for (unsigned int k = 0;k < crosspointVec.size()-1; k++)
		{
			CLine lineSegment;
			lineSegment.setPoints(crosspointVec[k],crosspointVec[k + 1]);
			output.push_back(lineSegment);
		}

	}
	return output;
}

//��ȡ����
Point CMinimumClosedArea::getcrosspoint(CLine L1, CLine L2)
{

	double x1 = L1.getStartPoint().x;
	double y1 = L1.getStartPoint().y;
	double x2 = L1.getEndPoint().x;
	double y2 = L1.getEndPoint().y;
	double x3 = L2.getStartPoint().x;
	double y3 = L2.getStartPoint().y;
	double x4 = L2.getEndPoint().x;
	double y4 = L2.getEndPoint().y;
	Point Q;
	Q.x = 0;
	Q.y = 0;

	if (!doselinecross(L1, L2)) //�ж�����lime�Ƿ��ཻ
	{
		return Q;
	}
	//L1�������L2������˵��ཻ
	if (Be_equal_to(L1.getStartPoint(), L2.getStartPoint()) || Be_equal_to(L1.getStartPoint(), L2.getEndPoint()))
	{
		return L1.getStartPoint(); 
	}
	//L1���յ���L2�������յ��ཻ
	if (Be_equal_to(L1.getEndPoint(), L2.getStartPoint()) || Be_equal_to(L1.getEndPoint(), L2.getEndPoint()))
	{
		return L1.getEndPoint();
	}
	//���㽻��
	double X = ((x1 - x2) * (x3 * y4 - x4 * y3) - (x3 - x4) * (x1 * y2 - x2 * y1)) / ((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4));
	double Y = ((y1 - y2) * (x3 * y4 - x4 * y3) - (x1 * y2 - x2 * y1) * (y3 - y4)) / ((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4));
	Q.x = X;
	Q.y = Y;

	//Q��ͬʱ��L1��L2��
	if (isonline(L1.getStartPoint(), L1.getEndPoint(), Q) && isonline(L2.getStartPoint(), L2.getEndPoint(), Q))
	{
		return Q;
	}
	else
	{
		Q.x = 0;
		Q.y = 0;

		return Q;
	}
}


/*----------------------����˼·�ܣ��Ƴ�һ���˵�������߶Σ�һ���˵�������߶��ǲ����ɶ���εģ�------------------------*/

//�Ƴ��˵�������߶�
vector<CLine> CMinimumClosedArea::removenonefieldlines(vector<CLine> input)
{
	vector<CLine> resultLines;
	int nSize = input.size();
	for (int i = 0;i < nSize; i++)
	{
		vector<Point> crossPoint;
		for (int j = 0;j < nSize; j++)
		{
			if (doselinecross(input[i],input[j]))
			{
				crossPoint.push_back(getcrosspoint(input[i],input[j]));
			}
		}

		bool bEqual = false;
		for (unsigned int m = 0;m < crossPoint.size() ;m++)
		{
			if (Be_equal_to(input[i].getStartPoint(),crossPoint[m]))
			{
				bEqual = true;
				break;
			}
		}

		if (bEqual)
		{
			for (unsigned int n = 0;n < crossPoint.size() ;n++)
			{
				if (Be_equal_to(input[i].getEndPoint(),crossPoint[n]))
				{
					resultLines.push_back(input[i]);
					break;
				}
			}
		}

	}

	
	return resultLines;
}

/*-------------------����˼·�ݣ��ҳ����еĴ������߶μ���M,M���߶μ��ϵļ���-----------------*/

vector<vector<CLine>> CMinimumClosedArea::get_all_big_field(vector<CLine> input)
{
	vector<CLine> alllines;
	alllines.clear();
	alllines = input;
	vector<CLine> M;
	M.clear();
	vector<vector<CLine>> output;
	output.clear();
	vector<CLine> field;
	field.clear();
	while (alllines.size() != 0)
	{
		M.clear();
		M.push_back(alllines[0]);
		for (unsigned int i = 0; i < M.size(); i++)
		{
			for (unsigned int j = 0; j < alllines.size();)
			{
				if (doselinecross(M[i], alllines[j]))
				{
					M.push_back(alllines[j]);
					alllines.erase(alllines.begin() + j);
					i = 0;
					j = 0;
					break;
				}
				else
				{
					j = j + 1;
				}
			}
		}
		M.erase(M.begin());//����ȥ���е����⡣
		output.push_back(M);
		M.clear();
	}
	return output;
}

bool CMinimumClosedArea::doeslinehascrossline(CLine L, vector<CLine> LS)
{
	bool doeshas = false;
	for (int i = 0; i < LS.size(); i++)
	{
		if (doselinecross(L, LS[i]))
		{
			doeshas = true;
			break;
		}
	}
	return doeshas;
}

//ͨ����ʷ�߶�����ȡ�������
vector<CLine> CMinimumClosedArea::doed_it_has_small_field(vector<CLine> input)
{
	vector<CLine> lines;
	lines.clear();
	lines = input;
	vector<CLine> output;
	output.clear();
	for (int i = 0; i < (lines.size() - 2); i++)
	{
		CLine A, B;
		A = lines[lines.size() - 1];
		B = lines[i];
		if ((Be_equal_to(A.getStartPoint(), B.getStartPoint()) && Be_equal_to(A.getEndPoint(), B.getEndPoint())) 
			|| (Be_equal_to(A.getStartPoint(), B.getEndPoint()) && Be_equal_to(A.getEndPoint(), B.getStartPoint())))
		{
			for (int j = i + 1; j < lines.size(); j++)
			{
				output.push_back(lines[j]);
			}
		}
	}
	return output;
}


CLine CMinimumClosedArea::getnextline(CLine L, vector<CLine> LS, bool isbigangel)
{
	vector<CLine> lines;
	lines.clear();
	lines = LS;
	for (int i = 0; i<lines.size(); i++)
	{
		if ((Be_equal_to(lines[i].getStartPoint(), L.getStartPoint()) && Be_equal_to(lines[i].getEndPoint(), L.getEndPoint())) 
			|| (Be_equal_to(lines[i].getStartPoint(), L.getEndPoint()) && Be_equal_to(lines[i].getEndPoint(), L.getStartPoint())))
		{
			lines.erase(lines.begin() + i);
			break;
		}
	}
	vector<CLine> crosslines;
	crosslines.clear();
	for (int i = 0; i < lines.size(); i++)
	{
		if (Be_equal_to(lines[i].getStartPoint(), L.getEndPoint()))
		{
			crosslines.push_back(lines[i]);
		}
		if (Be_equal_to(lines[i].getEndPoint(), L.getEndPoint()))
		{
			Point P;
			P = lines[i].getStartPoint();
			lines[i].getStartPoint() = lines[i].getEndPoint();
			lines[i].getEndPoint() = P;
			crosslines.push_back(lines[i]);
		}
	}
	CLine output;
	if (crosslines.size() == 0)
	{
		Point pt(0,0);

		output.setStartPoint(pt);
		output.setEndPoint(pt);

		return output;
	}
	if (crosslines.size() == 1)
	{
		output = crosslines[0];
		return output;
	}
	float A = 3.1415926 * 2;
	float B = 0;
	for (int i = 0; i < crosslines.size(); i++)
	{
		float angel = acos((L.getStartPoint() - L.getEndPoint()).operator|(crosslines[i].getEndPoint() - crosslines[i].getStartPoint()) 
			/ (((L.getStartPoint() - L.getEndPoint()).Size())*((crosslines[i].getEndPoint() - crosslines[i].getStartPoint()).Size())));
		if ((L.getStartPoint() - L.getEndPoint()).operator^((crosslines[i].getEndPoint() - crosslines[i].getStartPoint())).Z == 0)
		{
			angel = 3.1415926;
		}
		if ((L.getStartPoint() - L.getEndPoint()).operator^((crosslines[i].getEndPoint() - crosslines[i].getStartPoint())).Z > 0)
		{
			angel = 3.1415926 * 2 - angel;
		}
		if (isbigangel)
		{
			if (angel > B)
			{
				B = angel;
				output = crosslines[i];
			}
		}
		else
		{
			if (angel < A)
			{
				A = angel;
				output = crosslines[i];
			}
		}
	}
	return output;
}






