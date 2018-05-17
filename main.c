#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

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

void execute_sqlite_database(){

    int rc;
    char *errmsg;
    const char* data = "Zlecenie ";

    rc = sqlite3_exec(database, sql, callback, (void*)data, &errmsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
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

void create_database(){

    "CREATE TABLE ORDERS("  \
         "ID             INT PRIMARY KEY    NOT NULL," \
         "MARKA                     TEXT    NOT NULL," \
         "MODEL                     TEXT    NOT NULL," \
         "NUMER_REJESTRACYJNY       TEXT    NOT NULL," \
         "IMIE                      TEXT    NOT NULL," \
         "NAZWISKO                  TEXT    NOT NULL," \
         "DATA_URODZENIA            TEXT    NOT NULL," \
         "KONTAKT                   TEXT    NOT NULL," \
         "INFORMACJA                TEXT    NOT NULL," \
         "KOSZT_NAPRAWY             REAL    NOT NULL," \
         "STATUS_ZLECENIA           INT DEFAULT 1 );";
}

void menu();

void check_database_correct(){

    char create_new_database[1];

    system("cls");
    fprintf(stderr, "Blad polaczenia z baza danych\n");
    printf("Czy chcesz stworzyc nowa baze danych? (T/N)\n");
    scanf("%c", create_new_database);
    if(create_new_database == "T") {
        system("cls");
        fprintf(stderr, "Utworzono nowa baze danych\n");
        create_database();
        execute_sqlite_database();
    }
    if(create_new_database == "N") {
        system("cls");
        printf("\n Nie utworzono nowej bazy danych\n");
        menu();
    }
    if(create_new_database != "N" || create_new_database != "T") {
        system("cls");
        check_database_correct();
    }
}

void sqlite_end(){

    sqlite3_close(database);
}

int add_client_to_database(){

    char mark[25];
    char model[30];
    char registration_number[20];
    char name[40];
    char surname[50];
    char birth[15];
    char contact[40];
    char information[300];
    double *cost = (double *)malloc(sizeof(double));
    int swap = 0;

    system("cls");
    sqlite_connection();

    printf("\nUzupelnianie zlecenia\n\n");
    printf("Marka: ");
    scanf("%s",&mark);
    printf("Model: ");
    scanf("%s",&model);
    printf("Numer rejestracyjny: ");
    scanf("%s",&registration_number);
    printf("Imie: ");
    scanf("%s",&name);
    printf("Nazwisko: ");
    scanf("%s",&surname);
    printf("Data urodzenia: ");
    scanf("%s",&birth);
    printf("Kontakt: ");
    scanf("%s",&contact);
    printf("Informacja odnosnie naprawy: ");
    scanf("%s",&information);
    printf("Koszt naprawy: ");
    scanf("%lf",cost);


    if (sqlite3_prepare(database, "insert into ORDERS values (?,?,?,?,?,?,?,?,?,?,?)",  /* stmt*/ -1, /* If than zero, then stmt is read up to the first nul terminator*/&stmt,
                        0  /*Pointer to unused portion of stmt*/) != SQLITE_OK) {
        fprintf(stderr, "Could not prepare statement.");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 2,  /*Index of wildcard*/ mark, 25,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 3,  /*Index of wildcard*/ model, 30,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 4,  /*Index of wildcard*/ registration_number, 20,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 5,  /*Index of wildcard*/ name, 40,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 6,  /*Index of wildcard*/ surname, 50,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 7,  /*Index of wildcard*/ birth, 15,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 8,  /*Index of wildcard*/ contact, 40,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 9,  /*Index of wildcard*/ information, 300,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
        return 1;
    }

    if (sqlite3_bind_double(stmt, 10, *cost) != SQLITE_OK) {
        fprintf(stderr, "Could not bind double.\n");
        return 1;
    }

    if (sqlite3_bind_text(stmt, 11,  /*Index of wildcard*/ "W trakcie", 9,  /*length of text*/ SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind int.\n");
        return 1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Could not step (execute) stmt.\n");
    }
    else
        fprintf(stderr, "Operation done successfully\n");

    sqlite_end();

    printf("\n\nNacisnij 1 by wrocic do menu \n");
    scanf("%d", &swap);
    if(swap == 1)
        system("cls");
    menu();
}

void edit_client_in_database(){
/*
    int update_id = 0;
    int choose_data_to_edit = 0;
    char data_to_edit[20];
    char change_data_mark[25];
    char change_data_model[30];
    char change_data_registration_number[20];
    char change_data_name[40];
    char change_data_surname[50];
    char change_data_birth[15];
    char change_data_contact[40];
    char change_data_information[300];
    double *cost_change = (double *)malloc(sizeof(double));

    sqlite_connection();

    printf("\nPodaj ID zlecenia do edytowania: ");
    scanf("%d",&update_id);
    printf("\nWybierz, ktora wartosc chcesz edytowac: ");
    printf("\n1.Marka");
    printf("\n2.Model");
    printf("\n3.Numer rejestracyjny");
    printf("\n4.Imie");
    printf("\n5.Nazwisko");
    printf("\n6.Data urodzenia");
    printf("\n7.Kontakt");
    printf("\n8.Informacja odnosnie naprawy");
    printf("\n9.Koszt naprawy\n");
    scanf("%d",&choose_data_to_edit);

    if(choose_data_to_edit == 1) {
        data_to_edit[] = "MARKA";
    }
    if(choose_data_to_edit == 2) {
        data_to_edit[]="MODEL";
    }
    if(choose_data_to_edit == 3) {
        data_to_edit[]="NUMER_REJESTRACYJNY";
    }
    if(choose_data_to_edit == 4) {
        data_to_edit[] = "IMIE";
    }
    if(choose_data_to_edit == 5) {
        data_to_edit[] = "NAZWISKO";
    }
    if(choose_data_to_edit == 6) {
        data_to_edit[] = "DATA_URODZENIA";
    }
    if(choose_data_to_edit == 7) {
        data_to_edit[] = "KONTAKT";
    }
    if(choose_data_to_edit == 8) {
        data_to_edit[] = "INFORMACJA";
    }
    if(choose_data_to_edit == 9) {
        data_to_edit[]= "KOSZT_NAPRAWY";
    }

  //  printf("\nPodaj ID zlecenia do edytowania: ");
   // scanf("%d",&update_id);

    if (sqlite3_prepare(database, "update ORDERS set ? = ? where ID = ?" -1, &stmt, 0 ) != SQLITE_OK) {
        fprintf(stderr, "Could not prepare statement.");
    }

    if (sqlite3_bind_text(stmt, 1,  /*Index of wildcard*//* data_to_edit, 20,  /*length of text*//* SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Could not bind text.\n");
    }

    if (sqlite3_bind_int(stmt, 3, update_id) != SQLITE_OK) {
        fprintf(stderr, "Could not bind int.\n");
    }


    sqlite_end();*/
}

void delete_client_in_database(){

    int delete_id = 0;
    int swap = 0;

    sqlite_connection();

    printf("\nPodaj ID zlecenia do usuniecia: ");
    scanf("%d",&delete_id);

    if (sqlite3_prepare(database, "delete from ORDERS where ID = ?",  /* stmt*/ -1, /* If than zero, then stmt is read up to the first nul terminator*/&stmt,
                        0  /*Pointer to unused portion of stmt*/) != SQLITE_OK) {
        fprintf(stderr, "Could not prepare statement.");
    }

    if (sqlite3_bind_int(stmt, 1, delete_id) != SQLITE_OK) {
        fprintf(stderr, "Could not bind int.\n");
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Could not step (execute) stmt.\n");
    }
    else
        fprintf(stderr, "Operation done successfully\n");

    sqlite_end();

    printf("\n\nNacisnij 1 by wrocic do menu \n");
    scanf("%d", &swap);
    if(swap == 1)
        system("cls");
    menu();
}

void print_database(){

    int swap = 0;
    int choose_way = 0;

    system("cls");
    sqlite_connection();

    printf("\n\nW jaki sposob chcesz wyswietlic baze danych?\n\n");
    printf("1.W liscie (zalecane przy dlugich nazwach i opisach)\n2.W tabeli (latwiejsze odczytanie danych przy krotszych opisach)\n");
    scanf("%d",&choose_way);
    system("cls");
    printf("Lista zlecen:\n\n");
    if(choose_way == 1) {
        sql = "SELECT * from ORDERS";
        execute_sqlite_database();
    }
    if(choose_way == 2)
        select_stmt("select * from ORDERS");

    sqlite_end();
    printf("\n\nNacisnij 1 by wrocic do menu \n");
    scanf("%d", &swap);
    if(swap == 1)
        system("cls");
    menu();

}

void print_unclaimed_database(){

}

void menu()
{
    char type[1];
    int choice = 0;
    printf("Zarzadzanie warszatem samochodowym\n\n");
    printf("1. Dodaj klienta\n");
    printf("2. Edytuj klienta\n");
    printf("3. Usun klienta\n");
    printf("4. Pokaz liste zlecen\n");
    printf("5. Wyjdz\n");
    scanf("%s",&type);
    choice = atoi(type);

    if(choice == 1){
        add_client_to_database();

    }
    if(choice == 2){
        edit_client_in_database();

    }
    if(choice == 3){
        delete_client_in_database();

    }
    if(choice == 4){
        print_database();
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

int main() {

    menu();
    getchar();
    sqlite_end();
    return 0;
}