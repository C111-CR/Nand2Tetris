/* Program: hack_assembler
 *     function: translate hack language program to binary code
 *
 * step zero:
 *     map<string,int>储存符号与value
 *     预处理 将预处理符号文件读入 并载入到map
 * step one:
 *     读入asm文件
 * step two:
 *     逐行处理 a空行去掉 b去除注释和空格 c遇到左括号以label处理加入map
 * step three:
 *     处理变量符号
 *     遇到@symbol 在map中搜索symbol 没有就加入 从16开始赋值
 * step four:
 *     处理A指令和C指令
 */


#include <cstdio>
#include <map>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define ull unsigned long long

#define PRE_TABLE "pre/pre_symbol_table.txt"
#define SOL_FILE  "sol_file.txt"
#define CMP_TABLE "pre/cmp_inst_table.txt"
#define JMP_TABLE "pre/jmp_inst_table.txt"
#define DES_TABLE "pre/des_inst_table.txt"

#define BUF_SIZE 256
#define SYMBOL_SIZE 20

void filename_handle(string name);

void pre_symbol_handle(const string& filename,map<string,int> *_map);

void pre_symbol_handle(const string& filename,map<string,string> *_map);

void line_handle();

void variable_handle();

void instructions_handle();

void map_print(const map<string,int>& _map);

string asm_filename, hack_filename;
vector<string> sol_inst;

map<string,int> symbol_table;
map<string,string> jmp_inst_table;
map<string,string> des_inst_table;
map<string,string> cmp_inst_table;

int main(int argc,char *argv[]) {
    filename_handle(argv[1]);

    pre_symbol_handle(PRE_TABLE,&symbol_table);
    pre_symbol_handle(CMP_TABLE,&cmp_inst_table);
    pre_symbol_handle(DES_TABLE,&des_inst_table);
    pre_symbol_handle(JMP_TABLE,&jmp_inst_table);

    line_handle();

    variable_handle();

    instructions_handle();

//    map_print(symbol_table);

    return 0;
}

void filename_handle(string name){
    asm_filename = name;
    hack_filename = "hack/";

    string tmp = asm_filename;
    tmp.erase(tmp.find('.'));
    tmp.erase(0,4);
    tmp.append(".hack");

    hack_filename.append(tmp);
}

void pre_symbol_handle(const string& filename,map<string,int> *_map){
    FILE * fp = fopen(filename.c_str(),"r");
    if(fp == nullptr) perror("fopen");

    int index=1;
    char symbol[SYMBOL_SIZE],v[8];
    while(index != -1){
        memset(symbol,0,20);
        memset(v,0,8);

        index = fscanf(fp,"%s %s",symbol,v);

        int value = atoi(v);

        _map->insert(pair<string,int>(symbol,value));
    }

    if(fclose(fp) == -1)
        perror("fclose");
}

void pre_symbol_handle(const string& filename,map<string,string> *_map){
    FILE * fp = fopen(filename.c_str(),"r");
    if(fp == nullptr) perror("fopen");

    int index=1;
    char symbol[SYMBOL_SIZE],v[8];
    while(index != -1){
        memset(symbol,0,20);
        memset(v,0,8);

        index = fscanf(fp,"%s %s",symbol,v);

        _map->insert(pair<string,string>(symbol,v));
    }

    if(fclose(fp) == -1)
        perror("fclose");
}

void line_handle(){
    FILE *fp = fopen(asm_filename.c_str(),"r");
    if(fp == nullptr) perror("fopen");

    unsigned int index = 1;
    int pc=0;
    char buf[BUF_SIZE];

    while(index > 0){
        memset(buf,0, BUF_SIZE);
        fgets(buf,BUF_SIZE,fp);
        index = strlen(buf);

        string sol = buf;
        ull pos;

        // 消除注释
        while((pos = sol.find("//")) != string::npos){
            sol.erase(pos);
        }

        // 消除空格、空行和缩进
        if((pos = sol.find('\n')) != string::npos){
            sol.erase(pos);
        }
        while((pos = sol.find(' ')) != string::npos){
            ull i=pos+1;
            while(sol[i] == ' ') ++i;

            sol.erase(pos,i-pos);
        }
        while((pos = sol.find('\t')) != string::npos){
            sol.erase(pos,1);
        }

        // 处理label
        if(sol[0] == '('){
            string symbol = sol.substr(1,sol.find(')')-1);
            int value = pc;

            symbol_table.insert(pair<string,int>(symbol,value));
        }
        else if(sol.length() != 0){
            // 写入中间文件
            FILE *fp2;

            if(pc == 0){
                fp2 = fopen(SOL_FILE,"w");
            }
            else
                fp2 = fopen(SOL_FILE,"a");

            //插入到vector
            sol_inst.push_back(sol);
            fprintf(fp2,"%s\n",sol.c_str());

            if(fclose(fp2) == -1)
                perror("fclose");

            pc++;
        }
    }

    if(fclose(fp) == -1)
        perror("fclose");
}

void variable_handle(){
    int value_reg = 16;

    for(auto sol : sol_inst){
        if(sol[0] == '@'){
            sol.erase(0,1);

            ull pos;
            if((pos = sol.find('\n')) != string::npos){
               sol.erase(pos,1);
            }

            char c = sol[0];
            if((c>='a' && c<='z') || (c>='A' && c<='Z')){
                if(symbol_table.count(sol) == 0) {
                    symbol_table.insert(pair<string, int>(sol, value_reg));
                    value_reg++;
                }
            }
        }
    }
}

void instructions_handle(){
    int flag = 0;

    for(string sol : sol_inst){
        string ret;

        ull n = sol.find('\n');
        if(n != string::npos){sol.erase(n,1);}

        if(sol.begin() != sol.end()) {
            if (sol[0] == '@') {
                sol.erase(0, 1);
                ret = "0";

                int tmp = 0;
                char c = sol[0];
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    auto it = symbol_table.find(sol);
                    tmp = it->second;
                } else if (c >= '0' && c <= '9') {
                    tmp = atoi(sol.c_str());
                }

                while (tmp != 0) {
                    if (tmp % 2)
                        ret.insert(1, "1");
                    else
                        ret.insert(1, "0");
                    tmp /= 2;
                }
                while (ret.length() < 16) {
                    ret.insert(1, "0");
                }
            } else {
                ull pos,pos1;

                ret = "111";

                pos = sol.find('=');
                pos1 = sol.find(';');

                if (pos != string::npos) {
                    string des = sol.substr(0,pos);
                    auto it = des_inst_table.find(des);
                    string tmp = it->second;

                    ret.insert(3, tmp);

                    string cmp;
                    if(pos1 == string::npos){
                        cmp = sol.substr(pos+1);
                    }
                    else{
                        cmp = sol.substr(pos+1,pos1-pos-1);
                    }

                    it = cmp_inst_table.find(cmp);
                    tmp = it->second;

                    ret.insert(3,tmp);
                    ret.append("000");
                }
                else {
                    // des = "000"
                    ret.append("000");

                    // 默认存在 ';'
                    string jmp = sol.substr(pos1+1);
                    auto it = jmp_inst_table.find(jmp);
                    string tmp = it->second;
                    ret.append(tmp);
                    sol.erase(pos1);

                    // cmp 等于 sol
                    it = cmp_inst_table.find(sol);
                    tmp = it->second;
                    ret.insert(3,tmp);
                }

            }

            ret.append("\n");

            FILE *fp2;
            if (!flag) {
                fp2 = fopen(hack_filename.c_str(), "wb");
            } else {
                fp2 = fopen(hack_filename.c_str(), "ab");
            }

            fputs(ret.c_str(), fp2);

            if(fclose(fp2) == -1) perror("fclose");

            flag = 1;
        }
    }
}

void map_print(const map<string,int>& _map){
    auto it = _map.begin();
    while(it != _map.end()){
        cout << it->first << ' ' << it->second << endl;
        it++;
    }
}

