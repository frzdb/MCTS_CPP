//
//  gomoku.hpp
//  MCTS_Gomoku
//
//  Created by 白竞帆 on 2021/11/17.
//

#ifndef gomoku_hpp
#define gomoku_hpp

#include <stdio.h>
#include "BNTree.hpp"

class gomoku{
private:
    int length;
    int width;
    int **board;  //board代表键盘，表示当前下棋的状态
    int current_player;  //-1指玩家, 1指电脑, 0默认
    int nRowToWin;  //几子连珠为赢
    int availables;
public:
    gomoku(int len, int wid, int nw);
    void luoZi(int row, int col, int player);
    void mcts();
    Location* treePolicy(Location* lct, BNTree* bnt, int** tempBoard);
    Location* expand(Location* lct, BNTree* bnt);
    Location* expandTwo(Location* lct, BNTree* bnt, int** tempBoard);  // 这里只拓展两格，减少子树搜索时间
    Location* bestChild(Location* lct, BNTree* bnt, int** tempBoard);
    int defaultPolicy(Location* location, int** tempBoard);
    void backup(Elemtype* location, BNTree* bnt, int value);
    //bool isTerminal(Elemtype* location, BNTree* bnt);
    void outputBoard();
    void outputBoard(int** board);
    bool isBoardFull();
    bool isBoardFull(int** board);
    bool isBoardEmpty();
    bool isBoardEmpty(int** board);
    bool isFullyExpanded(Elemtype* location, BNTree* bnt);
    bool isFullyExpandedTwo(Elemtype* location, BNTree* bnt, int** tempBoard);  
    int isWinned();  // 输出0则无输赢，输出1则先手电脑赢，输出-1则后手玩家赢
    int isWinned(int** board);
    double getMCTSValue(double sonValue, double sonVisitedTimes, double pVisitedTimes);
};

#endif /* gomoku_hpp */
