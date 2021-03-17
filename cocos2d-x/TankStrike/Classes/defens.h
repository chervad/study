#pragma once

#define WIDTH 640
#define HEIGHT 480

#define DELTA 1
#define DELTA_MV 1.0f
#define DELTA_PH 4

#define MAZE_WIDTH   26
#define MAZE_HEIGHT  18

enum ObjType {
	PLAYER = 0b00000001,
	ENEMY  = 0b00000010,
	WALL   = 0b00000100,
	BRICK  = 0b00001000,
	EAGLE  = 0b00010000,
	SHOT   = 0b00100000
};

enum eDirection {
	LEFT  = 0b0001,
	RIGHT = 0b0010,
	UP    = 0b0100,
	DOWN  = 0b1000
};

//��������������� ������� ��� ��������� ������. 
//��� ������� ����� ��������� �������� ������� �������, � ���� ������ ����� �� ������������ � ���������
enum class ObjectiveType {
	PATROL, //�������������� �������� ������� (���� ���������� �������� �� �������� ������)
	ATTACK, //��������� ������ (���� ����� � ���������� :))
	HAUNT,  //������������ ���������� (������� �� ������������, ���� � ����� - �����������)
	FALL_BACK //��������� - ���� �� ���� ���, �� ������ ����� ������� �� ����������
};
