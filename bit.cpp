#include "bits.h"
#include "const.h"

int bitCountA(BitBoard bitBoard)
{
	int cnt = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if ((1ull << i) & bitBoard) cnt++;
	}
	return cnt;
}

int bitCountB(BitBoard bitBoard)
{
	BitBoard bits = bitBoard;
	bits = ((bits & 0xaaaaaaaaaaaaaaaa) >> 1) + (bits & 0x5555555555555555);
	bits = ((bits & 0xcccccccccccccccc) >> 2) + (bits & 0x3333333333333333);
	bits = ((bits & 0xf0f0f0f0f0f0f0f0) >> 4) + (bits & 0x0f0f0f0f0f0f0f0f);
	bits = ((bits & 0xff00ff00ff00ff00) >> 8) + (bits & 0x00ff00ff00ff00ff);
	bits = ((bits & 0xffff0000ffff0000) >> 16) + (bits & 0x0000ffff0000ffff);
	bits = ((bits & 0xffffffff00000000) >> 32) + (bits & 0x00000000ffffffff);
	return (int)bits;
}

int bitCountC(BitBoard bitBoard)
{
	BitBoard bits = bitBoard - 
		((bitBoard >> 1) & 0x7777777777777777ull) -
		((bitBoard >> 2) & 0x3333333333333333ull) -
		((bitBoard >> 3) & 0x1111111111111111ull);
	bits = ((bits + (bits >> 4)) & 0x0f0f0f0f0f0f0f0full) * 0x0101010101010101ull;
	return (int)(bits >> 56);
}

BitBoard bitMsbA(BitBoard b)
{
	b |= (b >> 1);
	b |= (b >> 2);
	b |= (b >> 4);
	b |= (b >> 8);
	b |= (b >> 16);
	b |= (b >> 32);
	return b ^ (b >> 1);
}

BitBoard bitLsbA(BitBoard b)
{
	// b & (-b) ‚Í•„†‚È‚µ®”‚Å‚ÍŽg‚¦‚È‚¢
	b ^= (b - 1);
	return b ^ (b >> 1);
}

/*BitBoard transfer(int dir, BitBoard bitBoard)
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
}*/