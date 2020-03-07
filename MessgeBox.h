#pragma once
#include <memory>
#include <string>
#include <vector>
#include "FrameCounter.h"

class MessgeBox
{
private:
	static std::shared_ptr<MessgeBox> _instance;
	std::vector<std::string> _messages;
	int _speed;
	int _messageIndex;
	std::string _activeMessage;
	FrameCounter _frameCounter;
	int _messageBackHandle;
public:
	bool isDisplay();
	void add(std::string);
	void displayToNextMessage();
	void update();

	static void create(){ _instance = std::make_shared<MessgeBox>(); };
	static std::shared_ptr<MessgeBox> getInstance();
	MessgeBox();
	~MessgeBox();
};

