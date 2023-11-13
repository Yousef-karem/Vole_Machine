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
    cout<<"The Registers: \n";
    for (int i = 0; i < R.size(); ++i) {
        stringstream stream;
        stream << hex << i;
        cout<<stream.str()<<' '<<R[i]<<endl;
    }
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
        cerr<<"the Memory location is not found\n";
    }
    else
    {
        M[i]=value;
    }
}

void Memory::DisplayMemory() {
    cout<<"The Memory cells: "<<endl;
    for (int i = 0; i < M.size(); ++i) {
        stringstream stream;
        stream << hex << i;
        cout<<stream.str()<<' '<<M[i]<<endl;
    }
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
    Memory(MemorySize, initValue),counter(0),Exit(false) {
}
void Machine::Instruction(int i) {
    switch (i)
    {
        case 1: {
            setMemory(B[counter][2] + B[counter][3], getRegister(B[counter][1]));
            cout << "the contents of the memory cell located at address " << B[counter][2] + B[counter][3]
                 << " placed in register" << B[counter][1] << endl;
        }
            break;
        case 2: {
            setRegister(B[counter][1], B[counter][2] + B[counter][3]);
            cout << "the value " <<
            B[counter][2] + B[counter][3] <<
            " placed in register " << B[counter][1] << endl;
        }
            break;
        case 3:
        {
            string value = getRegister(B[counter][1]);
            setMemory(B[counter][2]+B[counter][3], value);
            cout<<"the contents of register "<<B[counter][1]<<" placed in the memory cell whose address is " <<B[counter][2]+B[counter][3]<<endl;
        }
            break;
        case 4:
            setRegister(B[counter][3], getRegister(B[counter][2]));
            cout<<"the contents of register "<<B[counter][2]<<" copied into register "<< B[counter][3]<<endl;
            break;
        case 5:
        {
            const int a = stoi(getRegister(B[counter][2]), 0, 16);
            const int b = stoi(getRegister(B[counter][3]), 0, 16);
            bitset<16> bitsetA(a);
            bitset<16> bitsetB(b);
            bitset<16 + 1> resultBitset = bitsetA.to_ullong() + bitsetB.to_ullong();
            if (resultBitset[16]) {
                resultBitset &= ~(1 << 16);
            }
            int result = resultBitset.to_ulong();
            stringstream stream;
            stream << hex << result;
            setRegister(B[counter][1], stream.str());
            cout << "the binary values in registers " << B[counter][2] << " and " << B[counter][3]
                 << " to be added and the sum placed in register " << B[counter][1] << endl;
        }
            break;
        case 6:
            break;
        case 11:
        {
            if (getRegister("0") == getRegister(B[counter][1])) {
                cout << "the pattern " << B[counter][2] + B[counter][3] << " placed in the program counter "
                     << endl;
                counter = stoi(B[counter][2] + B[counter][3], 0, 16)-1;
                Instruction(stoi(B[counter][0], 0, 16));
            }
        }
            break;
        case 12:
        {
            Exit = true;
            cout << "program execution to stopped " << endl;
        }
            break;
        default:
            cerr<<"Error, the instruction is not valid\n";

    }
}

void Machine::RunMachine(string filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return;
    }
    int cnt=0;
    int counter_sz=0;
    vector<string> tmp(4);
    while (inputFile>>tmp[cnt])
    {
        tmp[cnt]=tmp[cnt].substr(2);
        if(tmp[cnt].size()==2)
        {
            tmp[cnt+1]=tmp[cnt].back();;
            tmp[cnt].pop_back();
            cnt++;
        }
        cnt++;
        if(cnt==4)
        {
            cnt=0;
            B.push_back(tmp);
            counter_sz++;
        }
    }
    for (; counter < counter_sz; ++counter) {
        int i=stoi(B[counter][0],0,16);
        Instruction(i);
        if(Exit)
            break;
    }
    inputFile.close();
    DisplayMemory();
    DisplayRegisters();
}


