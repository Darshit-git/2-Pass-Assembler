//Author :- Darshit Nagar 180101018
//2-Pass Assembler SIC

#include <bits/stdc++.h>
#include <direct.h>
#include <sstream>
typedef long long li;
using namespace std;
bool flag = false;
int singlehextoint(char x){
    int p = x - '0';
    if(p>=0&&p<=9)return p;
    p = x - '7';
    return p;
}

li strhextoint(string s){
    int n = s.size();
    int po = 0;
    li res = 0;
    for(int i=(s.size()-1);i>=0;i--){
        res+=(singlehextoint(s[i]))*floor(pow(16,po));
        po++;
    }
    return res;
}

li length_Byte(string S){/*Count BYTE length*/
	if(S[0]=='C'||S[0]=='c'){
	   return S.size()-3;
	}else if(S[0]=='X'||S[0]=='x'){
	    return (S.size()-3)/2;
	}
    return 0;
}

string dectostrhex(li x){
    string res = "";
    int i = 0;
    while(x!=0){
        int temp = 0;
        temp = x%16;
        if(temp<10){
            res+=char(temp+48);
        }
        else{
            res+=char(temp+55);
        }
        x/=16;
    }
    reverse(res.begin(),res.end());
    if(res.size()<4){
        while(res.size()<4){
            res = "0"+res;
        }
    }
    return res;
}

string dectostrhex2(li x){
    string res = "";
    int i = 0;
    while(x!=0){
        int temp = 0;
        temp = x%16;
        if(temp<10){
            res+=char(temp+48);
        }
        else{
            res+=char(temp+55);
        }
        x/=16;
    }
    reverse(res.begin(),res.end());
    return res;
}

string blankstr(li n){
    string res = "";
    for(int i=0;i<n;i++)res+=" ";
    return res;
}

string strtoasciistr(string tm){
    string res = "";
    for(int i=0;i<tm.size();i++){
        res+=dectostrhex2(li(tm[i]));
    }
    return res;
}

string hexsub(string a, string b){
    li fi = 0;
    li se = 0;
    li po = a.size()-1;
    for(int i=0;i<a.size();i++){
        fi+=singlehextoint(a[i])*floor(pow(16,po));
        po--;
    }
    po = b.size()-1;
    for(int i=0;i<b.size();i++){
        se+=singlehextoint(b[i])*floor(pow(16,po));
        po--;
    }
    return dectostrhex2(fi-se);
}

string twentyfourbinary(li val){
    string res = "0000000000000000";
    int idx = 15;
    while(val > 0){
        res[idx] = char((val%2) + 48);
        val/=2;
        idx--;
    }
    return res;
}

string sixbinary(li val){
    string res = "00000000";
    int idx = 7;
    while(val > 0){
        res[idx] = char((val%2) + 48);
        val/=2;
        idx--;
    }
    return res.substr(0,6);
}

string fourbinary(li val){
    string res = "0000";
    int idx = 3;
    while(val > 0){
        res[idx] = char((val%2) + 48);
        val/=2;
        idx--;
    }
    return res;
}

string twelvebinary(li val){
    string res = "000000000000";
    int idx = 11;
    while(val > 0){
        res[idx] = char((val%2) + 48);
        val/=2;
        idx--;
    }
    return res;
}

string twentybinary(li val){
    string res = "00000000000000000000";
    int idx = 19;
    while(val > 0){
        res[idx] = char((val%2) + 48);
        val/=2;
        idx--;
    }
    return res;
}

string binarytohex(string binary){

    string res = "";
    li len = binary.size();
    li lim = 20;
    if(len == 32)lim = 28;
    else if(len == 16)lim = 12;
    for(int i=0;i<=lim;i+=4){
        li sum = 0;
        sum+=floor(pow(2,3)*(binary[i] - '0'));
        sum+=floor(pow(2,2)*(binary[i+1] - '0'));
        sum+=floor(pow(2,1)*(binary[i+2] - '0'));
        sum+=floor(pow(2,0)*(binary[i+3] - '0'));
        //cout << "sum = " << sum << endl;
        if(sum<10){
            res += char(sum+48);
        }
        else{
            res += char(sum+55);
        }
    }
    return res;
}

string findaddr(char c, li val){
    string re = twentyfourbinary(val);
    if(c == 'X' || c == 'x')re[0] = '1';
    else re[0] = '0';
    string res = "0000";
    int idx = 0;
    for(li i=0;i<=12;i+=4){
        li sum = 0;
        sum+=floor(pow(2,3)*(re[i] - '0'));
        sum+=floor(pow(2,2)*(re[i+1] - '0'));
        sum+=floor(pow(2,1)*(re[i+2] - '0'));
        sum+=floor(pow(2,0)*(re[i+3] - '0'));
        //cout << "sum = " << sum << endl;
        if(sum<10){
            res[idx] = char(sum+48);
        }
        else{
            res[idx] = char(sum+55);
        }
        idx++;
    }
    //cout << "re = " << re << endl;
    return res;
}

string zerostr(int size){
    string res = "";
    for(int i=0;i<size;i++)res+="0";
    return res;
}

void optabinitialize(map <string,vector<int>> &ma){
    ma["LDA"] = {0x00,34,1};
    ma["LDX"] = {0x04,34,1};
    ma["LDL"] = {0x08,34,1};
    ma["STA"] = {0x0C,34,1};
    ma["STX"] = {0x10,34,1};
    ma["STL"] = {0x14,34,1};
    ma["LDCH"] = {0x50,34,2};
    ma["STCH"] = {0x54,34,2};
    ma["ADD"] = {0x18,34,1};
    ma["SUB"] = {0x1C,34,1};
    ma["MUL"] = {0x20,34,1};
    ma["DIV"] = {0x24,34,1};
    ma["COMP"] = {0x28,34,1};
    ma["J"] = {0x3C,34,1};
    ma["JLT"] = {0x38,34,1};
    ma["JEQ"] = {0x30,34,1};
    ma["JGT"] = {0x34,34,1};
    ma["JSUB"] = {0x48,34,1};
    ma["RSUB"] = {0x4C,34,0};
    ma["TIX"] = {0x2C,34,1};
    ma["TD"] = {0xE0,34,1};
    ma["RD"] = {0xD8,34,1};
    ma["WD"] = {0xDC,34,1};
    ma["LDB"] = {0x68,34,1};
    ma["CLEAR"] = {0x4,2,1};
    ma["LDT"] = {0x74,34,1};
    ma["COMPR"] = {0xA0,2,2};
    ma["TIXR"] = {0xB8,2,1};
    return;
}

void symtabinitialize(map<string,li> &ma){
    ma["A"] = 0;
    ma["X"] = 1;
    ma["L"] = 2;
    ma["B"] = 3;
    ma["S"] = 4;
    ma["T"] = 5;
    ma["F"] = 6;
    ma["PC"] = 8;
    ma["SW"] = 9;
    return;
}

int main(){
    // ==PASS 1==
   ifstream myf("input.txt");
   ofstream myf_;
   myf_.open("intermediate.txt");
   string x;
   li LOCCTR = 0;
   string starting_addr = "0000";
   li program_length = 0;
   int counter = 0;
   string program_name = "";
   string exe_label = "";
   map<string,li> symtab;
   map <string,vector<int>> optab;
   optabinitialize(optab);
   symtabinitialize(symtab);
   while(getline(myf,x)){
       //cout << x << endl;
       string label = "";
       string opcode = "";
       string operand = "";
       //cout << "x[0] = " << int(x[0]) << endl;
       if(x[0] == '.'){
           //cout << "case 1" << endl;
           myf_ << dectostrhex(LOCCTR) << "    " << x << endl;
           continue;
       }
       else if(x[0] == ' '){
           //cout << "case 2" << endl;
           string word;
           stringstream ss(x);
           int counter1 = 0;
           while(ss >> word){
               if(counter1 == 0)opcode = word;
               else if(counter1 == 1)operand = word;
               counter1++;
           }
       }
       else{
           //cout << "case 3" << endl;
           string word;
           stringstream ss(x);
           int counter1 = 0;
           while(ss >> word){
               if(counter1 == 0)label = word;
               else if(counter1 == 1)opcode = word;
               else operand = word;
               counter1++;
           }
       }
       counter+=1;
    //cout << " label: " << label  << " opcode: " << opcode << " operand: " << operand << endl << endl;
    if(counter == 1){
        if(opcode == "START"){
        if(operand.size()){
            starting_addr = operand;
            LOCCTR = strhextoint(operand);
        }
        else LOCCTR = 0;
        }
        program_name = label;
        string tmp1 = label + blankstr(8-label.size());
        string tmp2 = opcode + blankstr(8-opcode.size());
        myf_ << dectostrhex(LOCCTR) << "    " << tmp1 << tmp2 << operand << endl;
        continue;
    }
    if(opcode != "END"){
        if(label.size()){
            if(symtab.find(label) == symtab.end()){
                symtab[label] = LOCCTR;
            }
            else{
                //Duplicate label error
            }
        string tmp1 = label + blankstr(8-label.size());
        string tmp2 = opcode + blankstr(8-opcode.size());
        myf_ << dectostrhex(LOCCTR) << "    " << tmp1 << tmp2 << operand << endl;
        }
        else{
            string tmp2 = opcode + blankstr(8-opcode.size());
            myf_ << dectostrhex(LOCCTR) << "    " << "        " << tmp2 << operand << endl;
        }
            string opcode1 = opcode;
            if(opcode[0] == '+')opcode1 = opcode.substr(1,opcode.size()-1);
            if(optab.find(opcode1) != optab.end()){
                if(opcode[0] == '+'){
                    LOCCTR+=4;
                }
                else{
                  int format = optab[opcode1][1];
                  if(format == 1){
                      LOCCTR+=1;
                  }
                  else if(format == 2){
                      LOCCTR+=2;
                  }
                  else{
                      LOCCTR+=3;
                  }
                }
            }
            else if(opcode1 == "WORD"){
                LOCCTR+=3;
            }
            else if(opcode1 == "RESW"){
                LOCCTR+=(3*stoi(operand));
            }
            else if(opcode1 == "RESB"){
                LOCCTR+=stoi(operand);
            }
            else if(opcode1 == "BYTE"){
                LOCCTR+=length_Byte(operand);
            }
            else{
                //Undefined opcode error
            }

        }
    else{
        program_length = LOCCTR - strhextoint(starting_addr);
        string tmp2 = opcode + blankstr(8-opcode.size());
        myf_ << dectostrhex(LOCCTR) << "    " << "        " << tmp2 << operand << endl;
        exe_label = operand;
    }
   }
   myf.close();
   myf_.close();

   /* map <string,li>::iterator itr;
    for (itr = symtab.begin(); itr != symtab.end(); ++itr) { 
        cout << '\t' << itr->first 
             << '\t' << dectostrhex(itr->second) << '\n'; 
    } 
    cout << endl; 
    cout << "finished" << endl;*/

    //==Pass 2==
    counter = 0;
    LOCCTR = 0;
    li BASE = 0;
    bool isbaseset = false;
    myf.open("intermediate.txt");
    myf_.open("output.txt");
    string record = "T00";
    record += zerostr(4-starting_addr.size());
    record += starting_addr;
    record = record + "  ";
    string prev_starting_addr =  starting_addr;
    li size = 9;
    while(getline(myf,x)){
       string label = "";
       string opcode = "";
       string operand = "";
       string LOCCTR_ =  "";
       if(x[8] == '.'){
           continue;
       }
       else if(x[8] == ' '){
           string word;
           stringstream ss(x);
           int counter1 = 0;
           while(ss >> word){
               if(counter1 == 0)LOCCTR_ = word;
               else if(counter1 == 1)opcode = word;
               else{
                   operand = word;
               }
               counter1++;
           }
       }
       else{
           string word;
           stringstream ss(x);
           int counter1 = 0;
           while(ss >> word){
               if(counter1 == 0)LOCCTR_ = word;
               else if(counter1 == 1)label = word;
               else if(counter1 == 2)opcode = word;
               else operand = word;
               counter1++;
           }
           //if(opcode == "TD")cout << "HAPPENED" << endl;
       }
       counter+=1;
    cout << counter << " label: " << label  << " opcode: " << opcode << " operand: " << operand << endl << endl;
    if(counter == 1){
        if(opcode == "START"){
            string tmp1 = "H" + program_name + blankstr(6-program_name.size());
            string tmp2 = zerostr(6-starting_addr.size()) + starting_addr;
            string tmp3 = zerostr(6-dectostrhex(program_length).size()) + dectostrhex(program_length);
            myf_ << tmp1 << tmp2 << tmp3 << endl;
            if(operand.size()){
            LOCCTR = strhextoint(operand);
        }
        else LOCCTR = 0;
        }
        continue;
    }
    if((opcode == "RESW" || opcode == "RESB") && !flag){
        if(opcode == "RESB")LOCCTR+=stoi(operand);
        else{
            LOCCTR+=(3*stoi(operand));
        }
         string sub = hexsub(LOCCTR_,prev_starting_addr);
            if(sub.size()==1)sub = "0" + sub;
            //cout << "sub = " << sub << endl;
            record[7] = sub[0];
            record[8] = sub[1];
            prev_starting_addr = LOCCTR_;
            myf_ << record << endl;
            flag = true;
            //cout << "encountered =  " << LOCCTR << endl;
            continue;
    }
    if((opcode == "RESW" || opcode == "RESB") && flag){
        if(opcode == "RESB")LOCCTR+=stoi(operand);
        else{
            LOCCTR+=(3*stoi(operand));
        }
        //cout << "encountered =  " << LOCCTR << endl;
        continue;
    }
    if(flag){
        flag = false;
        prev_starting_addr = LOCCTR_;
        record = "T00" + LOCCTR_;
        record = record + "  ";
    }
    if(opcode != "END"){
        string opcode1 = opcode;
            if(opcode[0] == '+')opcode1 = opcode.substr(1,opcode.size()-1);
            if(optab.find(opcode1) != optab.end()){
                if(opcode[0] == '+'){
                    LOCCTR+=4;
                }
                else{
                  int format = optab[opcode1][1];
                  if(format == 1){
                      LOCCTR+=1;
                  }
                  else if(format == 2){
                      LOCCTR+=2;
                  }
                  else{
                      LOCCTR+=3;
                  }
                }
            }
            else if(opcode1 == "WORD"){
                LOCCTR+=3;
            }
            else if(opcode1 == "RESW"){
                LOCCTR+=(3*stoi(operand));
            }
            else if(opcode1 == "RESB"){
                LOCCTR+=stoi(operand);
            }
            else if(opcode1 == "BYTE"){
                LOCCTR+=length_Byte(operand);
            }
            else if (opcode == "BASE"){
                BASE = symtab[operand];
                isbaseset = true;
                continue;
            }
            else{
                //Undefined opcode error
            }
        string operandaddr = "000";
        if(opcode[0] == '+')operandaddr = "00000";
        string instructionbinary = "";
        string instruction;
        if(opcode1 == "RSUB")instruction = "4F0000";
        else if(optab.find(opcode1) != optab.end()){
            string opcodebinary = sixbinary(optab[opcode1][0]);
            int format = optab[opcode1][1];
            if(format == 1){
                instructionbinary = opcodebinary + "00";
            }
            else if(format == 2){
                int expectednum = optab[opcode1][2];
                if(expectednum == 1){
                    cout << "happened" << endl;
                    int firstregister = symtab[operand];
                    //cout << "first reg = " << firstregister << endl;
                    if(opcode == "CLEAR"){
                        instruction = "B4";
                        char firstreg = char(firstregister+48);
                        instruction+=firstreg;
                        instruction+="0";
                    }
                    else{
                        instruction = "B8";
                        char firstreg = char(firstregister+48);
                        instruction+=firstreg;
                        instruction+="0";
                    }
                    //cout << instruction << endl;
                }
                else{
                cout << "Happened" << endl;
                char delimiter = ',';
                int commaidx = operand.find(delimiter);
                int firstregister = symtab[operand.substr(0,commaidx)];
                int secondregister = symtab[operand.substr(commaidx+1,operand.size()-commaidx)];
                cout << "freg = " << firstregister << endl;
                cout << "sreg = " << secondregister << endl;
                instructionbinary = opcodebinary + "00";
                instructionbinary += (fourbinary(firstregister)) + (fourbinary(secondregister));
                }
            }
            else if(format == 34){
                //cout << "case 34" << endl;
                if(operand[0] == '#' && !(int(operand[1]) >= 65 && int(operand[1]) <= 90)){
                    //cout << "happened" << endl;
                    li operandnum = stoll(operand.substr(1,operand.size()-1));
                    
                    //  if(operand == "#LENGTH")cout << operandnum << endl;
                    if(0 <= operandnum && operandnum <= 4095){
                        instructionbinary = opcodebinary + "010000" + twelvebinary(operandnum);
                    }
                    else if(operandnum >= 4096 && operandnum <= 1048575 && opcode[0] == '+'){
                        instructionbinary = opcodebinary + "010001" + twentybinary(operandnum);
                    }
                    else{
                        //Immediate Out of range
                    }
                }
                else if (operand.size())
                {   
                    string newoperand = operand;
                    if(operand[0] == '@' || operand[0] == '#')newoperand = operand.substr(1,operand.size()-1);
                    if(operand[newoperand.size()-2] == ',')newoperand = newoperand.substr(0,newoperand.size()-2);
                    li targetaddr = symtab[newoperand];
                    if(opcode[0] == '+'){
                        instructionbinary = opcodebinary + "110001" + twentybinary(symtab[newoperand]);
                    }
                    else if (-2048 <= targetaddr-LOCCTR && 2047 >= targetaddr-LOCCTR)
                    {
                        li disp = targetaddr - LOCCTR;
                        if(disp < 0)disp += 4096;
                        instructionbinary = opcodebinary + "110010" + twelvebinary(disp);
                    }
                    else if (isbaseset &&  targetaddr-BASE >= 0 && targetaddr-BASE <= 4095){
                        instructionbinary = opcodebinary + "110100" + twelvebinary(targetaddr-BASE);
                    }
                    else{
                        // Instruction Addressing Error
                    }

                }
                if(operand[0] == '#')instructionbinary[6] = '0';
                if(operand[0] == '@')instructionbinary[7] = '0';
                if(operand[operand.size()-2] == ',')instructionbinary[8] = '1';
            }
            //cout << "reached" << endl;
            //cout << "opcode = " << opcode << endl;
            //if(opcode != "CLEAR")cout << "YES" << endl;
            //else cout << "NO" << endl;
            if(!(opcode == "CLEAR" || opcode == "TIXR")){
                instruction = binarytohex(instructionbinary);
            }

        }
        else if (opcode1 == "BYTE" || opcode1 == "WORD"){
            if(opcode1 == "BYTE"){
                if(operand[0] == 'C' || operand[0] == 'c'){
                    string tm = operand.substr(2,operand.size()-3);
                    instruction = strtoasciistr(tm);
                }
                else{
                    string tm = operand.substr(2,operand.size()-3);
                    instruction =  tm;
                }
            }
            else{
                instruction = "00" + dectostrhex(stoll(operand));
            }
        }
        else{
            //Undefined OPCODE
        }
        //cout << " label: " << label  << " opcode: " << opcode << " operand: " << operand << endl << endl;
        //cout << "happened" << endl;
        cout << instructionbinary << endl;
        cout << instruction << endl;
        if((record.size() + instruction.size()) <=69){
            record = record + instruction;
        }
        else{
            //cout << LOCCTR_ << " " << prev_starting_addr << endl;
            string sub = hexsub(LOCCTR_,prev_starting_addr);
            if(sub.size()==1)sub = "0" + sub;
            //cout << "sub = " << sub << endl;
            record[7] = sub[0];
            record[8] = sub[1];
            prev_starting_addr = LOCCTR_;
            myf_ << record << endl;
            record = "T00" + LOCCTR_;
            record = record + "  ";     
            record = record + instruction; 
        }
    }
    else{
        //cout << LOCCTR_ << " " << prev_starting_addr << endl;
        string sub = hexsub(LOCCTR_,prev_starting_addr);
            if(sub.size()==1)sub = "0" + sub;
            //cout << "sub = " << sub << endl;
            record[7] = sub[0];
            record[8] = sub[1];
            prev_starting_addr = LOCCTR_;
            myf_ << record << endl;
            string endfile = "E00";
            if(exe_label.size()){
                endfile = endfile + dectostrhex(symtab[exe_label]);
            }
            else{
                endfile = endfile + starting_addr;
            }
            myf_ << endfile << endl;
    }
   }
    myf.close();
    myf_.close();
    return 0;
}