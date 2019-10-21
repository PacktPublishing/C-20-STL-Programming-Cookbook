#include <string>
#include <vector>

#include <stdexcept>
#include <iostream>

struct TCPSocket {void send (char const*, int){} }; 
struct UDPSocket {void send (char const*, int){} }; 
struct File {void write (char const*, int){} }; 

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename SocketT>
concept bool is_socket_v = 
    requires (SocketT t) { 
        t.send((char const*)0, 0); 
    };

template<typename SocketT>
requires is_socket_v<SocketT>
void put(SocketT& socket, char const* buffer, int len)
{
    if (buffer != nullptr)
        socket.send(buffer, len);
    throw std::runtime_error("Bad buffer");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename FileT>
concept bool is_file_v = 
    requires (FileT t) { 
        t.write((char const*)0, 0); 
    };

template<typename FileT>
requires is_file_v<FileT>
void put(FileT& file, char const* buffer, int len)
{
    if (buffer != nullptr)
        file.write(buffer, len);
    throw std::runtime_error("Bad buffer");
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    
    TCPSocket tcp;
    put(tcp, (char const*)0, 0);

    UDPSocket udp;
    put(udp, (char const*)0, 0);

    File file;
    put(file, (char const*)0, 0);


    std::cout << "program end" << std::endl;
    return 0;
}

