//
//  udp_client_server.h
//  CPP_UDP_Client_Server
//
//  Created by Dariusz Adamczyk on 08/03/2021.
//  Copyright © 2021 Dariusz Adamczyk. All rights reserved.
//
// UDP Client Server -- send/receive UDP packets
// Copyright (C) 2013  Made to Order Software Corp.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#ifndef SNAP_UDP_CLIENT_SERVER_H
#define SNAP_UDP_CLIENT_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <string>

namespace udp_client_server
{

class udp_client_server_runtime_error : public std::runtime_error
{
public:
    udp_client_server_runtime_error(const char *w) : std::runtime_error(w) {}
};


class udp_client
{
public:
                        udp_client(const std::string& addr, int port);
                        ~udp_client();

    int                 get_socket() const;
    int                 get_port() const;
    std::string         get_addr() const;

    int                 send(const char *msg, size_t size);
    int                 recv(char *msg, size_t max_size);

private:
    int                 f_socket;
    int                 f_port;
    std::string         f_addr;
    struct addrinfo *   f_addrinfo;
    struct sockaddr_in  f_servaddr, f_cliaddr;
    socklen_t len;

};


class udp_server
{
public:
                        udp_server(const std::string& addr, int port);
                        ~udp_server();

    int                 get_socket() const;
    int                 get_port() const;
    std::string         get_addr() const;
    char *              get_client_addr() const;

    int                 recv(char *msg, size_t max_size);
    int                 reply(const char *msg, size_t size);
    int                 timed_recv(char *msg, size_t max_size, int max_wait_ms);

private:
    int                 f_socket;
    int                 f_port;
    std::string         f_addr;
    struct addrinfo *   f_addrinfo;
    struct sockaddr_in  f_servaddr, f_cliaddr;
    socklen_t len;

};

class udp_helpers
{
public:
    static const char * get_local_ip_address(void);
};

} // namespace udp_client_server
#endif

