#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

Patient patients[MAX_PATIENTS];
int patient_count = 0;
char* slots[] = {"2pm - 2:30pm", "2:30pm - 3pm", "3pm - 3:30pm", "4pm - 4:30pm", "4:30pm - 5pm"};

void admin_mode(void) {
    int pass, x = 0;

    while (x < 3) {
        printf("\n----------------------------------------\n");
        printf("          ADMIN AUTHENTICATION\n");
        printf("----------------------------------------\n");
        printf("Enter Admin Password: ");
        scanf("%d", &pass);
        if (pass == PASSWORD) break;
        x++;
        printf("Invalid password! Attempts left: %d\n", 3-x);
    }
    if (x == 3) {
        printf("\nAccess Denied. System Closing.\n");
        exit(0);
    }

    int choice;
    do {
        printf("\n----------------------------------------\n");
        printf("             ADMIN MENU\n");
        printf("----------------------------------------\n");
        printf("1. Add New Patient\n");
        printf("2. Edit Patient Details\n");
        printf("3. Reserve Appointment Slot\n");
        printf("4. Cancel Reservation\n");
        printf("5. Return to Main Menu\n");
        printf("----------------------------------------\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                 add_patient(); 
            break;
            case 2: 
                 edit_patient(); 
            break;
            case 3: 
                 reserve_slot(); 
            break;
            case 4:
                cancel_reservation();
            break;
            case 5: 
                 printf("Returning to Main Menu...\n");
            break;
            default: 
                 printf("Invalid option.\n");
        }
    } while (choice != 5);
}


void user_mode(void) {
    int choice;
    do {
        printf("\n----------------------------------------\n");
        printf("             USER MENU\n");
        printf("----------------------------------------\n");
        printf("1. View Patient Record\n");
        printf("2. View Today's Appointments\n");
        printf("3. Return to Main Menu\n");
        printf("----------------------------------------\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                view_patient(); 
            break;
            case 2: 
                view_reservations();
            break;
            case 3: 
                printf("Returning to Main Menu...\n");
            break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 3);
}

int find_patient(int id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == id) return i;
    }
    return -1;
}

void add_patient(void) {
    Patient p;
    printf("Enter ID: ");
    scanf("%d", &p.id);
    if (find_patient(p.id) != -1) {
        printf("ID already exists.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender: ");
    scanf(" %s", p.gender);
    p.slot = -1;

    patients[patient_count++] = p;
    printf("Patient added.\n");
}

void edit_patient(void) {
    int id;
    printf("Enter ID to edit: ");
    scanf("%d", &id);
    int idx = find_patient(id);
    if (idx == -1) {
        printf("ID not found.\n");
        return;
    }

    printf("Enter new Name: ");
    scanf(" %[^\n]", patients[idx].name);
    printf("Enter new Age: ");
    scanf("%d", &patients[idx].age);
    printf("Enter new Gender: ");
    scanf(" %s", patients[idx].gender);
    printf("Patient updated successfully.\n");
    
    if (patients[idx].slot != -1) {
        save_patients_to_file();
    }
}

void display_slots(void) {
    printf("Available Slots:\n");
    for (int i = 0; i < 5; i++) {
        int taken = 0;
        for (int j = 0; j < patient_count; j++) {
            if (patients[j].slot == i) {
                taken = 1;
                break;
            }
        }
        if (!taken) printf("%d. %s\n", i + 1, slots[i]);
    }
}

void reserve_slot(void) {
    int id, choice;
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    int idx = find_patient(id);
    if (idx == -1) {
        printf("ID not found.\n");
        return;
    }

    display_slots();
    printf("Choose slot (1-5): ");
    scanf("%d", &choice);
    choice--;

    for (int j = 0; j < patient_count; j++) {
        if (patients[j].slot == choice) {
            printf("Slot already taken.\n");
            return;
        }
    }

    patients[idx].slot = choice;
    printf("Slot reserved.\n");
    save_patients_to_file();
}

void cancel_reservation(void) {
    int id;
    printf("Enter Patient ID to cancel reservation: ");
    scanf("%d", &id);
    int idx = find_patient(id);
    if (idx == -1) {
        printf("ID not found.\n");
        return;
    }

    patients[idx].slot = -1;
    printf("Reservation cancelled successfully.\n");
    save_patients_to_file();
}

void view_patient(void) {
    int id;
    printf("\n----------------------------------------\n");
    printf("        PATIENT RECORD SEARCH\n");
    printf("----------------------------------------\n");
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    
    int idx = find_patient(id);
    if (idx == -1) {
        printf("\nPatient with ID %d not found.\n", id);
        return;
    }

    printf("\n----------------------------------------\n");
    printf("          PATIENT INFORMATION\n");
    printf("----------------------------------------\n");
    printf("Patient ID:    %d\n", patients[idx].id);
    printf("Name:          %s\n", patients[idx].name);
    printf("Age:           %d\n", patients[idx].age);
    printf("Gender:        %s\n", patients[idx].gender);
    
    if (patients[idx].slot != -1) {
        printf("Appointment:   %s\n", slots[patients[idx].slot]);
    } else {
        printf("Appointment:   No reservation\n");
    }
    printf("----------------------------------------\n");
}

void view_reservations(void) {
    printf("\n+-------+----------------------+---------------+\n");
    printf("| Slot  | Time                 | Status        |\n");
    printf("+-------+----------------------+---------------+\n");
    
    for (int i = 0; i < 5; i++) {
        int reserved = 0;
        for (int j = 0; j < patient_count; j++) {
            if (patients[j].slot == i) {
                printf("| %-5d | %-20s | Reserved: %-4d|\n", 
                      i+1, slots[i], patients[j].id);
                reserved = 1;
                break;
            }
        }
        if (!reserved) {
            printf("| %-5d | %-20s | Available     |\n", i+1, slots[i]);
        }
    }
    printf("+-------+----------------------+---------------+\n");
}

void save_patients_to_file() {
    FILE *file = fopen("patients.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }
    fprintf(file, "ID,Name,Age,Gender,Appointment\n");
    
    for (int i = 0; i < patient_count; i++) {
        char appointment[50];
        if (patients[i].slot != -1) {
            strcpy(appointment, slots[patients[i].slot]);
        } else {
            strcpy(appointment, "No reservation");
        }
        
        fprintf(file, "%d,%s,%d,%s,%s\n", 
                patients[i].id,
                patients[i].name,
                patients[i].age,
                patients[i].gender,
                appointment);
    }
    fclose(file);
}