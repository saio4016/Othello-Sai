// Othello.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "game.h"
#include "sai.h"
#include "bench.h"

void printBoard(const Game&);

int main()
{
	Game game;
	Sai sai;
	Bench bench;

	bool flag = true;
	while (flag) {
		// 出力
		std::printf("\n"); printBoard(game);
		std::printf("      Moves: %d,", game.getCurMoves() + 1);
		std::printf(" Turn: % s\n", (game.getNextColor() == BLACK ? "○" : "●"));
		std::printf("(Undo:u, Redo:r, New:n, Exit:e)\n");

		// パス
		if (game.isPass()) {
			game.pass();
			std::printf("Pass\n");
			continue;
		}

		// 入力
		std::string in;
		while (true) {
			std::printf("--> ");
			std::cin >> in;
			// xを入力することでベンチマークテスト
			if (in == "x") {
				bench.start();
				sai.search(game);
				bench.end();
				continue;
			}
			// その他の操作
			else if (in == "n") game.init();  // 新規
			else if (in == "e") flag = false; // 終了
			else if (in == "u") if (game.isUndo()) game.undo(); else continue; // 戻る
			else if (in == "r") if (game.isRedo()) game.redo(); else continue; // 進む
			else if(!game.move(in)) continue; // 石を置く
			break;
		}

		// 終局
		if (game.isGameOver()) {
			int black = game.countDisc(BLACK);
			int white = game.countDisc(WHITE);
			std::printf("\n"); printBoard(game);
			std::printf("\t(○,●) = (%d,%d)\n", black, white);
			if (black == white) std::printf("\t    Draw.\n");
			else std::printf("\t   %s Win.\n", (black > white ? "Black" : "White"));
			flag = false;
		}
	}

	return 0;
}

// 盤面表示
void printBoard(const Game& game)
{
	int color;
	std::printf("   ");
	for (int x = 0; x < 8; x++) std::printf("%2c ", 'a' + x); // The horizontal axis.
	std::printf("\n   ");
	for (int x = 0; x < 8; x++) printf("+--");
	std::printf("+\n");
	for (int y = 0; y < 8; y++) {
		std::printf("%2d ", y + 1); // The vertical axis.
		for (int x = 0; x < 8; x++) {
			color = game.getStat(x, y);
			switch (color) {
			case EMPTY:
				std::printf("|　");
				break;
			case BLACK:
				std::printf("|○");
				break;
			case WHITE:
				std::printf("|●");
				break;
			case MOVABLE:
				std::printf("|・");
				break;
			default:
				std::printf("|×");
				break;
			}
		}
		std::printf("|\n   ");
		for (int x = 0; x < 8; x++) printf("+--");
		std::printf("+\n");
	}
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
