
#include <stdio.h>

#define N 8
#define BASE 5
#define RATE 3
#define DISCOUNT 0.10

char stops[N][40] = {
    "UPES Bidholi",
    "UPES Kandoli",
    "Pondha",
    "Nanda Ki Chowki",
    "Prem Nagar",
    "Ballupur Chowk",
    "ISBT Dehradun",
    "Railway Station"
};

/* Approximate distances between stops in km */
double distance[N][N] = {
    {0,3.9,6.5,9.5,12.0,16.1,21.5,19.5},
    {3.9,0,2.9,5.9,8.4,12.5,17.9,15.9},
    {6.5,2.9,0,3.0,5.5,9.6,15.0,13.0},
    {9.5,5.9,3.0,0,2.5,6.6,12.0,10.0},
    {12.0,8.4,5.5,2.5,0,5.3,11.5,9.8},
    {16.1,12.5,9.6,6.6,5.3,0,6.2,4.5},
    {21.5,17.9,15.0,12.0,11.5,6.2,0,4.0},
    {19.5,15.9,13.0,10.0,9.8,4.5,4.0,0}
};

double fareTable[N][N];

/* Clear remaining characters from the input line */
void clearInput() {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

/* Generate predefined fares from the distance table */
void createFareTable() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                fareTable[i][j] = 0;
            else
                fareTable[i][j] = BASE + distance[i][j] * RATE;
        }
    }
}

void showStops() {
    printf("\n----- AVAILABLE STOPS -----\n");

    for (int i = 0; i < N; i++)
        printf("%d. %s\n", i + 1, stops[i]);
}

void calculateFare() {
    int from, to, student;
    double km, fare, concession, finalFare;

    showStops();

    printf("\nEnter pickup stop: ");
    if (scanf("%d", &from) != 1) {
        printf("Invalid input!\n");
        clearInput();
        return;
    }
    clearInput();

    printf("Enter destination stop: ");
    if (scanf("%d", &to) != 1) {
        printf("Invalid input!\n");
        clearInput();
        return;
    }
    clearInput();

    if (from < 1 || from > N ||
        to < 1 || to > N || from == to) {
        printf("Invalid stop selection!\n");
        return;
    }

    printf("Are you a student? (1=Yes, 0=No): ");
    if (scanf("%d", &student) != 1) {
        printf("Invalid input!\n");
        clearInput();
        return;
    }
    clearInput();

    if (student != 0 && student != 1) {
        printf("Invalid student selection!\n");
        return;
    }

    km = distance[from - 1][to - 1];

    if (km <= 0) {
        printf("Distance unavailable!\n");
        return;
    }

    fare = fareTable[from - 1][to - 1];

    concession = 0;

    if (student == 1)
        concession = fare * DISCOUNT;

    finalFare = fare - concession;

    printf("\n------- JOURNEY DETAILS -------\n");
    printf("From: %s\n", stops[from - 1]);
    printf("To: %s\n", stops[to - 1]);
    printf("Distance: %.2f km\n", km);
    printf("Base Charge: Rs. %.2f\n", (double)BASE);
    printf("Distance Charge: Rs. %.2f\n", km * RATE);
    printf("Fare Before Concession: Rs. %.2f\n", fare);
    printf("Student Concession: Rs. %.2f\n", concession);
    printf("Final Fare: Rs. %.2f\n", finalFare);

    FILE *fp = fopen("history.txt", "a");

    if (fp != NULL) {
        fprintf(fp, "%s to %s | %.2f km | Rs. %.2f\n",
                stops[from - 1], stops[to - 1],
                km, finalFare);

        fclose(fp);
        printf("Journey saved successfully!\n");
    } else {
        printf("Could not save journey history.\n");
    }
}

void viewHistory() {
    FILE *fp = fopen("history.txt", "r");
    char line[150];

    if (fp == NULL) {
        printf("\nNo journey history found.\n");
        return;
    }

    printf("\n------- JOURNEY HISTORY -------\n");

    while (fgets(line, sizeof(line), fp) != NULL)
        printf("%s", line);

    fclose(fp);
}

void viewFareChart() {
    int from;

    showStops();

    printf("\nEnter starting stop: ");

    if (scanf("%d", &from) != 1) {
        printf("Invalid input!\n");
        clearInput();
        return;
    }
    clearInput();

    if (from < 1 || from > N) {
        printf("Invalid stop!\n");
        return;
    }

    printf("\nFare Chart from %s:\n", stops[from - 1]);

    for (int i = 0; i < N; i++) {
        if (i == from - 1)
            continue;

        printf("%s: %.2f km | Rs. %.2f\n",
               stops[i],
               distance[from - 1][i],
               fareTable[from - 1][i]);
    }

    printf("Fares shown before student concession.\n");
}

int main() {
    int choice;

    createFareTable();

    do {
        printf("\n===== UPES SHUTTLE CALCULATOR =====\n");
        printf("1. Calculate Fare\n");
        printf("2. View Available Stops\n");
        printf("3. View Fare Chart\n");
        printf("4. View Journey History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Try again.\n");
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
                calculateFare();
                break;

            case 2:
                showStops();
                break;

            case 3:
                viewFareChart();
                break;

            case 4:
                viewHistory();
                break;

            case 5:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
