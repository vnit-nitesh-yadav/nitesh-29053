# nitesh-29053
DSPD Assignment 1 – Sports Fixture Database
## Project Overview

This project implements a sports fixture management system using C language.
The database is created using an array of structures (struct Fixture) to store details such as sport name, ground, city, date, and ticket price.

The program allows users to:

Search fixtures by city and date range.

Sort fixtures by date, ground, or city.

Check availability of a sport at a given time.

Find unique sports in a location.

Detect clashing matches.

List grounds hosting at least K matches.

Sort fixtures by price for a specific game.
## Tools & Techniques Used

Language: C (ANSI C, standard libraries <stdio.h> and <string.h>).

Data Structure: Array of struct to represent fixtures.

Sorting Algorithm:

Insertion Sort (custom implementation) for:

Sorting by Date & Time (insert_sort)

Sorting by Ground (insert_sort1)

Sorting by City (insert_sort2)

Searching: String comparison (strcmp) used for matching cities, games, and dates.

User Interaction:

Menu-driven program using switch-case for multiple operations.

Takes user input for city, ground, date, time, game, etc.
##  What We Learn

Structs in C → how to organize related data (fixtures).

Sorting with Insertion Sort → applied on custom fields (date, ground, city).

String Handling in C → using strcpy, strcmp, strncpy.

Menu-driven Programming → implementing multiple functionalities in one program.

Database Simulation → managing sports fixtures without an actual DBMS.

Problem Solving → searching, sorting, filtering, and condition-based queries.
## Features Implemented

getFixturesinCity → Show all matches in a city within a date range.

getFixturesSortedonDate → Display fixtures sorted by date & time.

isAvailable → Check availability of a game at a specific date & time.

UniqueSports → Find unique sports at a ground in a city.

FindLocationsForGameInTimeRange → List locations hosting a game within a range.

ClashOfMatches → Detect matches clashing at different grounds.

GiveListOfGroundsHavingAtLeastKMatches → Find grounds with at least K matches for a list of games.

SortOnPriceForAGame → Sort and list grounds by ticket price for a game.
