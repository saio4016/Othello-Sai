#pragma once
#include "board.h"

struct Move {
	int score;     // �]���l
	BitBoard put;  // �u�����ӏ�
	BitBoard flip; // �Ԃ����ӏ�
};