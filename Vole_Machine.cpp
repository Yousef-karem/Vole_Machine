#include "Vole_Machine.h"
void Register::setRegister(string location, string value)
{
    int i=stoi(location,0,16);
    if(i>=R.size())
    {
        cout<<"the Register location is not found\n";
    }
    else
    {
        R[i]=value;
    }
}

void Register::clearRegister() {
    for(string &value:R)
    {
        value="00";
    }
}

void Register::DisplayRegisters() {

}

string Register::getRegister(string location) {
    int i=stoi(location,0,16);
    if(i<R.size())
        return R[i];
    else
        cout<<"the Register is not found\n";
}

Register::Register(int size,string InitValue)
{
    for(int i=0;i<size;i++)
    {
        R.push_back(InitValue);
    }
}

void Memory::setMemory(string location, string value) {
    int i=stoi(location,0,16);
    if(i>=M.size())
    {
        cout<<"the Memory location is not found\n";
    }
    else
    {
        M[i]=value;
    }
}

void Memory::DisplayMemories() {

}

Memory::Memory(int size, string InitValue) {
    for(int i=0;i<size;i++)
    {
        M.push_back(InitValue);
    }
}

void Memory::clearMemory() {
    for(string&value:M)
    {
        value="00";
    }
}

string Memory::getMemory(string location, string value) {
    int i=stoi(location,0,16);
    if(i<M.size())
        return M[i];
    else
        cout<<"the Memory location is not found\n";
}

Machine::Machine(int RegisterSize, string initValue1, int MemorySize, string initValue)
: Register(RegisterSize, initValue1),
    Memory(MemorySize, initValue) {
}
void Machine::Instruction(int i) {
    switch (i)
    {
        case 1:
            setMemory(B[2]+B[3], getRegister(B[1]));
            break;
        case 2:
            setRegister(B[1],B[2]+B[3]);
            break;
        case 3:
            setMemory(0,getRegister( B[1]));
            break;
      case 4:
            setRegister(B[3], getRegister(B[2]));
            break;
        case 5:
            setRegister(B[1], getRegister(B[2])+ getRegister(B[3]));
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            cout<<"Error, the instruction is not valid\n";
    }
}


