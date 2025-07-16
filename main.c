#include <stdio.h>

void admin_mode(void);
void user_mode(void);

int main() {
int choice;

  while (1) {
    printf("--------------------------------------\n");
    printf("      CLINIC MANAGEMENT SYSTEM        \n");
    printf("--------------------------------------\n");
    printf("    1. Admin Mode                     \n");
    printf("    2. User Mode                      \n");
    printf("    3. Exit                           \n");
    printf("--------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        admin_mode();
        break;
    case 2:
        user_mode();
        break;
    case 3:
        printf("Exiting the system.\n");
            return 0;
    default:
        printf("invalid choice , Try again\n");
    }
  }
}