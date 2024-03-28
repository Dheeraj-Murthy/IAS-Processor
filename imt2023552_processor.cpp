#include<bits/stdc++.h>
#include "imt2023552_assembler.cpp"
using namespace std;


int AC = 0; // initiating the Accumulator
int PC = 0; // initiating the PC
int MQ = 1; // initiating the MQ

int binToDec(vector<int>bin)
{
    int count=1;
    int ans = 0;
    for (int it = bin.size()-1; it >=0; it--){
        ans += bin[it] * count;
        count *= 2;
    }
    return ans;
}
vector<int> decToBin(int d) // function to convert decimal to binary
{
    vector<int>ans;
    while (d > 1)
    {
        ans.push_back(d%2);
        d = d/2;
    }
    ans.push_back(d);
    reverse(ans.begin(), ans.end());

    if (ans.size() < 8)
    {
        vector<int> bin;
        
        for (int i = 0; i < 8 - ans.size(); i++)
            bin.push_back(0);
        for (auto it : ans)
            bin.push_back(it);
        return bin;
    }
    
    return ans;  
}

void Load(int pointer, vector< vector<int> > MainMemory)
{
    int data = binToDec(MainMemory[pointer]);
    AC = data;
}
void Store(int pointer, vector< vector<int> >& MainMemory)
{
    vector<int>a(decToBin(AC));
    vector<int>temp(32, 0);
    temp.insert(temp.end(), a.begin(), a.end());
    MainMemory[pointer].clear();
    MainMemory[pointer].assign(temp.begin(), temp.end());
}
void Jump(int pointer)
{
    PC = pointer;
}
int ConJump(int pointer)
{
    if (AC >= 0){
        PC = pointer;
        return 2;
    }
    return 0;
}
void add(int pointer, vector< vector<int> > MainMemory)
{
    AC += binToDec(MainMemory[pointer]);
}
void sub(int pointer, vector< vector<int> > MainMemory)
{
    AC -= binToDec(MainMemory[pointer]);
}
void mul(int pointer, vector< vector<int> > MainMemory)
{
    AC = binToDec(MainMemory[pointer]) * MQ;
}
void div(int pointer, vector< vector<int> > MainMemory){
    int t = binToDec(MainMemory[pointer]);
    MQ = AC / t;
    AC = AC % t;
    
}
void les(int pointer, vector< vector<int> > MainMemory){
    int val = binToDec(MainMemory[pointer]);
    if (AC <= val) AC = 1;
    else AC = -1;
}
void eq(int pointer, vector< vector<int> > MainMemory){
    int val = binToDec(MainMemory[pointer]);
    if (AC == val) AC = 1;
    else AC = -1;
}
void more(int pointer, vector< vector<int> > MainMemory){
    int val = binToDec(MainMemory[pointer]);
    if (AC >= val) AC = 1;
    else AC = -1;
}
void endProgram(){
    PC = 999;
}
void LoadMQ(int pointer, vector< vector<int> > MainMemory){
    MQ = binToDec(MainMemory[pointer]);
}

int decode_opcode(vector<int>IR, vector<int>MAR, vector< vector<int> >& MainMemory)
{
    int instruction_code = binToDec(IR); // Decode the opcode
    int pointer = binToDec(MAR); // find the address stored in MAR

    switch (instruction_code)
    {
        case 0:  return 0;
        case 1:  Load(pointer, MainMemory);     break;
        case 2:  LoadMQ(pointer, MainMemory);   break;
        case 3:  Store(pointer, MainMemory);    break;
        case 4:  add(pointer, MainMemory);      break;
        case 5:  sub(pointer, MainMemory);      break;
        case 6:  mul(pointer, MainMemory);      break;
        case 7:  div(pointer, MainMemory);      break;
        case 8:  Jump(pointer);                 return 2;
        case 9:  return ConJump(pointer);             
        case 10: eq(pointer, MainMemory);       break;
        case 11: les(pointer, MainMemory);      break;
        case 12: more(pointer, MainMemory);     break;
        case 13: cout << "value of AC: "<< AC << endl; break;
        case 14: endProgram();                  return -1;
        default: return -1;
    }
    return 0;

}

void fill_Mem(vector< vector<int> > &MainMemory, int n)
{
    while (MainMemory.size()  < 50)
    {
        vector<int> a(40, 0);
        MainMemory.push_back(a);
    }
    for (int i = 0; i < 10; i++)
    {
        vector<int>t = decToBin(i);
        while (t.size() < 40) t.insert(t.begin(), 0);
        MainMemory.push_back(t);
    }
    while (MainMemory.size()  < 100)
    {
        vector<int> a(40, 0);
        MainMemory.push_back(a);
    }
    // vector<int>tem(32, 0);
    // vector<int>t(decToBin(n)); // storing the value at 0 at location 100
    // tem.insert(tem.end(), t.begin(), t.end());
    vector<int>tem(MainMemory[n]);
    MainMemory.push_back(tem); 
    while (MainMemory.size()  < 110)
    {
        vector<int> a(40, 0);
        MainMemory.push_back(a);
    }
}

int main(){
    string Input;
    vector< vector<int> > MainMemory;
    int n;
    stringstream In = main1();
    // scanf("%d\n" , &n);
    // cout << n;
    // taking input and store in vector of strings
    while (In)
    {
        In >> Input;
        vector<int>line;
        for (auto it:Input) line.push_back(it-'0');
        MainMemory.push_back(line);
    } MainMemory.pop_back(); // remove the last element as it has been duplicated
    n = MainMemory.size()-1;
    fill_Mem(MainMemory, n);

    // processor starts here

    while (PC < MainMemory.size()) 
    {   

        // instruction fetch cycle
        vector<int> MBR(MainMemory[PC]); // store instruction from main memory into Memory Buffer Register 
        
        
        vector<int> IBR(MBR.begin()+20, MBR.end()); // send right half to Instruction Buffer Register 

        // send left half to Memory Address Register and Instruction Register       
        vector<int> IR(MBR.begin(), MBR.begin()+8); //store opcode
        vector<int> MAR(MBR.begin()+8, MBR.begin()+20); //store address location

        // Excecution cycle
        int check = decode_opcode(IR, MAR, MainMemory);
        
        if (check == -1) break;
        if (check == 2) continue;
        
        // now to fetch the right half
        IR.clear();
        IR.insert(IR.begin(), IBR.begin(), IBR.begin()+8);
       
        MAR.clear();
        MAR.insert(MAR.begin(), IBR.begin()+8, IBR.end());

        
        PC++; // increment the program counter
        
        // excecute the right half
        check = decode_opcode(IR, MAR, MainMemory); 
        if (check == -1) break;
        // cout << "line no: " << PC << endl;
    }   
}
