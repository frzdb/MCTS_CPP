//
//  gomoku.cpp
//  MCTS_Gomoku
//
//  Created by 白竞帆 on 2021/11/17.
//

#include <iostream>
#include "gomoku.hpp"
#include <math.h>

using namespace std;

time_t getCurTime();

gomoku::gomoku(int len, int wid, int nw):length(len), width(wid), nRowToWin(nw){
    board = new int*[length];
    availables = length*length;
    for (int i = 0; i<length; i++) {
        board[i] = new int[length];
        for (int j = 0; j<length; j++) {
            board[i][j] = 0;
        }
    }
}

void gomoku::luoZi(int row, int col, int player){
    if (row<0 || row>width || col<0 ||col>length) {
        cout<<"超出落子范围"<<endl;
    }
    board[row][col] = player;
    availables--;
}

void gomoku::outputBoard(){
    for (int i = 0; i<length; i++) {
        if (i == 0) {
            cout<<"   ";
            for (int j = 0; j<length; j++){
                if (j == length-1) {
                    cout<<j;
                }else
                    cout<<j<<"      ";
            }
            cout<<endl;
        }
        cout<<i<<"  ";
        for (int j = 0; j<length; j++) {
            if (j == length-1) {
                if (board[i][j]<0) {
                    cout<<'O'<<endl<<endl;
                }else if(board[i][j] == 0){
                    cout<<'-'<<endl<<endl;
                }else{
                    cout<<'X'<<endl<<endl;
                }
            }else{
                if (board[i][j]<0) {
                    cout<<'O'<<"      ";
                }else if(board[i][j] == 0){
                    cout<<'-'<<"      ";
                }else{
                    cout<<'X'<<"      ";
                }
            }
            
        }
    }
}
void gomoku::outputBoard(int** board){
    for (int i = 0; i<length; i++) {
        if (i == 0) {
            cout<<"   ";
            for (int j = 0; j<length; j++){
                if (j == length-1) {
                    cout<<j;
                }else
                    cout<<j<<"      ";
            }
            cout<<endl;
        }
        cout<<i<<"  ";
        for (int j = 0; j<length; j++) {
            if (j == length-1) {
                if (board[i][j]<0) {
                    cout<<'O'<<endl<<endl;
                }else if(board[i][j] == 0){
                    cout<<'-'<<endl<<endl;
                }else{
                    cout<<'X'<<endl<<endl;
                }
            }else{
                if (board[i][j]<0) {
                    cout<<'O'<<"      ";
                }else if(board[i][j] == 0){
                    cout<<'-'<<"      ";
                }else{
                    cout<<'X'<<"      ";
                }
            }
            
        }
    }
}

bool gomoku::isBoardFull(){
    bool isFull = true;
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            if (board[i][j] == 0) {
                isFull = false;
            }
        }
    }
    return isFull;
}
bool gomoku::isBoardFull(int** board){
    bool isFull = true;
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            if (board[i][j] == 0) {
                isFull = false;
            }
        }
    }
    return isFull;
}

bool gomoku::isBoardEmpty(){
    bool isEmpty = true;
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            if (board[i][j] != 0) {
                isEmpty = false;
            }
        }
    }
    return isEmpty;
}
bool gomoku::isBoardEmpty(int** board){
    bool isEmpty = true;
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            if (board[i][j] != 0) {
                isEmpty = false;
            }
        }
    }
    return isEmpty;
}

int gomoku::isWinned(){  // 判断有没有五子连珠，需要判断4种情况，分别是横竖撇捺，故需要4次全循环;输出0则没人赢，输出nRowToWin(比如4、5)或-nRowToWin-1(比如-5、-6)则先手(电脑)赢，输出-nRowToWin(比如-4、-5)或nRowToWin+1(比如5、6)(玩家)则后手赢；输出其他的值(在-nRowToWin+1到nRowToWin-1之间)则无输赢.
    int isWin = 0;
    //行
    for (int i = 0; i<length; i++) {
        isWin = 0;
        for (int j = 0; j<length; j++) {
            if ((isWin*board[i][j])<0 || board[i][j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                isWin = 0;
            }
            isWin += board[i][j];
            if (((isWin == nRowToWin)&&(j==length-1))
                ||
                ((isWin == nRowToWin)&&(j<length-1)&&board[i][j+1]!=1)
                ||
                ((isWin == -(nRowToWin))&&(j < length-1)&&(board[i][j+1]==-1))) {
                return 1;
            }
            if (((isWin == -nRowToWin)&&(j==length-1))
                ||
                ((isWin == -nRowToWin)&&(j<length-1)&&board[i][j+1]!=-1)
                ||
                ((isWin == (nRowToWin))&&(j < length-1)&&(board[i][j+1]==1))) {
                return -1;
            }
            /*
             
             
            if (isWin == nRowToWin || isWin == -(nRowToWin+1)) {
                return 1;
            }else if(isWin == -nRowToWin || isWin == nRowToWin+1){
                return -1;
            }
             */
        }
    }
    //列
    for (int i = 0; i<length; i++) {
        isWin = 0;
        for (int j = 0; j<length; j++) {
            if ((isWin*board[j][i])<0 || board[j][i] == 0) {  //isWin和棋盘棋子异号的时候置为0
                isWin = 0;
            }
            isWin += board[j][i];
            if (((isWin == nRowToWin)&&(j==length-1))
                ||
                ((isWin == nRowToWin)&&(j<length-1)&&board[j+1][i]!=1)
                ||
                ((isWin == -(nRowToWin))&&(j < length-1)&&(board[i][j+1]==-1))) {
                return 1;
            }
            if (((isWin == -nRowToWin)&&(j==length-1))
                ||
                ((isWin == -nRowToWin)&&(j<length-1)&&board[j+1][i]!=-1)
                ||
                ((isWin == (nRowToWin))&&(j < length-1)&&(board[j+1][i]==1))) {
                return -1;
            }
            /*
            if (isWin == nRowToWin || isWin == -(nRowToWin+1)) {
                return 1;
            }else if(isWin == -nRowToWin || isWin == nRowToWin+1){
                return -1;
            }
             */
        }
    }
    //撇
    for (int i = 0; i<2*length-1; i++) {
        isWin = 0;
        if (i/(length-1) == 0) {
            for (int j = 0; j<=i; j++) {
                if ((isWin*board[j][i-j])<0 || board[j][i-j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[j][i-j];
                if (((isWin == nRowToWin)&&(i-j==0))
                    ||
                    ((isWin == nRowToWin)&&(i-j>0)&&board[j+1][i-j-1]!=1)
                    ||
                    ((isWin == -(nRowToWin))&&(i-j > 0)&&(board[j+1][i-j-1]==-1))) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&(i-j==0))
                    ||
                    ((isWin == -nRowToWin)&&(i-j>0)&&board[j+1][i-j-1]!=-1)
                    ||
                    ((isWin == (nRowToWin))&&(i-j > 0)&&(board[j+1][i-j-1]==1))) {
                    return -1;
                }
                /*
                if (isWin == nRowToWin || isWin == -(nRowToWin+1)) {
                    return 1;
                }else if(isWin == -nRowToWin || isWin == nRowToWin+1){
                    return -1;
                }
                 */
            }
        }else{
            for (int j = (length-1); j>=i-(length-1); j--) {
                if ((isWin*board[i-j][j])<0 || board[i-j][j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[i-j][j];
                if (((isWin == nRowToWin)&&(i-j==length-1))
                    ||
                    ((isWin == nRowToWin)&&(i-j<length-1)&&board[i-j+1][j-1]!=1)
                    ||
                    ((isWin == -(nRowToWin))&&(i-j<length-1)&&(board[i-j+1][j-1]==-1))
                    ) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&(i-j==length-1))
                    ||
                    ((isWin == -nRowToWin)&&(i-j<length-1)&&(board[i-j+1][j-1]!=-1))
                    ||
                    ((isWin == (nRowToWin))&&(i-j<length-1)&&(board[i-j+1][j-1]==1))) {
                    return -1;
                }
                /*
                if (isWin == nRowToWin || isWin == -(nRowToWin+1)) {
                    return 1;
                }else if(isWin == -nRowToWin || isWin == nRowToWin+1){
                    return -1;
                }
                 */
            }
        }
    }
    //捺
    for (int i = 0; i<2*length-1; i++) {
        isWin = 0;
        if (i/(length-1) == 0) {
            for (int j = 0; j<=i; j++) {
                if ((isWin*board[j][(length-1)-(i-j)])<0 || board[j][(length-1)-(i-j)] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                if (((isWin == nRowToWin)&&((length-1)-i+j == length-1))
                    ||
                    ((isWin == nRowToWin)&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]!=1))
                    ||
                    ((isWin == -(nRowToWin))&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]==-1))) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&((length-1)-i+j == length-1))
                    ||
                    ((isWin == -nRowToWin)&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]!=-1))
                    ||
                    ((isWin == (nRowToWin))&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]==1))) {
                    return -1;
                }
                /*
                isWin += board[j][6-(i-j)];
                if (isWin == nRowToWin || isWin == -(nRowToWin+1)) {
                    return 1;
                }else if(isWin == -nRowToWin || isWin == nRowToWin+1){
                    return -1;
                }
                 */
            }
        }else{
            for (int j = (length-1); j>=i-(length-1); j--) {
                if ((isWin*board[i-j][(length-1)-j])<0 || board[i-j][(length-1)-j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[i-j][(length-1)-j];
                if (((isWin == nRowToWin)&&(i-j == length-1))
                    ||
                    ((isWin == nRowToWin)&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]!=1))
                    ||
                    ((isWin == -(nRowToWin))&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]==-1))) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&(i-j == length-1))
                    ||
                    ((isWin == -nRowToWin)&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]!=-1))
                    ||
                    ((isWin == (nRowToWin))&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]==1))) {
                    return -1;
                }
                /*
                if (isWin == nRowToWin || isWin == -(nRowToWin+1)) {
                    return 1;
                }else if(isWin == -nRowToWin || isWin == nRowToWin+1){
                    return -1;
                }
                 */
            }
        }
    }
    
    return 0;
}
int gomoku::isWinned(int** board){  // 判断有没有五子连珠，需要判断4种情况，分别是横竖撇捺，故需要4次全循环;输出0则没人赢，输出nRowToWin(比如4、5)或-nRowToWin-1(比如-5、-6)则先手(电脑)赢，输出-nRowToWin(比如-4、-5)或nRowToWin+1(比如5、6)(玩家)则后手赢；输出其他的值(在-nRowToWin+1到nRowToWin-1之间)则无输赢.
    int isWin = 0;
    //行
    for (int i = 0; i<length; i++) {
        isWin = 0;
        for (int j = 0; j<length; j++) {
            if ((isWin*board[i][j])<0 || board[i][j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                isWin = 0;
            }
            isWin += board[i][j];
            if (((isWin == nRowToWin)&&(j==length-1))
                ||
                ((isWin == nRowToWin)&&(j<length-1)&&board[i][j+1]!=1)
                ||
                ((isWin == -(nRowToWin))&&(j < length-1)&&(board[i][j+1]==-1))) {
                return 1;
            }
            if (((isWin == -nRowToWin)&&(j==length-1))
                ||
                ((isWin == -nRowToWin)&&(j<length-1)&&board[i][j+1]!=-1)
                ||
                ((isWin == (nRowToWin))&&(j < length-1)&&(board[i][j+1]==1))) {
                return -1;
            }
        }
    }
    //列
    for (int i = 0; i<length; i++) {
        isWin = 0;
        for (int j = 0; j<length; j++) {
            if ((isWin*board[j][i])<0 || board[j][i] == 0) {  //isWin和棋盘棋子异号或有空位置的时候置为0
                isWin = 0;
            }
            isWin += board[j][i];
            if (((isWin == nRowToWin)&&(j==length-1))
                ||
                ((isWin == nRowToWin)&&(j<length-1)&&board[j+1][i]!=1)
                ||
                ((isWin == -(nRowToWin))&&(j < length-1)&&(board[i][j+1]==-1))) {
                return 1;
            }
            if (((isWin == -nRowToWin)&&(j==length-1))
                ||
                ((isWin == -nRowToWin)&&(j<length-1)&&board[j+1][i]!=-1)
                ||
                ((isWin == (nRowToWin))&&(j < length-1)&&(board[j+1][i]==1))) {
                return -1;
            }
        }
    }
    //撇
    for (int i = 0; i<2*length-1; i++) {
        isWin = 0;
        if (i/(length-1) == 0) {
            for (int j = 0; j<=i; j++) {
                if ((isWin*board[j][i-j])<0 || board[j][i-j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[j][i-j];
                if (((isWin == nRowToWin)&&(i-j==0))
                    ||
                    ((isWin == nRowToWin)&&(i-j>0)&&board[j+1][i-j-1]!=1)
                    ||
                    ((isWin == -(nRowToWin))&&(i-j > 0)&&(board[j+1][i-j-1]==-1))) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&(i-j==0))
                    ||
                    ((isWin == -nRowToWin)&&(i-j>0)&&board[j+1][i-j-1]!=-1)
                    ||
                    ((isWin == (nRowToWin))&&(i-j > 0)&&(board[j+1][i-j-1]==1))) {
                    return -1;
                }
            }
        }else{
            for (int j = (length-1); j>=i-(length-1); j--) {
                if ((isWin*board[i-j][j])<0 || board[i-j][j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[i-j][j];
                if (((isWin == nRowToWin)&&(i-j==length-1))
                    ||
                    ((isWin == nRowToWin)&&(i-j<length-1)&&board[i-j+1][j-1]!=1)
                    ||
                    ((isWin == -(nRowToWin))&&(i-j<length-1)&&(board[i-j+1][j-1]==-1))
                    ) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&(i-j==length-1))
                    ||
                    ((isWin == -nRowToWin)&&(i-j<length-1)&&(board[i-j+1][j-1]!=-1))
                    ||
                    ((isWin == (nRowToWin))&&(i-j<length-1)&&(board[i-j+1][j-1]==1))) {
                    return -1;
                }
            }
        }
    }
    //捺
    for (int i = 0; i<2*length-1; i++) {
        isWin = 0;
        if (i/(length-1) == 0) {
            for (int j = 0; j<=i; j++) {
                if ((isWin*board[j][(length-1)-(i-j)])<0 || board[j][(length-1)-(i-j)] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[j][(length-1)-(i-j)];
                if (((isWin == nRowToWin)&&((length-1)-i+j == length-1))
                    ||
                    ((isWin == nRowToWin)&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]!=1))
                    ||
                    ((isWin == -(nRowToWin))&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]==-1))) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&((length-1)-i+j == length-1))
                    ||
                    ((isWin == -nRowToWin)&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]!=-1))
                    ||
                    ((isWin == (nRowToWin))&&((length-1)-i+j < length-1)&&(board[j+1][(length-1)-i+j+1]==1))) {
                    return -1;
                }
            }
        }else{
            for (int j = (length-1); j>=i-(length-1); j--) {
                if ((isWin*board[i-j][(length-1)-j])<0 || board[i-j][(length-1)-j] == 0) {  //isWin和棋盘棋子异号的时候置为0
                    isWin = 0;
                }
                isWin += board[i-j][(length-1)-j];
                if (((isWin == nRowToWin)&&(i-j == length-1))
                    ||
                    ((isWin == nRowToWin)&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]!=1))
                    ||
                    ((isWin == -(nRowToWin))&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]==-1))) {
                    return 1;
                }
                if (((isWin == -nRowToWin)&&(i-j == length-1))
                    ||
                    ((isWin == -nRowToWin)&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]!=-1))
                    ||
                    ((isWin == (nRowToWin))&&(i-j<length-1)&&(board[i-j+1][(length-1)-j-1]==1))) {
                    return -1;
                }
            }
        }
    }
    
    return 0;
}
void gomoku::mcts(){
    BNTree bnt;
    bnt.initTree();
    srand(int(getCurTime()));
    cout<<"start the game"<<endl;
    time_t startTime = getCurTime();
    int limits = 0;
    current_player = 1;
    while (limits<4000
           //&& getCurTime()-startTime<3000
           ) {
        limits++;
        cout<<"第"<<limits<<"次迭代:"<<endl;
        int** tempBoard;
        tempBoard = new int*[length];
        for (int i = 0; i<length; i++) {
            tempBoard[i] = new int[length];
            for (int j = 0; j<length; j++) {
                tempBoard[i][j] = board[i][j];
            }
        }
        Location* lct = treePolicy(bnt.getRoot()->location, &bnt, tempBoard);
        cout<<"模拟的最大子结点为:("<<lct->getRow()<<","<<lct->getColomn()<<")"<<endl;
        int value = defaultPolicy(lct, tempBoard);
        cout<<"获得的value:"<<value<<endl;
        backup(lct, &bnt, value);
        //cout<<bnt.findNode(lct)->location->getValue()<<endl;
        //cout<<bnt.findNode(lct)->location->getVisitedTimes()<<endl;
        if(limits%2000 == 0){
            cout<<"---------------"<<endl;
            bnt.outputValue();
            cout<<"---------------"<<endl;
        }
    }
    //bnt.output();
    Location* bestChildNode = bestChild(bnt.getRoot()->location, &bnt, nullptr);
    luoZi(bestChildNode->getRow(), bestChildNode->getColomn(), 1);
    cout<<"("<<bestChildNode->getRow()<<","<<bestChildNode->getColomn()<<")"<<endl;
    outputBoard();
    cout<<"the end"<<endl;
}

Location* gomoku::treePolicy(Location* lct, BNTree* bnt, int** tempBoard){
    //int **tempBoard = board;
    current_player = 1;
    bool isw;
    while (!(isw = isWinned(tempBoard))) {
        //if (!isFullyExpanded(lct, bnt)) {
        if (!isFullyExpandedTwo(lct, bnt, tempBoard)) {
            cout<<"还没有完全展开"<<endl;
            //return expand(lct, bnt);
            return expandTwo(lct, bnt, tempBoard);
        }else{
            cout<<"已经完全展开"<<endl;
            lct = bestChild(lct, bnt, tempBoard);
            cout<<"起始落子位置:("<<lct->getRow()<<","<<lct->getColomn()<<")"<<endl;
            //return bestChild(lct, bnt);
            tempBoard[lct->getRow()][lct->getColomn()] = current_player;
            if (isWinned(tempBoard) != 0) {
                            break;
            }
            current_player = (current_player==1?-1:1);
            
            Node* temp = bnt->findNode(lct);
            /*
             
             
            if (!(temp->firstChild)) {
                continue;
            }else{
                break;
            }
            */
        }
    }
    return lct;
}
Location* gomoku::expand(Location* lct, BNTree* bnt){
    // 这里有一个小变化，因为之前的expand为按顺序添加，可能排位靠前的结点访问次数较多，故采用随机方式
    Node* temp = bnt->findNode(lct);
    Node* lastSubNode = temp->firstChild;
    //lastSubNode->parent = temp;
    for (int i = 0; i<temp->childsCount-1; i++) {
        lastSubNode = lastSubNode->sibling;
    }
    Node* returnNode = lastSubNode;
    /*
     
    
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            //这里拓展的时候不只把已经落子的位置排除掉，应该把在此结点之上的父结点包括本结点的都排除掉
            bool isExisted = false;
            lastSubNode = returnNode;  // 每次循环都从最后一个子结点开始往父节点循环
            if (board[i][j]!=0) {
                continue;
            }
            if(!returnNode){
                lastSubNode = temp;
                while (lastSubNode) {
                    if (lastSubNode->location->equals(Location(i, j))) {
                        isExisted = true;
                    }
                    lastSubNode = bnt->getRealParentNode(lastSubNode->location);
                }
            }
            lastSubNode = returnNode;
            if (isExisted) {
                continue;
            }
            if (!lastSubNode){
                bnt->insertNode(temp->location, Location(i, j));
                cout<<"拓展的结点:("<<temp->firstChild->location->getRow()<<","<<temp->firstChild->location->getColomn()<<")"<<endl;
                return temp->firstChild->location;
            }
            while (lastSubNode && lastSubNode != temp) {
                // 先把结点
                if (lastSubNode->location->equals(Location(i, j))) {
                    isExisted = true;
                    break;
                }
                lastSubNode = lastSubNode->parent;
            }
            while (lastSubNode && lastSubNode != bnt->getRoot()) {
                // 先把结点
                if (lastSubNode->location->equals(Location(i, j))) {
                    isExisted = true;
                    break;
                }
                lastSubNode = bnt->getRealParentNode(lastSubNode->location);
            }
            if (isExisted) {
                continue;
            }
            lastSubNode = returnNode;
            bnt->insertNode(temp->location, Location(i, j));
            returnNode = returnNode->sibling;
            cout<<"拓展的结点:("<<returnNode->location->getRow()<<","<<returnNode->location->getColomn()<<")"<<endl;
            return returnNode->location;
        }
    }
     */
    
    while (true) {
        int i = rand() % length;
        int j = rand() % length;
        bool isExisted = false;
        lastSubNode = returnNode;  // 每次循环都从最后一个子结点开始往父节点循环
        if (board[i][j]!=0) {
            continue;
        }
        if(!returnNode){
            lastSubNode = temp;
            while (lastSubNode) {
                if (lastSubNode->location->equals(Location(i, j))) {
                    isExisted = true;
                }
                lastSubNode = bnt->getRealParentNode(lastSubNode->location);
            }
        }
        lastSubNode = returnNode;
        if (isExisted) {
            continue;
        }
        if (!lastSubNode){
            bnt->insertNode(temp->location, Location(i, j));
            cout<<"拓展的结点:("<<temp->firstChild->location->getRow()<<","<<temp->firstChild->location->getColomn()<<")"<<endl;
            return temp->firstChild->location;
        }
        while (lastSubNode && lastSubNode != temp) {
            // 先把结点
            if (lastSubNode->location->equals(Location(i, j))) {
                isExisted = true;
                break;
            }
            lastSubNode = lastSubNode->parent;
        }
        while (lastSubNode && lastSubNode != bnt->getRoot()) {
            // 先把结点
            if (lastSubNode->location->equals(Location(i, j))) {
                isExisted = true;
                break;
            }
            lastSubNode = bnt->getRealParentNode(lastSubNode->location);
        }
        if (isExisted) {
            continue;
        }
        lastSubNode = returnNode;
        bnt->insertNode(temp->location, Location(i, j));
        returnNode = returnNode->sibling;
        cout<<"拓展的结点:("<<returnNode->location->getRow()<<","<<returnNode->location->getColomn()<<")"<<endl;
        return returnNode->location;
    }
    
    
    return bnt->findNode(lct)->firstChild->location;
}

Location* gomoku::expandTwo(Location* lct, BNTree* bnt, int** tempBoard){
    // 这里有一个小变化，因为之前的expand为按顺序添加，可能排位靠前的结点访问次数较多，故采用随机方式
    Node* temp = bnt->findNode(lct);
    Node* lastSubNode = temp->firstChild;
    //lastSubNode->parent = temp;
    for (int i = 0; i<temp->childsCount-1; i++) {
        lastSubNode = lastSubNode->sibling;
    }
    Node* returnNode = lastSubNode;
    /*
     
    
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            //这里拓展的时候不只把已经落子的位置排除掉，应该把在此结点之上的父结点包括本结点的都排除掉
            bool isExisted = false;
            lastSubNode = returnNode;  // 每次循环都从最后一个子结点开始往父节点循环
            if (board[i][j]!=0) {
                continue;
            }
            if(!returnNode){
                lastSubNode = temp;
                while (lastSubNode) {
                    if (lastSubNode->location->equals(Location(i, j))) {
                        isExisted = true;
                    }
                    lastSubNode = bnt->getRealParentNode(lastSubNode->location);
                }
            }
            lastSubNode = returnNode;
            if (isExisted) {
                continue;
            }
            if (!lastSubNode){
                bnt->insertNode(temp->location, Location(i, j));
                cout<<"拓展的结点:("<<temp->firstChild->location->getRow()<<","<<temp->firstChild->location->getColomn()<<")"<<endl;
                return temp->firstChild->location;
            }
            while (lastSubNode && lastSubNode != temp) {
                // 先把结点
                if (lastSubNode->location->equals(Location(i, j))) {
                    isExisted = true;
                    break;
                }
                lastSubNode = lastSubNode->parent;
            }
            while (lastSubNode && lastSubNode != bnt->getRoot()) {
                // 先把结点
                if (lastSubNode->location->equals(Location(i, j))) {
                    isExisted = true;
                    break;
                }
                lastSubNode = bnt->getRealParentNode(lastSubNode->location);
            }
            if (isExisted) {
                continue;
            }
            lastSubNode = returnNode;
            bnt->insertNode(temp->location, Location(i, j));
            returnNode = returnNode->sibling;
            cout<<"拓展的结点:("<<returnNode->location->getRow()<<","<<returnNode->location->getColomn()<<")"<<endl;
            return returnNode->location;
        }
    }
     */
    
    bool ibe = isBoardEmpty(tempBoard);
    int** availableBoard;  // 记录1为可落子的位置，0不可以落子;如果整个棋盘没有落子，则所有位置都可以落子
    availableBoard = new int*[length];
    for (int i = 0; i<length; i++){
        availableBoard[i] = new int[length];
        for (int j = 0; j<length; j++){
            availableBoard[i][j] = 0;
        }
    }
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<length; j++) {
            if (ibe) {
                availableBoard[i][j] = 1;
                continue;
            }
            //availableBoard[i][j] = 0;
            if (tempBoard[i][j] != 0) {
                for (int k1 = -2; k1<3; k1++) {
                    for (int k2 = -2; k2<3; k2++) {
                        if ((i+k1<0) || (j+k2<0) || i+k1>=length || j+k2>=length) {
                            continue;
                        }
                        if (tempBoard[i+k1][j+k2] != 0) {
                            availableBoard[i+k1][j+k2] = 0;
                        }else{
                            availableBoard[i+k1][j+k2] = 1;
                        }
                    }
                }
            }
        }
    }
    //outputBoard(availableBoard);
    
    while (true) {
        int i = rand() % length;
        int j = rand() % length;
        bool isExisted = false;
        lastSubNode = returnNode;  // 每次循环都从最后一个子结点开始往父节点循环
        //if (board[i][j]!=0) {
        if (availableBoard[i][j]==0) {
            continue;
        }
        if(!returnNode){
            lastSubNode = temp;
            while (lastSubNode) {
                if (lastSubNode->location->equals(Location(i, j))) {
                    isExisted = true;
                }
                lastSubNode = bnt->getRealParentNode(lastSubNode->location);
            }
        }
        lastSubNode = returnNode;
        if (isExisted) {
            continue;
        }
        if (!lastSubNode){
            bnt->insertNode(temp->location, Location(i, j));
            cout<<"拓展的结点:("<<temp->firstChild->location->getRow()<<","<<temp->firstChild->location->getColomn()<<")"<<endl;
            return temp->firstChild->location;
        }
        while (lastSubNode && lastSubNode != temp) {
            // 先把结点
            if (lastSubNode->location->equals(Location(i, j))) {
                isExisted = true;
                break;
            }
            lastSubNode = lastSubNode->parent;
        }
        while (lastSubNode && lastSubNode != bnt->getRoot()) {
            // 先把结点
            if (lastSubNode->location->equals(Location(i, j))) {
                isExisted = true;
                break;
            }
            lastSubNode = bnt->getRealParentNode(lastSubNode->location);
        }
        if (isExisted) {
            continue;
        }
        lastSubNode = returnNode;
        bnt->insertNode(temp->location, Location(i, j));
        returnNode = returnNode->sibling;
        cout<<"拓展的结点:("<<returnNode->location->getRow()<<","<<returnNode->location->getColomn()<<")"<<endl;
        return returnNode->location;
    }
    
    
    return bnt->findNode(lct)->firstChild->location;
}

Location* gomoku::bestChild(Location* lct, BNTree* bnt, int** tempBoard){
    // 如果我们在最后MCTS算法结束后，根据得到的结果筛选的时候只选择胜率最高的那个(tempBoard为空的时候)
    Node* tempParent = bnt->findNode(lct);
    Node* temp = tempParent->firstChild;
    double maxMCTSValue = -1.0;
    Location* returnLocation;
    while (true) {
        Location *curLocation = temp->location;
        double curValue = curLocation->getValue();
        double pVisitedTimes = (double)bnt->getRealParentNode(curLocation) ->location->getVisitedTimes();
        double curVisitedTimes = curLocation->getVisitedTimes();
        if (curVisitedTimes == 0) {
            return curLocation;
        }
        int tempRow, tempCol;
        if (!tempBoard) {
            if (maxMCTSValue< curValue/curVisitedTimes) {
                maxMCTSValue = curValue/curVisitedTimes;
                returnLocation = curLocation;
            }
        }else{
            tempRow = tempParent->location->getRow();
            tempCol = tempParent->location->getColomn();
            if (tempParent == bnt->getRoot() ||  tempBoard[tempRow][tempCol] == -1) {
                if (maxMCTSValue<getMCTSValue(curValue, curVisitedTimes, pVisitedTimes)) {
                    maxMCTSValue = getMCTSValue(curValue, curVisitedTimes, pVisitedTimes);
                    returnLocation = curLocation;
                }
            }else if(tempBoard[tempRow][tempCol] == 1){
                if (maxMCTSValue<getMCTSValue(curVisitedTimes-curValue, curVisitedTimes, pVisitedTimes)) {
                    maxMCTSValue = getMCTSValue(curVisitedTimes-curValue, curVisitedTimes, pVisitedTimes);
                    returnLocation = curLocation;
                }
            }
        }
        
        if (temp->sibling) {
            temp = temp->sibling;
            continue;
        }else{
            break;
        }
    }
    return returnLocation;
}

int gomoku::defaultPolicy(Location* location, int** tempBoard){
    int randRow, randCol;
    randRow = location->getRow();
    randCol = location->getColomn();
    int tempCurrent_player = current_player;  //这里记录一下curplayer,返回的时候curplayer应该与进入函数时不变
    tempBoard[randRow][randCol] = current_player;  //把当前状态下第一步棋下了
    //tempBoard[randRow][randCol] = 1;  //把当前状态下第一步棋下了
    current_player = (current_player == 1?-1:1);
    //tempBoard[3][3] = 1;  //把预设的电脑的第一步棋下了
    //current_player = -1; // 现在该模拟玩家下棋了
    int randSeed = (int)getCurTime();
    //srand(randSeed);
    while (isWinned(tempBoard) == 0 && !isBoardFull(tempBoard)) {
        randRow = rand()%length;
        randCol = rand()%length;
        if (tempBoard[randRow][randCol] == 0) {
            tempBoard[randRow][randCol] = current_player;
            current_player = (current_player == 1?-1:1);
            //outputBoard(tempBoard);
            //cout<<"落子位置:("<<randRow<<","<<randCol<<")"<<endl;
        }
    }
    current_player = tempCurrent_player;
    //outputBoard(tempBoard);
    
    return (isWinned(tempBoard) == 1) ? 1 : 0;
    //return isWinned(tempBoard);
}
void gomoku::backup(Elemtype* location, BNTree* bnt, int value){
    Node* temp = bnt->findNode(location);
    while (temp) {
        temp->location->increaseValue(value);
        temp->location->increaseVisitedTimes(1);
        temp = bnt->getRealParentNode(temp->location);
    }
}


double gomoku::getMCTSValue(double sonValue, double sonVisitedTimes, double pVisitedTimes){
    return sonValue/sonVisitedTimes+2*(sqrt((log(pVisitedTimes)/sonVisitedTimes)));
}
bool gomoku::isFullyExpanded(Elemtype* location, BNTree* bnt){
    //这里看树是否完全展开，需要注意的是在此结点之上的父节点都是一个结点
    int counts = 0;
    Node* temp = bnt->findNode(location);
    Node* parent = bnt->getRealParentNode(location);
    if (!parent) { // 当前结点为父节点，则父节点的父节点为空
        if (temp->childsCount == availables) {
            return true;
        }else{
            return false;
        }
    }
    counts += temp->childsCount;
    //parent = bnt->getRealParentNode(parent->location);
    parent = temp;
    while (parent = bnt->getRealParentNode(parent->location)) {
        counts++;
    }
    if (counts == availables) {
        return true;
    }else{
        return false;
    }
}
bool gomoku::isFullyExpandedTwo(Elemtype* location, BNTree* bnt, int** tempBoard){
    
    int availablesCounts = 0;
    bool ibe = isBoardEmpty(tempBoard);
    
    int** availableBoard;  // 记录1为可落子的位置，0不可以落子;如果整个棋盘没有落子，则所有位置都可以落子
    availableBoard = new int*[length];
    for (int i = 0; i<length; i++){
        availableBoard[i] = new int[length];
        for (int j = 0; j<length; j++){
            availableBoard[i][j] = 0;
        }
    }
    
    if (ibe) {
        availablesCounts = length*length;
    }else{
        for (int i = 0; i<length; i++) {
                for (int j = 0; j<length; j++) {
                    if (ibe) {
                        continue;
                    }
                    //availableBoard[i][j] = 0;
                    if (tempBoard[i][j] != 0) {
                        for (int k1 = -2; k1<3; k1++) {
                            for (int k2 = -2; k2<3; k2++) {
                                if ((i+k1<0) || (j+k2<0) || i+k1>=length || j+k2>=length) {
                                    continue;
                                }
                                if (tempBoard[i+k1][j+k2] != 0) {
                                    availableBoard[i+k1][j+k2] = 0;
                                }else{
                                    if (availableBoard[i+k1][j+k2] == 0) {
                                        availableBoard[i+k1][j+k2] = 1;
                                        availablesCounts++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
    }
    
    
    cout<<"展开的个数为:"<<availablesCounts<<endl;
    //这里看树是否完全展开，需要注意的是在此结点之上的父节点都是一个结点
    int counts = 0;
    Node* temp = bnt->findNode(location);
    Node* parent = bnt->getRealParentNode(location);
    if (!parent) { // 当前结点为父节点，则父节点的父节点为空
        if (temp->childsCount == availablesCounts) {
            return true;
        }else{
            return false;
        }
    }
    counts += temp->childsCount;
    //parent = bnt->getRealParentNode(parent->location);
    parent = temp;
    while (parent = bnt->getRealParentNode(parent->location)) {
        counts++;
    }
    if (counts == availablesCounts) {
        return true;
    }else{
        return false;
    }
}
time_t getCurTime(){
    // 获取操作系统当前时间点（精确到微秒）
    chrono::time_point<chrono::system_clock, chrono::milliseconds> tpMicro
    = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    // (微秒精度的)时间点 => (微秒精度的)时间戳
    time_t totalMillSeconds = tpMicro.time_since_epoch().count();
    
    return totalMillSeconds;
}
