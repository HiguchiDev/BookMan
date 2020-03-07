#include "HandleCreater.h"
#include "DxLib.h"
#include "Obstacle.h"

HandleCreater::HandleCreater()
{
}


HandleCreater::~HandleCreater()
{
}

bool HandleCreater::isOriginHandle(int handle)
{
	for (auto originHandle : _originHandles){
		if (originHandle == handle){
			return true;
		}
	}
	return false;
}

std::vector<int> HandleCreater::_originHandles;
std::vector<std::string> HandleCreater::_registeredHandleName;


void HandleCreater::loadOrigins()
{
	/*_obstacleNames.push_back("cake");
	_obstacleNames.push_back("strawberry");
	_obstacleNames.push_back("cracker");
	_obstacleNames.push_back("crackerSingle");
	_obstacleNames.push_back("chocolate");
	_obstacleNames.push_back("koke");
	_obstacleNames.push_back("TutorialBlock");
	*/

	SetUseASyncLoadFlag(true);
	_handleMap["cake.pmd"] = MV1LoadModel("cake.pmd");
	_handleMap["strawberry.pmd"] = MV1LoadModel("strawberry.pmd");
	_handleMap["cracker.pmd"] = MV1LoadModel("cracker.pmd");
	_handleMap["crackerSingle.pmd"] = MV1LoadModel("crackerSingle.pmd");
	_handleMap["chocolate.pmd"] = MV1LoadModel("chocolate.pmd");
	_handleMap["koke.pmd"] = MV1LoadModel("koke.pmd");
	_handleMap["��l��/��l��������.pmd"] = MV1LoadModel("��l��/��l��������.pmd");
	_handleMap["��l��/��l��������.pmd"] = MV1LoadModel("��l��/��l��������.pmd");
	_handleMap["��l��/��l��������.pmd"] = MV1LoadModel("��l��/��l��������.pmd");
	_handleMap["��l��/��l��yoroi��.pmd"] = MV1LoadModel("��l��/��l��yoroi��.pmd");
	_handleMap["��l��/��l��yoroi��.pmd"] = MV1LoadModel("��l��/��l��yoroi��.pmd");
	_handleMap["��l��/��l��yoroi��.pmd"] = MV1LoadModel("��l��/��l��yoroi��.pmd");
	_handleMap["enemy.pmd"] = MV1LoadModel("enemy.pmd");
	_handleMap["��(�~�~�b�N)/��(�~�~�b�N).pmd"] = MV1LoadModel("��(�~�~�b�N)/��(�~�~�b�N).pmd");
	_handleMap["�s�G��.pmd"] = MV1LoadModel("�s�G��.pmd");
	_handleMap["�_�[�N�s�G��.pmd"] = MV1LoadModel("�_�[�N�s�G��.pmd");
	_handleMap["�L�����f�B.pmd"] = MV1LoadModel("�L�����f�B.pmd");
	_handleMap["���b�h�L�����f�B.pmd"] = MV1LoadModel("���b�h�L�����f�B.pmd");
	_handleMap["bag.pmd"] = MV1LoadModel("bag.pmd");
	_handleMap["�W���O���[/Juggler.pmd"] = MV1LoadModel("�W���O���[/Juggler.pmd");
	_handleMap["����.pmd"] = MV1LoadModel("����.pmd");
	_handleMap["�{�{/Miyamoto.pmd"] = MV1LoadModel("�{�{/Miyamoto.pmd");
	_handleMap["���̐���/Water.pmd"] = MV1LoadModel("���̐���/Water.pmd");
	_handleMap["�A���R�E/Ankou.pmd"] = MV1LoadModel("�A���R�E/Ankou.pmd");
	_handleMap["��/Hana.pmd"] = MV1LoadModel("��/Hana.pmd");
	_handleMap["�L���O�X���C��/Kingsuraimu.pmd"] = MV1LoadModel("�L���O�X���C��/Kingsuraimu.pmd");
	_handleMap["�h���L�[/Doraki.pmd"] = MV1LoadModel("�h���L�[/Doraki.pmd");
	_handleMap["�Ύ�/Kasya.pmd"] = MV1LoadModel("�Ύ�/Kasya.pmd");
	_handleMap["�S�����X�N/�S�����X�N.pmd"] = MV1LoadModel("�S�����X�N/�S�����X�N.pmd");
	_handleMap["�S�����X�N����/�S�����X�N����.pmd"] = MV1LoadModel("�S�����X�N����/�S�����X�N����.pmd");
	_handleMap["BookMonster/BookMonster.pmd"] = MV1LoadModel("BookMonster/BookMonster.pmd");
	_handleMap["���܂��N/���܂��N.pmd"] = MV1LoadModel("���܂��N/���܂��N.pmd");
	_handleMap["�L�m�R�N/�L�m�R�N.pmd"] = MV1LoadModel("�L�m�R�N/�L�m�R�N.pmd");
	_handleMap["���t���t�N/���t���t�N.pmd"] = MV1LoadModel("���t���t�N/���t���t�N.pmd");
	_handleMap["�؂�؂�N/�؂�؂�N.pmd"] = MV1LoadModel("�؂�؂�N/�؂�؂�N.pmd");
	_handleMap["BookMonster����/BookMonster����.pmd"] = MV1LoadModel("BookMonster����/BookMonster����.pmd");
	_handleMap["���܂��N����/���܂��N����.pmd"] = MV1LoadModel("���܂��N����/���܂��N����.pmd");
	_handleMap["�L�m�R�N����/�L�m�R�N����.pmd"] = MV1LoadModel("�L�m�R�N����/�L�m�R�N����.pmd");
	_handleMap["���t���t�N����/���t���t�N����.pmd"] = MV1LoadModel("���t���t�N����/���t���t�N����.pmd");
	_handleMap["�؂�؂�N����/�؂�؂�N����.pmd"] = MV1LoadModel("�؂�؂�N����/�؂�؂�N����.pmd");
	_handleMap["��(�~�~�b�N)����/��(�~�~�b�N)����.pmd"] = MV1LoadModel("��(�~�~�b�N)����/��(�~�~�b�N)����.pmd");
	_handleMap["�A���R�E����/Ankouasyu.pmd"] = MV1LoadModel("�A���R�E����/Ankouasyu.pmd");
	_handleMap["�L���O�X���C�����b�h/KingsuraimuRed.pmd"] = MV1LoadModel("�L���O�X���C�����b�h/KingsuraimuRed.pmd");
	_handleMap["�N���[�P���@��1/kurakenLegOne.pmd"] = MV1LoadModel("�N���[�P���@��1/kurakenLegOne.pmd");
	_handleMap["�N���[�P���@��2/kurakenLegTwo.pmd"] = MV1LoadModel("�N���[�P���@��2/kurakenLegTwo.pmd");
	_handleMap["�N���[�P���@�{��/kuraken.pmd"] = MV1LoadModel("�N���[�P���@�{��/kuraken.pmd");
	_handleMap["�ŋ{�{/MiyamotoDark.pmd"] = MV1LoadModel("�ŋ{�{/MiyamotoDark.pmd");
	_handleMap["�W���O���[����/JugglerAsyu.pmd"] = MV1LoadModel("�W���O���[����/JugglerAsyu.pmd");
	_handleMap["�Ԉ���/HanaAsyu.pmd"] = MV1LoadModel("�Ԉ���/HanaAsyu.pmd");
	_handleMap["����/Suisya.pmd"] = MV1LoadModel("����/Suisya.pmd");
	_handleMap["�΂̐���/Faire.pmd"] = MV1LoadModel("�΂̐���/Faire.pmd");
	_handleMap["�h���L�[�O���[��/GreenDoraki.pmd"] = MV1LoadModel("�h���L�[�O���[��/GreenDoraki.pmd");
	_handleMap["TutorialEnemy.pmd"] = MV1LoadModel("TutorialEnemy.pmd");
	_handleMap["openingTitle2.pmd"] = MV1LoadModel("openingTitle2.pmd");
	_handleMap["potion.pmd"] = MV1LoadModel("potion.pmd");
	_handleMap["saveBook.pmd"] = MV1LoadModel("saveBook.pmd");
	_handleMap["TreasureChest/TreasureChest.pmd"] = MV1LoadModel("TreasureChest/TreasureChest.pmd");
	_handleMap["��.pmd"] = MV1LoadModel("��.pmd");
	_handleMap["Stairs.pmd"] = MV1LoadModel("Stairs.pmd");
	_handleMap["��.pmd"] = MV1LoadModel("��.pmd");
	_handleMap["Spring.pmd"] = MV1LoadModel("Spring.pmd");
	_handleMap["Needle.pmd"] = MV1LoadModel("Needle.pmd");
	_handleMap["HanselAndGretelStageFloor.pmd"] = MV1LoadModel("HanselAndGretelStageFloor.pmd");
	_handleMap["HanselAndGretelStageSaveFloor.pmd"] = MV1LoadModel("HanselAndGretelStageSaveFloor.pmd");
	_handleMap["SeabedTempleStageSaveFloor.pmd"] = MV1LoadModel("SeabedTempleStageSaveFloor.pmd");
	_handleMap["SeabedTempleStageFloor.pmd"] = MV1LoadModel("SeabedTempleStageFloor.pmd");
	_handleMap["exp.pmd"] = MV1LoadModel("exp.pmd");
	_handleMap["exp.mqo"] = MV1LoadModel("exp.mqo");
	_handleMap["hitBox.mqo"] = MV1LoadModel("hitBox.mqo");
	_handleMap["TutorialStageFloor.pmd"] = MV1LoadModel("TutorialStageFloor.pmd");
	_handleMap["TutorialStageSaveFloor.pmd"] = MV1LoadModel("TutorialStageSaveFloor.pmd");
	_handleMap["TutorialBlock.pmd"] = MV1LoadModel("TutorialBlock.pmd");
	_handleMap["bigrock.pmd"] = MV1LoadModel("bigrock.pmd");
	_handleMap["beautifulrock.pmd"] = MV1LoadModel("beautifulrock.pmd");
	_handleMap["table.pmd"] = MV1LoadModel("table.pmd");
	_handleMap["savetableyoko.pmd"] = MV1LoadModel("savetableyoko.pmd");
	_handleMap["savetabletate.pmd"] = MV1LoadModel("savetabletate.pmd");
	_handleMap["savetablecorner.pmd"] = MV1LoadModel("savetablecorner.pmd");
	_handleMap["savewall.pmd"] = MV1LoadModel("savewall.pmd");
	_handleMap["tallglass.pmd"] = MV1LoadModel("tallglass.pmd");
	_handleMap["tree.pmd"] = MV1LoadModel("tree.pmd");
	_handleMap["cobble.pmd"] = MV1LoadModel("cobble.pmd");
	_handleMap["woodbox.pmd"] = MV1LoadModel("woodbox.pmd");
	_handleMap["MazeOfGrasslandStageFloor.pmd"] = MV1LoadModel("MazeOfGrasslandStageFloor.pmd");
	_handleMap["MazeOfGrasslandStageSaveFloor.pmd"] = MV1LoadModel("MazeOfGrasslandStageSaveFloor.pmd");
	
	SetUseASyncLoadFlag(false);

}

int HandleCreater::get3DHandle(std::string fileName)
{
	int handle;

	auto itr = _handleMap.find(fileName);
	
	if (itr == _handleMap.end()){
		SetUseASyncLoadFlag(false);
		handle = MV1LoadModel(fileName.c_str());

	//	printfDx("fn : %s\n", fileName.c_str());
	//	printfDx("fn  handle : %d\n", handle);
		if (handle != -1){
			add(handle, fileName);
		}

	}
	else{
		handle = MV1DuplicateModel(_handleMap[fileName]);
	}


	return handle;
}

void HandleCreater::add(int handle, std::string fileName)
{
	_handleMap[fileName] = handle;
	_originHandles.push_back(handle);
	_registeredHandleName.push_back(fileName);
}

int HandleCreater::getDuplicate3DHandle(int handle)
{
	return MV1DuplicateModel(handle);
}