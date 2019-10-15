#pragma once

#include "board.h"

// �ő�萔
constexpr int MAX_MOVE = 60;
constexpr int MAX_TURN = 80;

constexpr int BOARD_SIZE = 64;

constexpr int INF = 1e9;

constexpr int SCORE_INF = 127;
constexpr int SCORE_MAX = 64;

// BitBoard�̏����z�u
constexpr BitBoard NONE          = 0x0000000000000000;
constexpr BitBoard INITIAL_BLACK = 0x0000000810000000;
constexpr BitBoard INITIAL_WHITE = 0x0000001008000000;

// �Ԑl
constexpr BitBoard HORIZONTAL_GUARD = 0x7e7e7e7e7e7e7e7e;
constexpr BitBoard VERTICAL_GUARD   = 0x00FFFFFFFFFFFF00;
constexpr BitBoard DIAGONAL_GUARD   = 0x007e7e7e7e7e7e00;

// ���
enum Stat {
	EMPTY,
	BLACK,
	WHITE,
	MOVABLE,
	ERROR
};

// ����
enum Dir {
	UPPER,
	UPPER_RIGHT,
	RIGHT,
	LOWER_RIGHT,
	LOWER,
	LOWER_LEFT,
	LEFT,
	UPPER_LEFT
};