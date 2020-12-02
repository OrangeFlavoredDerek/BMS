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
    char adminName[1000];//管理员账号名称
    char password[1000];//管理员账号密码
    struct AdminInfo *next;
} Admin;

//书籍信息
typedef struct BookInfo {
    int id;//书籍号
    char bookname[1000];//书名
    char author[1000];//作者
    int year;//出版年份
    int month;//出版月份
    int count;//书籍
    struct BookInfo *next;
} Book;

Admin *adminHead = NULL, *adminEnd = NULL;
Book *bookHead = NULL, *bookEnd = NULL;
long int adminCount, bookCount;

//加载动画函数
void logtime(char *c,int n) {
    int i;
    for(i=0;i<n;i++) {
        printf("%s",c);
//        Sleep(500);
    }
    printf("\n");
}

//MARK: -写入文件
void WriteFile(int flag) {
    FILE *fp;
    Admin *adminp;
    Book *bookp;
 
    adminp = adminHead;
    bookp = bookHead;
 
    if (flag == 1) {
        fp = fopen("admin", "w");//打开管理员文件
        while (adminp != NULL){
            fwrite(adminp, sizeof(Admin), 1, fp);//写入信息
            adminp = adminp->next;
        }
    } else {
        fp = fopen("book", "w");//打开书籍文件
        while (bookp != NULL) {
            fwrite(bookp, sizeof(Book), 1, fp);//写入书籍信息
            bookp = bookp->next;
        }
    }
    fclose(fp);//关闭文件
}

//MARK: -读取管理员文件
void ReadAdminFile(){
    Admin *p;
    FILE *fp;
    
    p = adminHead;
    fp = fopen("admin", "ab+");//打开文件
    while (fread(p, sizeof(Admin), 1, fp)){
        if (p->next != NULL){
            p = (Admin*)malloc(sizeof(Admin));//分配动态内存
            
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
    fp = fopen("book", "ab+");//打开文件
    while (fread(p, sizeof(Book), 1, fp)){
        if (p->next != NULL){
            p = (Book*)malloc(sizeof(Book));//分配动态内存
            
            bookEnd->next = p;
            bookEnd = p;
            bookEnd->next = NULL;
        }
    }
}

//MARK: -从键盘键入书籍信息
void TypingInfo() {
    Book *p;
    char title[1000];//从键盘键入的书名
    int isExist = 0;//标签，判断所加入书籍是否存在
    
//    system("cls");
    if (bookCount == 0) {//当书籍数量为0时
        printf("输入新增书籍的书名: ");
        while (gets(title)) {
            if (strlen(title) > 1000) {
                printf("书名过长\n");
                printf("请重新输入书名：");
            } else {
                break;
            }
        }
        strcpy(bookHead->bookname, title);//strcpy()字符串复制函数
        printf("书号: ");
        scanf("%d", &bookHead->id);
        printf("作者: ");
        scanf("%s", bookHead->author);
        printf("出版年份: ");
        scanf("%d", &bookHead->year);
        printf("出版月份: ");
        scanf("%d", &bookHead->month);
        printf("书籍数量: ");
        scanf("%d", &bookHead->count);
        
        bookEnd = bookHead;
        bookEnd->next = NULL;
    } else {//数据库中已经存在书籍时
        printf("输入新增书籍的书名: ");
        while (gets(title)) {
            if (strlen(title) > 1000) {
                printf("书名过长\n请重新输入：");
            } else {
                break;
            }
        }
        p = bookHead;
        
        while (p != NULL) {
            if (strcmp(title, p->bookname) == 0) {//strcmp()字符串比较函数，当两字符串相同时返回0
                isExist = 1;//书籍已存在
                break;
            }
            p = p->next;
        }
        if (isExist == 1) {//当所添加书籍已经存在时
            int count;
            
            printf("输入新添书籍的数量: ");
            scanf("%d", &count);
            p->count += count;//仅添加改书籍数量
        } else {//若未存在
            p = (Book*)malloc(sizeof(Book));//分配动态内存
            
            strcpy(p->bookname, title);
            printf("id: ");
            scanf("%d", &p->id);
            printf("author: ");
            scanf("%s", p->author);
            printf("bookyear: ");
            scanf("%d", &p->year);
            printf("bookmonth: ");
            scanf("%d", &p->month);
            printf("bookcount: ");
            scanf("%d", &p->count);
            
            bookEnd->next = p;
            bookEnd = p;
            bookEnd->next = NULL;
        }
    }
    bookCount++;
    
    WriteFile(2);
    
    printf("书籍添加成功\n");
    printf("自动返回管理员界面...\n");
//    system("cls");
//    logtime('.', 6);
}

//MARK: -查询图书信息
void QueryBook() {
    Book *p;
    int exist = 0, xID = 0, n;
    
    printf("\n\n\n");
    printf("\n请输入书名号查询：\n ");
    printf("请输入所要查找书号：");
    scanf("%d", &xID);
    printf("\n\n\n");
    
    p = bookHead;
    while (p != NULL) {
        if (p->id == xID) {
            printf("**************************************************************");
            printf("书籍名称: ");
            puts(p->bookname);
            printf("书号: %d\n", p->id);
            printf("作者: %s\n", p->author);
            printf("出版时间: %d/%d\n", p->year, p->month);
            printf("书籍数量: %d\n", p->count);
            printf("**************************************************************\n");
            exist = 1;//1表示已找到书籍
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
    char title[1000];//从键盘键入的书名
    int Exist = 0;//标签，判断书籍是否存在
    
    p = bookHead;
    printf("请输入你要删除的书籍名称：");
    while (gets(title)){
        while (p != NULL){
            if (strcmp(title, p->bookname) == 0){
                Exist = 1;//1为书籍存在
                break;
            }
            p = p->next;
        }
        if (!Exist){//若改书籍不存在
            printf("不存在此书籍名称的书籍...\n");
            printf("请重新输入: ");
        } else {
            break;
        }
    }
//删除书籍
    p = bookHead;
    if (strcmp(bookHead->bookname, title) == 0){
        bookHead = bookHead->next;//删除链表内元素
    }
//    while (p->next != NULL){
//        if (strcmp(p->next->bookname, title) == 0){
//            p->next = p->next->next;
//            break;
//        }
//        p = p->next;
//    }
    p = NULL;
    WriteFile(2);//写入文件
    printf("删除成功！\n");
}

//MARK: -修改图书信息
void ModifyBookInfo() {
    Book *p;
    char title[1000], bookAuthur[1000];
    int exist = 0, end = 0;
    int bYear, bMonth, bID, count;
    
    p = bookHead;
    printf("书籍列表:\n");
    while (p != NULL) {
        printf("%10s\n", p->bookname);//现实数据库内所有存储书籍
        p = p->next;
    }
    
    p = bookHead;
    printf("输入你需要修改的书籍名称(按@退出): ");
    while (gets(title)) {
        if (strcmp(title, "@") == 0) {//当从键盘键入@时结束
            break;
        }
        while (p != NULL){
            if (strcmp(p->bookname, title) == 0){
                exist = 1;//要修改的书籍在数据库中存在
                break;
            }
            p = p->next;
        }
        if (!exist) {
            printf("不存在该书籍名称，请重新输入: ");
        } else {
            break;
        }
    }
    if (!exist) {
        return;
    } else {
        int cmd;
        
        system("cls");
        printf("\n\n\n");
        printf("**************************************************************\n");
        printf("1.修改书籍名称\n");
        printf("2.修改书籍图书号\n");
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
                    printf("修改成功！\n");
                    break;
                case 2:
                    printf("输入你修改后的书籍ID: ");
                    scanf("%d", &bID);
                    p->id = bID;
                    printf("修改成功！\n");
                    break;
                case 3:
                    printf("输入你修改后的书籍日期: ");
                    scanf("%d%d", &bYear, &bMonth);
                    p->year = bYear;
                    p->month = bMonth;
                    printf("修改成功！\n");
                    break;
                case 4:
                    printf("输入你修改后的书籍数量: ");
                    scanf("%d", &count);
                    p->count = count;
                    printf("修改成功！\n");
                    break;
                case 5:
                    printf("输入你修改后的书籍作者: ");
                    scanf("%s", bookAuthur);
                    strcpy(p->author, bookAuthur);
                    printf("修改成功！\n");
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
    WriteFile(2);//写入文件
}

//MARK: -修改管理员密码
void changeThePassword() {
    Admin *p;
    char xPassword[1000];
    int exist = 0;
    
    p = adminHead;
    printf("请输入旧密码：");
    while (gets(xPassword)) {
        while (p != NULL) {
            if (strcmp(p->password, xPassword) == 0) {
                exist = 1;
                break;
            }
            p = p->next;
        }
        if (exist == 0) {
            printf("密码输入错误！\n请重新输入：");
        } else {
            break;
        }
    }
    
    if (exist == 1) {
        printf("请输入新密码：");
        gets(xPassword);
        while (strcmp(p->password, xPassword) == 0) {
            printf("新密码不能与旧密码相同！\n请重新输入：");
            gets(xPassword);
        }
        strcpy(p->password, xPassword);
        printf("修改密码成功！\n");
        WriteFile(1);
        return;
    }
}

//MARK: -管理员账户注册
void adminRegister(){
    Admin *p;
    char adminName[1000];
    char adminPassword[1000];

//    system("cls");
    if (adminCount == 0) {//第一次添加
        adminHead = (Admin*)malloc(sizeof(Admin));
        printf("管理员姓名: ");
        while (gets(adminName)) {
            if (strlen(adminName) < 1000) {
                break;
            } else {
                printf("账号名称过长！");
                printf("管理员姓名:");
            }
        }
        strcpy(adminHead->adminName, adminName);
        printf("密码: ");
        while (gets(adminPassword)) {
            if (strlen(adminPassword) < 1000) {
                break;
            } else {
                printf("密码长度过长！");
            }
        }
        strcpy(adminHead->password, adminPassword);
        adminEnd = adminHead;
        adminEnd->next = NULL;
    } else {
        p = (struct AdminInfo *)malloc(sizeof(struct AdminInfo));
        printf("管理员姓名: ");
        while (gets(adminName)) {
            if (strlen(adminName) < 1000) {
                break;
            } else {
                printf("账号名称过长！");
                printf("管理员姓名:");
            }
        }
        strcpy(p->adminName, adminName);
        printf("管理员密码: ");
        while (gets(adminPassword)) {
            if (strlen(adminPassword) < 100) {
                break;
            } else {
                printf("密码长度过长！");
            }
        }
        strcpy(p->password, adminPassword);
        adminEnd->next = p;
        adminEnd = p;
        adminEnd->next = NULL;
    }
    adminCount++;
    
    WriteFile(1);

    printf("\n管理员%s创建成功\n", adminEnd->adminName);
}

//MARK: -管理员操作菜单
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
        printf("5.修改密码\n");
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
                changeThePassword();
                break;
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
    char adminName[1000];
    char adminPassword[1000];

    p = adminHead;
    printf("\n\n\n");
    printf("**************************************************************");
    printf("\n输入您的管理员信息(输入@取消登陆): \n");
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
        
        while (strcmp(p->password, adminPassword) != 0) {
            printf("密码错误!请重新输入\n");
            printf("管理员密码: ");
            gets(adminPassword);
        }
//        logtime('.', 6000);
        printf("管理员%s登陆成功!将自动跳转至用户界面...", p->adminName);
        adminFunction();
        
        p = p->next;
    }
}

#endif /* BMS4_h */
