

#ifndef UNTITLED3_HYDRO_H
#define UNTITLED3_HYDRO_H

#include "list.h"

void displayHeader();
void pressEnter();
int menu();
int readData(FlowList& list);
void display(FlowList list, int count);
double average(FlowList list, int count);
double median(FlowList list, int count);
int addData(FlowList& list, int count);
int removeData(FlowList& list);
void saveData(FlowList list);
#endif //UNTITLED3_HYDRO_H
