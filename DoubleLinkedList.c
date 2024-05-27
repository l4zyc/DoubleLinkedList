#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next, *prev;
    int value;
} *head = NULL, *tail = NULL;

struct Node* newNode(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void pushHead(int value) {
    struct Node* node = newNode(value);   
    if(head == NULL) {
        head = tail = node;
        return;
    } 

    node->next = head;
    head->prev = node;
    head = node;
}

void pushTail(int value) {
    struct Node* node = newNode(value);
    if(head == NULL) {
        head = tail = node;
        return;
    }

    node->prev = tail;
    tail->next = node;
    tail = node;
}

void pushMid(int value) {
    struct Node* node = newNode(value);
    if(head == NULL) {
        head = tail = node;
        return;
    } else if(value < head->value) {
        pushHead(value);
    } else if(value > tail->value) {
        pushTail(value);
    } else {
        struct Node* curr = head;

        while(curr->next != NULL && value > curr->next->value) {
            curr = curr->next;
        }

        node->next = curr->next;
        curr->next->prev = node;

        curr->next = node;
        node->prev = curr;
    }
}

void popHead() {
    if(head == NULL) {
        return;
    } 
    struct Node* temp = head;
    head = head->next;
    head->prev = NULL;
    free(temp);
}

void popTail() {
    if(head == NULL) {
        return;
    } 

    struct Node* temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    free(temp);
}

void popMid(int target) {
    if(head == NULL) {
        return;
    } else if(head->value == target) {
        popHead();
    } else if(tail->value == target) {
        popTail();
    } else {
        struct Node* curr = head;
        
        while(curr->next != NULL && curr->next->value != target) {
            curr = curr->next;
        }

        struct Node* temp = curr->next;
        curr->next = temp->next;
        temp->next->prev = curr;

        temp->prev = NULL;
        temp->next = NULL;

        free(temp);
    }
}

void displayList() {
    struct Node* curr = head;
    if(head == NULL) {
        return;
    }

    printf("NULL");

    while(curr != NULL) {
        printf("<- %d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL");
}

int main() {
    pushHead(7);
    pushHead(6);
    pushMid(8);
    pushTail(9);
    pushTail(10);
    popMid(8);
    displayList();
    return 0;
}