#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char action[100];
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;
Node* current = NULL;

// Perform a new action
void performAction(char act[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->action, act);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (current == NULL) {
        head = newNode;
        current = newNode;
    } else {
        // clear forward history
        Node* temp = current->next;
        while (temp != NULL) {
            Node* del = temp;
            temp = temp->next;
            free(del);
        }
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    printf("Performed: %s\n", act);
}

// Undo last action
void undo() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
        printf("Undo done. Current action: %s\n", current->action);
    } else {
        printf("Nothing to undo.\n");
    }
}

// Redo last undone action
void redo() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        printf("Redo done. Current action: %s\n", current->action);
    } else {
        printf("Nothing to redo.\n");
    }
}

// Show current action
void showCurrent() {
    if (current != NULL) {
        printf("Current Action: %s\n", current->action);
    } else {
        printf("No actions performed yet.\n");
    }
}

int main() {
    int choice;
    char act[100];

    while (1) {
        printf("\n--- Undo Redo Menu ---\n");
        printf("1. Perform New Action\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Show Current Action\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting.\n");
            break;
        }
        getchar(); // clear newline character after scanf()

        if (choice == 1) {
            printf("Enter action: ");
            fgets(act, sizeof(act), stdin);
            act[strcspn(act, "\n")] = 0; // remove newline
            if (strlen(act) > 0) {
                performAction(act);
            } else {
                printf("Empty action not allowed.\n");
            }
        } else if (choice == 2) {
            undo();
        } else if (choice == 3) {
            redo();
        } else if (choice == 4) {
            showCurrent();
        } else if (choice == 5) {
            printf("Thank you!\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

