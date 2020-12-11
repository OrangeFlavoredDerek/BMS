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
//#include <Windows.h>

#define Maxsize 3000

//管理员信息
typedef struct AdminInfo {
    char adminName[Maxsize];//管理员账号名称
    char password[Maxsize];//管理员账号密码
    struct AdminInfo *next;
} Admin;

//书籍信息
typedef struct BookInfo {
    int id;//书籍号
    char bookname[Maxsize];//书名
    char author[Maxsize];//作者
    int year;//出版年份
    int month;//出版月份
    int n;
    char t[Maxsize];
    struct BookInfo *next;
} Book;

Admin *adminHead = NULL, *adminEnd = NULL;
Book *bookHead = NULL, *bookEnd = NULL;

//加载动画函数
void logtime(char c, int n) {
    int i;
    for(i=0;i<n;i++) {
        printf("%c",c);
//        Sleep(500);
    }
    printf("\n");
}

//MARK: -写入文件
void WriteFile(int tag) {
    FILE *fp;
    Admin *adminp;
    Book *bookp;
    
    adminp = adminHead;
    bookp = bookHead;
    
    if (tag == 1) {
        fp = fopen("admin.txt", "w");
        while (adminp) {
            fputs(adminp->adminName, fp);
            fputs("", fp);
            fputs(adminp->password, fp);
            if (adminp->next) {
                fputs("\n", fp);
            }
            adminp = adminp->next;
        }
        fclose(fp);
    } else {
        fp = fopen("book.txt", "w");
        while (bookp) {
            fputc(bookp->id, fp);
            fputs("", fp);
            fputs(bookp->bookname, fp);
            fputs("", fp);
            fputs(bookp->author, fp);
            fputs("", fp);
            fputc(bookp->year, fp);
            fputs("", fp);
            fputc(bookp->month, fp);
            if (bookp->next) {
                fputs("\n", fp);
            }
            bookp = bookp->next;
        }
        fclose(fp);
    }
}

//void WriteFile(int tag) {
//    FILE *fp;
//    Admin *adminp;
//    Book *bookp;
//
//    adminp = adminHead;
//    bookp = bookHead;
//
//    if (tag == 1) {
//        fp = fopen("admin.txt", "w");//打开管理员文件
//        while (adminp != NULL){
//            fwrite(adminp, sizeof(Admin), 1, fp);//写入信息
//            adminp = adminp->next;
//        }
//    } else {
//        fp = fopen("book.txt", "w");//打开书籍文件
//        while (bookp != NULL) {
//            fwrite(bookp, sizeof(Book), 1, fp);//写入书籍信息
//            bookp = bookp->next;
//        }
//    }
//    fclose(fp);//关闭文件
//}

//MARK: -读取文件
void ReadFile(int tag) {
    Admin *adminp;
    Book *bookp;
    FILE *fp;
    
    adminp = adminHead;
    bookp = bookHead;
    
    if (tag == 1) {
        fp = fopen("admin.txt", "a+");
        while (!feof(fp)) {
            char w;
            adminp = (Admin*)malloc(sizeof(Admin));
            
            fscanf(fp, "%s", adminp->adminName);
            fscanf(fp, "%c", &w);
            fscanf(fp, "%s", adminp->password);
            
            adminEnd->next = adminp;
            adminEnd = adminp;
        }
        adminEnd->next = NULL;
    } else {
        fp = fopen("book.txt", "a+");
        while (!feof(fp)) {
            char w;
            bookp = (Book*)malloc(sizeof(Book));
            
            fscanf(fp, "%d", &bookp->id);
            fscanf(fp, "%s", bookp->bookname);
            fscanf(fp, "%s", bookp->author);
            fscanf(fp, "%d", &bookp->year);
            fscanf(fp, "%c", &w);
            fscanf(fp, "%d", &bookp->month);
            fscanf(fp, "%c", &w);
            
            bookEnd->next = bookp;
            bookEnd = bookp;
        }
        bookEnd->next = NULL;
    }
}

//void ReadFile(int tag) {
//    Admin *adminp;
//    Book *bookp;
//    FILE *fp;
//
//    adminp = adminHead;
//    bookp = bookHead;
//
//    if (tag == 1) {
//        fp = fopen("admin.txt", "a+");
//        while (fread(adminp, sizeof(Admin), 1, fp)) {
//            if (adminp->next != NULL) {
//                adminp = (Admin*)malloc(sizeof(Admin));
//
//                adminEnd->next = adminp;
//                adminEnd = adminp;
//                adminEnd->next = NULL;
//            }
//        }
//    } else {
//        fp = fopen("book.txt", "a+");
//        while (fread(bookp, sizeof(Book), 1, fp)) {
//            if (bookp->next != NULL) {
//                bookp = (Book*)malloc(sizeof(Book));
//
//                bookEnd->next = bookp;
//                bookEnd = bookp;
//                bookEnd->next = NULL;
//            }
//        }
//    }
//}

//MARK: -错误检查
void errorChecking(int element, char *charElem, int tag) {
    if (tag == 1) {
        while (element <= 0) {
            printf("输入格式错误\n请重新输入：");
            scanf("%d", &element);
        }
    } else {
        while (strcmp(charElem, "") == 0) {
            printf("输入格式错误\n请重新输入：");
            scanf("%s", charElem);
        }
    }
}

//MARK: -从键盘键入书籍信息
void TypingInfo() {
    char title[Maxsize];//从键盘键入的书名
    int isExist = 0;//标签，判断所加入书籍是否存在
    
//    system("cls");
    printf("输入新增书籍的书名: ");
    while (gets(title)) {
        if (strcmp(title, bookHead->bookname) == 0) {
            isExist = 1;
            printf("该书籍已存在，请勿重复添加！\n");
            return;
        } else {
            break;
        }
    }
    strcpy(bookHead->bookname, title);//strcpy()字符串复制函数
    printf("书籍号: ");
    scanf("%d", &bookHead->id);
    errorChecking(bookHead->id, bookHead->t, 1);
    printf("作者: ");
    scanf("%s", bookHead->author);
    errorChecking(bookHead->n, bookHead->author, 2);
    printf("出版年份: ");
    scanf("%d", &bookHead->year);
    errorChecking(bookHead->year, bookHead->t, 1);
    printf("出版月份: ");
    scanf("%d", &bookHead->month);
    errorChecking(bookHead->month, bookHead->t, 1);
    
    bookEnd = bookHead;
    bookEnd->next = NULL;
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
    printf("请输入书名号查询\n");
    printf("请输入所要查找书号：");
    scanf("%d", &xID);
    printf("\n\n\n");
    
    p = bookHead;
    while (p != NULL) {
        if (p->id == xID) {
            printf("**************************************************************");
            printf("\n书籍名称: %s\n", p->bookname);
            printf("书号: %d\n", p->id);
            printf("作者: %s\n", p->author);
            printf("出版时间: %d年%d月\n", p->year, p->month);
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
        fflush(stdin);
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
    Book *p = NULL, *q = NULL;
    char title[Maxsize], bookAuthur[Maxsize];
    int exist = 0, end = 0;
    int bYear, bMonth, bID;
    
    q = bookHead;
    printf("书籍列表:\n");
    while (q != NULL) {
        printf("%10s\t", q->bookname);//现实数据库内所有存储书籍
        printf("%d\n", q->id);
        q = q->next;
    }
    
    p = bookHead;
    printf("输入你需要修改的书籍号(按0退出): ");
    while (scanf("%d", &bID)) {
        if (bID == 0) {//当从键盘键入@时结束
            break;
        }
        while (p){
            if (p->id == bID){
                exist = 1;//要修改的书籍在数据库中存在
                break;
            }
            p = p->next;
        }
        if (exist != 1) {
            printf("不存在该书籍名称，请重新输入: ");
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
        printf("4.修改书籍作者\n");
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
                    errorChecking(p->n, p->bookname, 2);
                    strcpy(p->bookname, title);
                    printf("修改成功！\n");
                    break;
                case 2:
                    printf("输入你修改后的书籍ID: ");
                    scanf("%d", &bID);
                    errorChecking(p->id, p->t, 1);
                    p->id = bID;
                    printf("修改成功！\n");
                    break;
                case 3:
                    printf("输入你修改后的书籍日期: ");
                    scanf("%d%d", &bYear, &bMonth);
                    errorChecking(p->year, p->t, 1);
                    errorChecking(p->month, p->t, 1);
                    p->year = bYear;
                    p->month = bMonth;
                    printf("修改成功！\n");
                    break;
                case 4:
                    printf("输入你修改后的书籍作者: ");
                    scanf("%s", bookAuthur);
                    errorChecking(p->n, p->author, 2);
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
    char xPassword[Maxsize];
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
//        return;
    }
}

//MARK: -管理员账户注册
void adminRegister(){
//    Admin *p;
    char adminName[Maxsize];
    char adminPassword[Maxsize];

//    system("cls");
//    adminHead = (Admin*)malloc(sizeof(Admin));
    printf("管理员姓名: ");
    while (gets(adminName)) {
        if (strlen(adminName) < Maxsize) {
            break;
        } else {
            printf("账号名称过长！");
            printf("管理员姓名:");
        }
    }
    strcpy(adminHead->adminName, adminName);
    printf("密码: ");
    while (gets(adminPassword)) {
        if (strlen(adminPassword) < Maxsize) {
            break;
        } else {
            printf("密码长度过长！");
        }
    }
    strcpy(adminHead->password, adminPassword);
    adminEnd = adminHead;
    adminEnd->next = NULL;
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
    char adminName[Maxsize];
    char adminPassword[Maxsize];

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

        while (strcmp(p->password, adminPassword) != 0) {
            printf("密码错误!请重新输入\n");
            printf("管理员密码: ");
            gets(adminPassword);
        }
//        logtime('.', 6);
        printf("管理员%s登陆成功!将自动跳转至用户界面...", p->adminName);
        adminFunction();

        p = p->next;
    }
}

#endif /* BMS4_h */
