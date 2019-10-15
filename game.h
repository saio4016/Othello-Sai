#pragma once
#include <string>
#include "bitboard.h"
#include "board.h"
#include "move.h"
#include "const.h"

class Game
{
private:
	Board board;   // �Ֆ�
	
	int nextColor; // ���ɒu���΂̐F

	int curMoves;  // ���݂̎萔
	int curPasses; // ���݂̃p�X��
	int sumMoves;  // ���萔
	int sumPasses; // ���p�X��

	Move moveLog[MAX_TURN]; // i��ڂɒu�����΂ƕԂ�����

public:
	Game();
	void init();

	bool move(std::string in);
	bool move(BitBoard moveBoard);

	void pass();
	void undo();
	void redo();

	bool isPass() const;
	bool isGameOver() const;
	bool isUndo() const;
	bool isRedo() const;

	void changeTurn();

	int getNextColor() const;
	int getCurMoves() const;
	int getStat(int x, int y) const;
	int getStat(BitBoard bitBoard) const;
	int countDisc(int color) const;
	BitBoard getNextMovable() const;
	Board getBoard() const;
	
	BitBoard toBitBoard(std::string str) const;
	BitBoard toBitBoard(int x, int y) const;
	std::string toString(BitBoard bitBoard) const;

	void load(std::string record);
};