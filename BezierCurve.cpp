#include "BezierCurve.h"
#include "DxLib.h"

BezierCurve::BezierCurve()
{
	startingPoint_x = 0;
	startingPoint_y = 0;
	endPoint_x = 0;
	endPoint_y = 0;
	turnPoint_x = 0;
	turnPoint_y = 0;
	x = 0;
	y = 0;
	t = 1.0;
}


BezierCurve::~BezierCurve()
{
}


void BezierCurve::setPoint(int startingPoint_x, int startingPoint_y, int endPoint_x, int endPoint_y, int turnPoint_x, int turnPoint_y, double speed)
{
	this->startingPoint_x = startingPoint_x;
	this->startingPoint_y = startingPoint_y;
	this->endPoint_x = endPoint_x;
	this->endPoint_y = endPoint_y;
	this->turnPoint_x = turnPoint_x;
	this->turnPoint_y = turnPoint_y;
	this->speed = speed;
	t = 0.0;
}

bool BezierCurve::isEnd()
{
	bool end = false;

	if (t >= 1.0){
		end = true;
	}

	return end;
}

void BezierCurve::start()
{
	if (t < 1.0){
		t += speed;
		x = (int)(((1 - t)*(1 - t)) * startingPoint_x + 2 * (1 - t) * t * turnPoint_x + t * t * endPoint_x);
		y = (int)(((1 - t)*(1 - t)) * startingPoint_y + 2 * (1 - t) * t * turnPoint_y + t * t * endPoint_y);
	}


}

int BezierCurve::get_x()
{
	return x;
}

int BezierCurve::get_y()
{
	return y;
}

void BezierCurve::setT(double t)
{
	this->t = t;
}

void BezierCurve::UpdateEndPoint_x(int endPoint_x)
{
	this->turnPoint_x += endPoint_x;
	this->startingPoint_x += endPoint_x;
	this->endPoint_x += endPoint_x;

}

void BezierCurve::UpdateEndPoint_y(int turnPoint_y){
	this->turnPoint_y = (int)((4 * turnPoint_y - startingPoint_y - endPoint_y) / 2.0);
}

BezierCurve_ThreePoint::BezierCurve_ThreePoint()
{
	startingPoint_x = 0;
	startingPoint_y = 0;
	endPoint_x = 0;
	endPoint_y = 0;
	turnPoint_x = 0;
	turnPoint_y = 0;
	x = 0;
	y = 0;
	t = 1.0;
}

void BezierCurve_ThreePoint::setPoint(int startingPoint_x, int startingPoint_y, int endPoint_x, int endPoint_y, int turnPoint_x, int turnPoint_y, double speed, int speedLimit)
{
	this->startingPoint_x = startingPoint_x;
	this->startingPoint_y = startingPoint_y;
	y = startingPoint_y;
	this->endPoint_x = endPoint_x;
	this->endPoint_y = endPoint_y;
	this->speed = speed;
	this->speedLimit = speedLimit;
	t = 0.0;


	// x,yが通したい点
	// p0, p1 , p2はベジエ曲線の制御点。p1をp0,p2,(x,y)の3点とt = 0.5の条件から求めて使ってみる
	this->turnPoint_x = (int)((4 * turnPoint_x - startingPoint_x - endPoint_x) / 2.0);
	this->turnPoint_y = (int)((4 * turnPoint_y - startingPoint_y - endPoint_y) / 2.0);
}

void BezierCurve_ThreePoint::start()
{	
	temp_y = y;

	if (t < 1.0){
		t += speed;
	}

	x = (int)(((1 - t)*(1 - t)) * startingPoint_x + 2 * (1 - t) * t * turnPoint_x + t * t * endPoint_x);
	y = (int)(((1 - t)*(1 - t)) * startingPoint_y + 2 * (1 - t) * t * turnPoint_y + t * t * endPoint_y);


	if (t >= 1.0 || y - temp_y > speedLimit){
		y = temp_y + speedLimit;
	}
}

void BezierCurve_ThreePoint::turnOverPoint()
{
	int temp_x, temp_y;

	temp_x = startingPoint_x;
	temp_y = startingPoint_y;

	startingPoint_x = endPoint_x;
	startingPoint_y = endPoint_y;

	endPoint_x = temp_x;
	endPoint_y = temp_y;
}