
#ifndef UNTITLED3_LIST_H
#define UNTITLED3_LIST_H

struct ListItem {
    int year;
    double flow;
};

struct Node {
    ListItem item;
    Node *next;
};

class FlowList {
public:
    FlowList(); // PROMISES: Creates empty list.
    FlowList(const FlowList& source);
    FlowList& operator =(const FlowList& rhs);
    ~FlowList();


    const ListItem& getItem() const;
    //requires cursorM != null
    //returns item to which cursorM is attached to

    void reset(); //cursorM is equal to headm=M
    bool isOn() const; // return true if cursorm != null, else return false
    const Node* cursor() const; //returns cursorM
    void forward(); //promises: if cursorM != NULL, moves cursorM to the next

    void print();

    void insert(const ListItem& itemA);
    //node with copy of itema is added that preserves non decreasing order of flows in nodes

    void remove(int target_year);
    //if node has item matching target year, list is unchanged and gives clear message that target year not found
    //otherwise, one node is removed, then set cursorM to null

    int count()const;
    //return number of nodes in list

private:
//    always points to first node in list
    Node *headM;

//initially set to null, may point to any node
    Node *cursorM;

    void destroy();

    void copy(const FlowList& source);
};

#endif //UNTITLED3_LIST_H
