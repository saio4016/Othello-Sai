#include "sai.h"

#include "bits.h"
#include "const.h"
#include <iostream>
#include <algorithm>

Sai::Sai()
{
	presearch_depth = 3;
	normal_depth    = 8;
	perfect_depth   = 20; // åªíiäKÇ≈13éËÇ‹Ç≈çÇë¨

	evaluator = new PerfectEvaluator();
}

BitBoard Sai::search(Game game)
{
	std::vector<Move> moves = makeMoveArray(game.getNextMovable());

	sort(game, presearch_depth, moves);

	std::cout << "(p,e) = ";
	BitBoard best = NONE;
	int eval_max = -INF;
	int limit = (MAX_MOVE - game.getCurMoves() <= perfect_depth ? INF : normal_depth);
	for (auto move : moves) {
		game.move(move.put);
		move.score = -negaAlpha(game, limit - 1, -INF, INF);
		//move.score = -negaMax(game, limit - 1);
		game.undo();
		if (move.score > eval_max) {
			best = move.put;
			eval_max = move.score;
		}
		std::cout << "(" << game.toString(move.put) << "," << move.score << ")";
	}
	std::cout << std::endl;
	return best;
}

int Sai::negaMax(Game& game, int limit)
{
	// ê[Ç≥êßå¿
	if (game.isGameOver() || limit == 0) return evaluate(game);

	int score = -INF;
	BitBoard movableBoard = game.getNextMovable(), putBoard;
	if (movableBoard == NONE) {
		// ÉpÉXÇ≈Ç†ÇÈ
		game.pass();
		score = -negaMax(game, limit);
		game.undo();
	}
	else {
		// ÉpÉXÇ≈ÇÕÇ»Ç¢
		while (movableBoard != NONE) {
			putBoard = bitLsb(movableBoard);
			game.move(putBoard);
			score = std::max(score, -negaMax(game, limit - 1));
			game.undo();
			movableBoard &= ~putBoard;
		}
	}
	return score;
}

int Sai::negaAlpha(Game& game, int limit, int alpha, int beta)
{
	// ê[Ç≥êßå¿
	if (game.isGameOver() || limit == 0) return evaluate(game);

	int score;
	BitBoard movableBoard = game.getNextMovable(), putBoard;
	if (movableBoard == NONE) {
		// ÉpÉXÇ≈Ç†ÇÈ
		game.pass();
		score = -negaAlpha(game, limit, -beta, -alpha);
		game.undo();
		return score;
	}
	else {
		//if (limit > 0 && game.getCurMoves == MAX_MOVE - 1) // ç≈èIàÍéËìWäJ
		// ÉpÉXÇ≈ÇÕÇ»Ç¢
		while(movableBoard != NONE) {
			putBoard = bitLsb(movableBoard);
			game.move(putBoard);
			score = -negaAlpha(game, limit - 1, -beta, -alpha);
			game.undo();
			if (score >= beta) return score;
			if (score > alpha) alpha = score;
			movableBoard &= ~putBoard;
		}
	}
	return alpha;
}

void Sai::sort(Game& game, int limit, std::vector<Move>& moves)
{
	for (auto move : moves) {
		game.move(move.put);
		move.score = -negaAlpha(game, limit, -INF, INF);
		game.undo();
	}

	std::stable_sort(moves.begin(), moves.end(), [&](Move lhs, Move rhs) { return lhs.score < rhs.score; });
}


std::vector<Move> Sai::makeMoveArray(BitBoard movableBoard)
{
	std::vector<Move> moveArray;

	/*for (int i = 0; i < BOARD_SIZE; i++) {
		if ((1ull << i) & movableBoard) movableArray.push_back(1ull << i);
	}*/

	Move move;
	while (movableBoard != NONE) {
		move.put = bitMsb(movableBoard);
		moveArray.push_back(move);
		movableBoard &= ~move.put;
	}

	/*BitBoard bitBoard;
	int i = 0;
	while (movableBoard != NONE) {
		//std::cout << ++i << std::endl;
		bitBoard = bitLsbA(movableBoard);
		movableArray.push_back(bitBoard);
		movableBoard &= ~bitBoard;
	}*/

	return moveArray;
}

int Sai::evaluate(const Game& game)
{
	// éËî‘Ç©ÇÁå©ÇΩï]âø(ê‚ëŒìIï]âøÇ≈ÇÕÇ»Ç≠ëäëŒìIï]âø)
	return (game.getNextColor() == BLACK ? 1 : -1) * evaluator->evaluate(game.getBoard());
}
