#include "ExpEffect.h"
#include "BezierCurve.h"
#include "Object_3D_Duplicate.h"
#include "Collision.h"


ExpEffect::ExpEffect() : Effect("exp.mqo")
{
	const int MATERIALNUM = 10;

	for (int i = 0; i < MATERIALNUM; i++){
		this->_materials.push_back(std::make_shared<Object_3D_Duplicate>("exp.mqo"));
		this->_beziers.push_back(std::make_shared<BezierCurve_ThreePoint>());
		this->_beziersZ.push_back(std::make_shared<BezierCurve_ThreePoint>());
	}
}


ExpEffect::~ExpEffect()
{
}

void ExpEffect::setPos(VECTOR position)
{
	this->_position = position;
	int posX = 10 * (this->_beziers.size() / 2);
	int posY = 50;
	int posHeight = 5;

	for (int i = 0; i < this->_beziers.size(); i++){
		_beziers[i]->setPoint(position.x, position.y - 20, this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).x, this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).y - 20, ((this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).x + position.x) / 2) - posX, position.y + posY, 0.015, 100);
		posX -= 10;

		if (i <= this->_beziers.size() / 2){
			posY += posHeight;
		}
		else{
			posY -= posHeight;
		}
	}


	//int posZ = 10 * (this->_beziers.size() / 2);
	for (auto bezier : this->_beziersZ){
		bezier->setPoint(position.x, position.z, this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).x, this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).z, ((this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).x + position.x) / 2), ((this->_pc.get3DPosition(Collision::getInstance()->getPlayerPos()).z + position.z) / 2), 0.015, 100);
	//	posZ -= 10;
	}
}

void ExpEffect::finalize()
{
	for (auto material : this->_materials){
		material->finalize();
	}
}

void ExpEffect::update()
{
	int endNum = 0;
	int endNumZ = 0;

	for (auto bezier : this->_beziers){
		if (bezier->isEnd()){
			endNum++;
		}
	}

	for (auto bezier : this->_beziersZ){
		if (bezier->isEnd()){
			endNumZ++;
		}
	}


	if (endNum == this->_beziers.size() && endNumZ == this->_beziersZ.size()){
		this->_finish = true;
	}
	else{
		this->_position.x = this->_beziers[0]->get_x();
		this->_position.y = this->_beziers[0]->get_y();
		this->_position.z = this->_beziersZ[0]->get_y();
		this->_beziers[0]->start();
		this->_beziersZ[0]->start();
		this->_materials[0]->setPosition(VGet(this->_position.x, this->_position.y, this->_position.z));

		

		

		for (int i = 1; i < this->_beziers.size(); i++){
			
			this->_beziers[i]->start();
			this->_beziersZ[i]->start();this->_materials[i]->setPosition(VGet(this->_beziers[i]->get_x(), this->_beziers[i]->get_y(), this->_beziersZ[i]->get_y()));
		}
	}

	for (int i = 1; i < this->_materials.size(); i++){
		
		
	}

	this->_materials[4]->draw();


}

void ExpEffect::start()
{
	this->_finish = false;
}