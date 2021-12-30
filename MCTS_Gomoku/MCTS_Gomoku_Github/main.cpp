//
//  main.cpp
//  MCTS_Gomoku
//
//  Created by 白竞帆 on 2021/11/12.
//

#include <iostream>
#include "gomoku.hpp"
#include "BNTree.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    gomoku gmk(9, 9, 5);
    /*
    gmk.luoZi(4, 4, -1);
    gmk.luoZi(5, 5, 1);
    gmk.luoZi(5, 3, -1);
    gmk.luoZi(4, 5, 1);
    gmk.luoZi(3, 5, -1);
    gmk.luoZi(6, 2, 1);
    gmk.luoZi(2, 6, -1);
    gmk.luoZi(1, 7, 1);
    gmk.luoZi(2, 3, -1);
    gmk.luoZi(6, 5, 1);
    gmk.luoZi(3, 3, -1);
    gmk.luoZi(8, 5, 1);
    gmk.luoZi(7, 5, -1);
    gmk.luoZi(6, 3, 1);
    gmk.luoZi(4, 3, -1);
     */
    gmk.luoZi(4, 4, -1);
    gmk.luoZi(3, 5, 1);
    gmk.luoZi(3, 3, -1);
    gmk.luoZi(5, 5, 1);
    gmk.luoZi(4, 3, -1);
    gmk.luoZi(3, 6, 1);
    gmk.luoZi(4, 2, -1);
    gmk.luoZi(4, 5, 1);
    gmk.luoZi(2, 5, -1);
    gmk.luoZi(6, 4, 1);
    gmk.luoZi(4, 1, -1);
    gmk.luoZi(4, 0, 1);
    gmk.luoZi(5, 1, -1);
    gmk.luoZi(6, 5, 1);
    gmk.luoZi(7, 5, -1);
    
    gmk.mcts();
    
    
    return 0;
}
