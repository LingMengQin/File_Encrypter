#include "includes.hh"
#include "Definitions.hh"
#include <string.h>

extern int64_t filesize;

void ShowFilesize(int64_t _filesize){   //Print some message
    double filesize = _filesize;
    char* unitnames[] = {(char*)"Bytes",(char*)"KB",//(char*) is used to eliminate compiler warning
                        (char*)"MB",(char*)"GB",(char*)"TB",(char*)"PB",(char*)"EB"};
    int Unameindex = 0;
    for(; filesize >= 1024.0; filesize /= 1024, ++Unameindex);
    printf("FileSize:%lldBytes         (%.2lf)%s\n", _filesize, filesize, unitnames[Unameindex]);
}
void ShowStartMessage(){    //Print some message
    ShowFilesize(filesize);
    cout << "Do not close this window.\n" <<
           "     Processing...\n\n";
}
void ShowFinalMessage(){    //Print some message
    int second = 2;
    printf("finished.\n");
    printf("This program will be closed in %d seconds.\n", second);
    Delay(second);
}

int64_t GetFileSize(FILE *file){    //return filesize(Bytes)
    _off64_t curPosition = ftello64(file);
    fseeko64(file, 0, SEEK_END);
    _off64_t result = ftello64(file);
    fseeko64(file, curPosition-result, SEEK_CUR);
    return result;
}

string FilenameNoExtension(string filename){
    return filename.substr(0, filename.rfind(".",filename.length()-1));;
}
const char* FilenameNoExtension(const char* filename){
/**
 * @brief 
 * return a filename string copy eliminate Extentionname.
 * exameple:
 * input:".\Windows\explorer.exe"
 * return:".\Windows\explorer"
 */
    int nameLen = strlen(filename);
    char *returnval = (char*)malloc(nameLen + 1);
    strcpy(returnval, filename);
    int pointer = nameLen - 1;
    for(; returnval[pointer] != '.'; --pointer);
    returnval[pointer] = '\0';
    return returnval;
}

const char* GetFileExtensionName(const char *filename){
/**
 * @brief 
 * return a fileExtensionName string
 * example:
 * input:".\Windows\explorer.exe"
 * return:"exe"
 * input:"explorer"
 * return:""
 */
    const char *fileExtensionName = "";
    const char *strPtr = filename;
    for( ; *strPtr != '\0'; strPtr++){
        if(*strPtr == '.')
            fileExtensionName = strPtr + 1;
    }
    return fileExtensionName;
}

const char* GetFileRelativeName(const char *filename){
/**
 * @brief 
 * return a relative path filename string
 * example:
 * input:".\Windows\explorer.exe"
 * return:"explorer.exe"
 */
    const char *fileRelativeName = nullptr;
    const char *strPtr = filename;
    for( ; *strPtr != '\0'; strPtr++){
        if(*strPtr == '\\')
            fileRelativeName = strPtr + 1;
    }
    return fileRelativeName;
}

const char* MakeOutputFileName(const char *filenameNoExtention, const char *ExtensionName){
/**
 * @brief 
 * example:
 * input: ".\Windows\explorer" "exe"
 * return:".\Windows\explorer.exe"
 */
    char *returnval = (char*)malloc(strlen(filenameNoExtention) + strlen(ExtensionName) + 3);
    strcpy(returnval, filenameNoExtention);
    strcat(returnval, ".");
    strcat(returnval, ExtensionName);
    return returnval;
}