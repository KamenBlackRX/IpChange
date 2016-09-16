#ifndef IPCHANGE_H_INCLUDED
#define IPCHANGE_H_INCLUDED
#include <iostream>
#include <stdio.h>
// Include for WSADATA
#include <winsock2.h>

//include for Date related functions
#include <ctime>

//Include for interface name
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")


using namespace std;

class IpChange
{
public:

    //Default constructor
    IpChange();
    ~IpChange();

    /**
    * Execute function in system shell, with thread safe"
    * @param string Function -> Command line to execute
    * @param bool verbose -> Show information on console or not.
    */
    void ExecuteFunction(string arg, bool verbose);
    /* Translate Program menu */
    void TranslateProgram(string Language);

    /**
    * Get windows current IP from winsock2 lib.
    * just use in windows, or will get compile error;
    */
    char* ReturnWindowsCurrentIP();

    /**
    * Register informations to log, in determinated path.
    * @param _path -> A path to save log file.
    */
    bool RegisterLog(char* _path);

    /**
    * Read Log and show content into screen.
    * this is a safe thread method and should not be instanciated.
    **/
    inline void ReadLog(char* _path)
    {
        //Create buffer with dynamic memoryu=
        char* buffer = new char[256];
        size_t nread;
        //instaciate FILE pointer
        if(pLogFile != NULL)
        {
            pLogFile = fopen(_path, F_FLAG->write);
        }
        else
        {
            pLogFile = new FILE;
            pLogFile = fopen(_path, F_FLAG->write);
        }

        while(nread = fread(buffer,1, 256, pLogFile) < 0)
        {
            cout << buffer;
        }
        fclose(pLogFile);

        delete pLogFile, buffer;
    }
    /**
    * Write file to log, thread safe,
    * singleton is required, buts need to be filled.
    * @param char* _path -> Get content of buffer and write to file.
    * @param FILE* pFile -> File Pointer.
    */
    inline void _WriteFile(char* _path, char* message, DATE date)
    {


    }
private:
    //File structure to hold log files.
    FILE *pLogFile;
    //File flag srutct
    struct FILE_FLAG
    {

        const char* read = "r";
        const char* append = "a+w";
        const char* write = "w";


    }*F_FLAG;

};



#endif // IPCHANGE_H_INCLUDED
