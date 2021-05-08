#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logica.h"
#include "ll.h"

ListElem Cons(void* data, ListElem tail) {
	ListElem aux = (ListElem)malloc(sizeof(SListElem));
	aux->data = data;
	aux->next = tail;
	return aux;
}

ListElem Snoc(ListElem list, void* data) {
	if (list == NULL) return Cons(data, NULL);
	else list->next = Snoc(list->next, data);
	return list;
}

ListElem addItemHead(ListElem head, void *data) {
	ListElem aux;
	
	if((aux = (ListElem) malloc(sizeof(SListElem))) == NULL)
		return head;
	
	aux->data = data;
	aux->next = head;
	
	return aux;
}


ListElem AddItemLast(ListElem head, void* data) {
	ListElem aux, first;
	aux = NULL;
	aux->data = data;
	first = head;
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = addItemHead(head, data);
	return first;
}


ListElem addItemLastRecursive(ListElem head, void *data) {
	ListElem aux;
	
	if(head == NULL) {
		aux = (ListElem) malloc(sizeof(SListElem));
		aux->data = data;
		aux->next = NULL;
		return aux;
	}
	
	head->next = addItemLastRecursive(head->next, data);
	
	return head;
}

ListElem addItemLastIterative(ListElem head, void *data) {
	ListElem aux, prev;

	aux = (ListElem)malloc(sizeof(SListElem));
	aux->data = data;
	aux->next = NULL;

	if (head == NULL) {	
		return aux;
	}

	for(prev = head; prev->next != NULL; prev = prev->next)
		;

	prev->next = aux;

	return head;
}

void showListIterative(ListElem head, void (*show)(void *data)) {
	
	while(head != NULL) {
		show(head->data);
		head = head->next;
	}
	
}

void showListRecursive(ListElem head, void (*show)(void *data)) {
	if(head != NULL) {
		show(head->data);
		showListRecursive(head->next, show);
	}
}

ListElem removeItemIterative(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem aux, prev;
	
	// List is empty
	if(head == NULL)
		return NULL;
	
	// Element to remove is on the head of the list
	if(compare(head->data, data) == 1) {
		aux = head->next;
		free(head);
		return aux;
	} 
	
	// Element to remove is in the tail of the list
	for(prev = head; prev->next != NULL; prev = prev->next)
	{
		if(compare(prev->next->data, data) == 1) {
			aux = prev->next;
			prev->next = prev->next->next;
			free(aux);
			break;
		}
	}
	
	return head;
}

ListElem removeItemRecursive(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem aux;
	
	if(head == NULL) return NULL;
		
	if(compare(head->data, data) == 1) {
		aux = head->next;
		free(head);
		return aux;
	} else {
		head->next = removeItemRecursive(head->next, data, compare);
		return head;
	}
}

ListElem addItemOrderedIterative(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem n, aux;
	
	n = (ListElem) malloc(sizeof(SListElem));
	n->data = data;
	n->next = NULL;
	
	if(head == NULL || compare(data, head->data) < 0) {
		n->next = head;
		return n;
	}
	
	for(aux = head; aux->next != NULL; aux = aux->next) {
		if(compare(data, aux->next->data) < 0) {
			n->next = aux->next;
			aux->next = n;
			return head;
		}
	}
	
	aux->next = n;
	return head;
}

ListElem addItemOrderedRecursive(ListElem head, void *data, int (*compare)(void *data1, void *data2)) {
	ListElem aux;
	
	if(head == NULL || compare(data, head->data) < 0) {
		aux = (ListElem) malloc(sizeof(SListElem));
		aux->data = data;
		aux->next = head;
		return aux;
	}
	
	head->next = addItemOrderedRecursive(head->next, data, compare);
	return head;
}

ListElem Filter(ListElem head, int (*rmv)(void* data)) {
	ListElem aux = head;

	if (head == NULL) return NULL;	
	else if (rmv(head->data) == 1) {
		aux = head->next;
		free(head);
		return Filter(aux, rmv);
	}
	else {
		head->next = Filter(head->next, rmv);
		return aux;
	}
}

ListElem FindItem(ListElem head, void* data1) {
	if (head == NULL) return NULL;
	else {
		if (data1 == head->data) return head;
		else head = head->next;
	}
}

int ContainsRec(ListElem head, void* data) {
	if (head == NULL) return 0;
	else {
		if (data != head->data) ContainsRec(head->next, data);
		else return 1;
	}
}

ListElem GoToIndex(ListElem head, int index) {
	if (head != NULL) {
		if (index += 0) return head;
		else GoToIndex(head, index - 1);
	}
	else return NULL;
}

int getIndex(ListElem head, void* data) {
	if (head != NULL) {
		if (ContainsRec(head, data) == 1) {
			int index = 0;
			while (head->data != data) {
				head = head->next;
				index++;
			}
			return index;
		}
		else return -1;
	}
	else return -1;
}

void* ReturnData(ListElem head) {
	if (head == NULL) return NULL;
	else {
		return head->data;
	}
}

int ListLen(ListElem head) {
	int aux = 0;
	while (head != NULL) {
		head = head->next;
		aux++;
	}
	return aux;
}

ListElem Merge(ListElem l1, ListElem l2, int(*cmp)(void* arg1, void* arg2)) {
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;

	//Se l1.data menor igual a l2.data retorna -1 ou 0
	if (cmp(l1->data, l2->data) > 0) {
		l2->next = Merge(l1, l2->next, cmp);
		return l2;
	}
	else {
		l1->next = Merge(l1->next, l2, cmp);
		return l1;
	}
}

void Split(ListElem l1, ListElem* l2) {
	if (l1 == NULL) return;
	if (l1->next == NULL) return;

	ListElem aux = l1->next;
	l1->next = l1->next->next;
	aux->next = *l2;
	*l2 = aux;

	Split(l1->next, l2);
}

ListElem MergeSort(ListElem head, int(*cmp)(void* arg1, void* arg2)) {
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	ListElem aux = NULL;
	Split(head, &aux);
	head = MergeSort(head, cmp);
	aux  = MergeSort(aux, cmp);
	return Merge(head, aux, cmp);
}

void FreeList(ListElem head) {
	if (head == NULL) return;
	else {
		ListElem aux = head->next;
		free(head);
		FreeList(aux);
	}
}