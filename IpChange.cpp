#include "IpChange.h"
#include <errno.h>

//Default ctr and dctr
IpChange::IpChange()
{

}

IpChange::~IpChange()
{

}

void IpChange::ExecuteFunction(string arg, bool verbose)
{
    //Intialize buffer and File pointer;
    char* buffer = new char[256];
    FILE *pPipe;

    //insert ip string
    arg.insert(56, ReturnWindowsCurrentIP());

    //Run command intro a pipe, and save his content to buffer.
    try
    {
            const char * c = arg.c_str();
            if((pPipe = _popen(c, "rt")) == NULL)
               throw;
    }
    catch(exception& ex)
    {
        cout<<"Internal error, see error code in manual to get more information\nError code: " << ex.what();
    }

    //Read pPipe content and send to buffer, if verbose is enabled
    if(verbose == true)
    {
        while(fgets(buffer,128,pPipe))
        {
            cout << buffer;
        }
    }
    if(verbose == false)
    {

    }

    //Close process and return value of Pipe, 1 STDERR
    if (feof( pPipe))
    {
      cout << "\nProcess returned " <<_pclose( pPipe ) << std::endl;
    }
    else
    {
     cout << "Error: Failed to read the pipe to the end.\n";
    }
}

char* IpChange::ReturnWindowsCurrentIP()
{
    //DWOR to get ipv4 or ipv6
    WORD wVersionRequested;
    WSADATA wsaData;
    char name[255];
    char* ip;
    PHOSTENT hostinfo;
    wVersionRequested = MAKEWORD( 2, 0 );

    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
    {
        if( gethostname ( name, sizeof(name)) == 0)
        {
            if((hostinfo = gethostbyname(name)) != NULL)
            {
                cout<< "\n !! DEBUG !! \n";
                ip =  inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                cout << inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list) <<endl;
            }
        }
        WSACleanup( );
    }
    return ip;
}


bool IpChange::RegisterLog(char* _path)
{
    //Initialize struct with dynamic memory allocation
    F_FLAG = new FILE_FLAG;
    char* buffer = new char[sizeof(CHAR_MAX)];
    this->pLogFile = new FILE;
    int errcode;

    //Checking if we dont have any log file;

    if(pLogFile = fopen(_path, F_FLAG->write ))
    {
        errcode = errno;
        if(errcode == EEXIST)
            cout << "\nAn error has occured.\nError code: " << errno << "\n Error status: File Exists.";
        fclose(pLogFile);
        return false;

    }
    else
    {
        errcode = errno;
        if(errcode == EEXIST)
        {
            cout << "\nAn error has occured.\nError code: " << errno << "\n Error status: File not exists.";
            return false;
        }

        fclose(pLogFile);
        return true;
    }

    delete buffer, pLogFile, F_FLAG;
}
