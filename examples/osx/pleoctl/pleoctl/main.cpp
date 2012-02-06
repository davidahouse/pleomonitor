//
//  main.cpp
//  pleoctl
//
//  Created by David House on 2/1/12.
//  Copyright (c) 2012 Random Accident. All rights reserved.
//

#include <string.h>
#include <iostream>
#include "pleomonitor.h"
using namespace std;

int main (int argc, const char * argv[])
{

    // insert code here...
    cout << "pleoctl:" << endl;
    
    string port = argv[1];
    cout << "connecting to port: " << port << endl;
    
    PleoMonitor *pleo = new PleoMonitor();
    pleo->Connect(port);
    
    while ( true )
    {
        pleo->SendAndReceive();
        string inMsg = pleo->GetReceiveBuffer();
        if ( inMsg.length() > 0 )
            cout << "PLEO: " << inMsg << endl;
    }
    
    return 0;
}

