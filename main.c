#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "menu.h"

/**
 * @code
 * main()
 * @endcode
 * @note Główna funkcja projektu. Po starcie uruchamia menu programu.
 * */

int main() {

    menu();
    getchar();
    sqlite_end();
    return 0;
}