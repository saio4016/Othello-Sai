#pragma once
#include <string>
#include "bitboard.h"
#include "board.h"
#include "move.h"
#include "const.h"

class Game
{
private:
	Board board;   // 盤面
	
	int nextColor; // 次に置く石の色

	int curMoves;  // 現在の手数
	int curPasses; // 現在のパス数
	int sumMoves;  // 総手数
	int sumPasses; // 総パス数

	Move moveLog[MAX_TURN]; // i手目に置いた石と返した石

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