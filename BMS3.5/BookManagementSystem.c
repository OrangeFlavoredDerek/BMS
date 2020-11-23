//
//  BookManagementSystem.c
//  BMS3.5
//
//  Created by Derek Chan on 2020/11/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "BookManagementSystem.h"

int main(){
    char *fileName = "ID.txt";
    int flag = 0;

    while (flag == 0) {
        Menu();
        switch (Menu()) {
            case 1:
                Import(fileName);
                break;
            case 2:
                TypingInfo(fileName);
                break;
            case 3:
                Query(fileName);
                break;
            case 4:
                DeleteBookInfo(fileName);
            case 5:
                ModifyBookInfo(fileName);
                break;

            case 7:
                printf("退出系统\n");
                break;
        }
    }

    return 0;
}
