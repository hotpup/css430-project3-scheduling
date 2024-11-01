#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "cpu.h"
#include "task.h"
#include "schedulers.h"

struct node *head;

void add(char *name, int priority, int burst)
{
    Task *temp = (Task *)malloc(sizeof(Task));
    temp->name = strdup(name);
    temp->priority = priority;
    temp->burst = burst;
    insert(&head, temp);
}

bool comesBefore(char *a, char *b)
{
    return strcmp(a, b) < 0;
}

Task *pickNextTask()
{
    // if list is empty, nothing to do
    if (!head)
        return NULL;

    struct node *temp;
    temp = head;
    Task *best_sofar = temp->task;

    while (temp != NULL)
    {
        if (comesBefore(temp->task->name, best_sofar->name))
            best_sofar = temp->task;
        temp = temp->next;
    }

    delete (&head, best_sofar);
    return best_sofar;
}

void schedule()
{
    int time = 0;

    while (head != NULL)
    {
        Task *task = pickNextTask();
        run(task, task->burst);
        time += task->burst;
        printf("Time is now:  %d\n", time);
    }
}