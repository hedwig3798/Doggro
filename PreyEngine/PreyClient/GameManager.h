#pragma once
#include <string>

#include "Singleton.h"


class IGraphicsEngine;

/// <summary>
/// ���������� �����ϰԵ� ģ��
/// �������� �� ���°����� �մϴ�.
/// ���� �̱���.
/// </summary>
class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();

	void Initialize(IGraphicsEngine* _iGraphicsEngine);
public:
	//ĸó�� ������ �����ϱ� ���� IgraphicEngine�� �ʿ��ϳ���
	IGraphicsEngine* gmGraphics;
	
	//�� �������� �� ���� üũ�� ���� ����
	bool isStage1Clear;
	bool isStage2Clear;
	bool isStage3Clear;
	bool isStage4Clear;

	//���� ���� �ٹ��� �������� �˷��ִ� ����
	int nowStage;
	std::string nowStageName;

};

