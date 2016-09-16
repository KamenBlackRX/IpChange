#include "IpChange.h"

int main(int argc, char* argv[])
{
    //Declare variables
    string ip, gw, dns;
    int choice;

    bool loop = true;

    //instanciate class
    IpChange *Ipchange = new IpChange();
    //Open debug menu
    if( argv[0] == string("-debug") || argc > 1)
    {
        //alocate string
        string in_command, response;

        cout<<"Type command: ";
        cin >> in_command;

        if(in_command == "ip")
        {
            cout << "\n IP from Machine: " << Ipchange->ReturnWindowsCurrentIP() <<endl;
        }

        if(in_command == "log")
        {

            cout << "Do you whant to read log?[Y/N]: ";
            cin >> response;
            for(unsigned int i = 0; i < response.length(); i++)
            {
                 response[i] = std::tolower(response[i]);
            }

            if(response == "y")
            {
                //we chose read from FILE pointer, but we can go test ofstream C++ mode;
                if(Ipchange->RegisterLog("D:\\Jefferson\\log.txt") == true)
                {

                    Ipchange->ReadLog("D:\\Jefferson\\log.txt");
                }
                else
                {
                    cout << "Error Log not Found."<<endl;
                }

            }
        }
    }
    while(loop)
    {
        cout << "---------------------- Welcome to IP changer. ----------------------- " << endl;
        cout << "Select an option from menu below." << endl;
        cout << "1 -> Change gateway and DNS to 252." << endl;
        cout << "2 -> Change gateway and DNS to 253."<< endl;
        cout << "3 -> Change gateway and DNS to 254."<< endl;
        cout << "4 -> Insert your ip, mask, gateway and DNS."<<endl;
        cout << "5 -> Exit from program." << endl;

        cout << "Choose an option [1-4]: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            Ipchange->ExecuteFunction("netsh interface ipv4 set address \"Conexão local\" static  255.255.255.0 192.168.136.252", true);
            break;
            case 2:
            Ipchange->ExecuteFunction("netsh interface ipv4 set address \"Conexão local\" static  255.255.255.0 192.168.136.253", true);
            break;
            case 3:
            Ipchange->ExecuteFunction("netsh interface ipv4 set address \"Conexão local\" static  255.255.255.0 192.168.136.254", true);
            break;
            case 5:
                loop = false;


        }

    }


    return 0;
}
