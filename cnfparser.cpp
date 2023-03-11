#include "sat.h"
ClauseNode* CreateClauseForSudoku(int& VARNUM, string& filename) {

    string HFilePath = R"(D:\VS_project\sat\sat\)";
    //这样就可以不用转义了
    string path = HFilePath + filename;
    ifstream fis(path);
    if (!fis) {
        cout << "文件无法打开" << endl;
        return nullptr;
    }
    char ch;
    char buf[100];
    fis >> ch;
    while (ch != 'p') {
        fis.getline(buf, 100);
        fis >> ch;
    }
    string cnf;
    int VarNum, ClauseNum;
    fis >> cnf >> VarNum >> ClauseNum;
    fis.get();

    ClauseNode* HEAD = new ClauseNode;
    ClauseNode* headRear = HEAD;
    ClauseNode* END = new ClauseNode;
    for (int i = 0; i < ClauseNum; i++) {

        int temp;
        fis >> temp;

        VarNode* front = new VarNode;
        front->data = temp;
        headRear->right = front;
        headRear->num_of_var++;

        fis >> temp;
        while (temp != 0) {
            VarNode* rear = new VarNode;
            front->next = rear;
            rear->data = temp;
            front = front->next;
            headRear->num_of_var++;
            fis >> temp;
        }
        front->next = nullptr;
        fis.get();
        ClauseNode* tp = new ClauseNode;
        headRear->down = tp;
        END = headRear;
        headRear = headRear->down;
    }
    END->down = nullptr;


    ClauseNode* Phead = HEAD;
    VarNode* front;


    cout << "需要在当前窗口中打印cnf文件吗？需要请键入Y，否则请键入N" << endl;
    char judge_cnfshow;
    cin >> judge_cnfshow;
    while (judge_cnfshow != 'N')
    {
        if (judge_cnfshow == 'Y') {
            while (Phead != nullptr) {
                front = Phead->right;
                while (front != nullptr) {
                    cout << front->data << " ";
                    front = front->next;
                }
                cout << endl;
                Phead = Phead->down;
            }
        }

        judge_cnfshow = 'N';
    }
    cout << "\n测试成功！" << endl;
    VARNUM = VarNum;
    return HEAD;
}
ClauseNode* CreateClause(int& VARNUM, string& filename) {
    
    string path =  filename;
    ifstream ifs(path);
    if (!ifs) {
        cout << "文件无法打开" << endl;
        return nullptr;
    }
    char ch;
    char buf[100];
    ifs >> ch;
    while (ch != 'p') {
        ifs.getline(buf, 100);
        ifs >> ch;
    }
    string cnf;
    int VarNum, ClauseNum;
    ifs >> cnf >> VarNum >> ClauseNum;
    ifs.get();

    ClauseNode* HEAD = new ClauseNode;
    ClauseNode* headRear = HEAD;
    ClauseNode* END = new ClauseNode;
    for (int i = 0; i < ClauseNum; i++) {
      
        int temp;
        ifs >> temp;
       
        VarNode* front = new VarNode;
        front->data = temp;
        headRear->right = front;
        headRear->num_of_var++;
        
        ifs >> temp;
        while (temp != 0) {
            VarNode* rear = new VarNode;
            front->next = rear;
            rear->data = temp;
            front = front->next;
            headRear->num_of_var++;
            ifs >> temp;
        }
        front->next = nullptr;
        ifs.get();
        ClauseNode* tp = new ClauseNode;
        headRear->down = tp;
        END = headRear;
        headRear = headRear->down;
    }
    END->down = nullptr;

  
    ClauseNode* Phead = HEAD;
    VarNode* front;
    
    cout << "是否需要在命令行窗口打印cnf文件，需要请键入Y，否则键入N" << endl;
    char judge_cnfshow;
    cin >> judge_cnfshow;
    while (judge_cnfshow != 'N')
    {
        if (judge_cnfshow == 'Y') {
            while (Phead != nullptr) {
                front = Phead->right;
                while (front != nullptr) {
                    cout << front->data << " ";
                    front = front->next;
                }
                cout << endl;
                Phead = Phead->down;
            }
        }

        judge_cnfshow = 'N';
    }
    cout << "\n测试成功！" << endl;

    VARNUM = VarNum;
    return HEAD;
}

