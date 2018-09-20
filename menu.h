#ifndef CAR_WORKSHOP_MANAGEMENT_V_0_1_MENU_H
#define CAR_WORKSHOP_MANAGEMENT_V_0_1_MENU_H
#include <stdlib.h>
#include <stdio.h>
#include "client_management.h"
#include "print_database.h"
#include "notification.h"

/**
 * @code
 * sqlite_connection()
 * @endcode
 * @note Funkcja sprawdzająca połączenie z bazą danych. Jeżeli taka baza danych nie istnieje tworzy nową. Do poprawnego działania programu wymagana jest do tej funkcji dodatkowo check_database_correct(). Nic nie otrzymuje, nic nie zwraca.
 * */

int sqlite_connection(void){


    int connection;

    connection = sqlite3_open("SQLite_database.db", &database);

    if(connection) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(database));
        return(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

}

/**
 * @code
 * check_database_correct()
 * @endcode
 * @note Funkcja sprawdzająca czy baza danych jest poprawnie utworzona. Zawiera przykład poprawnej bazy danych. Nic nie otrzymuje, nic nie zwraca.
 * */

void check_database_correct(void){

    sql = "CREATE TABLE IF NOT EXISTS CARS (ID_CAR INTEGER PRIMARY KEY AUTOINCREMENT, MARKA TEXT, MODEL TEXT,NUMER_REJESTRACYJNY TEXT,ID_PERSON INT);";
    execute_sqlite_database();
    sql = "CREATE TABLE IF NOT EXISTS PERSON(ID_PERSON INTEGER PRIMARY KEY AUTOINCREMENT,IMIE TEXT,NAZWISKO TEXT,DATA_URODZENIA TEXT,KONTAKT TEXT);";
    execute_sqlite_database();
    sql = "CREATE TABLE IF NOT EXISTS REPAIR(ID INTEGER PRIMARY KEY AUTOINCREMENT,INFORMACJA TEXT,KOSZT_NAPRAWY REAL,STATUS_ZLECENIA TEXT DEFAULT 'W trakcie',ID_CAR INT);";
    execute_sqlite_database();
}

/**
 * @code
 * sqlite_end()
 * @endcode
 * @note Funkcja zamykająca dostęp do bazy danych. Zamyka połączenie. Nic nie otrzymuje, nic nie zwraca.
 * */

void sqlite_end(void){

    sqlite3_close(database);
}


/**
 * @code
 * menu()
 * @endcode
 * @note Główna funkcja projektu. Wyświetla menu oraz zawiera opcje do przechodzenia do kolejnych etapów. Nic nie otrzymuje, nic nie zwraca.
 * */


void menu(void)
{
    char type[1];
    int choice = 0;

    sqlite_connection();

    check_database_correct();

    printf("Zarzadzanie warszatem samochodowym\n\n");
    printf("1. Dodaj zlecenie\n");
    printf("2. Usun zlecenie\n");
    printf("3. Pokaz liste zlecen\n");
    printf("4. Wyszukaj samochod\n");
    printf("5. Wyjdz\n");

    sql = "SELECT COUNT(STATUS_ZLECENIA) FROM REPAIR WHERE STATUS_ZLECENIA = 'Do odebrania'";

    execute_sqlite_database_notification();

    printf("\n");
    scanf("%s",&type);
    choice = atoi(type);

    if(choice == 1){
        add_client_to_database();
        system("cls");
        menu();

    }
    if(choice == 2){
        delete_client_in_database();
        system("cls");
        menu();
    }
    if(choice == 3){
        print_database();
        system("cls");
        menu();
    }
    if(choice == 4){
        find_car();
        system("cls");
        menu();
    }
    if(choice == 5){
        sqlite_end();
        exit(0);
    }
    if(choice < 1 || choice > 5){
        system("cls");
        menu();
    }
}


#endif //CAR_WORKSHOP_MANAGEMENT_V_0_1_MENU_H
