//
//  BNTree.cpp
//  MCTS_Gomoku
//
//  Created by 白竞帆 on 2021/11/22.
//

#include "BNTree.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

void BNTree::initTree(){
    depth = 0;
    //root = (RootNode*)malloc(sizeof(RootNode));
    root = createNode(Location(-1, -1));
    root->parent = nullptr;
}
BNTree::~BNTree(){
    
}

Node* BNTree::getRoot(){
    return root;
}

int BNTree::getDepth(){
    return depth;
}


void BNTree::output(){
//    因为如果想按照层次输出，需要一个队列来储存父节点，所以用一棵树来模拟队列
    BNTree deque;
    deque.initTree();
    Node* temp = this->root;
    if (this->isEmpty()) {
        cout<<"树为空"<<endl;
        return;
    }
    temp = temp->firstChild;
    deque.insertNode(deque.getRoot()->location, *(temp->location));
    //deque.insertNode(root->location, *(temp->location));
    while (!deque.isEmpty()) {
        temp = deque.root->firstChild;  // 队头结点
        Elemtype* curLocation = (temp->location);
        Node* loopNode = this->findNode(curLocation);
        deque.deleteNode(*curLocation);
        cout<<"父节点 "<<"("<<loopNode->parent->location->getRow()<<","<<loopNode->parent->location->getColomn()<<")"<<" : ";
        while (loopNode) {
            cout<<"("<<loopNode->location->getRow()<<","<<loopNode->location->getColomn()<<")"<<" ";
            if (loopNode->firstChild) {
                deque.insertNode(root->location, *(loopNode->firstChild->location));
            }
            loopNode = loopNode->sibling;
        }
        cout<<endl;
        
        
    }
}
void BNTree::outputValue(){
//    因为如果想按照层次输出，需要一个队列来储存父节点，所以用一棵树来模拟队列
    BNTree deque;
    deque.initTree();
    Node* temp = this->root;
    if (this->isEmpty()) {
        cout<<"树为空"<<endl;
        return;
    }
    temp = temp->firstChild;
    deque.insertNode(deque.getRoot()->location, (temp->location));
    while (!deque.isEmpty()) {
        temp = deque.root->firstChild;  // 队头结点
        Elemtype *curLocation = (temp->location);
        Node* loopNode = this->findNode(curLocation);
        deque.deleteNode(curLocation);
        cout<<"父节点 "<<"("<<loopNode->parent->location->getRow()<<","<<loopNode->parent->location->getColomn()<<")"<<loopNode->parent->location->getValue()<<" "<<
        loopNode->parent->location->getVisitedTimes()<<" : ";
        while (loopNode) {
            cout<<"("<<loopNode->location->getRow()<<","<<loopNode->location->getColomn()<<")"<<loopNode->location->getValue()<<" "<<
            loopNode->location->getVisitedTimes()<<" ";
            if (loopNode->firstChild) {
                deque.insertNode(deque.getRoot()->location, (loopNode->firstChild->location));
            }
            loopNode = loopNode->sibling;
        }
        cout<<endl;
        
        
    }
}

bool BNTree::isEmpty(){
    return depth==0?true:false;
}

Node* BNTree::createNode(Elemtype location){
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    Location *lct = (Location*)malloc(sizeof(Location));
    lct->setRow(location.getRow());
    lct->setCol(location.getColomn());
    lct->setValue(location.getValue());
    lct->setVisitedTimes(location.getVisitedTimes());
    node->location = lct;
    node->childsCount = 0;
    node->firstChild = nullptr;
    node->sibling = nullptr;
    return node;
}
Node* BNTree::findNode(Elemtype* location){
    Node* temp = this->root;
    if (temp = preFindNode(temp, location)) {
        return temp;
    }
    return nullptr;
}
Node* BNTree::preFindNode(Node *parent, Elemtype* location){
    Node* temp = parent;
    if (location == (temp->location)) {
        return temp;
    }else{
        Node* tempp = temp;
        if (tempp->firstChild && (tempp = preFindNode(tempp->firstChild, location))) {
            return tempp;
        }
        if (temp->sibling && (temp = preFindNode(temp->sibling, location))) {
            return temp;
        }
    }
    return nullptr;
}

Node* BNTree::findNode(Elemtype location){
    Node* temp = this->root;
    if (temp = preFindNode(temp, location)) {
        return temp;
    }
    return nullptr;
}
Node* BNTree::preFindNode(Node *parent, Elemtype location){
    Node* temp = parent;
    if (location.equals(*(temp->location))) {
        return temp;
    }else{
        Node* tempp = temp;
        if (tempp->firstChild && (tempp = preFindNode(tempp->firstChild, location))) {
            return tempp;
        }
        if (temp->sibling && (temp = preFindNode(temp->sibling, location))) {
            return temp;
        }
    }
    return nullptr;
}

bool BNTree::insertNode(Elemtype parentLocation, Elemtype location){
    //if (parentLocation.equals(location)) {  //不允许重复输入
    //    return false;
    //}
    Node* newNode = this->createNode(location);
    Node* parentNode = this->findNode(parentLocation);
    if (!parentNode) {
        return false;
    }
    parentNode->childsCount++;
    if (!parentNode->firstChild) {
        parentNode->firstChild = newNode;
        depth++;
    }else{
        parentNode = parentNode->firstChild;
        while (parentNode->sibling) {
            parentNode = parentNode->sibling;
        }
        parentNode->sibling = newNode;
    }
    newNode->parent = parentNode;
    
    return true;
}
bool BNTree::insertNode(Elemtype* parentLocation, Elemtype location){
    //if (parentLocation.equals(location)) {  //不允许重复输入
    //    return false;
    //}
    Node* newNode = this->createNode(location);
    Node* parentNode = this->findNode(parentLocation);
    if (!parentNode) {
        return false;
    }
    parentNode->childsCount++;
    if (!parentNode->firstChild) {
        parentNode->firstChild = newNode;
        depth++;
    }else{
        parentNode = parentNode->firstChild;
        while (parentNode->sibling) {
            parentNode = parentNode->sibling;
        }
        parentNode->sibling = newNode;
    }
    newNode->parent = parentNode;
    
    return true;
}
bool BNTree::insertNode(Elemtype* parentLocation, Elemtype* location){
    //if (parentLocation.equals(location)) {  //不允许重复输入
    //    return false;
    //}
    //Node* newNode = this->createNode(location);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->location = location;
    newNode->childsCount = 0;
    newNode->firstChild = nullptr;
    newNode->sibling = nullptr;
    Node* parentNode = this->findNode(parentLocation);
    if (!parentNode) {
        return false;
    }
    parentNode->childsCount++;
    if (!parentNode->firstChild) {
        parentNode->firstChild = newNode;
        depth++;
    }else{
        parentNode = parentNode->firstChild;
        while (parentNode->sibling) {
            parentNode = parentNode->sibling;
        }
        parentNode->sibling = newNode;
    }
    newNode->parent = parentNode;
    
    return true;
}
bool BNTree::deleteNode(Elemtype* location){
    Node* temp = this->findNode(location);
    if(!temp){
        return false;
    }
    Node* parent = temp->parent;
    this->getRealParentNode(location)->childsCount--;
    //parent->childsCount--;
    if (temp->sibling) {  // 这里是有右节点的情况
        if (parent->firstChild == temp) {
            parent->firstChild = temp->sibling;
            temp->sibling->parent = parent;
        }else{
            parent->sibling = temp->sibling;
            temp->sibling->parent = parent;
        }
        temp->sibling = nullptr;
    }else{
        if (parent->firstChild == temp) {
            parent->firstChild = nullptr;
            this->depth--;
        }else{
            parent->sibling = nullptr;
        }
    }
    //this->freeWholeNodes(temp);
    return true;
}
bool BNTree::deleteNode(Elemtype location){
    Node* temp = this->findNode(location);
    if(!temp){
        return false;
    }
    Node* parent = temp->parent;
    this->getRealParentNode(location)->childsCount--;
    //parent->childsCount--;
    if (temp->sibling) {  // 这里是有右节点的情况
        if (parent->firstChild == temp) {
            parent->firstChild = temp->sibling;
        }else{
            parent->sibling = temp->sibling;
        }
        temp->sibling = nullptr;
    }else{
        if (parent->firstChild == temp) {
            parent->firstChild = nullptr;
            this->depth--;
        }else{
            parent->sibling = nullptr;
        }
    }
    this->freeWholeNodes(temp);
    return true;
}

void BNTree::freeWholeNodes(Node *node){
    if (!node->firstChild && !node->sibling) {
        free(node);
        return;
    }
    if (node->firstChild) {
        freeWholeNodes(node->firstChild);
    }
    if (node->sibling) {
        freeWholeNodes(node->sibling);
    }
    
}
Node* BNTree::getRealParentNode(Elemtype location){
    if (location.equals(*(root->location))) {
        return nullptr;
    }
    Node* temp = findNode(location);
    while (true) {
        Node* parent = temp->parent;
        if (parent->firstChild == temp) {
            return parent;
        }else{
            temp = temp->parent;
        }
    }
}
Node* BNTree::getRealParentNode(Elemtype* location){
    if (location->equalsAddress(root->location)) {
        return nullptr;
    }
    Node* temp = findNode(location);
    while (true) {
        Node* parent = temp->parent;
        if (parent->firstChild == temp) {
            return parent;
        }else{
            temp = temp->parent;
        }
    }
}

Location::Location(int row, int colomn):row(row), colomn(colomn){
    value = 0;
    visitedTimes = 0;
}
Location::~Location(){
    
}

int Location::getRow(){
    return this->row;
}
int Location::getColomn(){
    return this->colomn;
}
bool Location::equals(Location lct){
    return (this->getRow() == lct.getRow() && this->getColomn() == lct.getColomn())?true:false;
}
bool Location::equalsAddress(Location* lct){
    return (this == lct)?true:false;
}
int Location::getValue(){
    return value;
}
int Location::getVisitedTimes(){
    return visitedTimes;
}
void Location::setValue(int value){
    this->value = value;
}
void Location::setRow(int value){
    this->row = value;
}
void Location::setCol(int value){
    this->colomn = value;
}
void Location::increaseValue(int value){
    this->value += value;
}
void Location::setVisitedTimes(int visitedTimes){
    this->visitedTimes = visitedTimes;
}
void Location::increaseVisitedTimes(int visitedTimes){
    this->visitedTimes += visitedTimes;
}
