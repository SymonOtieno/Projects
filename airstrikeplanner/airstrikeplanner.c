#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LEN 15

void loadTargetFile();
void showTargets();
void searchTarget();
void planAirstrike();
void executeAirstrike();

typedef struct Target {
    char name[16];
    double x;
    double y;
    struct Target *next;
} Target;

Target *head = NULL;

//Main function
int main(){
  int choice;
  while ( 1 )
  {
    printf("\nWelcome To Airstrike Target!!!\n");
    printf("\n");
    printf("1 : Load a target file\n");
    printf("2 : Show current targets\n");
    printf("3 : Search a target\n");
    printf("4 : Plan an airstrike\n");
    printf("5 : Execute an airstrike\n");
    printf("6 : Quit\n");
    printf("Enter your option : \n");

    if ( scanf("%d", &choice) == 1)
    {
      switch ( choice)
      {
      case 1:
        loadTargetFile();
        break;
      case 2:
        showTargets();
        break;
      case 3:
        searchTarget();
        break;
      case 4:
        planAirstrike();
        break;
      case 5:
        executeAirstrike();
        break;
      case 6:
        printf("Thanks!! \n");
        return 0;
      default:
        printf("Invalid choice, please insert a valid number\n");
        break;
      }
    }
  }
}


int addTarget(Target *head, char *name, double x, double y) {
    Target *current = head;
    while (current->next != NULL) {
        current = current->next;
        double distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
        if (distance <= 0.1) {
            return 0; // target is in conflict
        }
    }

    Target *newTarget = (Target *)malloc(sizeof(Target));
    strcpy(newTarget->name, name);
    newTarget->x = x;
    newTarget->y = y;
    newTarget->next = NULL;
    current->next = newTarget;
    return 1; // target successfully added
}

void loadTargetFile(Target *targets) {
    char fileName[256];
    printf("Enter a target file: ");
    scanf("%s", fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Invalid file.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char name[16];
        double x, y;
        int valid = sscanf(buffer, "%s %lf %lf", name, &x, &y);
        if (valid == 3 && x >= -180 && x <= 180 && y >= -180 && y <= 180) {
            if (!addTarget(targets, name, x, y)) {
                printf("%s %lf %lf discarded due to conflict.\n", name, x, y);
            }
        }
    }

    fclose(file);
    printf("Target file loaded successfully.\n");
}

void current_Targets(){
  if (head == NULL) {
      printf("No target.\n");
      } 
  else {
      Target *current = head;
      while (current != NULL) {
      printf("%s %f %f\n", current->name, current->x, current->y);
      current = current->next;
      }
    }
}

void showTargets(Target *targets) {
    Target *current = targets->next;
    if (current == NULL) {
        printf("No target.\n");
        return;
    }
    while (current != NULL) {
        printf("%s %lf %lf\n", current->name, current->x, current->y);
        current = current->next;
    }
}

void searchTargets(Target *targets){
  char name[MAX_NAME_LEN + 1];
        printf("Enter the name: ");
        scanf("%s", name);

        if(strcmp(name,"\n")) { // if the user pressed return without entering any character
            printf("Returning to main menu.\n");
        }else{
            int found = 0;
            Target *current = head;
            while (current != NULL) {
                if (strstr(current->name, name) != NULL) {
                    printf("%s %f %f\n", current->name, current->x, current->y);
                    found = 1;
                }
                current = current->next;
            }
            if (!found) {
                printf("Entry does not exist.\n");
            }
        }
}

void searchTarget(Target *targets) {
    char searchString[256];
    printf("Enter the name: ");
    scanf("%s", searchString);
    Target *current = targets->next;
    int found = 0;
    while (current != NULL) {
        if (strstr(current->name, searchString) != NULL) {
            printf("%s %lf %lf\n", current->name, current->x, current->y);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Entry does not exist.\n");
    }
}

int numberOfTargets(Target *targets) {
    Target *current = targets->next;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

#include <stdio.h>
#include <math.h>

void planAirstrike(Target* head) {
    Target* current = head;
    if (current == NULL) {
        printf("No target.\n");
        return;
    }

    // Find the collision point (the point closest to all targets)
    double collisionX = 0, collisionY = 0;
    int targetCount = 0;
    while (current != NULL) {
        collisionX += current->x;
        collisionY += current->y;
        targetCount++;
        current = current->next;
    }
    collisionX /= targetCount;
    collisionY /= targetCount;

    // Find the maximum distance from the collision point to a target
    double maxDistance = 0;
    current = head;
    while (current != NULL) {
        double distance = sqrt((current->x - collisionX) * (current->x - collisionX) +
                               (current->y - collisionY) * (current->y - collisionY));
        if (distance > maxDistance) maxDistance = distance;
        current = current->next;
    }
    int choice;
    double radius;
    do {
        printf("\nPlease select a option:\n");
        printf("1. Plan amount of nuclear missiles\n");
        printf("2. Plan damage zone of nuclear missiles\n");
        printf("3. Quit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        if(choice ==1) {
            printf("Enter the radius of damage zone of single nuclear missile: ");
            scanf("%lf", &radius);
            double area = 3.14159265358979323846 * radius * radius;
            double total_area = 0.0;
            current = head;
            while (current != NULL) {
                double distance = sqrt((current->x - collisionX) * (current->x - collisionX) +
                               (current->y - collisionY) * (current->y - collisionY));
                if(distance>radius)
                    total_area += (3.14159265358979323846 * distance * distance);
                current = current->next;
            }
            int missiles = ceil(total_area / area);
            printf("%d nuclear missiles needed.", missiles);
        }
        else if(choice == 2) {
            if(targetCount == 1) 
                printf("Required minimum radius of damage zone 0.00.\n");
            else
                printf("Required minimum radius of damage zone %.2lf.\n", maxDistance);
        }
    } while (choice != 3);
}


void executeAirstrike(Target** head) {
    double collisionX, collisionY, damageRadius;
    printf("Enter the targeted collision point and damage zone of a nuclear missile: ");
    scanf("%lf %lf %lf", &collisionX, &collisionY, &damageRadius);

    Target* current = *head;
    Target* prev = NULL;
    int count = 0;
    while (current != NULL) {
        double distance = sqrt((current->x - collisionX) * (current->x - collisionX) +
                               (current->y - collisionY) * (current->y - collisionY));
        if (distance <= damageRadius) {
            printf("Target destroyed: %s, x: %lf, y: %lf\n", current->name, current->x, current->y);
            count++;
            Target* temp = current;
            current = current->next;
            if (prev == NULL) *head = current;
            else prev->next = current;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    if (count == 0) {
        printf("No target aimed. Mission cancelled.");
    } else {
        printf("%d targets destroyed.", count);
    }
}
