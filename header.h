#ifndef HEADER_H
#define HEADER_H

#define MAX_PATIENTS 100
#define PASSWORD 1234

typedef struct {
    char name[50];
    int age;
    char gender[10];
    int id;
    int slot; 
} Patient;

extern Patient patients[MAX_PATIENTS];
extern int patient_count;
extern char* slots[];

void admin_mode(void);
void user_mode(void);

void add_patient(void);
void edit_patient(void);
void reserve_slot(void);
void cancel_reservation(void);
void view_patient(void);
void view_reservations(void);
int find_patient(int id);
void display_slots(void);
void save_patients_to_file(void);
#endif