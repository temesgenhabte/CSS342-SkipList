//
// Created by Temesgen on 11/12/2019.
//

#include "skiplist.h"
#include <iostream>
#include <cassert>
#include <climits>


using namespace std;


SkipList::SNode::SNode(int data) { //SNode Constructor
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->upLevel = nullptr;
    this->downLevel = nullptr;
}

SkipList::SkipList(int depth) {
    if(depth <= 0){ //check for invalid depths
        cout << "Invalid depth" << endl;
    }

    this-> depth = depth;
    frontGuards = new SNode*[depth]; //setting depth amount of pointers
    rearGuards = new SNode*[depth];

    for(int i = 0; i < depth; i++){
        frontGuards[i] = new SNode (INT_MIN); //set the ends to MIN and MAX
        rearGuards[i] = new SNode (INT_MAX);

        frontGuards[i]->next = rearGuards[i]; //connect Guards
        rearGuards[i]->prev = frontGuards[i];
    }

    for(int i = 0; i < depth - 1; i++){ //doubly link "upwards" until you get
                              // to the last level, it is upLinked to nullptr
        frontGuards[i]->upLevel = frontGuards[i+1];
        frontGuards[i+1]->downLevel = frontGuards[i];
        rearGuards[i]->upLevel = rearGuards[i+1];
        rearGuards[i+1]->downLevel = rearGuards[i];
    }

}

SkipList::~SkipList() {
    for(int i = 0; i < depth; i++){
        SNode* cur = frontGuards[i]->next;
        SNode* toDelete = cur->prev; //tails current
        while(cur->next != nullptr){ //go until the end of the current level
            delete toDelete; //delete behind current
            cur = cur->next; //current moves right
            toDelete = cur->prev; //tail current
        }
        delete cur;
        delete toDelete;
    }

    delete[] frontGuards; //delete the arrays after everything else
    delete[] rearGuards;
}

bool SkipList::Add(int data) {
    if(Contains(data)){
        cout << "No duplicates allowed" << endl;
        return false;
    }

    int depthCounter = 2; //keep track of depth

    SNode* cur = frontGuards[0]; //set current to the bottom left
    while(data > cur->next->data){
        cur = cur->next; //move current to the node before insert spot
    }

    SNode* addedNode = new SNode(data); //node to add
    addBefore(addedNode, cur->next); // add in front of current
    while(alsoHigher() && depthCounter <= this->depth){ //coin toss and check
                                             // if you are already at the top
        SNode* upAdded = new SNode(data);
        cur = addedNode;
        while(cur->upLevel == nullptr){ //go back to first node with upLevel
            cur = cur->prev; //worst case scenario it goes all the way
                             // to frontGuard, which still works
        }
        cur = cur->upLevel; //go up a level
        addBefore(upAdded, cur->next);

        addedNode->upLevel = upAdded; //doubly link to the lower level counterpart
        upAdded->downLevel = addedNode;
        addedNode = upAdded; //move addedNode to the upper level counterpart
        depthCounter++;
    }

    return true;
}

bool SkipList::Remove(int data) {
    if(!Contains(data)){ //check if the value is not in the list
        cout << data << " not in the list" << endl;
        return false;
    }

    SNode* cur = frontGuards[0];

    while(cur->data != data){ //only possible because we used Contains in the
                              // beginning, otherwise check nullptr
        cur = cur->next;
    }

    while(cur->upLevel != nullptr) //go to the top
        cur = cur->upLevel;

    while(cur->downLevel != nullptr){ //delete as you go down
        cur = cur->prev;
        SNode* toDelete = cur->next;
        cur->next = cur->next->next; //skip toDelete
        cur->next->prev = cur;
        cur = toDelete->downLevel; //cur follows toDelete's link downwards


        delete cur->upLevel; //delete toDelete
    }

    cur = cur->prev; //this is the same process for the lowest level version
    SNode* toDelete = cur->next;
    cur->next = cur->next->next;
    cur->next->prev = cur;


    delete toDelete;

    return true;
}

bool SkipList::Contains(int data) {
    if(data == INT_MIN || data == INT_MAX){
        return true;
    }
    SNode* cur = frontGuards[depth-1]; //current goes to the top-left

    while(cur != nullptr){
        if(cur->next->data < data) { //check that the next is less than data
            cur = cur->next;
        }
        else if(cur->next->data == data){ //if not check if it is the target
            return true;
        }else{
            cur = cur->downLevel; //if not then move down a level and try again
        }
    }

    return false; //if it is not in any of the levels, then return false

//    SNode* cur = frontGuards[0]; //THIS IS THE O(n) SEARCH METHOD
//
//    while(cur->next != nullptr){
//        if(cur->data == data)
//            return true;
//        cur = cur->next;
//    }
//    return false;
}

void SkipList::addBefore(SkipList::SNode *newNode, SkipList::SNode *nextNode) {
    assert(newNode != nullptr && nextNode != nullptr);
    newNode->prev = nextNode->prev;  //insert in front of nextNode->prev
    newNode->next = nextNode;
    nextNode->prev->next = newNode; //link between nextNode->prev and nextNode
    nextNode->prev = newNode; //link nextNode to newNode
}

bool SkipList::alsoHigher() const {
    return (rand() % 2) == 1;
}

ostream &operator<<(ostream &os, const SkipList &list) {
    for(int i = list.depth - 1; i >= 0; i--){
        os << "Level: " << i << " -- ";
        SkipList::SNode* cur = list.frontGuards[i];
        while(cur != nullptr){ //output all items of each level into os
            os << cur->data << ", ";
            cur = cur->next;
        }
        os << "\n"; //end the line after every level
    }
    return os;
}

