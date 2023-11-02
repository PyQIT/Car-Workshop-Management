#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "menu.h"

/* 28.05.2018 */

/**
 * @code
 * main()
 * @endcode
 * @note Główna funkcja projektu. Po starcie uruchamia menu programu.
 * */
=======

sqlite3* database;
sqlite3_stmt *stmt;

char *sql;

int first_row;

static int callback(void *data, int argc, char **argv, char **azColName){

    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {

    int i;

    int* nof_records = (int*) p_data;
    (*nof_records)++;

    if (first_row) {
        first_row = 0;

        printf("%1s", p_col_names[0]);

        for (i=1; i < num_fields; i++) {
            printf("%16s", p_col_names[i]);
        }

        printf("\n");
        for (i=0; i< num_fields*15; i++) {
            printf("=");
        }
        printf("\n");
    }

    printf("%2s", p_fields[0]);

    for(i=1; i < num_fields; i++) {
        if (p_fields[i]) {
            printf("%16s", p_fields[i]);
        }
        else {
            printf("%16s", " ");
        }
    }

    printf("\n");
    return 0;
}

void select_stmt(const char* stmt) {
    char *errmsg;
    int   ret;
    int   nrecs = 0;

    first_row = 1;

    ret = sqlite3_exec(database, stmt, select_callback, &nrecs, &errmsg);

    if(ret!=SQLITE_OK) {
        printf("Error in select statement %s [%s].\n", stmt, errmsg);
        sqlite3_free(errmsg);
    }
    else {
        fprintf(stdout, "\n\nOperation done successfully\n");
    }
}

void execute_sqlite_database();
void execute_sqlite_database_ID();

static int callback_ID_PERSON(void *data, int argc, char **argv, char **azColName){

    int i;
    char notification[20];
    int not = 0;
    char buffor1[300];
    char mark[25];
    char model[30];
    char registration_number[20];



    for(i = 0; i<argc; i++){
        sprintf(notification, "%s", argv[i] ? argv[i] : "NULL");
    }

    not = atoi(notification);

    printf("Marka: ");
    scanf("%s",&mark);
    printf("Model: ");
    scanf("%s",&model);
    printf("Numer rejestracyjny: ");
    scanf("%s",&registration_number);

    sprintf(buffor1, "insert into CARS (MARKA, MODEL, NUMER_REJESTRACYJNY, ID_PERSON) values (\"%s\",\"%s\",\"%s\",\"%d\") ",mark, model, registration_number,not);

    sql = buffor1;
    execute_sqlite_database();

    sql = "SELECT (ID_CAR) FROM CARS WHERE ID_CAR=(SELECT max(ID_CAR) FROM CARS)";
    execute_sqlite_database_ID();

    return 0;
}

void execute_sqlite_database_ID_PERSON(){

    int rc;
    char *errmsg;
    const char* data = " ";

    rc = sqlite3_exec(database, sql, callback_ID_PERSON, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

static int callback_ID(void *data, int argc, char **argv, char **azColName){

    int i;
    char notification[20];
    int not = 0;
    char buffor1[300];
    char information[300];
    double cost;
    char status[10] = "W trakcie";

    for(i = 0; i<argc; i++){
        sprintf(notification, "%s", argv[i] ? argv[i] : "NULL");
    }

    not = atoi(notification);

    printf("Informacja odnosnie naprawy: ");
    scanf("%s",&information);
    printf("Koszt naprawy: ");
    scanf("%lf",&cost);

    sprintf(buffor1, "insert into REPAIR (INFORMACJA, KOSZT_NAPRAWY, STATUS_ZLECENIA, ID_CAR) values (\"%s\",\"%lf\",\"%s\",\"%d\") ",information, cost,status,not);

    sql = buffor1;
    execute_sqlite_database();

    return 0;
}

void execute_sqlite_database_ID(){

    int rc;
    char *errmsg;
    const char* data = " ";

    rc = sqlite3_exec(database, sql, callback_ID, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

static int callback_notification(void *data, int argc, char **argv, char **azColName){

    int i;
    char notification[20];
    int not = 0;

    for(i = 0; i<argc; i++){
        sprintf(notification, "%s", argv[i] ? argv[i] : "NULL");
    }

    not = atoi(notification);


    if(not > 0) {
        printf("\nPowiadomienie:");
        printf("\nW warsztacie znajduja sie nieodebrane pojazdy");
    }
    return 0;
}

void execute_sqlite_database_notification(){

    int rc;
    char *errmsg;
    const char* data = " ";

    rc = sqlite3_exec(database, sql, callback_notification, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

void execute_sqlite_database(){

    int rc;
    char *errmsg;
    const char* data = "Zlecenie ";

    rc = sqlite3_exec(database, sql, callback, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

int sqlite_connection(){


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

void check_database_correct(){

    sql = "CREATE TABLE IF NOT EXISTS CARS (ID_CAR INT PRIMARY KEY AUTOINCREMENT, MARKA TEXT, MODEL TEXT,NUMER_REJESTRACYJNY TEXT,ID_PERSON INT);";
    execute_sqlite_database();
    sql = "CREATE TABLE IF NOT EXISTS PERSON(ID_PERSON INT PRIMARY KEY AUTOINCREMENT,IMIE TEXT,NAZWISKO TEXT,DATA_URODZENIA TEXT,KONTAKT TEXT);";
    execute_sqlite_database();
    sql = "CREATE TABLE IF NOT EXISTS REPAIR(ID INT PRIMARY KEY AUTOINCREMENT,INFORMACJA TEXT,KOSZT_NAPRAWY REAL,STATUS_ZLECENIA TEXT DEFAULT 'W trakcie',ID_CAR INT);";
    execute_sqlite_database();
}

void menu();

void sqlite_end(){

    sqlite3_close(database);
}

int add_person();

int add_client_to_database(){

    int swap = 0;
    int choose = 0;
    int choose_ID_PERSON = 0;
    int choose_ID_CAR = 0;
    int choose_ID_CAR_IF_EXISTS = 0;
    char buffor[300];
    char buffor1[300];
    char information[300];
    double cost;
    char status[10] = "W trakcie";

    system("cls");
    printf("\nUzupelnianie zlecenia\n\n");

    printf("1. Nowy klient\n");
    printf("2. Staly klient\n");
    scanf("%d",&choose);

    if(choose == 1){
        system("cls");
        add_person();

        sql = "SELECT (ID_PERSON) FROM PERSON WHERE ID_PERSON=(SELECT max(ID_PERSON) FROM PERSON)";
        execute_sqlite_database_ID_PERSON();

    }

    if(choose == 2){
        system("cls");
        select_stmt("SELECT ID_PERSON, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT FROM PERSON");
        printf("\n\nPodaj ID osoby: ");
        scanf("%d",&choose_ID_PERSON);

        sprintf(buffor, "SELECT ID_CAR, MARKA,MODEL,NUMER_REJESTRACYJNY FROM CARS WHERE ID_PERSON =  \"%d\"", choose_ID_PERSON);
        select_stmt(buffor);

        printf("\n\n1.Wpisany samochod");
        printf("\n2.Nowy samochod");
        scanf("%d",&choose_ID_CAR);

        if(choose_ID_CAR == 1){

            printf("\n\nPodaj ID samochodu: ");
            scanf("%d",&choose_ID_CAR_IF_EXISTS);
            printf("Informacja odnosnie naprawy: ");
            scanf("%s",&information);
            printf("Koszt naprawy: ");
            scanf("%lf",&cost);



            sprintf(buffor1, "insert into REPAIR (INFORMACJA, KOSZT_NAPRAWY, STATUS_ZLECENIA, ID_CAR) values (\"%s\",\"%lf\",\"%s\") ",information, cost,status);

            sql = buffor1;
            execute_sqlite_database();
        }

        if(choose_ID_CAR == 2){

            char mark[25];
            char model[30];
            char registration_number[20];

            printf("\nMarka: ");
            scanf("%s",&mark);
            printf("Model: ");
            scanf("%s",&model);
            printf("Numer rejestracyjny: ");
            scanf("%s",&registration_number);

            char buffor[300];

            sprintf(buffor, "insert into CARS (MARKA, MODEL, NUMER_REJESTRACYJNY, ID_PERSON) values (\"%s\",\"%s\",\"%s\",\"%d\")",mark, model, registration_number, choose_ID_PERSON);

            sql = buffor;
            execute_sqlite_database();

            sql = "SELECT (ID_CAR) FROM CARS WHERE ID_CAR=(SELECT max(ID_CAR) FROM CARS)";
            execute_sqlite_database_ID();

        }

    }

    printf("\n\nNacisnij 1 by wrocic do menu \n");
    scanf("%d", &swap);
    if(swap == 1)
        system("cls");
    menu();
}

int add_person(){

    char name[40];
    char surname[50];
    char birth[15];
    char contact[40];

    printf("Imie: ");
    scanf("%s",&name);
    printf("Nazwisko: ");
    scanf("%s",&surname);
    printf("Data urodzenia: ");
    scanf("%s",&birth);
    printf("Kontakt: ");
    scanf("%s",&contact);

    char buffor[300];

    sprintf(buffor, "insert into PERSON (IMIE, NAZWISKO, DATA_URODZENIA, KONTAKT) values (\"%s\",\"%s\",\"%s\",\"%s\") ",name, surname, birth, contact);

    sql = buffor;
    execute_sqlite_database();
}

void delete_client_in_database(){

    int delete_id = 0;
    int swap = 0;

    printf("\nPodaj ID zlecenia do usuniecia: ");
    scanf("%d",&delete_id);

    if (sqlite3_prepare(database, "delete from REPAIR where ID = ?",  /* stmt*/ -1, /* If than zero, then stmt is read up to the first nul terminator*/&stmt,
                        0  /*Pointer to unused portion of stmt*/) != SQLITE_OK) {
        fprintf(stderr, "Could not prepare statement.");
    }

    char buffor[300];

    sprintf(buffor, "delete from REPAIR where ID = \"%d\"",delete_id);

    sql = buffor;
    execute_sqlite_database();

    printf("\n\nNacisnij 1 by wrocic do menu \n");
    scanf("%d", &swap);
    if(swap == 1)
        system("cls");
    menu();
}

int print_database(){

    int decision = 0;
    int choose_way = 0;
    int change_ID = 0;
    int decision_2 = 0;

    system("cls");

    printf("\n\nW jaki sposob chcesz wyswietlic baze danych?\n\n");
    printf("1.W liscie (zalecane przy dlugich nazwach i opisach)\n2.W tabeli (latwiejsze odczytanie danych przy krotszych opisach)\n");
    scanf("%d",&choose_way);
    system("cls");
    printf("Lista zlecen:\n\n");
    if(choose_way == 1) {
        do {
            system("cls");
            sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR";
            execute_sqlite_database();

            if (decision == 1) {
                system("cls");
                sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND STATUS_ZLECENIA = \"W trakcie\" ";
                execute_sqlite_database();
            }

            if (decision == 2) {
                system("cls");
                sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_CAR = c.ID_CAR AND a.ID_PERSON=b.ID_PERSON WHERE STATUS_ZLECENIA = \"Do odebrania\"";
                execute_sqlite_database();
            }

            if (decision == 3) {
                system("cls");
                sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND STATUS_ZLECENIA = \"Zakonczone\"";
                execute_sqlite_database();
            }

            if (decision == 4) {
                system("cls");
                sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR";
                execute_sqlite_database();
            }

            if (decision == 5){
                system("cls");
                sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR";
                execute_sqlite_database();

                do {
                    if (decision_2 == 1) {
                        sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY IMIE";
                        execute_sqlite_database();
                    }

                    if (decision_2 == 2) {
                        sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY NAZWISKO";
                        execute_sqlite_database();
                    }

                    if (decision_2 == 3) {
                        sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY MARKA";
                        execute_sqlite_database();
                    }

                    if (decision_2 == 4) {
                        sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY NUMER_REJESTRACYJNY";
                        execute_sqlite_database();
                    }

                    if (decision_2 == 5) {
                        sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY STATUS_ZLECENIA";
                        execute_sqlite_database();
                    }

                    printf("Nacisnij 1 by sortowac po imieniu\n");
                    printf("Nacisnij 2 by sortowac po nazwisku \n");
                    printf("Nacisnij 3 by sortowac po marce \n");
                    printf("Nacisnij 4 by sortowac po numerze rejestracyjnym \n");
                    printf("Nacisnij 5 by sortowac po statusie zlecenia \n");
                    printf("Nacisnij 6 by wrocic \n");
                    scanf("%d", &decision_2);
                }while (decision_2!= 6);

            }

            if (decision == 6){

                system("cls");
                sql = "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR";
                execute_sqlite_database();

                do {
                    if (decision_2 == 1) {
                        printf("\n\nPodaj ID zlecenia do zmiany statusu:");
                        scanf("%d", &change_ID);

                        char buffor[300];

                        sprintf(buffor, "UPDATE REPAIR SET STATUS_ZLECENIA = 'W trakcie' WHERE ID =  \"%d\"",
                                change_ID);

                        sql = buffor;
                        execute_sqlite_database();
                    }

                    if (decision_2 == 2) {
                        printf("\n\nPodaj ID zlecenia do zmiany statusu:");
                        scanf("%d", &change_ID);

                        char buffor[300];

                        sprintf(buffor, "UPDATE REPAIR SET STATUS_ZLECENIA = 'Do odebrania' WHERE ID =  \"%d\"",
                                change_ID);

                        sql = buffor;
                        execute_sqlite_database();
                    }

                    if (decision_2 == 3) {
                        printf("\n\nPodaj ID zlecenia do zmiany statusu:");
                        scanf("%d", &change_ID);

                        char buffor[300];

                        sprintf(buffor, "UPDATE REPAIR SET STATUS_ZLECENIA = 'Zakonczone' WHERE ID =  \"%d\"",
                                change_ID);

                        sql = buffor;
                        execute_sqlite_database();
                    }

                    printf("Nacisnij 1 by zmienic status zlecenia na \"W trakcie\" \n");
                    printf("Nacisnij 2 by zmienic status zlecenia na \"Do odebrania\" \n");
                    printf("Nacisnij 3 by zmienic status zlecenia na \"Zakonczone\" \n");
                    printf("Nacisnij 4 by wrocic \n");
                    scanf("%d", &decision_2);
                }while (decision_2!= 4);

            }

            printf("\n\nNacisnij 1 by wyswietlic zlecenia w trakcie \n");
            printf("Nacisnij 2 by wyswietlic zlecenia do odebrania \n");
            printf("Nacisnij 3 by wyswietlic zlecenia ukonczone \n");
            printf("Nacisnij 4 by wyswietlic zlecenia wszystkie \n");
            printf("Nacisnij 5 by wyswietlic sortowania \n");
            printf("Nacisnij 6 by zmienic status zlecenia \n");
            printf("Nacisnij 7 by wrocic do menu \n");
            scanf("%d", &decision);
        }while(decision != 7);
    }
    if(choose_way == 2) {

            do {
                system("cls");
                select_stmt( "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR");

                if (decision == 1) {
                    system("cls");
                    select_stmt("SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND STATUS_ZLECENIA = \"W trakcie\"");
                }

                if (decision == 2) {
                    system("cls");
                    select_stmt("SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND STATUS_ZLECENIA = \"Do odebrania\"");
                }

                if (decision == 3) {
                    system("cls");
                    select_stmt("SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND STATUS_ZLECENIA = \"Zakonczone\"");
                }

                if (decision == 4) {
                    system("cls");
                    select_stmt( "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR");
                }

                if (decision == 5){

                    system("cls");
                    select_stmt( "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR");

                    do {
                        if (decision_2 == 1) {
                            system("cls");
                            select_stmt( "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY IMIE");
                        }

                        if (decision_2 == 2) {
                            system("cls");
                            select_stmt( "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY NAZWISKO");
                        }

                        if (decision_2 == 3) {
                            system("cls");
                            select_stmt( "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY MARKA");
                        }

                        if (decision_2 == 4) {
                            system("cls");
                            select_stmt("SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY NUMER_REJESTRACYJNY");
                        }

                        if (decision_2 == 5) {
                            system("cls");
                            select_stmt("SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR ORDER BY STATUS_ZLECENIA");
                        }

                        printf("Nacisnij 1 by sortowac po imieniu\n");
                        printf("Nacisnij 2 by sortowac po nazwisku \n");
                        printf("Nacisnij 3 by sortowac po marce \n");
                        printf("Nacisnij 4 by sortowac po numerze rejestracyjnym \n");
                        printf("Nacisnij 5 by sortowac po statusie zlecenia \n");
                        printf("Nacisnij 6 by wrocic \n");
                        scanf("%d", &decision_2);
                    }while (decision_2!= 6);

                }

                if (decision == 6){

                    system("cls");
                    select_stmt("SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR");

                    do {
                        if (decision_2 == 1) {
                            printf("\n\nPodaj ID zlecenia do zmiany statusu:");
                            scanf("%d", &change_ID);

                            char buffor[300];

                            sprintf(buffor, "UPDATE REPAIR SET STATUS_ZLECENIA = 'W trakcie' WHERE ID =  \"%d\"",
                                    change_ID);

                            sql = buffor;
                            execute_sqlite_database();
                        }

                        if (decision_2 == 2) {
                            printf("\n\nPodaj ID zlecenia do zmiany statusu:");
                            scanf("%d", &change_ID);

                            char buffor[300];

                            sprintf(buffor, "UPDATE REPAIR SET STATUS_ZLECENIA = 'Do odebrania' WHERE ID =  \"%d\"",
                                    change_ID);

                            sql = buffor;
                            execute_sqlite_database();
                        }

                        if (decision_2 == 3) {
                            printf("\n\nPodaj ID zlecenia do zmiany statusu:");
                            scanf("%d", &change_ID);

                            char buffor[300];

                            sprintf(buffor, "UPDATE REPAIR SET STATUS_ZLECENIA = 'Zakonczone' WHERE ID =  \"%d\"",
                                    change_ID);

                            sql = buffor;
                            execute_sqlite_database();
                        }

                        printf("Nacisnij 1 by zmienic status zlecenia na \"W trakcie\" \n");
                        printf("Nacisnij 2 by zmienic status zlecenia na \"Do odebrania\" \n");
                        printf("Nacisnij 3 by zmienic status zlecenia na \"Zakonczone\" \n");
                        printf("Nacisnij 4 by wrocic \n");
                        scanf("%d", &decision_2);
                    }while (decision_2!= 4);

                }

                printf("\n\nNacisnij 1 by wyswietlic zlecenia w trakcie \n");
                printf("Nacisnij 2 by wyswietlic zlecenia do odebrania \n");
                printf("Nacisnij 3 by wyswietlic zlecenia ukonczone \n");
                printf("Nacisnij 4 by wyswietlic zlecenia wszystkie \n");
                printf("Nacisnij 5 by wyswietlic sortowania \n");
                printf("Nacisnij 6 by zmienic status zlecenia \n");
                printf("Nacisnij 7 by wrocic do menu \n");
                scanf("%d", &decision);
            }while(decision != 7);
    }
    system("cls");
    menu();
}

int find_car() {

    char registration_number[20];

    int swap = 0;

    printf("\nNumer rejestracyjny do znalezienia: ");
    scanf("%s", &registration_number);

    char buffor[300];

    sprintf(buffor, "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND NUMER_REJESTRACYJNY = \"%s\"", registration_number);

    select_stmt(buffor);

       printf("\n\nNacisnij 1 by wrocic do menu \n");
       scanf("%d", &swap);
       if(swap == 1){
          system("cls");
          menu();
        }
}

void menu()
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

    }
    if(choice == 2){
        delete_client_in_database();

    }
    if(choice == 3){
        print_database();
    }
    if(choice == 4){
        find_car();
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
>>>>>>> d7996431e865c372b3a724d76ffc3b671386044c

int main() {

    menu();
    getchar();
    sqlite_end();
    return 0;
}
