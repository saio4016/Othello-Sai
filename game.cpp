#include "game.h"

#include "bits.h"

Game::Game()
{
	init();
	//    f5d6c3d3c4f4f6f3e6e7d7g6f8f7g5h6h4g4h3h5h7c5b4e8d8b5e3c8b8c6a5d2b6c7b3f2c2a6d1a4e2g3f1g2a3a2g8c1e1b2a1b1a7b7h2h1g1h8a8g7
	load("f5d6c3d3c4f4f6f3e6e7d7g6f8f7g5h6h4g4h3h5h7c5b4e8d8b5e3c8b8c6a5d2b6c7b3f2c2a6d1a4e2g3f1g2a3a2g8c1e1b2a1b1a7b7h2h1g1");
}

void Game::init()
{
	board.init();
	nextColor = BLACK;
	curMoves  = 0;
	curPasses = 0;
	sumMoves  = 0;
	sumPasses = 0;

	for (int i = 0; i < MAX_TURN; i++) {
		moveLog[i].score = 0;
		moveLog[i].put   = 0;
		moveLog[i].flip  = 0;
	}
}

bool Game::move(std::string in)
{
	return move(toBitBoard(in));
}

bool Game::move(BitBoard putBoard)
{
	// 指定の箇所に石を置けるか
	BitBoard movableBoard = board.makeMovableBoard(nextColor);
	if (!(putBoard & movableBoard)) return false; // 置けなかった

	// 盤面の更新+ログに追加
	Move moved;
	moved.put = putBoard;
	moved.flip = board.makeFlipBoard(nextColor, putBoard);
	board.update(nextColor, moved);
	moveLog[curMoves + curPasses] = moved;
	// その他の更新
	sumMoves = ++curMoves;
	changeTurn();
	return true; // 置けた
}

void Game::pass()
{
	if (!isPass()) return; // パスできない

	moveLog[curMoves + curPasses].put  = NONE;
	moveLog[curMoves + curPasses].flip = NONE;
	sumPasses = ++curPasses;
	changeTurn();
}

void Game::undo()
{
	if (!isUndo()) return; // 戻れない

	(moveLog[curMoves + curPasses - 1].put != NONE ? --curMoves : --curPasses);
	changeTurn();

	board.update(nextColor, moveLog[curMoves + curPasses]);	
}

void Game::redo()
{
	if (!isRedo()) return; // 進めない

	board.update(nextColor, moveLog[curMoves + curPasses]);

	(moveLog[curMoves + curPasses].put != NONE ? ++curMoves : ++curPasses);
	changeTurn();
}

bool Game::isPass() const
{
	return (board.makeMovableBoard(nextColor) == NONE) && 
		   (board.makeMovableBoard((nextColor == BLACK ? WHITE : BLACK)) != NONE);
}

bool Game::isGameOver() const
{
	return (board.makeMovableBoard(BLACK) == NONE) &&
		   (board.makeMovableBoard(WHITE) == NONE);
}

bool Game::isUndo() const
{
	return (curMoves + curPasses > 0);
}

bool Game::isRedo() const
{
	return (curMoves + curPasses < sumMoves + sumPasses);
}

void Game::changeTurn()
{
	nextColor = (nextColor == BLACK ? WHITE : BLACK);
}

int Game::getNextColor() const
{
	return nextColor;
}

int Game::getCurMoves() const
{
	return curMoves;
}

int Game::getStat(int x, int y) const
{
	return getStat(toBitBoard(x, y));
}

int Game::getStat(BitBoard bitBoard) const
{
	if (bitBoard & board.makeMovableBoard(nextColor)) return MOVABLE;
	else return board.getColor(bitBoard);
}

int Game::countDisc(int color) const
{
	return board.countDisc(color);
}

BitBoard Game::getNextMovable() const
{
	return board.makeMovableBoard(nextColor);
}

Board Game::getBoard() const
{
	return board;
}

BitBoard Game::toBitBoard(std::string str) const
{
	BitBoard bitBoard = NONE;
	if (str.size() == 2) {
		int num = (str[0] - 'a') + (str[1] - '1') * 8;
		if (0 <= num && num < 64) bitBoard |= (1uLL << num);
	}
	return bitBoard;
}

BitBoard Game::toBitBoard(int x, int y) const
{
	BitBoard bitBoard = NONE;
	int num = x + y * 8;
	if (0 <= num && num < 64) bitBoard |= (1uLL << num);
	return bitBoard;
}

std::string Game::toString(BitBoard bitBoard) const
{
	std::string str1,str2;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (bitBoard & (1ull << i)) {
			str1 = char((i%8)+'a');
			str2 = char((i/8)+'1');
		}
	}
	return str1 + str2;
}

void Game::load(std::string record)
{
	for (int i = 0; i < record.size(); i += 2) {
		move(record.substr(i, 2));
	}
}
