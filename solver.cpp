
#include "sat.h"

//寻找有无空子句
status IsEmptyClause(ClauseNode* LIST) {
    ClauseNode* PHead = LIST;
    while (PHead != nullptr) {
        if(PHead->num_of_var == 0)
            return 1;
        PHead = PHead->down;
    }
    return 0;
}

//单子句的判断
ClauseNode* IsSingleClause(ClauseNode* Pfind) {
    while (Pfind != nullptr ) {
        if(Pfind->num_of_var == 1)
            return Pfind;
        Pfind = Pfind->down;
    }
    return nullptr;
}

//此函数用于保存二维链表的一个副本，避免抹掉原始数据
ClauseNode* Duplication(ClauseNode* LIST) {  
    ClauseNode* SrcHead = LIST;
    ClauseNode* ReHead = new ClauseNode;
    ReHead->num_of_var = SrcHead->num_of_var; 
    ClauseNode* Phead = ReHead; 
    VarNode *ReData = new VarNode; 
    VarNode *FirstSrcData = SrcHead->right; 
    ReData->data = FirstSrcData->data;
    Phead->right = ReData;
    for (FirstSrcData = FirstSrcData->next;FirstSrcData != nullptr; FirstSrcData = FirstSrcData->next) {
        VarNode *NewDataNode = new VarNode;
        NewDataNode->data = FirstSrcData->data;
        ReData->next = NewDataNode;
        ReData = ReData->next;
    }
  
    for(SrcHead = SrcHead->down; SrcHead != nullptr ; SrcHead = SrcHead->down) {
        ClauseNode* NewHead = new ClauseNode;
        VarNode* NewData = new VarNode;
        NewHead->num_of_var = SrcHead->num_of_var;
        Phead->down = NewHead;
        Phead = Phead->down;
        VarNode* SrcData = SrcHead->right;
        NewData->data = SrcData->data;
        Phead->right = NewData;
        for (SrcData = SrcData->next;SrcData != nullptr; SrcData = SrcData->next) {
            VarNode* node = new VarNode;
            node->data = SrcData->data;
            NewData->next = node;
            NewData = NewData->next;
        }
        NewData->next = nullptr;
    }
    Phead->down = nullptr;

    return ReHead;
}

//直接将单位子句加到二维链表的头部，用于DPLL算法的分支变元策略
ClauseNode* ADDSingleClause(ClauseNode* LIST,int Var) { 
    ClauseNode* AddHead = new ClauseNode;
    VarNode* AddData = new VarNode;

    AddData->data = Var;
    AddData->next = nullptr;
    AddHead->right = AddData;
    AddHead->num_of_var = 1;
    AddHead->down = LIST;
    LIST = AddHead;
    return LIST;
}

//删除变元结点
void DeleteVarNode(int temp,ClauseNode *&LIST) {
    VarNode* p_rear = nullptr;
    for (ClauseNode* pHeadNode = LIST; pHeadNode != nullptr ; pHeadNode = pHeadNode->down)
        for (VarNode *rear = pHeadNode->right; rear != nullptr ; rear = rear->next) {
            if (rear->data == temp)  
            {
               
                DeleteClauseNode(pHeadNode, LIST);
           
                break;
            }
                
            else if (abs(rear->data) == abs(temp)) { 
                if(rear == pHeadNode->right) { 
                    pHeadNode->right = rear->next;
                    pHeadNode->num_of_var--;
                }
                else{
                    for (VarNode* front = pHeadNode->right; front != nullptr; front= front->next)
                        if(front->next == rear) {
                            front->next = rear->next;
                            delete rear;
                            rear = front;
                            pHeadNode->num_of_var--;
                        }
                }
            }
        }
}

//删除子句结点
void DeleteClauseNode(ClauseNode *Clause,ClauseNode *&LIST) {
    if (!Clause) return;
    if (Clause == LIST) {
        LIST = Clause->down;
        FreeClauseNode(Clause); 
    }
       
    else {
        for (ClauseNode *front = LIST; front != nullptr; front = front->down)
            if (front->down == Clause) {
                front->down = Clause->down;
               FreeClauseNode(Clause); 
            }
    }
}

//释放子句头结点
void FreeClauseNode(ClauseNode* Clause) {
   
        VarNode* p1_DataNode = Clause->right;
        VarNode* p2_DataNode = Clause->right;
        Clause->right = nullptr;
        while (p2_DataNode != nullptr) {
            p1_DataNode = p2_DataNode->next;
            delete p2_DataNode;
            p2_DataNode = p1_DataNode;
        }
}

//打印cnf文件
void show(struct consequence *result,int VarNum) {
    cout<<"V ";
    for(int i = 0; i < VarNum; i++) {
        if (result[i].value == 1)
            cout<<i+1<<" ";
        else if(result[i].value == 0)
            cout<<-(i+1)<<" ";
        else
            cout<<(i+1)<<" ";
        //可正可负的统一记录为true即可
    }
    cout<<endl;
}

//寻求频率最高的布尔变元
int Choose_max(ClauseNode* LIST) {
    ClauseNode* p_head = LIST;
    VarNode* p_data = LIST->right;
    Count Result_fre[CHOOSE_SOLUTION];
    Count* p_count = Result_fre;
    int flag_count = 0;
    int max_count = 0;
    int max_num = 0;
    while (p_head != nullptr) {
        p_data = p_head->right;
        while (p_data != nullptr) {
            p_count = Result_fre;
            flag_count = 0;
            while (p_count->num) {
                if (p_count->num == abs(p_data->data)) {
                    (p_count->count)++;
                    flag_count = 1;
                }
                p_count++;
            }
            if (flag_count == 0) {
                p_count->num = abs(p_data->data);
                (p_count->count)++;
            }
            p_data = p_data->next;
        }
        p_head = p_head->down;
    }
    p_count = Result_fre;
    while (p_count->num) {
        if (p_count->count > max_count) {
            max_num = p_count->num;
        }
        p_count++;
    }
    return max_num;
}

//优化算法的区别是分支变元选取的是频率最高的变元，减少了盲目性
status DPLL_Pro(ClauseNode *LIST,consequence *result) {
    ClauseNode* Pfind = LIST;
    ClauseNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data)-1].value = 1 : result[abs(SingleClause->right->data)-1].value = 0;
        int temp = SingleClause->right->data;
        DeleteClauseNode(SingleClause,LIST);
        DeleteVarNode(temp,LIST);
        if(!LIST) return 1;
        else if(IsEmptyClause(LIST)) return 0;
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind);
    }
    int Var = Choose_max(LIST);
    ClauseNode* replica = Duplication(LIST);
    ClauseNode *temp1 = ADDSingleClause(LIST,Var);
    if(DPLL_Pro(temp1,result)) return 1;
    else {
        ClauseNode *temp2 = ADDSingleClause(replica,-Var);
        if (DPLL_mini(temp2, result))  return 1;
        else  return 0;
       }
}

//mini版DPLL算法运用了单位子句传播算法和分支变元策略，分支变元的选取直接取二维链表第一个子句的第一个布尔变元
status DPLL_mini(ClauseNode* LIST, consequence* result) {
   
    ClauseNode* Pfind = LIST;
    ClauseNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data) - 1].value = 1 : result[abs(SingleClause->right->data) - 1].value = 0;
        int temp = SingleClause->right->data;
        DeleteClauseNode(SingleClause, LIST);
        DeleteVarNode(temp, LIST); 
        if (!LIST) return 1;
        else if (IsEmptyClause(LIST)) return 0;
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind); 
    }
      int Var = LIST->right->data; 
    ClauseNode* replica = Duplication(LIST);
    ClauseNode* temp1 = ADDSingleClause(LIST, Var);
    if (DPLL_mini(temp1, result)) return 1;
    else {
        ClauseNode* temp2 = ADDSingleClause(replica, -Var);
        if (DPLL_mini(temp2, result))    return 1;
        else return 0;
    }
}