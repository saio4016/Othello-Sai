#include "board.h"

#include "bits.h"
#include "const.h"

Board::Board()
{
	init();
}

void Board::init()
{
	black = INITIAL_BLACK;
	white = INITIAL_WHITE;
}

void Board::update(const int color, const Move& move)
{
	(color == BLACK ? black : white) ^= move.put | move.flip;
	(color == BLACK ? white : black) ^= move.flip;
}

BitBoard Board::makeMovableBoard(const int color) const
{
	BitBoard colorBoard = (color == BLACK ? black : white);
	BitBoard uncolorBoard = (color == BLACK ? white : black);
	BitBoard emptyBoard = ~(black | white);
	return ((getSomeMoves(1, colorBoard, uncolorBoard & 0x7e7e7e7e7e7e7e7eull) |  // â°
			 getSomeMoves(8, colorBoard, uncolorBoard & 0x00ffffffffffff00ull) |  // èc
			 getSomeMoves(7, colorBoard, uncolorBoard & 0x007e7e7e7e7e7e00ull) |  // éŒÇﬂ(1)
			 getSomeMoves(9, colorBoard, uncolorBoard & 0x007e7e7e7e7e7e00ull)) & // éŒÇﬂ(2)
			emptyBoard);
}

BitBoard Board::getSomeMoves(const int shift, const BitBoard colorBoard, const BitBoard mask) const
{
	BitBoard flip = (((colorBoard << shift) | (colorBoard >> shift)) & mask);
	flip |= (((flip << shift) | (flip >> shift)) & mask);
	flip |= (((flip << shift) | (flip >> shift)) & mask);
	flip |= (((flip << shift) | (flip >> shift)) & mask);
	flip |= (((flip << shift) | (flip >> shift)) & mask);
	flip |= (((flip << shift) | (flip >> shift)) & mask);
	return (flip << shift) | (flip >> shift);
}

BitBoard Board::makeFlipBoard(const int color, const BitBoard putBoard) const
{
	// éwíËÇÃèÍèäÇ…êŒÇ™Ç†ÇÍÇŒNONEÇï‘Ç∑
	if ((black | white) & putBoard) return NONE;

	BitBoard flipBoard    = NONE; // îΩì]Ç≥ÇπÇÈâ”èä
	BitBoard colorBoard   = (color == BLACK ? black : white);
	BitBoard uncolorBoard = (color == BLACK ? white : black);
	BitBoard mask, tmp;
	// è„Ç©ÇÁéûåvâÒÇËÇ…íTÇ∑
	for (int dir = UPPER; dir <= UPPER_LEFT; dir++) {
		tmp = NONE;
		mask = transfer(dir, putBoard);
		while (mask & uncolorBoard) {
			tmp |= mask;
			mask = transfer(dir, mask);
		}
		if (mask & colorBoard) flipBoard |= tmp;
	}
	return flipBoard;
}

BitBoard Board::transfer(const int dir, const BitBoard bitBoard) const
{
	BitBoard transBoard = NONE;
	switch (dir) {
	case UPPER:
		transBoard = (bitBoard >> 8) & 0x00FFFFFFFFFFFFFF;
		break;
	case UPPER_RIGHT:
		transBoard = (bitBoard >> 7) & 0x00FEFEFEFEFEFEFE;
		break;
	case RIGHT:
		transBoard = (bitBoard << 1) & 0xFEFEFEFEFEFEFEFE;
		break;
	case LOWER_RIGHT:
		transBoard = (bitBoard << 9) & 0xFEFEFEFEFEFEFE00;
		break;
	case LOWER:
		transBoard = (bitBoard << 8) & 0xFFFFFFFFFFFFFF00;
		break;
	case LOWER_LEFT:
		transBoard = (bitBoard << 7) & 0x7F7F7F7F7F7F7F00;
		break;
	case LEFT:
		transBoard = (bitBoard >> 1) & 0x7F7F7F7F7F7F7F7F;
		break;
	case UPPER_LEFT:
		transBoard = (bitBoard >> 9) & 0x007F7F7F7F7F7F7F;
		break;
	}
	return transBoard;
}

int Board::getColor(const BitBoard bitBoard) const
{
	if (black & white & bitBoard) return ERROR;
	else if (bitBoard & black) return BLACK;
	else if (bitBoard & white) return WHITE;
	else return EMPTY;
}

int Board::countDisc(const int color) const
{
	return (color == BLACK ? bitCount(black) : bitCount(white));
}

int Board::countMobility(const int color) const
{
	return bitCount(makeMovableBoard(color));
}

