//
//  LoginSystem.c
//  BMS3.5
//
//  Created by Derek Chan on 2020/11/23.
//

#ifndef LoginSystem_h
#define LoginSystem_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Login {
    int Account;
    char Password[20];
    struct Login *Next;
};

//MARK: -登陆页面
void LoginMenu(){
    printf("\n\n\t    欢迎使用图书管理员登录系统\n\n");
    printf("**********************************************");
    printf("\n\n\t\t1.登录系统\n\n");
    printf("\n\n\t\t2.创建账号\n\n");
    printf("\n\n\t\t3.修改密码\n\n");
    printf("\n\n\t\t4.退出系统\n\n");
    printf("\n\n\t    请按键选择，回车确定\n");
    printf("**********************************************");
    return ;
}

void LoginMain(){
    void LoginMenu();
    
}

void SignUp(){
    FILE *fp;
    int account;
    char password[20], password1[20];
    char hit = 0;
    if ((fp == fopen("land.txt")) == NULL) {
        fp = fopen("land.txt", "w");
        fclose(fp);
    }
    
}

#endif
