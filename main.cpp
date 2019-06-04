//
//  main.cpp
//  phonebook
//
//  Created by 薛培培 on 2019/6/3.
//  Copyright © 2019 薛培培. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//声明一个结构体类型Student
typedef struct Student {
    string name;   // 姓名
    string id;    // 学号
    unsigned int age;   // 年龄
    string sex;           // 性别
    string from;        // 籍贯
    string addr;       // 通信地址
    string email;      // email
    string phone;      // 手机号
    string qq;         // qq 号
    string room;       // 寝室号
//    struct Student *next;      // 结构体指针
}Student;

// 登记学生信息
Student appendStudent() {
    Student s;
    cout << "请输入学生姓名:";
    cin >> s.name;
    cout << "请输入学号:";
    cin >> s.id;
    //    cout << "请输入年龄:";
    //    cin >> s.age;
    //    cout << "请输入性别:";
    //    cin >> s.sex;
    //    cout << "请输入籍贯:";
    //    cin >> s.from;
    //    cout << "请输入通信地址:";
    //    cin >> s.addr;
    //    cout << "请输入电子邮箱:";
    //    cin >> s.email;
    //    cout << "请输入手机号:";
    //    cin >> s.phone;
    //    cout << "请输入qq号:";
    //    cin >> s.qq;
    //    cout << "请输入寝室号:";
    //    cin >> s.room;
    return s;
}

// 根据学号查找联系人
int searchStudent(int &num, Student *stus) {
    string id;
    int i;
    cout << "请输入学生学号：";
    cin >> id;
    for (i = 0; i < num; i++) {
        if (stus[i].id == id) {
            return i;   //找到返回在数组中的位置
        }
    }
    cout << "没有找到学号是" << id << "的学生记录。" << endl;
    return -1;   //找不到返回-1；
}

// 根据学号删除联系人
void deleteStudent(int &num, Student *stus) {
    if (num < 1) {
        cout << "通讯录是空的" << endl;
        return;
    }
    int index = searchStudent(num, stus);
    int j;
    if (index >= 0 && index < num) {
        for (j = index; j < num - 1; j++) {
            stus[j] = stus[j + 1];
        }
        stus[num - 1].name = "";
        stus[num - 1].id = "";
        num--;   //学生个数减1
        cout << "该联系人已被成功移出通讯录" << endl;
    }
}

void printStudentInfo(int i, Student stus[]) {
    std::cout << "学号:" << stus[i].name << " " << "姓名:" << stus[i].id;
}

void editName(Student *stu, int &i){
    string newName;
    cout << "输入新名字：";
    cin >> newName;
    stu[i].name = newName;
    cout << "修改完毕，新的名字是" << stu[i].name;
}
void editId(Student *stu, int &i){
    string newId;
    cout << "输入新id：";
    cin >> newId;
    stu[i].id = newId;
    cout << "修改完毕，新的id是" << stu[i].id;
}

void writeToText(int &num, Student *s) {
    int i;
    ofstream file;   // 以写模式打开文件
    file.open("./out.txt", ofstream::app);
    for (i = 0; i < num; i++) {
        file << s[i].name << " " << s[i].id << endl;
    }
    file.close();
    cout << "数据写入成功" << endl;
}

void readFromText(int &num, Student *s) {
    ifstream infile("./infile.txt");    // 以读模式打开文件
    cout << "开始从文件中读取数据" << endl;
    string str;
    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile, str);
            cout << "Read from file:" << str << endl;
            int index = str.find_first_of(' ');
            if (-1 == index)
                break;
            string name = str.substr(0, index);
            string id = str.substr(index+1, str.length());
            Student stu = { name, id };
            s[num] = stu;
            num++;
        }
        //    infile.close();
        cout << "读取完毕" << endl;
    }
    else {
        cout << "open file error" << endl;
    }
}

char exit() {
    return 's';
}

int main()
{
    Student students[100];   // 声明一个包含100个成员的数组
    Student student;
    int flag;    // 功能flag
    int num = 0;    // 已经录入的联系人数
    char y = 'n';      // 标识是否继续进行
    cout << "****************<班级通讯录管理系统>****************" << endl << endl;
    cout << "※ ※" << endl;
    cout << "※ 1. 添加学生基本信息. 2. 删除学生基本信息 . ※" << endl;
    cout << "※ 3. 查询学生基本信息. 4. 修改学生基本信息 . ※" << endl;
    cout << "※ 5. 输出到文件. 6. 从文件中读取. ※" << endl;
    cout << "※ 7. 退出程序. ※" << endl << endl;
    cout << "*****************************************************" << endl << endl;
    while (y == 'n') {
        cout << "请输入数字1到7选择功能:";
        cin >> flag;
        switch (flag) {
        case 1:
            do {
                students[num] = appendStudent();
                num++;
                cout << "是否继续录入(y/n): ";
                cin >> y;
            } while (y == 'y');
            break;
        case 2:
            do {
                deleteStudent(num, students);
                cout << "是否继续删除(y/n): ";
                cin >> y;
            } while (y == 'y');
            break;
        case 3:
            do {
                int index = searchStudent(num, students);
                if (index >= 0) {
                    printStudentInfo(index, students);
                }
                cout << "是否继续删除(y/n): ";
                cin >> y;
            } while (y == 'y');
            break;
        case 4:
            int a;    // 标识要修改的信息项
            do{
                int index = searchStudent(num, students);
                if(index>=0){
                    cout << "*****请输入要修改的信息项,‘:’提示输入*****" <<endl;
                    cout << "1.姓名 2.学号 3.年龄 4.性别 5.籍贯 6.通信地址 7.电子邮箱 8.手机号 9.qq号 10.寝室号" <<endl;
                    cout << ":";
                    cin >> a;
                    switch(a){
                        case 1: 
                            editName(students, index);
                            break;
                        case 2: 
                            editId(students, index); 
                            break;
                    }
                }
                cout << "是否继续修改(y/n): ";
                cin >> y;
            }while(y=='y');
            break;
        case 5:
            writeToText(num, students);
            break;
        case 6:
            readFromText(num, students);
            break;
        case 7:
            y = exit();
        }
        cout << "现有记录数：" << num << endl;
    };

    return 0;
}
