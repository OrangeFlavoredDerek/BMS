//
//  SignUp:In.h
//  BMS3.5
//
//  Created by Derek Chan on 2020/11/28.
//

#ifndef SignUp_In_h
#define SignUp_In_h

#include "BMS4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//管理员操作菜单
void adminFunction() {
    int cmd;
    int end = 0;
 
    while (1) {
        system("cls");
        printf("\n\n\n\n\n\n\n");
        printf("**************************************************************");
        printf("\n图书馆管理员功能系统\n");
        printf("1.添加书籍信息\n");
        printf("2.删除书籍信息\n");
        printf("3.修改书籍信息\n");
        printf("4.查询书籍信息\n");
        printf("0.退出\n");
        printf("**************************************************************");
        printf("\n\n\n\n\n\n\n");
        printf("输入您需要进行的操作: ");
        scanf("%d", &cmd);
        getchar();
        switch (cmd){
            case 1:
                TypingInfo();
                break;
            case 2:
                DeleteBookInfo();
                break;
            case 3:
                ModifyBookInfo();
                break;
            case 4:
                QueryBook();
                break;
            case 0:
                end = 1;
                break;
            default:
            printf("错误的输入!\n");
        }
        if (end == 1)
            break;
    }
}

//MARK: -管理员登陆
void adminLogin() {
    Admin *p;
    char adminName[100];
    char adminPassword[100];
    
    p = adminHead;
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("**************************************************************");
    printf("\n输入您的管理员信息: \n");
    printf("管理员姓名: ");
    gets(adminName);
    printf("管理员密码: ");
    gets(adminPassword);
    printf("**************************************************************");
    printf("\n\n\n\n\n\n\n");
    
    while (p != NULL) {
        if (strcmp(p->adminName, adminName) == 0) {
            while (strcmp(p->scert, adminPassword) != 0) {
                printf("密码错误!请重新输入\n");
                printf("adminscert: ");
                gets(adminPassword);
            }
            printf("管理员%s登陆成功!将自动跳转至用户界面...", p->adminName);
            adminFunction();
        }
        p = p->next;
    }
}

//MARK: -管理员账户注册
void adminRegister(){
    Admin *p;
    char adminName[1000];
    char adminPassword[1000];
    FILE *fp;
    
    system("cls");
    if (adminCount == 0) {//第一次添加
        adminHead = (struct AdminInfo *)malloc(sizeof(struct AdminInfo));
        printf("adminname: ");
        while (gets(adminName)) {
            if (strlen(adminName) < 10) {
                break;
            } else {
                printf("too long");
            }
        }
        strcpy(adminHead->adminName, adminName);
        printf("adminscert: ");
        while (gets(adminPassword)) {
            if (strlen(adminPassword) < 10) {
                break;
            } else {
                printf("too long");
            }
        }
        strcpy(adminHead->scert, adminPassword);
        adminEnd = adminHead;
        adminEnd->next = NULL;
    } else {
        p = (struct AdminInfo *)malloc(sizeof(struct AdminInfo));
        printf("管理员姓名: ");
        while (gets(adminName)) {
            if (strlen(adminName) < 10) {
                break;
            } else {
                printf("too long");
            }
        }
        strcpy(p->adminName, adminName);
        printf("管理员密码: ");
        while (gets(adminPassword)) {
            if (strlen(adminPassword) < 10) {
                break;
            } else {
                printf("too long");
            }
        }
        strcpy(p->scert, adminPassword);
        adminEnd->next = p;
        adminEnd = p;
        adminEnd->next = NULL;
    }
    adminCount++;
    
    fp = fopen("admin", "w");
    p = adminHead;
    while (p != NULL) {
        fwrite(p, sizeof(struct AdminInfo), 1, fp);
        p = p->next;
    }
    fclose(fp);
    
    system("cls");
    printf("管理员%s创建成功\n", adminEnd->adminName);
}
#endif /* SignUp_In_h */
