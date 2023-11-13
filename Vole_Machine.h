#ifndef VOLE_MACHINE_VOLE_MACHINE_H
#define VOLE_MACHINE_VOLE_MACHINE_H
#include<bits/stdc++.h>
using namespace std;
class Register
{
    private:
        vector<string>R;
    public:
        Register(int size,string InitValue);
        void setRegister(string location,string value);
        string getRegister(string location);
        void clearRegister();
        void DisplayRegisters();
};
class Memory
{
    private:
        vector<string>M;
    public:
        Memory(int size,string InitValue);
        void setMemory(string location,string value);
        string getMemory(string location,string value);
        void clearMemory();
        void DisplayMemory();

};
class Machine:Register,Memory
{
    private:
        int counter;
        bool Exit;
        vector<vector<string>>B;
        void Instruction(int i);
    public:
        Machine(int RegisterSize, string initValue1, int MemorySize, string initValue);
        void RunMachine(string filename);


};
#endif //VOLE_MACHINE_VOLE_MACHINE_H
