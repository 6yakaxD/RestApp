#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <thread>
#include "shellapi.h"

#include "Data.h"

#include "json.hpp"

#define _CRT_SECURE_NO_WARNINGS

#define	C_SERVER			"C:\\Server"			// директория сервера
#define C_SERVER_USERS		"C:\\Server\\Users"		// директория пользователей (персонала)
#define C_SERVER_MENU		"C:\\Server\\Menu"		// директория меню блюд
#define C_SERVER_CLIENTS	"C:\\Server\\Clients"	// директория клиентов

#pragma warning (disable : 4996)

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::asio;

std::string slesh = "\\";

class Server
{

public:

    std::shared_ptr<ip::tcp::socket> kassa_po;
    std::shared_ptr<ip::tcp::socket> kassa_to_client;
    std::shared_ptr<ip::tcp::socket> kitchen;
    std::shared_ptr<ip::tcp::socket> visitors;

    ip::tcp::acceptor acceptor_;

    std::vector<ip::tcp::socket> clients;

    

public:

    Server(io_context& ioContext, int port) : acceptor_(ioContext, ip::tcp::endpoint(ip::tcp::v4(), port))
    {
        StartAccept();
    
        std::cout << "[Server]: Started" << std::endl;
        g_data.SendInformationNotification("Resto", "Server Started");
    }

    void StartAccept()
    {
        auto socket = std::make_shared<ip::tcp::socket>(acceptor_.get_executor());

        acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& error)
            {
                if (!error)
                {

                    boost::system::error_code error;
                    char data[1024];
                    size_t length = socket->read_some(buffer(data), error);
                    std::string request(data, length);

                    if (request == "kassa_po")
                    {
                        kassa_po = socket;
                        HandleKassa_po(kassa_po);
                    }
                    else if (request == "kassa_to_client")
                    {
                        kassa_to_client = socket;

                    }
                    else if (request == "kitchen")
                    {
                        kitchen = socket;

                    }
                    else if (request == "visitors")
                    {
                        visitors = socket;

                    }
                    else if (request == "client")
                    {
                        HandleClient(socket);
                    }
                    
                }
                StartAccept();
            });
    }

    void HandleKassa_po(std::shared_ptr<ip::tcp::socket> socket)
    {
        std::thread([this, socket]()
            {
                try
                {

                    std::cout << "[Server]: Kassa Po connected IP -> " << socket->remote_endpoint();
                    g_data.COUT_CurrTime();

                    while (true)
                    {
                        boost::system::error_code error;

                        // Recieve
                        char data[1024];
                        size_t length = socket->read_some(buffer(data), error);

                        // проверка ошибok
                        if (error == error::eof)
                        {
                            std::cout << "[Server]: Kassa Po disconnected -> " << socket->remote_endpoint() << std::endl;
                            break;
                        }
                        else if (error)
                        {
                            throw boost::system::system_error(error);
                        }

                        std::string request(data, length);


                        std::vector<std::string> tokens;
                        size_t pos = 0, found;
                        while ((found = request.find("#", pos)) != std::string::npos)
                        {
                            tokens.push_back(request.substr(pos, found - pos));
                            pos = found + 1;
                        }
                        tokens.push_back(request.substr(pos));

                        if (tokens.size() >= 2)
                        {

                            std::string requestType = tokens[0];
                            std::string requestData = tokens[1];
                            std::cout << "[Kassa Po]: " << requestType << "#" << requestData << std::endl;


                            // [ Requests ]

                            if (requestType == "AUTH")
                            {
                                std::string log_fromServer;
                                std::string pas_fromServer;
                                std::string log;
                                std::string pas;

                                // requestData (разделить по) ":"
                                char delimiter = ':';
                                std::vector<std::string> result = g_data.split(requestData, delimiter);
                                if (result.size() >= 2) {
                                    log = result[0];
                                    pas = result[1];
                                }

                                std::string path = C_SERVER_USERS + slesh + log + slesh + "Logs.json";
                                if (g_data.CheckFile(path))
                                {
                                    std::ifstream file(path);
                                    nlohmann::json j;
                                    file >> j;
                                    log_fromServer = j["login"];
                                    pas_fromServer = j["password"];
                                    file.close();

                                    if ((log == log_fromServer) && (pas == pas_fromServer))
                                    {
                                        std::cout << "[Server]: Kassa Po Authorizate Successfully -> " << log << ", " << socket->remote_endpoint() << std::endl;
                                        std::string response = "true";
                                        write(*socket, buffer(response));
                                    }
                                    else
                                    {
                                        std::cout << "[Server]: Kassa Po Authorizate Failed -> " << log << ", " << socket->remote_endpoint() << std::endl;
                                        std::string response = "false";
                                        write(*socket, buffer(response));
                                    }

                                }
                                else
                                {
                                    std::cout << "[Server]: This User is not registred in Kassa Po\n";
                                    std::string response = "false";
                                    write(*socket, buffer(response));
                                }

                            }

                            if (requestType == "GET_USER_STATE")
                            {
                                std::string log = requestData;

                                std::string path = C_SERVER_USERS + slesh + log + slesh + "Logs.json";
                                if (g_data.CheckFile(path))
                                {
                                    std::ifstream file(path);
                                    nlohmann::json j;
                                    file >> j;
                                    std::string user_status = j["state"];
                                    file.close();

                                    write(*socket, buffer(user_status));
                                }
                            }



                            if (error == error::eof)
                            {
                                std::cout << "[Server]: Kassa Po disconnected -> " << socket->remote_endpoint() << std::endl;
                                break;
                            }
                            else if (error)
                            {
                                throw boost::system::system_error(error);
                            }
                        }
                    }

                }
                catch (std::exception& e)
                {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }




            }).detach();
    }

    void HandleClient(std::shared_ptr<ip::tcp::socket> socket)
    {
        std::thread([this, socket]()
            {
                try
                {
                    std::cout << "[Server]: New client connected IP -> " << socket->remote_endpoint();
                    g_data.COUT_CurrTime();

                    while (true)
                    {
                        boost::system::error_code error;

                        // Recieve
                        char data[1024];
                        size_t length = socket->read_some(buffer(data), error);

                        // проверка ошибok
                        if (error == error::eof)
                        {
                            std::cout << "[Server]: Client disconnected -> " << socket->remote_endpoint() << std::endl;
                            break;
                        }
                        else if (error)
                        {
                            throw boost::system::system_error(error);
                        }


                        std::string request(data, length);


                        std::vector<std::string> tokens;
                        size_t pos = 0, found;
                        while ((found = request.find("#", pos)) != std::string::npos)
                        {
                            tokens.push_back(request.substr(pos, found - pos));
                            pos = found + 1;
                        }
                        tokens.push_back(request.substr(pos));

                        if (tokens.size() >= 2)
                        {
                            
                            std::string requestType = tokens[0];
                            std::string requestData = tokens[1];
                            std::cout << "[Client]: " << requestType << "#" << requestData << std::endl;


                            // [ ЗАПРОСЫ ]


                            if (requestType == "AUTH")
                            {

                            }


                        }

                       

                        if (error == error::eof)
                        {
                            std::cout << "[Server]: Client disconnected -> " << socket->remote_endpoint() << std::endl;
                            break;
                        }
                        else if (error)
                        {
                            throw boost::system::system_error(error);
                        }

                    }
                }
                catch (std::exception& e)
                {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }
                



            }).detach();
    }


    
    
    
};