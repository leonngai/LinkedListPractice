
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "hydro.h"
#include "list.h"

using namespace std;

ifstream inObj;
ofstream outObj;

void displayHeader() {
    cout << "HEF Hydropower Studies - Winter 2019\n";
    cout << "Prorgam: Flow Studies\n";
    cout << "Version: 1.0\n";
    cout << "Instructor: Dr. Moshirpour\n";
    cout << "Produced by: Leon Ngai\n\n";
}

void pressEnter() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "<<< Press Enter to Continue >>>";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int menu() {
    int input;

    cout << "Please select on the following operations\n";
    cout <<"\t1. Display flow list, average and median\n"
           "\t2. Add data\n"
           "\t3. Save data into the file\n"
           "\t4. Remove data\n"
           "\t5. Quit\n"
           "\tEnter your choice (1,2,3,4,5):\n";

    cin >> input;
    return input;
}

int addData(FlowList& list, int count) {
    int inputYear;
    double inputFlow;

    cout << "Please enter a year: ";
    cin >> inputYear;
    cout << "Pleae enter the flow: ";
    cin >> inputFlow;

    list.reset();
    while(list.isOn()) {
        if(list.getItem().year == inputYear) {
            cout << "Error: duplicate data." << endl;
            return count;
        }
        list.forward();
    }

    ListItem temp = {
            inputYear,
            inputFlow
    };

    list.insert(temp);
    cout << "New record inserted successfully." << endl;

    count++;
    return count;

}

int removeData(FlowList& list) {
    int inputYear;

    cout << "Please enter the year that you want to remove: ";
    cin >> inputYear;

    list.remove(inputYear);
    return list.count();
}

//displays years flows, average and medians in list
void display(FlowList list, int count) {
    cout << "Year\tFlow\n";
    list.print();

    cout << "\nThe annual average of the flow is: " << average(list, count) << " millions cubic meter" << endl;
    cout << "The median flow is: " << median(list, count)  << " millions cubic meter" << endl;
}

double average(FlowList list, int count) {
    double average = 0.0;
    list.reset();
    while(list.isOn()) {
        average += list.getItem().flow;
        list.forward();
    }
    return average / count;
}

double median(FlowList list, int count) {
    list.reset();
    //odd list
    if (count % 2 != 0) {
        for (int i = 0; i < count / 2; i++) {
            list.forward();
        }

        return list.getItem().flow;
    }
    //even list
    else {
        for (int i = 1; i < count / 2; i++) {
            list.forward();
        }

        double firstFlow = list.getItem().flow;
        list.forward();
        double secondFlow = list.getItem().flow;

        return (firstFlow + secondFlow) / 2;
    }
}


int readData(FlowList& list) {

    inObj.open("/Users/Leon/CLionProjects/untitled3/flow.txt");
    if (!inObj) {
        cout <<"Error: Could not locate file. The program will exit now.";
        exit(1);
    }

    while(!inObj.eof()) {
        int inputYear;
        double inputFlow;
        inObj >> inputYear >> inputFlow;
        if (inObj.eof())
            break;

        ListItem temp = {
            inputYear,
            inputFlow
        };

        list.insert(temp);
    }

    inObj.close();
    return list.count();
}

void saveData(FlowList list) {
    outObj.open("/Users/Leon/CLionProjects/untitled3/flow.txt");
    list.reset();

    while(list.isOn()) {
        ListItem temp = list.getItem();
        outObj << temp.year << "\t" << temp.flow << "\n";
        list.forward();
    }

    outObj.close();
    cout << "Data has been saved into the file" << endl;
}