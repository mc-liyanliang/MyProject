#include "stdafx.h"
#include "InputAndOutput.h"
#include "Point.h"
#include "Line.h"
#include "Polyline.h"
#include <vector>
#include <iostream>
#include <iosfwd>
#include <fstream> 
#include <string>
#include "ModalEntity.h"
using namespace std;


CInputAndOutput::CInputAndOutput(void)
{
	DoesInputData = FALSE;
}


CInputAndOutput::~CInputAndOutput(void)
{

}

//��ȡtxt�ĵ��е�����
void CInputAndOutput::InputData( char *filename, CModalEntity& modelEntity)
{
	ifstream ReadFile;
	ReadFile.open(filename,ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
	
	string readline;
	Point point1,point2,point3;
	CLine line;
	CPolyline polyline;

	if(ReadFile.fail())//�ļ���ʧ��
	{
		AfxMessageBox(_T("�ļ���ʧ��!"));
		return;
	}
	else//�ļ�����
	{
		while(getline(ReadFile,readline,'\n'))
		{
			if (readline == "line")  //������������line
			{
				line.read(&ReadFile);

				modelEntity.AddLine(line);
			}
			else if(readline == "polyline")  //������������polyline
			{
				polyline.read(&ReadFile);
				
				modelEntity.AddPolyline(polyline);
			}
			else
			{
				break;
			}
			
		}
		ReadFile.close();
	}

	DoesInputData = TRUE;
}

Point CInputAndOutput::ReadPoint( string readline )
{
	double x1;
	double y1;
	Point point;
	string comma = ",";
	string newline_1=readline.substr(0,readline.find_first_of(comma));
	x1=stod(newline_1);
	string newline_2=readline.substr(readline.find_first_of(comma)+1,readline.size());
	y1=stod(newline_2);

	//��ȡһ����
	point.x=x1;  
	point.y=y1;
	return point;
}

BOOL CInputAndOutput::HasInputData()
{
	return DoesInputData;
}

