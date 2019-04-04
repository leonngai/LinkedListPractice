
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "list.h"

FlowList::FlowList()
        : headM(0), cursorM(0)
{
}

FlowList::FlowList(const FlowList& source)
{
    copy(source);
}

FlowList& FlowList::operator =(const FlowList& rhs)
{
    if (this != &rhs) {
        destroy();
        copy(rhs);
    }
    return *this;
}

FlowList::~FlowList()
{
    destroy();
}

void FlowList::destroy()
{
    reset();
    while(cursorM != 0) {
        forward();
        delete headM;
        headM = cursorM;
    }
    headM = 0;
}

const ListItem& FlowList::getItem() const {
    if (isOn()) {
        return cursorM->item;
    }
}

void FlowList::insert(const ListItem& itemA)
{
    double itemAFlow = itemA.flow;
    Node *new_node = new Node;
    new_node->item = itemA;

    if (headM == 0 || itemAFlow <= headM->item.flow ) {
        new_node->next = headM;
        headM = new_node;

    }
    else {
        Node *before = headM;      // will point to node in front of new node
        Node *after = headM->next; // will be 0 or point to node after new node
        while(after != 0 && itemAFlow > after->item.flow) {
            before = after;
            after = after->next;
        }
        new_node->next = after;
        before->next = new_node;

    }

    cursorM = 0;
}

void FlowList::remove(int target_year) {
    // if list is empty, do nothing
    if (headM == 0)
        return;

    Node *doomed_node = 0;

    if (target_year == headM->item.year) {
        doomed_node = headM;
        headM = headM->next;
    }
    else {
        Node *before = headM;
        Node *maybe_doomed = headM->next;

        while(maybe_doomed != 0) {
            if (maybe_doomed->item.year == target_year) {
                before->next = maybe_doomed->next;
                delete maybe_doomed;
                cursorM = 0;
                cout << "Record was successfully removed" << endl;
                return;
            }
            before = maybe_doomed;
            maybe_doomed = maybe_doomed->next;
        }

        cout << "Error: No such data exists" << endl;
    }
}

void FlowList::forward() {
    cursorM = cursorM->next;
}

void FlowList::copy(const FlowList& source)
{
//    check to see if list is empty
    if (source.headM == 0) {
        return;
    }

    else {
//        initializes the head of the list
        Node *new_head = new Node;
        new_head->item = source.headM->item;
        new_head->next = 0;
        this->headM = new_head;

        Node *tail = new_head;

        cursorM = source.headM->next;
        while(cursorM != 0) {
            Node *temp_node = new Node;
            temp_node->item = cursorM->item;
            temp_node->next = 0;

            tail->next = temp_node;
            tail = tail->next;
            forward();
        }

    }

}

void FlowList::print()
{
    if (headM != 0) {
        cout << headM->item.year << "\t" << headM->item.flow << "\n";
        for (const Node *p = headM->next; p != 0; p = p->next)
            cout << p->item.year << "\t" << p->item.flow << "\n";
    }

}

int FlowList::count() const{
    Node* cursor = headM;
    int count = 0;
    while(cursor != 0) {
        count++;
        cursor = cursor->next;
    }

    return count;
}

void FlowList::reset() {
    cursorM = headM;
}

bool FlowList::isOn() const {
    return cursor() != 0;
}


const Node* FlowList::cursor() const {
    return cursorM;
}

