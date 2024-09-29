#include <stdio.h>

typedef struct {
    int id;
    char title[100];
    char description[255];
    int isCompleted;
} Task;


int main(){
    Task tasks[100];
    int taskCount = 0;
    int choice, id;

    while (1) {
      printf("\n1. Add Task\n2. View Tasks\n3. Mark Task Completed\n4. Delete Task\n5. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
      getchar(); // Clear the newline character from input

      switch(choice) {
      case 1:
	addTask(tasks, &taskCount);
	break;
      }
    }
}

void addTask(Task tasks[], int *taskCount){
  
}
