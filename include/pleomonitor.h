//-----------------------------------------------------------------
//
// pleomonitor.h
//
//
//
//-----------------------------------------------------------------
#pragma once
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <vector>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

struct PleoJointInfo
{
    int joint;
    int min;
    int max;
};

struct PleoJointStatus
{
    int joint;
    int angle;
};

struct PleoSensorStatus
{
    int sensor;
    int status;
};

class PleoMonitor
{
public:
    // Constructor & Destructor
    PleoMonitor(void);
    ~PleoMonitor(void);
    
    // Initialization & Connectivity
    void Connect(string port);
    void Disconnect();
    bool IsConnected();
    void SendAndReceive();
    
    // Information methods
    vector<PleoJointInfo> GetJointInfo();
    vector<PleoJointStatus> GetJointStatus();
    vector<PleoSensorStatus> GetSensorStatus();
    vector<string> GetMotions();
    vector<string> GetSounds();
    
    // Control methods
    void SetJointAngle(int joint, int angle);
    void ExecuteMotion(string motion);
    void LoadMotion(string motion);
    void RunMotion(string motion, int loops);
    void PlaySound(string sound);
    
    // General methods
    string GetReceiveBuffer();
    
private:
    struct termios m_portSettings;
    int m_portHandle;
    vector<PleoJointInfo> m_jointInfo;
    vector<PleoJointStatus> m_jointStatus;
    vector<PleoSensorStatus> m_sensorStatus;
    vector<string> m_motions;
    vector<string> m_sounds;
    queue<string> m_sendQueue;
    queue<string> m_receiveQueue;
};
