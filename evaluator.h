#pragma once
#include "board.h"

class Evaluator
{
public:
	virtual int evaluate(const Board& board) = 0;
};

class PerfectEvaluator : public Evaluator
{
public:
	int evaluate(const Board& board);
};

class NormalEvaluator : public Evaluator
{
	int evaluate(const Board& board);
};

