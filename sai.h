#pragma once
#include <vector>
#include "game.h"
#include "bitboard.h"
#include "evaluator.h"

class Sai
{
private:
	int presearch_depth;
	int normal_depth;
	int perfect_depth;

	Evaluator *evaluator;

public:
	Sai();
	BitBoard search(Game game);

	int negaMax(Game& game, int limit);
	int negaAlpha(Game& game, int limit, int alpha, int beta);
	//int negaScout(Game& game, int limit, int alpha, int beta);
	//int iddfs(Game& game, int limit, int alpha, int beta); // ƒnƒbƒVƒ…ŽÀ‘•Œã
	void sort(Game& game, int limit, std::vector<Move>& moves);

	std::vector<Move> makeMoveArray(BitBoard movableBoard);

	int evaluate(const Game& game);
};

