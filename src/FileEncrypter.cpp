#include "includes.hh"
#include "Definitions.hh"
#include <string.h>

static FILE *inputfile = nullptr;
extern int64_t filesize;
static FILE *outputfile = nullptr;
static const char *inputFileExtensionName = nullptr;
static const char *iputFname;       //input filename
static bool isSftfile;

static string shiftKeys;
static int keysLenth = 0;
static char bitstream[1];

static int64_t processedCount = 0;

static void (*shiftOrUnshiftBitstream)(const uint8_t shiftval);

//==================================================

const char* FilenameNoExtension(const char* filename);
const char* GetFileExtensionName(const char *filename);
const char* MakeOutputFileName(const char *filenameNoExtention, const char *ExtensionName);
void ShowStartMessage();
void ShowFinalMessage();



static void GetShiftKeys(bool askToConfirm){
    printf("Please enter your password(no space)\n::");
    cin >> shiftKeys;
    if(askToConfirm){
        string temp;
        printf("Please enter again to confirm\n::");
        cin >> temp;
        if(temp != shiftKeys){
            printf("inputs not match!!\n");
            Delay(1);
            GetShiftKeys(1);
        }
    }
    keysLenth = shiftKeys.size();
}
char MovingKeysReader(){
    static int index = 0;
    if(index >= keysLenth)
        index = 0;
    return shiftKeys[index++];
}

static bool IsSftfile(const char* fileExtentionName){
    if((string)"sft" == (string)fileExtentionName)
        return true;
    else
        return false;
}

static void initialize(const char* _filename){
    iputFname = _filename;

    inputfile = fopen64(iputFname, "rb");
    if(inputfile == nullptr)
        ErrorHandling("Can't open file.");


    filesize = GetFileSize(inputfile);
    isSftfile = IsSftfile(GetFileExtensionName(iputFname));
}

static void OpenOutputFile(const char* filename){
    outputfile = fopen64(filename, "wb");
}

void ShiftBitstream(const uint8_t shiftval){
    uint16_t preShiftVal = bitstream[0] + shiftval;
    bitstream[0] = preShiftVal > 255 ? preShiftVal - 256 : preShiftVal;
}
void UnShiftBitstream(const uint8_t shiftval){
    uint16_t preShiftVal = bitstream[0] - shiftval;
    bitstream[0] = preShiftVal < 0 ? preShiftVal + 256 : preShiftVal;
}

void UnEncryptePreparation(){
    GetShiftKeys(0);
    OpenOutputFile(FilenameNoExtension(iputFname));
    shiftOrUnshiftBitstream = UnShiftBitstream;
}
void EncryptePreparation(){
    GetShiftKeys(1);
    OpenOutputFile(MakeOutputFileName(iputFname, "sft"));
    shiftOrUnshiftBitstream = ShiftBitstream;
}

void Processing(){
    InitProgressBar(filesize, 50);
    for(processedCount = 0; processedCount < filesize; processedCount++){
        if(0 == fread(bitstream, 1, 1, inputfile))
            ErrorHandling("Can't read data!! Maybe the file is occupied by another program.");
        shiftOrUnshiftBitstream(MovingKeysReader());
        if(0 == fwrite(bitstream, 1, 1, outputfile))
            ErrorHandling("Can't write data!! Maybe the file is occupied by another program.");
        UpdateProgressBar(processedCount);
    }
    printf("\n\n");
    printf("%lld bytes was Processed.\n", processedCount);
    if(processedCount != filesize)
        ErrorHandling("processedCount != filesize??");
}

void FileEncrypter(const char* FileName){
    initialize(FileName);

    if(isSftfile){
        UnEncryptePreparation(); 
    }else{
        EncryptePreparation();
    }

    ShowStartMessage();
    Processing();
    ShowFinalMessage();
    return;
}