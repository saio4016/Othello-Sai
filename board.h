#pragma once
#include "bitboard.h"
#include "move.h"

class Board
{
private:
	BitBoard black;
	BitBoard white;

public:
	Board();
	void init();

	void update(const int color, const Move& move);

	BitBoard makeMovableBoard(const int color) const;
	BitBoard getSomeMoves(const int shift, const BitBoard colorBoard, const BitBoard mask) const;

	BitBoard makeFlipBoard(const int color, const BitBoard putBoard) const;
	BitBoard transfer(const int dir, const BitBoard bitBoard) const;

	int getColor(const BitBoard bitBoard) const;
	int countDisc(const int color) const;
	int countMobility(const int color) const;
	//int getCorner(const int color);
	//int getEdge(const int color);
	//int getStable(const int color);
};
