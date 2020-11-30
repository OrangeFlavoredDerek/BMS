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

//管理员信息
typedef struct AdminInfo {
    char adminName[100];
    char scert[100];
    struct AdminInfo *next;
} Admin;

//书籍信息
typedef struct BookInfo {
    int id;
    char bookname[100];
    char author[100];
    int year;
    int month;
    int day;
    int count;
    struct BookInfo *next;
} Book;

Admin *adminHead = NULL, *adminEnd = NULL;
Book *bookHead = NULL, *bookEnd = NULL;
int adminCount, bookCount;

void writefile(int flag) {
    FILE *fp;
    Admin *adminp;
    Book *bookp;
 
    adminp = adminHead;
    bookp = bookHead;
 
    if (flag == 1) {
        fp = fopen("admin", "w");
        while (adminp != NULL){
            fwrite(adminp, sizeof(Admin), 1, fp);
            adminp = adminp->next;
        }
    } else {
        fp = fopen("book", "w");
        while (bookp != NULL) {
            fwrite(bookp, sizeof(Book), 1, fp);
            bookp = bookp->next;
        }
    }
    fclose(fp);
}

void ReadAdminFile(){
    Admin *p;
    FILE *fp;
    
    p = adminHead;
    fp = fopen("admin", "ab+");
    while (fread(p, sizeof(Admin), 1, fp)){
        if (p->next != NULL){
            p = (Admin*)malloc(sizeof(Admin));
            
            adminEnd->next = p;
            adminEnd = p;
            adminEnd->next = NULL;
        }
    }
}

void ReadBookFile(){
    Book *p;
    FILE *fp;
    
    p = bookHead;
    fp = fopen("book", "ab+");
    while (fread(p, sizeof(Book), 1, fp)){
        if (p->next != NULL){
            p = (Book*)malloc(sizeof(Book));
            
            bookEnd->next = p;
            bookEnd = p;
            bookEnd->next = NULL;
        }
    }
}

//MARK: -从键盘键入书籍信息
void TypingInfo() {
    Book *p;
    char title[100];
    int isExist = 0;
    FILE *fp;
    p = bookHead;
    
    if (bookCount == 0) {
        printf("输入新增书籍的书名: ");
        while (gets(title)) {
            if (strlen(title) > 30) {
                printf("书名过长\n");
                printf("请重新输入书名：");
                gets(title);
            } else {
                break;
            }
        }
        strcpy(bookHead->bookname, title);
        printf("书号: ");
        scanf("%d", &bookHead->id);
        printf("作者: ");
        scanf("%s", bookHead->author);
        printf("出版年份: ");
        scanf("%d", &bookHead->year);
        printf("出版月份: ");
        scanf("%d", &bookHead->month);
        printf("bookday: ");
        scanf("%d", &bookHead->day);
        printf("书籍数量: ");
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
            p = (Book*)malloc(sizeof(Book));
            
            strcpy(p->bookname, title);
            printf("id: ");
            scanf("%d", &p->id);
            printf("author: ");
            scanf("%s", p->author);
            printf("bookyear: ");
            scanf("%d", &p->year);
            printf("bookmonth: ");
            scanf("%d", &p->month);
//            printf("bookday: ");
//            scanf("%d", &p->day);
            printf("bookcount: ");
            scanf("%d", &p->count);
            
            bookEnd->next = p;
            bookEnd = p;
            bookEnd->next = NULL;
        }
    }
    bookCount++;
    
    fp = fopen("book", "w");
    while (p != NULL) {
        fwrite(p, sizeof(Book), 1, fp);
        p = p->next;
    }
    fclose(fp);
    
    printf("书籍添加成功\n");
}

//MARK: -查询图书信息
void QueryBook() {
    Book *p;
    char title[100];
    int exist = 0, xID = 0, tag = 0, n;
    
    printf("\n\n\n");
    printf("\n通过书名号查询或书名查询：\n ");
    printf("\n1.书名\n2.书名号\n");
    printf("请选择：");
    scanf("%d", &tag);
    switch (tag) {
        case 1:
            printf("请输入所要查找书名：");
            gets(title);
            break;
        case 2:
            printf("请输入所要查找书号：");
            scanf("%d", &xID);
            break;
    }
    printf("\n\n\n");
    
    p = bookHead;
    while (p != NULL) {
        if (strcmp(p->bookname, title) == 0 || p->id == xID) {
            printf("**************************************************************");
            printf("\nbookname: ");
            puts(p->bookname);
            printf("bookid: %d\n", p->id);
            printf("author: %s\n", p->author);
            printf("year/month: %d/%d\n", p->year, p->month);
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
    
    while (1) {
        scanf("%d", &n);
        if (n == 0)
            break;
    }
}

//MARK: -删除图书信息
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
    writefile(2);
}

//MARK: -修改图书信息
void ModifyBookInfo() {
    Book *p;
    char title[100], bookAuthur[100];
    int exist = 0, end = 0;
    int bYear, bMonth, bDay, bID, count;
    
    p = bookHead;
    printf("书籍列表:\n");
    while (p != NULL)
    {
        printf("bookname: %10s\n", p->bookname);
        p = p->next;
    }
    
    p = bookHead;
    printf("输入你需要修改的书籍名称(按@退出): ");
    while (gets(title)){
        if (strcmp(title, "@") == 0) {
            break;
        }
        while (p != NULL){
            if (strcmp(p->bookname, title) == 0){
                exist = 1;
                break;
            }
            p = p->next;
        }
        if (!exist){
            printf("不存在该书籍名称，请重新输入: ");
        } else {
            break;
        }
    }
    if (!exist) {
        return;
    } else {
        int cmd;
        
        printf("\n\n\n");
        printf("**************************************************************\n");
        printf("1.修改书籍名称\n");
        printf("2.修改书籍id号\n");
        printf("3.修改书籍日期\n");
        printf("4.修改书籍数量\n");
        printf("5.修改书籍作者\n");
        printf("0.退出\n");
        printf("**************************************************************");
        printf("\n\n\n");
        while (1){
            printf("输入您需要进行的操作: ");
            scanf("%d", &cmd);
            switch (cmd){
                case 1:
                    printf("输入你修改后的书籍名称: ");
                    scanf("%s", title);
                    strcpy(p->bookname, title);
                    break;
                case 2:
                    printf("输入你修改后的书籍ID: ");
                    scanf("%d", &bID);
                    p->id = bID;
                    break;
                case 3:
                    printf("输入你修改后的书籍日期: ");
                    scanf("%d%d%d", &bYear, &bMonth, &bDay);
                    p->year = bYear;
                    p->month = bMonth;
                    break;
                case 4:
                    printf("输入你修改后的书籍数量: ");
                    scanf("%d", &count);
                    p->count = count;
                    break;
            case 5:
                printf("输入你修改后的书籍作者: ");
                scanf("%s", bookAuthur);
                strcpy(p->author, bookAuthur);
                break;
            case 0:
                end = 1;
                break;
            }
            if (end == 1){
                break;
            }
        }
    }
    writefile(2);
}

//MARK: -管理员账户注册
void adminRegister(){
    Admin *p;
    char adminName[1000];
    char adminPassword[1000];
    FILE *fp;

//    system("cls");
    if (adminCount == 0) {//第一次添加
        adminHead = (Admin*)malloc(sizeof(Admin));
        printf("管理员姓名: ");
        while (gets(adminName)) {
            if (strlen(adminName) < 50) {
                break;
            } else {
                printf("账号名称过长！");
            }
        }
        strcpy(adminHead->adminName, adminName);
        printf("密码: ");
        while (gets(adminPassword)) {
            if (strlen(adminPassword) < 18) {
                break;
            } else {
                printf("密码长度过长！");
            }
        }
        strcpy(adminHead->scert, adminPassword);
        adminEnd = adminHead;
        adminEnd->next = NULL;
    } else {
        p = (struct AdminInfo *)malloc(sizeof(struct AdminInfo));
        printf("管理员姓名: ");
        while (gets(adminName)) {
            if (strlen(adminName) < 50) {
                break;
            } else {
                printf("账号名称过长！");
            }
        }
        strcpy(p->adminName, adminName);
        printf("管理员密码: ");
        while (gets(adminPassword)) {
            if (strlen(adminPassword) < 18) {
                break;
            } else {
                printf("密码长度过长！");
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

    printf("\n管理员%s创建成功\n", adminEnd->adminName);
}

//管理员操作菜单
void adminFunction() {
    int cmd;
    int end = 0;

    while (1) {
//        system("cls");
        printf("\n\n\n");
        printf("**************************************************************");
        printf("\n图书馆管理员功能系统\n");
        printf("1.添加书籍信息\n");
        printf("2.删除书籍信息\n");
        printf("3.修改书籍信息\n");
        printf("4.查询书籍信息\n");
        printf("0.退出\n");
        printf("**************************************************************");
        printf("\n\n\n");
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
            case 5:
                ReadBookFile();
                break;
            case 6:
                ReadAdminFile();
            case 0:
                end = 1;
                break;
            default:
            printf("输入错误!\n");
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
    printf("\n\n\n");
    printf("**************************************************************");
    printf("\n输入您的管理员信息: \n");
    printf("管理员姓名: ");
    gets(adminName);
    printf("管理员密码: ");
    gets(adminPassword);
    printf("**************************************************************");
    printf("\n\n\n");

    while (p != NULL) {
        while (strcmp(p->adminName, adminName) != 0) {
            printf("管理员姓名输入错误！请重新输入\n");
            printf("管理员姓名：");
            gets(adminName);
        }
        
        while (strcmp(p->scert, adminPassword) != 0) {
            printf("密码错误!请重新输入\n");
            printf("管理员密码: ");
            gets(adminPassword);
        }
        printf("管理员%s登陆成功!将自动跳转至用户界面...", p->adminName);
        adminFunction();
        
        p = p->next;
    }
}
#endif /* BMS4_h */
