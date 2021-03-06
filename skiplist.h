//
// Created by Temesgen on 11/12/2019.
//

#ifndef HW4_SKIPLIST_SKIPLIST_H
#define HW4_SKIPLIST_SKIPLIST_H

#include <iostream>

using namespace std;



class SkipList {
public:
    // default SkipList has depth of 1, just one doubly-linked list
    explicit SkipList(int depth = 1);
    // destructor
    virtual ~SkipList();

    /**
     * ADD
     * This method inserts a node containing the data argument passed into
     * the method in order from least to greatest. In the case that data
     * already exists in the list, it outputs a message notifying the user
     * and returns false. If successfully added, return true.
     * @param data
     * @return true or false
     */
    bool Add(int data);

    /**
     * REMOVE
     * This method removes a node containing the data argument passed into
     * the method . In the case that data does not exist in the list, it
     * outputs a message notifying the user and returns false. If
     * successfully removed, return true.
     * @param data
     * @return true or false
     */
    bool Remove(int data);
    // return true if found in SkipList
    /**
     * CONTAINS
     * This method returns true if the data argument passed into the method
     * exists in the SkipList. Otherwise it returns false.
     * @param data
     * @return
     */
    bool Contains(int data);

    //output overload
    friend ostream &operator<<(ostream &os, const SkipList &list);

private:
    class SNode {
    public:
    // SNode stores int as data
        explicit SNode(int data = 1);
    // data for SNode
        int data;
    // link to next SNode
        SNode *next;
    // link to prev SNode
        SNode *prev;
    // link to up one level
        SNode *upLevel;
    // link to down one level
        SNode *downLevel;
    };

    // depth of SkipList, levels are 0 to depth-1
    int depth;

    // array of depth SNode* objects as frontGuards linking levels
    // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
    SNode **frontGuards;

    // array of depth SNode* objects as rearGuards linking levels
    SNode **rearGuards;

    /**
     * ADDBEFORE
     * Given an SNode to add, this method inserts that node directly
     * before the given SNode nextNode
     * @param newNode
     * @param nextNode
     */
    void addBefore(SNode *newNode, SNode *nextNode);


    // return true 50% of time,
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;

};


#endif //HW4_SKIPLIST_SKIPLIST_H
