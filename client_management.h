#ifndef CAR_WORKSHOP_MANAGEMENT_V_0_1_CLIENT_MANAGEMENT_H
#define CAR_WORKSHOP_MANAGEMENT_V_0_1_CLIENT_MANAGEMENT_H
#include "menu.h"

char *sql; /**< Globalna zmienna sql do zapisywania zapytań do bazy danych*/
sqlite3* database; /**< Zmienna odnosząca się do bazy sqlite*/
sqlite3_stmt* stmt; /**< Zmienna odnosząca się do bazy sqlite przez stmt*/

/**
 * @code
 * callback()
 * @endcode
 * @note Funkcja wypisuje na ekranie zapytanie z bazy danych w formie listy. Otrzymuje wartosc pola, numer kolumny, wiersz oraz nazwe kolumny. Po wykonaniu zadania zwraca 0.
 * */

static int callback(void *data, int argc, char **argv, char **azColName){

    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int first_row; /**< Globalna zmienna do wypisywania zapytań bazy danych w formie tabeli.*/


/**
 * @code
 * select_callback()
 * @endcode
 * @note Funkcja wypisuje na ekranie zapytanie z bazy danych w formie tabelki. Otrzymuje wartosc pola, numer kolumny, wiersz oraz nazwe kolumny. Zwraca 0.
 * */

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

/**
 * @code
 * select_stmt()
 * @endcode
 * @note Funkcja pobierająca zapytania z bazy danych. Otrzymuje komendę w zmiennej stmt.
 * */

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

/**
 * @code
 * execute_sqlite_database()
 * @endcode
 * @note Funkcja pobierajaca zapytania do bazy danych. Służy do późniejszego wypisywania w formie listy. Nic nie otrzymuje, nic nie zwraca.
 * */

void execute_sqlite_database(void){

    int rc;
    char *errmsg;
    const char* data = "Zlecenie ";

    rc = sqlite3_exec(database, sql, callback, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

/**
 * @code
 * callback_ID_PERSON()
 * @endcode
 * @note Funkcja pobiera dane od użytkownika odnośnie samochodu. Otrzymuje wartosc pola, numer kolumny, wiersz oraz nazwe kolumny. Po wykonaniu zwraca 0.
 * */

static int callback_ID_PERSON(void *data, int argc, char **argv, char **azColName){

    int i;
    char notification[20];
    int not = 0;
    char buffor1[300];
    char mark[40];
    char model[40];
    char registration_number[20];



    for(i = 0; i<argc; i++){
        sprintf(notification, "%s", argv[i] ? argv[i] : "NULL");
    }

    not = atoi(notification);

    printf("Marka: ");
    scanf(" %[^\n]",&mark);
    printf("Model: ");
    scanf(" %[^\n]",&model);
    printf("Numer rejestracyjny: ");
    scanf(" %[^\n]",&registration_number);

    sprintf(buffor1, "insert into CARS (MARKA, MODEL, NUMER_REJESTRACYJNY, ID_PERSON) values (\"%s\",\"%s\",\"%s\",\"%d\") ",mark, model, registration_number,not);

    sql = buffor1;
    execute_sqlite_database();

    sql = "SELECT (ID_CAR) FROM CARS WHERE ID_CAR=(SELECT max(ID_CAR) FROM CARS)";
    execute_sqlite_database_ID();

    return 0;
}

/**
 * @code
 * execute_sqlite_database_ID_PERSON()
 * @endcode
 * @note Funkcja pobierająca zapytania z bazy danych. Nic nie otrzymuje, nic nie zwraca.
 * */

void execute_sqlite_database_ID_PERSON(void){

    int rc;
    char *errmsg;
    const char* data = " ";

    rc = sqlite3_exec(database, sql, callback_ID_PERSON, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

/**
 * @code
 * callback_ID()
 * @endcode
 * @note Funkcja pobiera dane od użytkownika odnośnie zlecenia. Otrzymuje wartosc pola, numer kolumny, wiersz oraz nazwe kolumny. Zwraca 0.
 * */

static int callback_ID(void *data, int argc, char **argv, char **azColName){

    int i;
    char notification[20];
    int not = 0;
    char buffor1[300];
    char information[300];
    double cost = 0;
    char status[10] = "W trakcie";

    for(i = 0; i<argc; i++){
        sprintf(notification, "%s", argv[i] ? argv[i] : "NULL");
    }

    not = atoi(notification);

    printf("Informacja odnosnie naprawy: ");
    scanf (" %[^\n]",&information);
    printf("Koszt naprawy: ");
    scanf("%lf",&cost);

    sprintf(buffor1, "insert into REPAIR (INFORMACJA, KOSZT_NAPRAWY, STATUS_ZLECENIA, ID_CAR) values (\"%s\",\"%lf\",\"%s\",\"%d\") ",information, cost,status,not);

    sql = buffor1;
    execute_sqlite_database();

    return 0;
}

/**
 * @code
 * execute_sqlite_database_ID()
 * @endcode
 * @note Funkcja pobierająca zapytania z bazy danych. Nic nie otrzymuje, nic nie zwraca.
 * */

void execute_sqlite_database_ID(void){

    int rc;
    char *errmsg;
    const char* data = " ";

    rc = sqlite3_exec(database, sql, callback_ID, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

/**
 * @code
 * add_person()
 * @endcode
 * @note Funkcja dodająca nową osobę w bazie, jeżeli jeszcze nie istnieje. Nic nie otrzymuje, nic nie zwraca.
 * */

void add_person(void){

    char name[40];
    char surname[50];
    char birth[15];
    char contact[40];

    printf("Imie: ");
    scanf(" %[^\n]",&name);
    printf("Nazwisko: ");
    scanf(" %[^\n]",&surname);
    printf("Data urodzenia: ");
    scanf(" %[^\n]",&birth);
    printf("Kontakt: ");
    scanf(" %[^\n]",&contact);

    char buffor[300];

    sprintf(buffor, "insert into PERSON (IMIE, NAZWISKO, DATA_URODZENIA, KONTAKT) values (\"%s\",\"%s\",\"%s\",\"%s\") ",name, surname, birth, contact);

    sql = buffor;
    execute_sqlite_database();
}

/**
 * @code
 * delete_client_in_database()
 * @endcode
 * @note Funkcja usuwająca zlecenie w bazie danych. Nic nie otrzymuje, nic nie zwraca.
 * */

void delete_client_in_database(void){

    int delete_id = 0;
    int swap = 0;
    char type2[1];

    printf("\nPodaj ID zlecenia do usuniecia: ");
    scanf("%d",&delete_id);

    char buffor[300];

    sprintf(buffor, "delete from REPAIR where ID = \"%d\"",delete_id);

    sql = buffor;
    execute_sqlite_database();

    printf("\n\nNacisnij 1 by wrocic do menu \n");
    do{
        scanf("%s",&type2);
        swap = atoi(type2);
    }while(swap != 1);

}

/**
 * @code
 * add_client_to_database()
 * @endcode
 * @note Funkcja zajmująca się dodawaniem zleceń. Sprawdza czy klient już istnieje, jeżeli tak to pyta czy chcemy wybrać istniejący już samochód czy dodać nowy i dopisać do niego nowe zlecenie. Nic nie otrzymuje, nic nie zwraca.
 * */

void add_client_to_database(void){

    int swap = 0;
    int choose = 0;
    int choose_ID_PERSON = 0;
    int choose_ID_CAR = 0;
    int choose_ID_CAR_IF_EXISTS = 0;
    char buffor[300];
    char buffor1[300];
    char information[300];
    double cost = 0;
    char status[10] = "W trakcie";
    char type[1];
    char type2[1];
    char type1[1];

    system("cls"); /**< Wyczyszczenie ekranu. */
    printf("\nUzupelnianie zlecenia\n\n");

    printf("1. Nowy klient\n");
    printf("2. Staly klient\n");
    do{
        scanf("%s",&type);
        choose = atoi(type);
    }while(choose != 1 && choose != 2);

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
        do{
            printf("\n");
            scanf("%s",&type1);
            choose_ID_CAR = atoi(type1);
        }while(choose_ID_CAR != 1 && choose_ID_CAR != 2);

        if(choose_ID_CAR == 1){

            printf("\n\nPodaj ID samochodu: ");
            scanf("%d",&choose_ID_CAR_IF_EXISTS);
            printf("Informacja odnosnie naprawy: ");
            scanf (" %[^\n]",&information);
            printf("Koszt naprawy: ");
            scanf("%lf",&cost);



            sprintf(buffor1, "insert into REPAIR (INFORMACJA, KOSZT_NAPRAWY, STATUS_ZLECENIA, ID_CAR) values (\"%s\",\"%lf\",\"%s\") ",information, cost,status);

            sql = buffor1;
            execute_sqlite_database();
        }

        if(choose_ID_CAR == 2){

            char mark[40];
            char model[40];
            char registration_number[20];

            printf("\nMarka: ");
            scanf(" %[^\n]",&mark);
            printf("Model: ");
            scanf(" %[^\n]",&model);
            printf("Numer rejestracyjny: ");
            scanf(" %[^\n]",&registration_number);

            char buffor[300];

            sprintf(buffor, "insert into CARS (MARKA, MODEL, NUMER_REJESTRACYJNY, ID_PERSON) values (\"%s\",\"%s\",\"%s\",\"%d\")",mark, model, registration_number, choose_ID_PERSON);

            sql = buffor;
            execute_sqlite_database();

            sql = "SELECT (ID_CAR) FROM CARS WHERE ID_CAR=(SELECT max(ID_CAR) FROM CARS)";
            execute_sqlite_database_ID();

        }
    }

    printf("\n\nNacisnij 1 by wrocic do menu \n");
    do{
        scanf("%s",&type2);
        swap = atoi(type2);
    }while(swap != 1);
}

/**
 * @code
 * find_car()
 * @endcode
 * @note Funkcja wyszukuje samochod po numerze rejestracyjnym. Nic nie otrzymuje, nic nie zwraca.
 * */

void find_car(void) {

    char registration_number[20];

    int swap = 0;
    char type[1];

    printf("\nNumer rejestracyjny do znalezienia: ");
    scanf(" %[^\n]", &registration_number);

    char buffor[300];

    sprintf(buffor, "SELECT ID, IMIE,NAZWISKO,DATA_URODZENIA,KONTAKT,MARKA,MODEL,NUMER_REJESTRACYJNY,INFORMACJA,KOSZT_NAPRAWY,STATUS_ZLECENIA FROM CARS as a INNER JOIN PERSON as b INNER JOIN REPAIR as c ON a.ID_PERSON=b.ID_PERSON WHERE a.ID_CAR=c.ID_CAR AND NUMER_REJESTRACYJNY GLOB \"%s*\"", registration_number);

    select_stmt(buffor);

    printf("\n\nNacisnij 1 by wrocic do menu \n");

    do{
        scanf("%s",&type);
        swap = atoi(type);

    }while(swap != 1);
}

#endif //CAR_WORKSHOP_MANAGEMENT_V_0_1_CLIENT_MANAGEMENT_H
