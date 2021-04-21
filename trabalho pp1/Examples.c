#include "Examples.h"

void memswap(void** a, void** b) {
	void* aux = *a;
	*a = *b;
	*b = aux;
}



Point* newPoint(int a, int b) {
	Point* p = (Point*)malloc(sizeof(Point));
	p->x = a;
	p->y = b;
	p->l = NULL;
	return p;
}
Point* newPointLE(int a, int b, ListElem le) {
	Point* p = (Point*)malloc(sizeof(Point));
	p->x = a;
	p->y = b;
	p->l = le;
	return p;
}
void PrintInt(void* i) {
	printf("%d, ", (int)i);
}

void PrintPoint(Point* p) {
	printf("(%d , %d) {", p->x, p->y);
	showListRecursive(p->l, &PrintInt);
	printf("}");
}

void PrintPointVoid(void* p) {
	PrintPoint((Point*)p);
}


int MyPred(void* data) {
	Point* p = (Point*)data;
	return (p->x + p->y >= 100);
}


//this part should be in the main if someone wants to understand this example and code

//ListElem le0 = NULL;
//le0 = addItemHead(le0, (void*)43);
//le0 = addItemHead(le0, (void*)44);
//
//ListElem le = NULL;
//le = addItemHead(le, (void*)newPointLE(42, 42, le0));
//le = addItemHead(le, (void*)newPoint(50, 50));
//le = addItemHead(le, (void*)newPoint(100, 100));
//le = addItemHead(le, (void*)newPoint(1, 50));
//
//le = Filter(le, &MyPred);
//
//showListIterative(le, &PrintPointVoid);