#include "evaluator.h"
#include "const.h"

int PerfectEvaluator::evaluate(const Board& board)
{
	return board.countDisc(BLACK) - board.countDisc(WHITE);
}

int NormalEvaluator::evaluate(const Board& board)
{
	// ���_�e�[�u��
	int table[] = {
		200, -50,-20,-20,-20,-20, -50,200,
		-50,-100,-10,-10,-10,-10,-100,-50,
		-20, -10, -5, -5, -5, -5, -10,-20,
		-20, -10, -5,  0,  0, -5, -10,-20,
		-20, -10, -5,  0,  0, -5, -10,-20,
		-20, -10, -5, -5, -5, -5, -10,-20,
		-50,-100,-10,-10,-10,-10,-100,-50,
		200, -50,-20,-20,-20,-20, -50,200
	};

	// �]���l�v�Z
	int score = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (board.getColor(1ull << i) == BLACK) score += table[i];
		if (board.getColor(1ull << i) == WHITE) score -= table[i];
	}
	score += (board.countMobility(BLACK) - board.countMobility(WHITE)) * 30;
	return score;
}
