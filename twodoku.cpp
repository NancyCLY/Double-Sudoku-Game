#include "sat.h"

//随机生成一个双数独
void InitialTwodoku(int a[][15])
{ //生成数独
    InitialSkyLine(a[0],9);//随机生成上宫第一行
    RandomBoardForUpPalace(a,1,0,9,8);//递归生成后i行 
    randomDownPalace(a);
    RandomBoardForDownPalace(a, 7, 9,8,15);
    RandomBoardForDownPalace(a, 8, 9,9,15);
    RandomBoardForUpPalace(a, 9, 6,15,14);
    TrimBoard(a);
}

//随机生成数独格局的第一行
void InitialSkyLine(int a0[], int n) { 
    int i, j;
    srand((unsigned)time(nullptr));
    for (i = 0; i < n; i++) {
        a0[i] = rand() % 9 + 1;
        j = 0;
        while (j < i) {
            if (a0[i] == a0[j]) {
                a0[i] = rand() % 9 + 1;
                j = 0;
            }
            else j++;
        }
    }
}
//把双数独右上角和左下角的空缺全部标记为-1
void TrimBoard(int a[][15]) {
    for (int i = 9; i <= 14; i++) {
        for (int j = 0; j <= 5; j++) {
            a[i][j] = -1;
        }
    }
    for (int i = 0; i <= 5; i++) {
        for (int j = 9; j <= 14; j++) {
            a[i][j] = -1;
        }
    }
}
//使用高效的回溯法生成上面的九宫格，称为上宫
int RandomBoardForUpPalace(int a[][15], int i, int j, int loc1, int loc2) {
    if (i < loc1 && j < loc1) {
        int x, y, k;
        int check1[10] = { 0 };
        for (x = loc1 - 9; x < i; x++)
            check1[a[x][j]] = -1;
        for (x = loc1 - 9; x < j; x++)
            check1[a[i][x]] = -1;
        for (x = i / 3 * 3; x <= i; x++) {
            if (x == i)
                for (y = j / 3 * 3; y < j; y++)
                    check1[a[x][y]] = -1;
            else
                for (y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
                    check1[a[x][y]] = -1;
        }
        int flag = 0;
        for (k = 1; k <= 9 && flag == 0; k++) {
            if (check1[k] == 0) {
                flag = 1;
                a[i][j] = k;
                if (j == loc2 && i != loc2) {
                    if (RandomBoardForUpPalace(a, i + 1, 0, loc1, loc2) == 0) return 0;
                    else flag = 0;
                }
                else if (j != loc2) {
                    if (RandomBoardForUpPalace(a, i, j + 1, loc1, loc2) == 0) return 0;
                    else flag = 0;
                }
            }
        }
        if (flag == 0) {
            a[i][j] = 0;
            return -1;
        }
    }
    return 0;
}
//把重叠的九宫格（称之为叠宫）补齐，这样就可以用本质上相同的回溯法生成下宫了
void randomDownPalace(int a[][15]) {//随机补全叠宫的那三行
    int i, j, k;
    srand((unsigned)time(nullptr));
    i = 6;
    for (j = 9; j <= 14; j++) {

        a[i][j] = rand() % 9 + 1;
        k = 6;
        while (k < j) {
            if (a[i][j] == a[i][k]) {
                a[i][j] = rand() % 9 + 1;
                k = 6;
            }
            else k++;
        }
    }
}

int RandomBoardForDownPalace(int a[][15], int i, int j, int loc1, int loc2) {//递归填充数独元素
    if (i < loc1 && j < loc2) {
        int x, y, k;
        int check3[10] = { 0 };//用于排除已经使用过的的数字
        for (x = 6; x < i; x++)
            check3[a[x][j]] = -1;//当前列已使用的数字置为-1
        for (x = 6; x < j; x++)
            check3[a[i][x]] = -1;//当前行使用过的数字置为-1
        for (x = i / 3 * 3; x <= i; x++) {
            if (x == i)//这里是为了判断同行同列时不用置为-1
                for (y = j / 3 * 3; y < j; y++)
                    check3[a[x][y]] = -1;
            else
                for (y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
                    check3[a[x][y]] = -1;
        }
        int flag = 0;
        for (k = 1; k <= 9 && flag == 0; k++) {//从check数组中查找安全的数字
            if (check3[k] == 0) {
                flag = 1;
                a[i][j] = k;
                if (j != 14) {
                    if (RandomBoardForDownPalace(a, i, j + 1, loc1, loc2) == 0) return 0;
                    else flag = 0;
                }
            }
        }
        if (flag == 0) {
            a[i][j] = 0;
            return -1;
        }
    }
    return 0;
}

void InitialGameBoard(const int a[][15], int b[][15], int numDigits) {//这个numDigits就是要挖的holes
    int i,j,k;
    int crt1, crt2;
    if (numDigits == 0) crt1 = crt2 = 0;
    else {
        crt1 = rand() % numDigits + 1;
        crt2 = numDigits - crt1;
    }
    //随机分配在上下宫分别挖的洞数
    srand((unsigned)time(nullptr));
    for( i = 0; i < 15 ; i ++)
        for( j = 0; j < 15 ; j++)
            b[i][j] = a[i][j];
    //先用b数组把原盘记录一下
    int** c1 = new int* [crt1];  
    for (int i = 0; i < crt1; i++) c1[i] = new int[2];  
    //用c[i]记录挖掉的第i个洞的坐标

    int m,flag = 0;
   
    for( i = 0; i < crt1 ; i++) {
        j = rand()%9;
        k = rand()%9;

        flag = 0;
        for(m = 0; m < i ; m++)
            if( j == c1[m][0] && k == c1[m][1])
                flag = 1;//如果刚生成的洞已经被挖过了
        
        if(flag == 0){
            b[j][k] = 0;
            c1[i][0] = j;
            c1[i][1] = k;
        }
        else
            i--;//挖过的洞数恢复至初始状态
    }
    for (int i = 0; i < crt1; i++) delete[]c1[i];
    delete[]c1; 
    //上宫的洞挖完了，释放内存
    int** c = new int* [crt2];

    for (int i = 0; i < crt2; i++) c[i] = new int[2];
    for (i = 0; i < crt2; i++) {
        j = rand() % 9 +6;
        k = rand() % 9 +6;

        flag = 0;
        for (m = 0; m < i; m++)
            if ((j == c[m][0] && k == c[m][1])||b[j][k]==0)
                flag = 1;//如果刚生成的洞已经被挖过了

        if (flag == 0) {
            b[j][k] = 0;
            c[i][0] = j;
            c[i][1] = k;
        }
        else
            i--;//挖过的洞数恢复至初始状态
    }
    for (int i = 0; i < crt2; i++) delete[]c[i];
    delete[]c;
}

void ShowInitialBoard(const int a[][15]){
    int i,j;
    for( i = 0 ; i < 15 ; i++){
        for (j = 0; j < 15; j++) {
            if (a[i][j] != -1) printf("%d ", a[i][j]);
            else printf("  ");
        }
        cout<<endl;
    }
}

string BoardTranslateIntoCnf(int a[][15],int holes) {
    cout << endl;
    cout << "请给这一盘双数独游戏取个名字QAQ!" << endl;
    cout << endl;
    string any;
    cin >> any;
    cout << endl;
    any = any + ".cnf";
    ofstream sherry ("twodoku\\"+ any);//定义输入文件
    if(!sherry.is_open())
        cout<<"文件打开失败!\n";
    int cnt = 0;
    for (int x = 6; x <= 8; x++) {
        for (int y = 6; y <= 8; y++) {
            if (a[x][y] == 0) cnt++;
        }
    }
    sherry<<"p"<<" "<<"cnf"<<" "<<1458<<" "<<17982-cnt-holes<<" "<<endl;
  
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y)
            if(a[x][y] != 0)
                sherry<< 1 << (x+1)*100 + (y+1)*10 + a[x][y]<<" "<<0<<endl;
    }
    for (int x = 6; x <= 14; x++) {
        for (int y = 6; y <= 14; y++)
            if (a[x][y] != 0)
                sherry << 2 << (x - 5) * 100 + (y - 5) * 10 + a[x][y] << " " << 0 << endl;
    }
    for (int x = 1; x <= 9; ++x) {
        for (int y = 1; y <= 9; ++y) {
            for (int z = 1; z <= 9; ++z)
                sherry << 1 << x * 100 + y * 10 + z << " ";
            sherry<<0;
            sherry<<endl;
        }
    }
     
    for (int x = 1; x <= 9; ++x) {
        for (int y = 1; y <= 9; ++y) {
            for (int z = 1; z <= 9; ++z)
                sherry << 2 << x * 100 + y * 10 + z << " ";
            sherry << 0;
            sherry << endl;
        }
    }
    //这一部分是每一行每一列每一个数字都要有
    for (int y = 1; y <= 9; ++y) {
        for (int z = 1; z <= 9; ++z)
            for (int x = 1; x <= 8; ++x)//八行都约束完了，剩下的一行自然就有了约束
                for (int i = x+1; i <= 9; ++i)
                    sherry<<0 - (1000+x*100 + y*10 + z)<<" "
                      <<0 - (1000+i*100 + y*10 + z)<<" "<<0<<endl;
    }
    for (int y = 1; y <= 9; ++y) {
        for (int z = 1; z <= 9; ++z)
            for (int x = 1; x <= 8; ++x)//八行都约束完了，剩下的一行自然就有了约束
                for (int i = x + 1; i <= 9; ++i)
                    sherry << 0 - (2000+x * 100 + y * 10 + z) << " "
                    << 0 - (2000+i * 100 + y * 10 + z) << " " << 0 << endl;
    }
    //上面这块表示每一行的数字都不可以重复
    for (int x = 1; x <= 9; ++x) {
        for (int z = 1; z <=9 ; ++z)
            for (int y = 1; y <= 8; ++y)
                for (int i = y+1; i <= 9; ++i)
                    sherry<<0-(1000+x*100 + y*10 + z)<<" "
                      <<0-(1000+x*100 + i*10 + z)<<" "<<0<<endl;
    }
    for (int x = 1; x <= 9; ++x) {
        for (int z = 1; z <= 9; ++z)
            for (int y = 1; y <= 8; ++y)
                for (int i = y + 1; i <= 9; ++i)
                    sherry << 0 - (2000+x * 100 + y * 10 + z) << " "
                    << 0 - (2000+x * 100 + i * 10 + z) << " " << 0 << endl;
    }
    //上面这块表示每一列的数字都不可以重复
    for (int z = 1; z <= 9 ; ++z) {
        for (int i = 0; i <=2 ; ++i)
            for (int j = 0; j <=2 ; ++j)
                for (int x = 1; x <= 3 ; ++x)
                    for (int y = 1; y <= 3; ++y)
                        for (int k = y+1; k <= 3; ++k)
                            sherry<<0 - (1000+(3*i+x)*100 + (3*j+y)*10 + z)<<" "
                              <<0-(1000+(3*i+x)*100 + (3*j+k)*10 + z)<<" "<<0<<endl;
    }
    for (int z = 1; z <= 9; z++) {
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int x = 1; x <= 3; x++)
                    for (int y = 1; y <= 3; y++)
                        for (int k = x + 1; k <= 3; k++)
                            for (int l = 1; l <= 3; l++)
                                sherry << 0 - (1000+(3 * i + x) * 100 + (3 * j + y) * 10 + z) << ' '
                                << 0 - (1000+(3 * i + k) * 100 + (3 * j + l) * 10 + z) << ' ' << 0 << endl;
    }
    for (int z = 1; z <= 9; ++z) {
        for (int i = 0; i <= 2; ++i)
            for (int j = 0; j <= 2; ++j)
                for (int x = 1; x <= 3; ++x)
                    for (int y = 1; y <= 3; ++y)
                        for (int k = y + 1; k <= 3; ++k)
                            sherry << 0 - (2000 + (3 * i + x) * 100 + (3 * j + y) * 10 + z) << " "
                            << 0 - (2000 + (3 * i + x) * 100 + (3 * j + k) * 10 + z) << " " << 0 << endl;
    }
    for (int z = 1; z <= 9; z++) {
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int x = 1; x <= 3; x++)
                    for (int y = 1; y <= 3; y++)
                        for (int k = x + 1; k <= 3; k++)
                            for (int l = 1; l <= 3; l++)
                                sherry << 0 - (2000 + (3 * i + x) * 100 + (3 * j + y) * 10 + z) << ' '
                                << 0 - (2000 + (3 * i + k) * 100 + (3 * j + l) * 10 + z) << ' ' << 0 << endl;
    }
    //上面这一块是3*3九宫格约束，z代表数字，i和j是九个九宫格

        for (int x = 7; x <= 9; x++) {
            for (int y = 7; y <= 9; y++) {
                for (int z = 1; z <= 9; z++) {
                    sherry << -1000 - x * 100 - y * 10 - z << ' ' << 2000 + (x - 6) * 100 + (y - 6) * 10 + z << ' ' << 0 << endl
                        << 1000 + x * 100 + y * 10 + z << ' ' << -2000 - (x - 6) * 100 - (y - 6) * 10 - z << ' ' << 0 << endl;
                }
            }
    }
    //上面这一块是重叠九宫格的约束
    sherry.close();
    return string("twodoku\\" + any);
}

int twodoku[15][15] = { 0 };
int gameboard[15][15] = { 0 };
int holes;
string createSudokuToFile() {

     
    cout << "***********************请 输 入 需 要 挖 的 洞 数***************************" << endl;
   
    cin >> holes;
    
    InitialTwodoku(twodoku); 
    ShowInitialBoard(twodoku);
    InitialGameBoard(twodoku,gameboard,holes); 
    cout << "****************************双 数 独 初 始 化 完 成****************************" << endl;
    ShowInitialBoard(gameboard); 
   
    string filename = BoardTranslateIntoCnf(gameboard,holes);
    return filename;
}

static int T = 0;

status SudoDPLL(ClauseNode *LIST,conse *result,int VARNUM) {
    ClauseNode* Pfind = LIST;
    ClauseNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) {
        result[T].num = SingleClause->right->data;
        SingleClause->right->data > 0 ? result[T++].value = 1 : result[T++].value = 0; 
        int temp = SingleClause->right->data;
        DeleteClauseNode(SingleClause,LIST); 
        DeleteVarNode(temp,LIST); 
        if(!LIST) return 1;
        else if(IsEmptyClause(LIST)) return 0;
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind); 
    }
    int Var = LIST->right->data; 
    ClauseNode* replica = Duplication(LIST);
    ClauseNode *temp1 = ADDSingleClause(LIST,Var);
    if(SudoDPLL(temp1,result,VARNUM)) return 1;
    else {
        ClauseNode *temp2 = ADDSingleClause(replica,-Var);
        return SudoDPLL(temp2,result,VARNUM);
    }
}
 //独一性检验，检查是否唯一解
void UniquenessCheck(const int a[][15], const int b[][15])
{
    int i, j ;
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (a[i][j] != b[i][j]) {
                cout << "结果不唯一!" << endl;
                return;
            }
        }
    }
    return;
}

//打印由DPLL算法解出来的数独原始格局，并进行唯一性检验
void SudokuDisplay(conse *result,int VARNUM) {
    int res[15][15];
    memset(res, -1, sizeof(res));
    for (int i = 0; i < VARNUM; ++i) {
        if(result[i].value == 1)
        {
            if (abs(result[i].num) / 1000 < 2) {
                int x = (int)(abs(result[i].num) % 1000 / 100) - 1;
                int y = (int)((abs(result[i].num) % 1000 - (x + 1) * 100) / 10) - 1;
                res[x][y] = abs(result[i].num) % 1000 - (x + 1) * 100 - (y + 1) * 10;
            }
            else {
                int x = (int)(abs(result[i].num) % 1000 / 100) - 1;
                int y = (int)((abs(result[i].num) % 1000 - (x + 1) * 100) / 10) - 1;
                res[x+6][y+6] = abs(result[i].num) % 1000 - (x + 1) * 100 - (y + 1) * 10;
            }
        }
    }
  
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (res[i][j] == -1) cout << "  ";
            else cout<<res[i][j]<<" ";
        }
        cout<<endl;
    }
    UniquenessCheck(twodoku, res);
}

