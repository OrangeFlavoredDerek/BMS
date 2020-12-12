//
//  BMS4.c
//  BMS3.5
//
//  Created by Derek Chan on 2020/11/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <Windows.h>
#include "BMS4.h"

//MARK: -开始界面
void startSystem() {
    int cmd, end = 0;
    while (1) {
        system("cls");
        printf("\n\n\n");
        printf("**************************************************************");
        printf("\n图书馆管理系统\n");
        printf("1.管理员登陆\n");
        printf("2.管理员注册\n");
        printf("0.退出\n");
        printf("**************************************************************");
        printf("\n\n\n");
        printf("输入你需要进行的操作: ");
        scanf("%d", &cmd);
        getchar();
        switch (cmd){
            case 1:
                adminLogin();
                break;
            case 2:
                adminRegister();
                break;
            case 0:
                end = 1;
                break;
            default:
                printf("错误输入!\n");
        }
        if (end == 1)
            break;
    }
}



int main() {
    FILE *fp;
    adminHead = (Admin*)malloc(sizeof(Admin));
    bookHead = (Book*)malloc(sizeof(Book));
    system("color 3f");

    fp = fopen("admin.txt", "a+");
    adminCount = fread(adminHead, sizeof(Admin), 100, fp);
    fclose(fp);
    adminEnd = adminHead;
    readFile(1);

    fp = fopen("book.txt", "a+");
    bookCount = fread(bookHead, sizeof(Book), 100, fp);
    fclose(fp);
    bookEnd = bookHead;
    readFile(2);

    startSystem();
    return 0;
}
