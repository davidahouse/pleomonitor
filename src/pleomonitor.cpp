//-----------------------------------------------------------------
//
// pleomonitor.cpp
//
//
//
//-----------------------------------------------------------------
#include "pleomonitor.h"

// Constructor & Destructor
PleoMonitor::PleoMonitor(void)
{
    m_portHandle = -1;
    
    // Go ahead and create the port settings that we will use
    // once the port is connected
    memset(&m_portSettings,0,sizeof(m_portSettings));
    m_portSettings.c_iflag = 0;
    m_portSettings.c_oflag = 0;
    m_portSettings.c_cflag = CS8|CREAD|CLOCAL;
    m_portSettings.c_lflag = 0;
    m_portSettings.c_cc[VMIN] = 1;
    m_portSettings.c_cc[VTIME] = 5;
}

PleoMonitor::~PleoMonitor(void)
{
    if ( m_portHandle != -1 )
        close(m_portHandle);
}
    
// Initialization & Connectivity
void PleoMonitor::Connect(string port)
{
    // open the port and set it's settings
    m_portHandle = open(port.c_str(),O_RDWR|O_NONBLOCK);
    cfsetospeed(&m_portSettings,B115200);
    cfsetispeed(&m_portSettings,B115200);
    tcsetattr(m_portHandle,TCSANOW,&m_portSettings);
    
    // queue up a few commands to get the pleo general information. We will only do this once
    m_sendQueue.push("joint info\r\n");
    m_sendQueue.push("sensor show\r\n");
    m_sendQueue.push("motion show\r\n");
    m_sendQueue.push("sound show\r\n");
}

void PleoMonitor::Disconnect()
{
    close(m_portHandle);
    m_portHandle = -1;
}

bool PleoMonitor::IsConnected()
{
    if ( m_portHandle == -1 )
        return false;
    else
        return true;
}

void PleoMonitor::SendAndReceive()
{
    // Perform a send and receive. This method should be called in a run loop in the main program so that
    // we can read the output from the Pleo. Here is also where we will query the pleo sensors and joint
    // information periodically.
    
    // If we have something to send, pop it from the queue and send it
    if ( !m_sendQueue.empty() )
    {
        string sendMsg = m_sendQueue.front();
        m_sendQueue.pop();
        
        const char *sMsg = sendMsg.c_str();
        write(m_portHandle,sMsg,sendMsg.length());
        cout << "SENT: " << sendMsg << endl;
    }
    
    // Now try to read some data from the port. We will keep reading until we have
    // found the end of a line, OR we have we have passed a certain number of characters.
    //char buffer[128];
    //size_t read_size = read(m_portHandle,&buffer,128);
    //if ( read_size > 0 )
    //{
    //    cout << "BUFFER: (" << read_size << ") " << buffer << endl;
    //}
    unsigned char c ='D';
    if ( read(m_portHandle,&c,1) > 0 )
    {
        char out[255];
        sprintf(out,"%c %d",c,c);
        cout << "BUFFER: " << out << endl;
    }
}
    
// Information methods
vector<PleoJointInfo> PleoMonitor::GetJointInfo()
{
    return m_jointInfo;
}

vector<PleoJointStatus> PleoMonitor::GetJointStatus()
{
    return m_jointStatus;
}

vector<PleoSensorStatus> PleoMonitor::GetSensorStatus()
{
    return m_sensorStatus;
}

vector<string> PleoMonitor::GetMotions()
{
    return m_motions;
}

vector<string> PleoMonitor::GetSounds()
{
    return m_sounds;
}
    
// Control methods
void PleoMonitor::SetJointAngle(int joint, int angle)
{
    
}

void PleoMonitor::ExecuteMotion(string motion)
{
}
    
void PleoMonitor::LoadMotion(string motion)
{
    
}

void PleoMonitor::RunMotion(string motion, int loops)
{
    
}

void PleoMonitor::PlaySound(string sound)
{
    
}
    
// General methods
string PleoMonitor::GetReceiveBuffer()
{
    if ( !m_receiveQueue.empty() )
    {
        string sendMsg = m_receiveQueue.front();
        m_receiveQueue.pop();
        return sendMsg;
    }
    else
        return "";
}

