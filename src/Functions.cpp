#include "includes.hh"
#include <time.h>

#define KEYBOARD_BACKSPACE 8
#define KEYBOARD_TAB 9
#define KEYBOARD_ENTER 13
#define KEYBOARD_ESC 27

void Exit_manual(int exitcode){
    cout << "Press |Enter| to exit." << endl;
    fflush(stdin);
    getchar();
    exit(exitcode);
}
void ErrorHandling(string message){
    cout << "Error:" << message << endl;
    Exit_manual(1);
}

void Delay(int second)
/**
 * This function will stop program for several seconds.
 * Devation <= 1
 */
{
    int start = time(NULL);
    while(1){
        if(time(NULL) - start > second)
            break;
    }
}