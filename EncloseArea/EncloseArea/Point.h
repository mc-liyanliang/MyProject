#pragma once
class Point
{
public:
	//Ĭ�Ϲ��캯��
	Point();

	~Point(void);

	double Distance(const Point &p) const; 
	Point(double new_x, double new_y);
	Point(const Point& src);//���忽�����캯��;
	Point& operator=(const Point& src);



public:
	double x;
	double y;
};

