#pragma once
#include <string>

class SceneNames
{
public:
	enum SceneTypes{
		TUTORIALSTAGE,
		HANSELANDGRETELSTAGE,
		MAZEOFGRASSLANDSTAGE,
		SEABEDTEMPLESTAGE,
		STAGESELECT,
		DATAREAD,
		ITEMSCREEN,
		OPENING,
		DATAWRITE,
		PAUSEMENU,
		STARTINGPREPARATION,
		KEYCONFIG,
		EQUIPSCREEN,
		ENDING,
	};

	static bool isStageName(std::string name);
	static std::string getName(SceneTypes SCREENTYPE);
	SceneNames();
	~SceneNames();
};

