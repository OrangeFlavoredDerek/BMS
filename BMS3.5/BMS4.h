//
//  BMS4.h
//  BMS3.5
//
//  Created by Derek Chan on 2020/11/24.
//

//MARK: -BookManagementSystem
//(1) 能从文件导入图书的信息
//(2) 能从键盘录入图书的信息;
//(3) 给定图书号，显示某本图书信息;
//(4) 能根据图书号修改图书的信息
//(5) 能根据图书号删除图书的信息;
//(6) 能将图书信息导出到指定文件
//*管理员账户注册与登录与修改密码

#ifndef BMS4_h
#define BMS4_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//管理员信息
typedef struct AdminInfo {
    char adminName[10];
    char scert[10];
    struct AdminInfo *next;
} Admin;

//书籍信息
typedef struct BookInfo {
    int id;
    char bookname[10];
    char author[10];
    int year;
    int month;
    int day;
    int count;
    struct BookInfo *next;
} Book;

struct AdminInfo *adminHead = NULL, *adminEnd = NULL;
struct BookInfo *bookHead = NULL, *bookEnd = NULL;
int adminCount, bookCount;

//MARK: -开始界面（待完善）
void startSystem() {
    int cmd, end = 0;
    while (1) {
        <#statements#>
    }
}

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
        printf("5.查询用户信息\n");
        printf("0.退出\n");
        printf("**************************************************************");
        printf("\n\n\n\n\n\n\n");
        printf("输入您需要进行的操作: ");
        scanf("%d", &cmd);
        getchar();
//        switch (cmd)
//        {
//        case 1:
//            addbook();
//            break;
//        case 2:
//            deletebook();
//            break;
//        case 3:
//            changebook();
//            break;
//        case 4:
//            searchbook();
//            break;
//        case 5:
//            searchuser();
//            break;
//        case 0:
//            end = 1;
//            break;
//        default:
//            printf("错误的输入!\n");
//        }
        if (end == 1)
            break;
    }
}

//管理员登陆
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

//管理员账户注册
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

//从键盘键入书籍信息
void TypingInfo() {
    Book *p;
    char title[100];
    int isExist = 0;
    FILE *fp;
    
    system("cls");
    if (bookCount == 0) {
        printf("输入新增书籍的书名: ");
        while (gets(title)) {
            if (strlen(title) > 10) {
                printf("too long\n");
            } else {
                break;
            }
        }
        strcpy(bookHead->bookname, title);
        printf("ISBN: ");
        scanf("%d", &bookHead->id);
        printf("author: ");
        scanf("%s", bookHead->author);
        printf("bookyear: ");
        scanf("%d", &bookHead->year);
        printf("bookmonth: ");
        scanf("%d", &bookHead->month);
        printf("bookday: ");
        scanf("%d", &bookHead->day);
        printf("bookcount: ");
        scanf("%d", &bookHead->count);
        
        bookEnd = bookHead;
        bookEnd->next = NULL;
    } else {
        printf("输入新增书籍的书名: ");
        while (gets(title)) {
            if (strlen(title) > 10) {
                printf("too long\n");
            } else {
                break;
            }
        }
        
        p = bookHead;
        while (p != NULL) {
            if (strcmp(title, p->bookname) == 0) {
                isExist = 1;
                break;
            }
            p = p->next;
        }
        if (isExist == 1) {
            int count;
            
            printf("输入新添书籍的数量: ");
            scanf("%d", &count);
            p->count += count;
        } else {
            p = (struct BookInfo *)malloc(sizeof(struct BookInfo));
            
            strcpy(p->bookname, title);
            printf("id: ");
            scanf("%d", &p->id);
            printf("author: ");
            scanf("%s", p->author);
            printf("bookyear: ");
            scanf("%d", &p->year);
            printf("bookmonth: ");
            scanf("%d", &p->month);
            printf("bookday: ");
            scanf("%d", &p->day);
            printf("bookcount: ");
            scanf("%d", &p->count);
            
            bookEnd->next = p;
            bookEnd = p;
            bookEnd->next = NULL;
        }
    }
    bookCount++;
    
    p = bookHead;
    fp = fopen("book", "w");
    while (p != NULL) {
        fwrite(p, sizeof(struct BookInfo), 1, fp);
        p = p->next;
    }
    fclose(fp);
    
    system("cls");
    printf("书籍添加成功\n");
}

//查询图书信息
void QueryBook() {
    Book *p;
    char title[100];
    int exist = 0;
    
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("\n请输入您需要查询的书籍名称或书籍编号: ");
    gets(title);
    printf("\n\n\n\n\n\n\n");
    
    p = bookHead;
    while (p != NULL) {
        if (strcmp(p->bookname, title) == 0) {
            printf("**************************************************************");
            printf("\nbookname: ");
            puts(p->bookname);
            printf("bookid: %d\n", p->id);
            printf("author: %s\n", p->author);
            printf("year/month/day: %d/%d/%d\n", p->year, p->month, p->day);
            printf("bookcount: %d\n", p->count);
            printf("**************************************************************\n");
            exist = 1;
            break;
        }
        p = p->next;
    }
    if (exist == 0) {
        printf("未找到相关书籍...\n");
    }
    printf("输入0返回管理员界面: ");
    int n;
    
    while (1) {
        scanf("%d", &n);
        if (n == 0)
            break;
    }
}

//删除图书信息
void DeleteBookInfo() {
    Book *p;
    char title[100];
    int Exist = 0;
    
    p = bookHead;
    printf("请输入你要删除的书籍名称：");
    while (gets(title)){
        while (p != NULL){
            if (strcmp(title, p->bookname) == 0){
                Exist = 1;
                break;
            }
            p = p->next;
        }
        if (!Exist){
            printf("不存在此书籍名称的书籍...\n");
            printf("请重新输入: ");
        } else {
            break;
        }
    }
//    deleteuserbook(bookname);
    p = bookHead;
    if (strcmp(bookHead->bookname, title) == 0){
        bookHead = bookHead->next;
    }
    while (p->next != NULL){
        if (strcmp(p->next->bookname, title) == 0){
            p->next = p->next->next;
            break;
        }
        p = p->next;
    }
    p = NULL;
    //TODO: -
}

//修改图书信息
void ModifyBookInfo() {
    
}

#endif /* BMS4_h */
