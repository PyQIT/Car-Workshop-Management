#ifndef CAR_WORKSHOP_MANAGEMENT_V_0_1_PRINT_DATABASE_H
#define CAR_WORKSHOP_MANAGEMENT_V_0_1_PRINT_DATABASE_H
#include "client_management.h"
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/**
 * @code
 * print_database()
 * @endcode
 * @note Funkcja wyświetlająca bazę danych w wybrany przez użytkownika sposób. Pozwala również na edytowanie statusu zlecenia. Nic nie otrzymuje, nic nie zwraca.
 * */

void print_database(void){

    int decision = 0;
    int choose_way = 0;
    int change_ID = 0;
    int decision_2 = 0;
    char type[1];
    char type1[1];
    char type2[1];

    system("cls");

    printf("\n\nW jaki sposob chcesz wyswietlic baze danych?\n\n");
    printf("1.W liscie (zalecane przy dlugich nazwach i opisach)\n2.W tabeli (latwiejsze odczytanie danych przy krotszych opisach)\n");
    do{
        scanf("%s",&type);
        choose_way = atoi(type);
    }while(choose_way != 1 && choose_way != 2);

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
                    scanf("%s",&type1);
                    decision_2 = atoi(type1);
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
                    scanf("%s",&type1);
                    decision_2 = atoi(type1);
                }while (decision_2!= 4);

            }

            printf("\n\nNacisnij 1 by wyswietlic zlecenia w trakcie \n");
            printf("Nacisnij 2 by wyswietlic zlecenia do odebrania \n");
            printf("Nacisnij 3 by wyswietlic zlecenia ukonczone \n");
            printf("Nacisnij 4 by wyswietlic zlecenia wszystkie \n");
            printf("Nacisnij 5 by wyswietlic sortowania \n");
            printf("Nacisnij 6 by zmienic status zlecenia \n");
            printf("Nacisnij 7 by wrocic do menu \n");
            scanf("%s",&type2);
            decision = atoi(type2);
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
                    scanf("%s",&type1);
                    decision_2 = atoi(type1);
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
                    scanf("%s",&type1);
                    decision_2 = atoi(type1);
                }while (decision_2!= 4);

            }

            printf("\n\nNacisnij 1 by wyswietlic zlecenia w trakcie \n");
            printf("Nacisnij 2 by wyswietlic zlecenia do odebrania \n");
            printf("Nacisnij 3 by wyswietlic zlecenia ukonczone \n");
            printf("Nacisnij 4 by wyswietlic zlecenia wszystkie \n");
            printf("Nacisnij 5 by wyswietlic sortowania \n");
            printf("Nacisnij 6 by zmienic status zlecenia \n");
            printf("Nacisnij 7 by wrocic do menu \n");
            scanf("%s",&type2);
            decision = atoi(type2);
        }while(decision != 7);
    }
}

#endif //CAR_WORKSHOP_MANAGEMENT_V_0_1_PRINT_DATABASE_H
