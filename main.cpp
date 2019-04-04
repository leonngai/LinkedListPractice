#include <iostream>
using namespace std;

#include "list.h"
#include "hydro.h"

int main() {
    FlowList mylist;
    int numRecords;
    displayHeader();
    numRecords = readData(mylist);
    int quit = 0;

    while(1) {
        switch (menu()) {
            case 1:
                display(mylist, numRecords);
                pressEnter();
                break;
            case 2:
                numRecords = addData(mylist, numRecords);
                pressEnter();
                break;
            case 3:
                saveData(mylist);
                pressEnter();
                break;
            case 4:
                numRecords = removeData(mylist);
                pressEnter();
                break;
            case 5:
                cout << "\nProgram terminated!\n\n";
                quit = 1;
                break;
            default:
                cout << "\nNot a valid input.\n";
                pressEnter();
        }

        if (quit == 1) break;
    }

    FlowList copy1;
    copy1 = mylist;
    ListItem temp = {2012, 459.99};
    copy1.insert(temp);
    temp = {2012, 2000.34};
    copy1.insert(temp);

    FlowList copy2 = copy1;
    copy2.remove(1922);
    copy2.remove(2003);
    copy2.remove(2001);

    cout << "\n values in copy 2 are: \n";
    display(copy2, copy2.count());

    cout << "\n values in copy1 are: \n";
    display(copy1, copy1.count());

    cout << "\n values in original list are: \n";
    display(mylist, mylist.count());

    return 0;
}