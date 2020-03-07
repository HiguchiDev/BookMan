#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "EffekseerForDXLib.h"

class HandleCreater
{
private:
	static std::unordered_map<std::string, int> _handleMap;
	static std::vector<int> _originHandles;
	static std::vector<std::string> _registeredHandleName;
	void add(int handle, std::string fileName);
public:
	bool isOriginHandle(int handle);
	int get3DHandle(std::string fileName);
	void loadOrigins();
	bool isLoadOrigin(){ return GetASyncLoadNum() == 0; };
	int getDuplicate3DHandle(int handle);
	HandleCreater();
	~HandleCreater();
};

