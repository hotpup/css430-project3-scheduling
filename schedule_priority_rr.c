#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "cpu.h"
#include "task.h"
#include "schedulers.h"

struct node *head;
bool isRR = false;
void add(char *name, int priority, int burst)
{
    Task *temp = (Task *)malloc(sizeof(Task));
    temp->name = strdup(name);
    temp->priority = priority;
    temp->burst = burst;
    insert(&head, temp);
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
        if (isRR)
        {
            if (task->burst > 10)
            {
                run(task, 10);
                time += 10;
                task->burst -= 10;
            }
            else
            {
                run(task, task->burst);
                time += task->burst;
                delete (&head, task);
            }
        }
        else
        {
            run(task, task->burst);
            time += task->burst;
            delete (&head, task);
        }
        printf("\tTime is now:  %d\n", time);
    }