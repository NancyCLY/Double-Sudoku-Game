#include "sat.h"

int main() {
    initialInterface();
    int choice = 0;
    int value = 0;
    double T1 = 0.0;
    double T2 = 0.0;
    //记录时间
    char restartOrEnd;
    cin>>choice;
    while (choice){
        if(choice == 1) {
        string filename = createSudokuToFile();
        sudoku_easyx();
        cout <<filename.substr(8,filename.length()) << "已经成功创建!" << endl;
        cout << endl;
        cout << "可以进入twodoku文件夹进行查看哦！" << endl;
        cout << endl;
        int VARNUM;
        ClauseNode* LIST = CreateClauseForSudoku(VARNUM,filename);
        conse * SudoResult= new conse [10000000];  
        clock_t StartTime,EndTime;
        StartTime = clock();
        int value = SudoDPLL(LIST,SudoResult,VARNUM);
        EndTime = clock();
        cout << "********************************打 印 所 用 时 间********************************" << endl;
        cout<<"The time is "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";
        if (value == 1)
        {
            cout << "******************************双 数 独 游 戏 结 束******************************" << endl;
            SudokuDisplay(SudoResult, VARNUM);
            delete[] SudoResult; 
            cout << "是否返回初始流程? Y/N" << endl;
            cout << endl;
            cin >> restartOrEnd;
            if (restartOrEnd == 'Y') {
                initialInterface();
                cin >> choice;
                
                continue;
            }
        }
        else {
            cout << "无解.";
            cout << "需要再试一次吗? Y/N" << endl;
            cin >> restartOrEnd;
            if (restartOrEnd == 'Y') {
                initialInterface();
                cin >> choice;
                continue;
            }
        }
            choice = 0;
            exit(0);
        }
        
        else if (choice == 2) {
            int VARNUM;
            string filename;
            cout << endl;
            cout << endl;
            int choose_dpll = 0;
             
            

            clock_t StartTime,EndTime;
            cout << "是否需要优化DPLL算法，需要请键入1，否则请键入2,pro版优化请键入3" << endl;
            cin >> choose_dpll;
            while (choose_dpll != 1 && choose_dpll != 2 && choose_dpll != 3) {
                cout << "请输入正确的数字！" << endl;
                cin >> choose_dpll;
            }
            if (choose_dpll == 3)
            {
                Sat();
                /*
                cout << "是否需要再做一次无优化（输入1），普通优化（输入2），都要（输入3）" << endl;
                int ts;
                cin >> ts;
                if (ts == 1) {

                }
                */
            }
            cout << endl;
            cout << "下面将进行普通优化与不优化的选择" << endl;
            cout << endl;
            cout << "请输入文件名,需要带.cnf后缀" << endl;
            cout << endl;
            cout << endl;
            ClauseNode* LIST = nullptr;

            do {
                cin >> filename;

                LIST = CreateClause(VARNUM, filename);
                if (LIST == nullptr)cout << "请不要输入不存在的文件路径!" << endl;
            } while (LIST == nullptr);
            consequence* result = new consequence[VARNUM];
            cout << "为了保存文件，请输入它的名字！不用输入后缀.res" << endl;
            string loc = "res\\";
            string name;
            cin >> name;
            loc = loc + name;
            loc = loc + ".res";
            ofstream fos(loc.c_str());
            if (!fos.is_open()) {
                cout << "写入失败！\n";
                exit(0);
            }
            
            cout << "普通优化和不优化算法对比的文件打印键入1，不优化算法的文件打印键入2"<<endl;
            cout << endl;
            cin >> choose_dpll;
            if (choose_dpll == 1)
            {
                
                 StartTime = clock();
                value = DPLL_mini(LIST, result);
                  EndTime = clock();
                T1 = (double)(EndTime - StartTime); 
               
                ClauseNode* LIST = CreateClause(VARNUM, filename);
                 StartTime = clock(); 
                 DPLL_Pro(LIST, result); 
                 EndTime = clock();
                T2 = (double)(EndTime - StartTime); 
                
                cout << "Done！" << endl;
            }
                
            else if(choose_dpll==2) {
                StartTime = clock();
                value = DPLL_mini(LIST, result);
                EndTime = clock();
                cout << "Done!" << endl;
                T2= (double)(EndTime - StartTime);
            }
            if(value) {
                fos << "S " << 1 << endl;
                fos<<"V ";
                for(int i = 0; i < VARNUM; i++) {
                    if (result[i].value == 1)
                        fos<<i+1<<" ";
                    else if(result[i].value == 0)
                        fos<<-(i+1)<<" ";
                    else//可正可负的全部输出为true
                        fos<<(i+1)<<" ";
                }

                fos<<endl;
            }
            else {
                fos << "S " << NoAnwser << endl;
                fos<<"V ";
                fos<<endl;
            }
            if (choose_dpll == 1) {
               if (T1 > T2) {
                    fos << "T1 " << T1 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                    fos << "T2 " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                   
                    if(T1)
                    fos << "Improve by " << (T1 - T2) / T1 * 100.0<<"%";
               }
                else {
                    fos << "T1 " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                    fos << "T2 " << T1 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                    if (T1 && T2)
                    fos << "Improve by " << (T2 - T1) / T2 * 100.0<<"%";
                }
            }
            else if(choose_dpll==2) {
                fos << "T " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
            }
            fos.close();
            if (choose_dpll == 3)
                Sat();
            cout << "需要继续吗，需要请键入Y，否则请键入N" << endl;
            cin >> restartOrEnd;
            if (restartOrEnd == 'Y') {
                initialInterface();
                cin >> choice;
                continue;
            }
            delete[] result;
            choice = 0;
            exit(0);
        }
        else { 
            cout<<"请输入正确的选项! "<<endl;
            cin >> choice;
            cout << endl;
        }
        
    }
}