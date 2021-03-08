#include "../include/Network.hpp"

Network::Network()
{
}

sf::IpAddress Network::getplayer1Ip(){
    return player1Ip;
}
sf::IpAddress Network::getplayer2Ip(){
    return player2Ip;
    
}
unsigned short Network::getplayer1Port(){
    return player1Port;
}
unsigned short Network::getplayer2Port(){
    return player2Port;
    
}

int Network::ReceiveWithWaitPlayer1(){
    sf::SocketSelector selector;
    selector.add(socket);
    
    if (selector.wait(sf::seconds(60)))
    {
        sf::Packet packetReceive;
        sf::IpAddress player2ip;
        unsigned short player2port;
        socket.receive(packetReceive, player2ip, player2port);
        int a;
        packetReceive >> a;

        player2Ip = player2ip;
        player2Port = player2port;
        player1Port = 6666;
        std::cout << "Player1 successfully connected with Player2" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Time out to find Player2" << std::endl;
        return 3;
    }
}



int Network::ReceiveWithWaitPlayer2(){
    
    sf::SocketSelector selector;
    selector.add(socket);
    if (selector.wait(sf::seconds(60)))
    {

        
        sf::Packet packetReceive;
        sf::IpAddress player1ip;
        unsigned short player1port;
        socket.receive(packetReceive, player1ip, player1port);
        player1Ip = player1ip;
        player1Port = player1port;
        player2Port = 7777;
        
        
        
        sf::Packet packetSend;
        packetSend << 5;
        
        if (socket.send(packetSend, player1Ip, player1Port) != sf::Socket::Done) {
            std::cout << "Failed to send verification to Player2" << std::endl;
            return 2;
        }
        
        if (socket.send(packetSend, player1Ip, player1Port) != sf::Socket::Done) {
            std::cout << "Time out to send message to Player1" << std::endl;
            return 2;
        }
        std::cout << "Player2 successfully connected with Player1" << std::endl;
        
        return 0;
    }
    else
    {
        std::cout << "Time out to find Player1" << std::endl;
        return 3;
    }
}


int Network::CreateRoom(){
    socket.unbind();
    if (socket.bind(6666) != sf::Socket::Done)
    {
        std::cout << "Player 1 failed to bind UDP socket" << std::endl;
        return 1;
    }
    else {
        std::cout << "Player1 successfully bind UDP socket" << std::endl;
    }
    
    sf::Packet packetSend;
    packetSend << 1;
    
    socket.setBlocking(true);
    sf::SocketSelector selector;
    selector.add(socket);
    while (!selector.wait(sf::seconds(1)))
    {
        if (socket.send(packetSend, sf::IpAddress::Broadcast, 7777) != sf::Socket::Done) {
            std::cout << "Time out to send message to Player2" << std::endl;
            return 2;
        }
        
    }
    socket.setBlocking(false);
    return ReceiveWithWaitPlayer1();
}

int Network::EnterRoom(){
    socket.unbind();
    if (socket.bind(7777) != sf::Socket::Done)
    {
        std::cout << "Player 2 failed to bind UDP socket" << std::endl;
        return 1;
    }
    else {
        std::cout << "Player2 successfully bind UDP socket" << std::endl;
    }
    
    return ReceiveWithWaitPlayer2();
    
}




void Network::receiveField(std::vector<int>& field_vector, sf::IpAddress senderip, unsigned short senderport)
{
    sf::Packet packetReceive;
    socket.setBlocking(true);

    if (socket.receive(packetReceive, senderip, senderport) == sf::Socket::Done) {
        for (int i = 0; i < field_vector.size(); i++){
            
                
                packetReceive >> field_vector[i];
              
                
            
        }
    }
    else{
        std::cout << "Failed to receive Field" << std::endl;
    }
}


void Network::sendField (std::vector<int> field_vector, sf::IpAddress receiveip, unsigned short receiveport)
{
    sf::Packet packetSend;
    
    socket.setBlocking(true);
    for (int i = 0; i < field_vector.size(); i++){
        
            packetSend << field_vector[i];
        
    }
    
    if (socket.send(packetSend, receiveip, receiveport) != sf::Socket::Done)
    {
        std::cout << "Failed to send Field" << std::endl;
    }


}


