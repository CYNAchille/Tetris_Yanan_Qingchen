#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#ifndef NETWORK_CLASS
#define NETWORK_CLASS

class Network
{
private:
    sf::UdpSocket socket;
    sf::IpAddress player1Ip;
    unsigned short player1Port;
    sf::IpAddress player2Ip;
    unsigned short player2Port;


public:
    Network();
    
    sf::IpAddress getplayer1Ip();
    sf::IpAddress getplayer2Ip();
    unsigned short getplayer1Port();
    unsigned short getplayer2Port();

    int ReceiveWithWaitPlayer1();
    int ReceiveWithWaitPlayer2();
    
    int CreateRoom();
    int EnterRoom();

    void sendField (std::vector<int> field_vector, sf::IpAddress receiveip, unsigned short receiveport);
    void receiveField(std::vector<int>& field_vector, sf::IpAddress senderip, unsigned short senderport);

};


#endif
