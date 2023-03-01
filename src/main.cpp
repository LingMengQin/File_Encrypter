#include "includes.hh"
#include "Definitions.hh"

void FileEncrypter(const char* filename);
const char* GetFileRelativeName(const char *filename);

int main(int argc, char** args){
    if(argc >= 2){
        // if((string)args[1] == (string)"--help"){
        //     ErrorHandling("message");
        // }
        FileEncrypter(args[1]);
    }else{
        cout << "Usage:" << "\n\n";
        cout << "\t" << GetFileRelativeName(args[0]) << " " << "<filename>" << "\n";
        cout << "\n\n";
        cout << "or u can drag a file open with this application." << "\n\n";
        Exit_manual(0);
    }

    return 0;
}