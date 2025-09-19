//Student Attendance Scheduler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SESSIONS 200
#define DAYS 6
#define SUBJECT_LENGTH 50
#define FACULTY_LENGTH 50
#define FILENAME "schedule.txt"

#ifdef _WIN32
#include <windows.h>
void initColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004;
    SetConsoleMode(hOut, dwMode);
}
#else
void initColors() {}
#endif

const char* dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

typedef struct {
    char subject[SUBJECT_LENGTH];
    char faculty[FACULTY_LENGTH];
    int day;
    int startHour, startMinute;
    int endHour, endMinute;
} Session;

Session sessions[MAX_SESSIONS];
int sessionCount = 0;

void printColor(const char* text, const char* color) {
    printf("%s%s\033[0m", color, text);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inputSession(Session* s) {
    printColor("Enter subject name: ", "\033[35m");
    fgets(s->subject, SUBJECT_LENGTH, stdin);
    s->subject[strcspn(s->subject, "\n")] = '\0';

    printColor("Enter faculty name: ", "\033[35m");
    fgets(s->faculty, FACULTY_LENGTH, stdin);
    s->faculty[strcspn(s->faculty, "\n")] = '\0';

    printColor("Enter day (0-Monday to 5-Saturday): ", "\033[35m");
    scanf("%d", &s->day);

    printColor("Enter start time (HH MM): ", "\033[35m");
    scanf("%d %d", &s->startHour, &s->startMinute);

    printColor("Enter end time (HH MM): ", "\033[35m");
    scanf("%d %d", &s->endHour, &s->endMinute);

    clearInputBuffer();
}

bool isConflict(Session s1, Session s2) {
    if (s1.day != s2.day) return false;
    int start1 = s1.startHour * 60 + s1.startMinute;
    int end1 = s1.endHour * 60 + s1.endMinute;
    int start2 = s2.startHour * 60 + s2.startMinute;
    int end2 = s2.endHour * 60 + s2.endMinute;
    if (start1 < end2 && start2 < end1) return true;
    if (strcmp(s1.faculty, s2.faculty) == 0 && start1 == start2) return true;
    return false;
}

bool addSession(Session s) {
    for (int i = 0; i < sessionCount; i++) {
        if (isConflict(s, sessions[i])) {
            return false;
        }
    }
    sessions[sessionCount++] = s;
    return true;
}

void displaySchedule() {
    printColor("\n======= Weekly Schedule =======\n", "\033[36;1m");
    for (int d = 0; d < DAYS; d++) {
        printf("\n\033[33m--- %s ---\033[0m\n", dayNames[d]);
        for (int i = 0; i < sessionCount; i++) {
            if (sessions[i].day == d) {
                printf("\033[34m+--------------------------------------------------+\n");
                printf("| \033[32m%-10s\033[34m | \033[36m%-10s\033[34m | \033[35m%02d:%02d - %02d:%02d \033[34m|\n",
                    sessions[i].subject, sessions[i].faculty,
                    sessions[i].startHour, sessions[i].startMinute,
                    sessions[i].endHour, sessions[i].endMinute);
                printf("+--------------------------------------------------+\033[0m\n");
            }
        }
    }
}

void saveToFile() {
    FILE* fp = fopen(FILENAME, "w");
    if (!fp) return;
    for (int i = 0; i < sessionCount; i++) {
        fprintf(fp, "%s,%s,%d,%d,%d,%d,%d\n",
            sessions[i].subject, sessions[i].faculty, sessions[i].day,
            sessions[i].startHour, sessions[i].startMinute,
            sessions[i].endHour, sessions[i].endMinute);
    }
    fclose(fp);
    printColor("Schedule saved successfully!\n", "\033[32m");
}

void loadFromFile() {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) return;
    sessionCount = 0;
    while (fscanf(fp, "%[^,],%[^,],%d,%d,%d,%d,%d\n",
        sessions[sessionCount].subject, sessions[sessionCount].faculty,
        &sessions[sessionCount].day, &sessions[sessionCount].startHour,
        &sessions[sessionCount].startMinute, &sessions[sessionCount].endHour,
        &sessions[sessionCount].endMinute) == 7) {
            sessionCount++;
    }
    fclose(fp);
}

void editSession() {
    displaySchedule();
    printColor("Enter session index to edit: ", "\033[35m");
    int index;
    scanf("%d", &index);
    clearInputBuffer();
    if (index >= 0 && index < sessionCount) {
        Session temp;
        inputSession(&temp);
        sessions[index] = temp;
        printColor("Session updated successfully!\n", "\033[32m");
    } else {
        printColor("Invalid session index!\n", "\033[31m");
    }
}

void deleteSession() {
    displaySchedule();
    printColor("Enter session index to delete: ", "\033[35m");
    int index;
    scanf("%d", &index);
    if (index >= 0 && index < sessionCount) {
        for (int i = index; i < sessionCount-1; i++) {
            sessions[i] = sessions[i+1];
        }
        sessionCount--;
        printColor("Session deleted successfully!\n", "\033[32m");
    } else {
        printColor("Invalid session index!\n", "\033[31m");
    }
}

void autoGenerate() {
    char subjects[][SUBJECT_LENGTH] = {"Math", "Physics", "Chemistry", "Biology", "CS", "English"};
    char faculty[][FACULTY_LENGTH] = {"Prof.A", "Prof.B", "Prof.C", "Prof.D", "Prof.E", "Prof.F"};
    int startHour[] = {8, 9, 10, 11, 13, 14};
    int startMinute[] = {30, 30, 30, 30, 30, 30};
    sessionCount = 0;
    for (int d = 0; d < DAYS; d++) {
        for (int s = 0; s < 6; s++) {
            Session temp;
            strcpy(temp.subject, subjects[s]);
            strcpy(temp.faculty, faculty[s]);
            temp.day = d;
            temp.startHour = startHour[s];
            temp.startMinute = startMinute[s];
            temp.endHour = temp.startHour + 1;
            temp.endMinute = temp.startMinute;
            addSession(temp);
        }
    }
    printColor("Auto-generated weekly schedule!\n", "\033[32m");
}

int main() {
    initColors();
    loadFromFile();
    int choice;
    do {
        printColor("\n========= WindSurf - Smart Scheduler =========\n", "\033[34;1m");
        printColor("1. Add New Session\n", "\033[33m");
        printColor("2. Display Schedule\n", "\033[33m");
        printColor("3. Edit Session\n", "\033[33m");
        printColor("4. Delete Session\n", "\033[33m");
        printColor("5. Save to File\n", "\033[33m");
        printColor("6. Auto-Generate Weekly Schedule\n", "\033[33m");
        printColor("7. Exit\n", "\033[33m");
        printColor("Enter your choice: ", "\033[35m");
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice) {
            case 1: {
                Session temp;
                inputSession(&temp);
                if (addSession(temp))
                    printColor("Session added!\n", "\033[32m");
                else
                    printColor("Conflict detected! Cannot add session.\n", "\033[31m");
                break;
            }
            case 2:
                displaySchedule();
                break;
            case 3:
                editSession();
                break;
            case 4:
                deleteSession();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                autoGenerate();
                break;
            case 7:
                saveToFile();
                printColor("Exiting...\n", "\033[33m");
                break;
            default:
                printColor("Invalid choice!\n", "\033[31m");
        }
    } while (choice != 7);

    return 0;
}
