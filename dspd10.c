/*This project is part of DSPD assignemnt 1, 2023.
Submitted by: Nitesh Yadav (BT22CSE086): VNIT, nagpur
Database created using array of structs.*/
#include <stdio.h>
#include <string.h>

struct Fixture {
    char sport[20];
    char ground[20];
    char city[20];
    char date[20];
    int price;
};

struct Fixture fixtures[] = {
    {"Football", "Stadium A", "City X", "2023-10-30 14:00", 50},
    {"Cricket", "Stadium B", "City X", "2023-10-30 15:00", 40},
    {"Tennis", "Tennis Club A", "City Y", "2023-10-31 10:00", 20},
};

int numFixtures = sizeof(fixtures) / sizeof(fixtures[0]);
//sorting for date , ground, and city
//insertion sorting method used
void insert_sort(struct Fixture fixtures[], int n) {
    char sport[20];
    char ground[20];
    char city[20];
    char date[20];
    int price;
    for (int i = 1; i < n; i++) {
        strcpy(sport, fixtures[i].sport);
        strcpy(ground, fixtures[i].ground);
        strcpy(city, fixtures[i].city);
        strcpy(date, fixtures[i].date);
        price = fixtures[i].price;
        int j = i - 1;
        while (strcmp(date, fixtures[j].date) < 0 && j >= 0) { //sorting for date 
            strcpy(fixtures[j + 1].sport, fixtures[j].sport);
            strcpy(fixtures[j + 1].ground, fixtures[j].ground);
            strcpy(fixtures[j + 1].city, fixtures[j].city);
            strcpy(fixtures[j + 1].date, fixtures[j].date);
            fixtures[j + 1].price = fixtures[j].price;
            j--;
        }
        strcpy(fixtures[j + 1].sport, sport);
        strcpy(fixtures[j + 1].ground, ground);
        strcpy(fixtures[j + 1].city, city);
        strcpy(fixtures[j + 1].date, date);
        fixtures[j + 1].price = price;
    }
}

void insert_sort1(struct Fixture fixtures[], int n) {
    char sport[20];
    char ground[20];
    char city[20];
    char date[20];
    int price;
    for (int i = 1; i < n; i++) {
        strcpy(sport, fixtures[i].sport);
        strcpy(ground, fixtures[i].ground);
        strcpy(city, fixtures[i].city);
        strcpy(date, fixtures[i].date);
        price = fixtures[i].price;
        int j = i - 1;
        while (strcmp(ground, fixtures[j].ground) < 0 && j >= 0) { //sorting for ground
            strcpy(fixtures[j + 1].sport, fixtures[j].sport);
            strcpy(fixtures[j + 1].ground, fixtures[j].ground);
            strcpy(fixtures[j + 1].city, fixtures[j].city);
            strcpy(fixtures[j + 1].date, fixtures[j].date);
            fixtures[j + 1].price = fixtures[j].price;
            j--;
        }
        strcpy(fixtures[j + 1].sport, sport);
        strcpy(fixtures[j + 1].ground, ground);
        strcpy(fixtures[j + 1].city, city);
        strcpy(fixtures[j + 1].date, date);
        fixtures[j + 1].price = price;
    }
}

void insert_sort2(struct Fixture fixtures[], int n) {
    char sport[20];
    char ground[20];
    char city[20];
    char date[20];
    int price;
    for (int i = 1; i < n; i++) {
        strcpy(sport, fixtures[i].sport);
        strcpy(ground, fixtures[i].ground);
        strcpy(city, fixtures[i].city);
        strcpy(date, fixtures[i].date);
        price = fixtures[i].price;
        int j = i - 1;
        while (strcmp(city, fixtures[j].city) < 0 && j >= 0) { //sorting for city
            strcpy(fixtures[j + 1].sport, fixtures[j].sport);
            strcpy(fixtures[j + 1].ground, fixtures[j].ground);
            strcpy(fixtures[j + 1].city, fixtures[j].city);
            strcpy(fixtures[j + 1].date, fixtures[j].date);
            fixtures[j + 1].price = fixtures[j].price;
            j--;
        }
        strcpy(fixtures[j + 1].sport, sport);
        strcpy(fixtures[j + 1].ground, ground);
        strcpy(fixtures[j + 1].city, city);
        strcpy(fixtures[j + 1].date, date);
        fixtures[j + 1].price = price;
    }
}

void getFixturesinCity(char city[], char start_date[], char end_date[]) {
    printf("Sports happening in %s from %s to %s:\n", city, start_date, end_date);
    for (int i = 0; i < numFixtures; i++) {
        if (strcmp(fixtures[i].city, city) == 0 &&
            strcmp(fixtures[i].date, start_date) >= 0 &&
            strcmp(fixtures[i].date, end_date) <= 0) {
            printf("%s at %s on %s, Price: %d\n", fixtures[i].sport, fixtures[i].ground, fixtures[i].date, fixtures[i].price);
        }
    }
}

void getFixturesSortedonDate() {
    printf("Sports fixtures sorted by date and time:\n");
    for (int i = 0; i < numFixtures; i++) {
        printf("%s at %s in %s on %s, Price: %d\n", fixtures[i].sport, fixtures[i].ground, fixtures[i].city, fixtures[i].date, fixtures[i].price);
    }
}

void isAvailable(char game[], char date_time[]) {
    printf("Available grounds for %s on %s:\n", game, date_time);
    for (int i = 0; i < numFixtures; i++) {
        if (strcmp(fixtures[i].sport, game) == 0 && strcmp(fixtures[i].date, date_time) == 0) {
            printf("%s in %s, Price: %d\n", fixtures[i].ground, fixtures[i].city, fixtures[i].price);
        }
    }
}

void UniqueSports(char ground[], char city[]) {
    printf("Unique sports at %s in %s:\n", ground, city);
    for (int i = 0; i < numFixtures; i++) {
        if (strcmp(fixtures[i].ground, ground) == 0 && strcmp(fixtures[i].city, city) == 0) {
            printf("%s\n", fixtures[i].sport);
        }
    }
}

void FindLocationsForGameInTimeRange(char game[], char start_date[], char end_date[]) {
    printf("Locations for %s from %s to %s:\n", game, start_date, end_date);
    for (int i = 0; i < numFixtures; i++) {
        if (strcmp(fixtures[i].sport, game) == 0 &&
            strcmp(fixtures[i].date, start_date) >= 0 &&
            strcmp(fixtures[i].date, end_date) <= 0) {
            printf("%s in %s\n", fixtures[i].ground, fixtures[i].city);
        }
    }
}

void ClashOfMatches(char ground_list[][20], char date[], char game[]) {
    printf("Clashing matches for %s on %s:\n", game, date);
    int num_grounds = sizeof(ground_list) / sizeof(ground_list[0]);

    for (int i = 0; i < numFixtures; i++) {
        for (int j = 0; j < num_grounds; j++) {
            if (strcmp(fixtures[i].ground, ground_list[j]) == 0 &&
                strcmp(fixtures[i].date, date) == 0 &&
                strcmp(fixtures[i].sport, game) == 0) {
                printf("%s at %s in %s, Price: %d\n", fixtures[i].sport, fixtures[i].ground, fixtures[i].city, fixtures[i].price);
            }
        }
    }
}

void GiveListOfGroundsHavingAtLeastKMatches(char game_list[][20], char date[], char city[], int K) {
    printf("Grounds in %s with at least %d matches for the specified games on %s:\n", city, K, date);
    for (int i = 0; i < numFixtures; i++) {
        if (strcmp(fixtures[i].city, city) == 0) {
            int matchCount = 0;
            for (int j = 0; j < sizeof(game_list) / sizeof(game_list[0]); j++) {
                if (strcmp(fixtures[i].sport, game_list[j]) == 0 && strcmp(fixtures[i].date, date) == 0) {
                    matchCount++;
                }
            }
            if (matchCount >= K) {
                printf("%s at %s, Price: %d\n", fixtures[i].ground, fixtures[i].city, fixtures[i].price);
            }
        }
    }
}

void SortOnPriceForAGame(char game[], char date[], char time[]) {
    printf("Grounds for %s on %s at %s sorted by price:\n", game, date, time);

    for (int i = 0; i < numFixtures; i++) {
        if (strcmp(fixtures[i].sport, game) == 0) {
            char fixtureDate[20];
            strcpy(fixtureDate, fixtures[i].date);

            // Check if the fixture date is the same as the input date
            if (strcmp(fixtureDate, date) == 0) {
                // Extract the time from the fixture date
                char fixtureTime[20];
                strncpy(fixtureTime, fixtureDate + 11, 5); // Extract HH:MM from "YYYY-MM-DD HH:MM"
                
                // Compare the extracted time with the provided time
                if (strcmp(fixtureTime, time) >= 0) {
                    printf("%s in %s, Price: %d\n", fixtures[i].ground, fixtures[i].city, fixtures[i].price);
                }
            }
        }
    }
}

//size of array string is passed here in main
int main() {
    char choice;
    char city[20], start_date[20], end_date[20];
    char game[20], date_time[20];
    char ground[20], city_name[20];
    char game_name[20], start_date_range[20], end_date_range[20];
    char ground_list[2][20];
    char game_list[2][20];
    char date[20], time[20];
    int K;

    do {
        printf("\nMenu:\n");
        printf("a. getFixturesinCity\n");
        printf("b. getFixturesSortedonDate\n");
        printf("c. isAvailable\n");
        printf("d. UniqueSports\n");
        printf("e. FindLocationsForGameInTimeRange\n");
        printf("f. ClashOfMatches\n");
        printf("g. GiveListOfGroundsHavingAtLeastKMatches\n");
        printf("h. SortOnPriceForAGame\n");
        printf("Enter your choice (q to quit): ");
        scanf(" %c", &choice);
        //we used here switch case for running the program for each condition
        //and taking command according to the condition for each
        switch (choice) {
            case 'a':
                printf("Enter city: ");
                scanf("%s", city);
                printf("Enter start date (YYYY-MM-DD HH:MM): ");
                scanf("%s", start_date);
                printf("Enter end date (YYYY-MM-DD HH:MM): ");
                scanf("%s", end_date);
                getFixturesinCity(city, start_date, end_date);
                break;
            case 'b':
                getFixturesSortedonDate();
                break;
            case 'c':
                printf("Enter game: ");
                scanf("%s", game);
                printf("Enter date and time (YYYY-MM-DD HH:MM): ");
                scanf("%s", date_time);
                isAvailable(game, date_time);
                break;
            case 'd':
                printf("Enter ground name: ");
                scanf("%s", ground);
                printf("Enter city: ");
                scanf("%s", city_name);
                UniqueSports(ground, city_name);
                break;
            case 'e':
                printf("Enter game name: ");
                scanf("%s", game_name);
                printf("Enter start date (YYYY-MM-DD HH:MM): ");
                scanf("%s", start_date_range);
                printf("Enter end date (YYYY-MM-DD HH:MM): ");
                scanf("%s", end_date_range);
                FindLocationsForGameInTimeRange(game_name, start_date_range, end_date_range);
                break;
            case 'f':
                printf("Enter the list of grounds (comma-separated): ");
                scanf("%s", ground_list[0]);
                scanf("%s", ground_list[1]);
                printf("Enter date: ");
                scanf("%s", date);
                printf("Enter game: ");
                scanf("%s", game);
                ClashOfMatches(ground_list, date, game);
                break;
            case 'g':
                printf("Enter the list of games (comma-separated): ");
                scanf("%s", game_list[0]);
                scanf("%s", game_list[1]);
                printf("Enter date: ");
                scanf("%s", date);
                printf("Enter city: ");
                scanf("%s", city_name);
                printf("Enter K: ");
                scanf("%d", &K);
                GiveListOfGroundsHavingAtLeastKMatches(game_list, date, city_name, K);
                break;
            case 'h':
                printf("Enter game: ");
                scanf("%s", game);
                printf("Enter date (YYYY-MM-DD): ");
                scanf("%s", date);
                printf("Enter time (HH:MM): ");
                scanf("%s", time);
                SortOnPriceForAGame(game, date, time);
                break;
            case 'q':
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice.\n"); //if user chooses out of data menu
        }
    } while (choice != 'q');
    return 0;
}
