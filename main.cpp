#include "Vole_Machine.h"

int main() {
    Machine vole_machine(16,"00",256,"00");
    cout<<"Enter the file name:";
    string fileName;cin>>fileName;
    if(fileName.size()<=3||fileName.substr(fileName.size()-3)!="txt")
    {
        fileName+=".txt";
    }
    vole_machine.RunMachine(fileName);
}
