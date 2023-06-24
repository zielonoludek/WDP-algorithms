#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    int id;
    char name[50];
    struct User* next;
} User;

typedef struct Queue {
    User* front;
    User* back;
} Queue;

void init(Queue* queue) {
    queue->front = NULL;
    queue->back = NULL;
}

void addUser(Queue* queue, int id, const char* name) {
    User* newUser = (User*)malloc(sizeof(User));
    newUser->id = id;
    strcpy_s(newUser->name, sizeof(newUser->name), name);
    newUser->next = NULL;

    if (queue->back == NULL) {
        queue->front = newUser;
        queue->back = newUser;
    }
    else {
        queue->back->next = newUser;
        queue->back = newUser;
    }
    printf("User '%s' added\n", newUser->name);
}

void delUser(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    User* userToRemove = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) queue->back = NULL;

    printf("User '%s' removed\n", userToRemove->name);
    free(userToRemove);
}

void userList(const Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("List:\n");
    User* current = queue->front;
    while (current != NULL) {
        printf("ID: %d, Name: %s\n", current->id, current->name);
        current = current->next;
    }
}

void saveQueue(const Queue* queue, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("Error.\n");
        return;
    }

    User* current = queue->front;
    while (current != NULL) {
        fprintf(file, "%d %s\n", current->id, current->name);
        current = current->next;
    }

    fclose(file);
    printf("Queue saved\n", filename);
}

void loadQueue(Queue* queue, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) return;

    int id;
    char name[50];
    while (fscanf_s(file, "%d %s\n", &id, name, sizeof(name)) == 2) addUser(queue, id, name);

    fclose(file);
    printf("Queue loaded\n", filename);
}

void clearList(Queue* queue) {
    while (queue->front != NULL) delUser(queue);
}

void delList(Queue* queue) {
    clearList(&queue);
    free(queue->front);
    free(queue->back);
}


int main() {
    Queue queue;
    init(&queue);

    addUser(&queue, 1, "a");
    addUser(&queue, 2, "b");

    userList(&queue);

    saveQueue(&queue, "queue.txt");

    clearList(&queue);

    loadQueue(&queue, "queue.txt");
    userList(&queue);

    delList(&queue);
    return 0;
}
