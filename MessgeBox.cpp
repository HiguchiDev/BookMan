#include "MessgeBox.h"
#include "DxLib.h"

MessgeBox::MessgeBox()
{
	this->_messageIndex = 0;
	this->_messageBackHandle = LoadGraph("メッセージ画面.png");
	this->_speed = 4;
}


MessgeBox::~MessgeBox()
{
}

void MessgeBox::add(std::string message)
{
	this->_messages.push_back(message);
}

bool MessgeBox::isDisplay()
{
	return !this->_messages.empty();
}

std::shared_ptr<MessgeBox> MessgeBox::_instance;
std::shared_ptr<MessgeBox> MessgeBox::getInstance()
{
	if (_instance == nullptr){
		_instance = std::make_shared<MessgeBox>();
	}

	return _instance;
}

void MessgeBox::update()
{
	if (!this->_messages.empty()){
		if (this->_frameCounter.getCount() % this->_speed == 0){
			if (this->_messageIndex < this->_messages[0].size()){
				//char c = this->_messages[0][this->_messageIndex];
				//if (IsDBCSLeadByte(c) != 0){
					this->_activeMessage = this->_messages[0].substr(0, this->_messageIndex + 2);
					//this->_messages[0].erase(this->_messageIndex, this->_messageIndex + 2);
				//}
				this->_messageIndex += 2;
			}
		}

	}


	

	if (!this->_activeMessage.empty()){
		DrawGraph(0, 768 - 300, this->_messageBackHandle, TRUE);
		DrawString(50, 768 - 280, this->_activeMessage.c_str(), GetColor(255, 255, 255));
		DrawString(600, 700, "次へ : SPACE", GetColor(255, 255, 0));
	}

	this->_frameCounter.update();
}

void MessgeBox::displayToNextMessage()
{	
	if (!this->_messages.empty()){
		if (this->_messageIndex < this->_messages[0].size()){
			this->_activeMessage = this->_messages[0].c_str();
			
			this->_messageIndex = this->_messages[0].size();
		}
		else{
			
			this->_messages.erase(this->_messages.begin());
			this->_activeMessage.clear();
			this->_messageIndex = 0;
		}
	}	
}