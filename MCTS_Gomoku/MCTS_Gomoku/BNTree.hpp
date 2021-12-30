//
//  BNTree.hpp
//  MCTS_Gomoku
//
//  Created by 白竞帆 on 2021/11/22.
//

#ifndef BNTree_hpp
#define BNTree_hpp

#include <stdio.h>

#include <stdio.h>

class Location;
typedef Location Elemtype;

class Location{
private:
    int row;
    int colomn;
    int value;
    int visitedTimes;
public:
    Location(int row, int colomn);
    ~Location();
    int getRow();
    int getColomn();
    int getValue();
    int getVisitedTimes();
    bool equals(Location lct);  // 这个是表示数值相等
    bool equalsAddress(Location* lct);  // 这个是位置相等
    void setRow(int value);
    void setCol(int value);
    void setValue(int value);
    void increaseValue(int value);
    void setVisitedTimes(int visitedTimes);
    void increaseVisitedTimes(int visitedTimes);
};

typedef struct Node{
    Elemtype* location;
    int childsCount;
    struct Node *firstChild, *sibling, *parent;
}Node, *PNode, RootNode;



class BNTree{
private:
    Node* root;
    int depth;
public:
    void initTree();
    ~BNTree();
    int getDepth();
    void output();
    void outputValue();
    bool isEmpty();
    bool insertNode(Elemtype parentLocation, Elemtype location);  //增
    bool insertNode(Elemtype* parentLocation, Elemtype location);  //增
    bool insertNode(Elemtype* parentLocation, Elemtype* location);  //增
    bool deleteNode(Elemtype location);  //删
    bool deleteNode(Elemtype* location);  //删
    void freeWholeNodes(Node* node);
    Node* getRoot();
    Node* createNode(Elemtype location);
    Node* findNode(Elemtype location);  //查
    Node* findNode(Elemtype* location);  //查
    Node* preFindNode(Node* parent, Elemtype location);
    Node* preFindNode(Node* parent, Elemtype* location);
    Node* getRealParentNode(Elemtype location);
    Node* getRealParentNode(Elemtype* location);
    
};




#endif /* BNTree_hpp */
