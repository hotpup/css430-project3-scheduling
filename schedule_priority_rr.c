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
        if (temp->task->priority < best_sofar->priority)
        {
            best_sofar = temp->task;
        }
        else if (temp->task->priority == best_sofar->priority)
        {

            if (comesBefore(temp->task->name, best_sofar->name))
                best_sofar = temp->task;
        }
        temp = temp->next;
    }

    return best_sofar;
}

void schedule()
{
    int time = 0;

    while (head != NULL)
    {
        Task *task = pickNextTask();
        if (task->burst <= 10)
        {

            run(task, task->burst);
            time += task->burst;
            delete (&head, task);
        }
        else
        {
            run(task, 10);
            time += 10;
            task->burst -= 10;
        }
        printf("Time is now:  %d\n", time);
    }
}