//
//  BookManagementSystem.h
//  BMS3.5
//
//  Created by Derek Chan on 2020/11/18.
//

//MARK: -BookManagementSystem
//(1) 能从文件导入图书的信息
//(2) 能从键盘录入图书的信息;
//(3) 给定图书号，显示某本图书信息;
//(4) 能根据图书号修改图书的信息
//(5) 能根据图书号删除图书的信息;
//(6) 能将图书信息导出到指定文件
//*管理员账户注册与登录与修改密码

#ifndef BookManagementSystem_h
#define BookManagementSystem_h

#include <stdio.h>
#include <string.h>

void IsNULL(FILE *file) {
    if (file == NULL) {
        printf("打开文件夹失败\n");
        return;
    }
}

int Menu(){
    int cmd;
    
    printf("╔═══════════════════════╗\n");
    printf("║            菜单界面                          ║\n");
    printf("║1 . 文件导入                                  ║\n");
    printf("║2. 从键盘中导入图书信息                         ║\n");
    printf("║3. 查询图书信息                                ║\n");
    printf("║4. 删除图书信息                                ║\n");
    printf("║5. 修改图书信息                                ║\n");
    printf("║6. 导出图书信息                                ║\n");
    printf("║7. 退出系统                                 ║\n");
    printf("╚═══════════════════════╝\n");
    printf("\n请输入执行操作的编号：");
    
    scanf("%d", &cmd);
    return cmd;
}

//MARK: -从键盘键入信息
void TypingInfo(char *fp){
    FILE *file;
    FILE *fileTemp;
    char *fpTemp = "tmp.txt";
    int res, ISBN = 0, xISBN;
    char title[20], author[30], publisher[40];
    int i;
    char t[20], a[30], p[40];
    file = fopen(fp, "r");
    fileTemp = fopen(fpTemp, "w");
    IsNULL(file);
//    printf("请输入ISBN号：\n");
//    scanf("%d", &ISBN);
    
    while (1) {
        res = fscanf(file, "%d %s %s %s\n", &xISBN, title, author, publisher);
        if (res == -1){
            printf("请输入ISBN号 书名 作者 出版社，以空格间隔\n");
            scanf("%d %s %s %s", &i, t, a, p);
            fprintf(fileTemp, "%10d %10s %10s %10s\n", ISBN, t, a, p);
            printf("插入成功\n");
            fclose(file);
            fclose(fileTemp);
            remove(fp);
            rename(fpTemp, fp);
            return;
        }
        
        if (ISBN == xISBN){
            printf("该书已存在，插入失败\n");
            fclose(file);
            fclose(fileTemp);
            return;
        } else {
            fprintf(fileTemp, "%10d %10s %10s %10s\n", ISBN, title, author, publisher);
        }
    }
}

//MARK: -从文件导入信息
void Import(char *fp){
    int c;
    char fileName[20];
    
    FILE *s = NULL, *d = NULL; {
        printf("输入文件名称：");
        scanf("%s", fileName);
    }
    
    s = fopen(fileName, "rt+");
    d = fopen("ID.txt", "a");//打开文件
    if (s == NULL || d == NULL){//打开文件失败
        if (s) {
            fclose(s);
        } else if (d) {
            fclose(d);
        }
        return;
    }
    fprintf(d, "\n");
    while ((c = fgetc(s)) != EOF) {//循环读取文件直至文件末尾
        fputc(c, d);//写目标文件
    }
    printf("成功！\n");
    fclose(s);
    fclose(d);//关闭文件
}

//MARK: -根据ISBN号删除信息
void DeleteBookInfo(char *fp){
    FILE *file, *fileTemp;
    char *fpTemp = "text.txt";
    int res, ISBN, xISBN, success;
    char title[20], authur[30], publisher[40];
    file = fopen(fp, "r");
    fileTemp = fopen(fpTemp, "w");
    
    IsNULL(file);
    
    printf("请输入ISBN号：\n");
    scanf("%d", &ISBN);
    success = 0;
    
    while (1) {
        res = fscanf(file, "%d %s %s %s\n", &xISBN, title, authur, publisher);
        if (res == -1) {
            if (success == 0) {
                printf("无此书信息\n");
                fclose(file);
                fclose(fileTemp);
                return;
            } else {
                printf("删除成功!\n");
                fclose(file);
                fclose(fileTemp);
                remove(fp);
                rename(fpTemp, fp);
            }
        }
        if (ISBN == xISBN) {
            success = 1;
        } else {
            fprintf(fileTemp, "%d %s %s %s\n", xISBN, title, authur, publisher);
        }
    }
}

//MARK: -根据图书号查询
void Query(char *fp) {
    FILE *file;
    int res, ISBN, xISBN;
    char title[20], authur[30], publisher[40];
    file = fopen(fp, "r");
    
    IsNULL(file);
    printf("请输入ISBN号: \n");
    scanf("%d", &ISBN);
    
    while (1) {
        res = fscanf(file, "%d %s %s %s\n", &xISBN, title, authur, publisher);
        if (res == -1) {
            fclose(file);
            return;
        } else if (ISBN == xISBN){
            printf("ISBN：%d\n", ISBN);
            printf("书名：《%s》 作者：%s 出版社：%s\n", title, authur, publisher);
        }
    }
}

//MARK: -根据图书号修改信息
void ModifyBookInfo(char *fp) {
    FILE *file;
    FILE *fileTemp;
    char *fpTemp = "tmp.txt";
    int res, ISBN, xISBN, success;
    char title[20], xtitle[20];
    char authur[30], xAuthur[30];
    char publisher[40], xPublisher[40];
    file = fopen(fp, "r");
    fileTemp = fopen(fpTemp, "w");
    
    IsNULL(file);
//    if (file == NULL) {
//        printf("打开文件夹失败\n");
//        return;
//    }
    printf("请输入ISBN号：\n");
    scanf("%d", &ISBN);
    success = 0;
    
    while (1) {
        res = fscanf(file, "%d %s %s %s\n", &xISBN, title, authur, publisher);
        if (res == -1){
            if (success == 0){
                printf("无此书籍信息\n");
                fclose(file);
                fclose(fileTemp);
                return;
            } else {
                printf("修改成功！\n");
                fclose(file);
                fclose(fileTemp);
                remove(fp);
                rename(fpTemp, fp);
                return;
            }
        }
        if (ISBN == xISBN) {
            success = 1;
            printf("请输入书名、作者、出版社，以空格分隔\n");
            scanf("%s %s %s", xtitle, xAuthur, xPublisher);
            fprintf(fileTemp, "%10d %10s %10s %s\n", ISBN, xtitle, xAuthur, xPublisher);
        } else {
            fprintf(fileTemp, "%10d %10s %10s %10s\n", xISBN, title, authur, publisher);
        }
    }
}

//MARK: -导入文件
void Export(char *fp) {
    FILE *a, *b;
    char temp[100];
    char z[70] = "      ISBN号       书名       作者      出版社";
    char fpTemp[20];
    
    printf("请输入导出的文件名：\n");
    scanf("%s", fpTemp);
    a = fopen(fp, "r");
    b = fopen(fpTemp, "w");
    
    IsNULL(a);
    fprintf(b, "%s\n", z);
    while (1) {
        char *p = fgets(temp, 50, a);
        if (p == NULL) {
            break;
        }
        fputs(temp, b);
    }
    printf("导出成功！\n");
    fclose(a);
    fclose(b);
}


#endif /* BookManagementSystem_h */
