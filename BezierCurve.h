#pragma once
class BezierCurve
{
protected:
	int startingPoint_x, startingPoint_y;
	int endPoint_x, endPoint_y;
	int turnPoint_x, turnPoint_y;
	int x, y;
	double speed;
	double t;
public:
	virtual void setPoint(int startingPoint_x, int starting_y, int endPoint_x, int endPoint_y, int turnPoint_x, int turnPoint_y, double speed);
	virtual void setPoint(int startingPoint_x, int startingPoint_y, int endPoint_x, int endPoint_y, int turnPoint_x, int turnPoint_y, double speed, int speedLimit){};
	void UpdateEndPoint_x(int endPoint_x);
	void UpdateEndPoint_y(int endPoint_y);
	void setT(double t);
	bool isEnd();
	virtual void start();
	int get_x();
	int get_y();
	BezierCurve();
	~BezierCurve();
};

class BezierCurve_ThreePoint : public BezierCurve
{
private:
	int speedLimit;
	int temp_x, temp_y;
public:
	void start();
	void turnOverPoint();
	void setPoint(int startingPoint_x, int starting_y, int endPoint_x, int endPoint_y, int turnPoint_x, int turnPoint_y, double speed, int speedLimit);
	BezierCurve_ThreePoint();
	~BezierCurve_ThreePoint(){};
};