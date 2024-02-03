#pragma once

//#include "Admin.h"

#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <Windows.h>
#include "shellapi.h"
#include <thread>
#include <mutex>
#include <condition_variable>

#pragma warning (disable : 4996)

using boost::asio::ip::tcp;

class Network {
public:
    Network() : ioContext_(), socket_(ioContext_), resolver_(ioContext_) {}

    bool connectToServer(const std::string& serverIP, const std::string& serverPort)
    {
        try
        {
            boost::asio::ip::tcp::resolver::results_type endpoints = resolver_.resolve(serverIP, serverPort);
            connect(socket_, endpoints);

            g_Admin.Is_ClientConnectedToServer = true;

            return true;
        }
        catch (std::exception& e)
        {
            g_Admin.Is_ClientConnectedToServer = false;

            return false;
        }

        return false;
    }

    // +-------------------------[ Requests && Responses ]--------------------------+

    void Identify(std::string text)
    {
        std::string request = text;
        boost::asio::write(socket_, boost::asio::buffer(request));
    }

    bool Authenticate(std::string log_and_pass)
    {

        std::string request = "AUTH#" + log_and_pass;
        boost::asio::write(socket_, boost::asio::buffer(request));

        char responseBuffer[64];
        boost::system::error_code responseError;
        size_t responseLength = socket_.read_some(boost::asio::buffer(responseBuffer, sizeof(responseBuffer)));

        std::string response = std::string(responseBuffer, responseLength);

        if (response == "true")
        {
            return true;
        }
        if (response == "false")
        {
            return false;
        }
        return false;
    }

    void GetUserState(std::string login, std::string* answer)
    {
        std::string request = "GET_USER_STATE#" + login;
        boost::asio::write(socket_, boost::asio::buffer(request));

        char responseBuffer[64];
        boost::system::error_code responseError;
        size_t responseLength = socket_.read_some(boost::asio::buffer(responseBuffer, sizeof(responseBuffer)));

        std::string response = std::string(responseBuffer, responseLength);

        *answer = response;
    }



public:

    bool Is_ServerAvailable = false;

private:
    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
};
inline Network g_Net;
