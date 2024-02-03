/*
*  Project development start: 19 December 2023
*  Author: R4m1L
*  License:
*  Support: mail
*  (C) Commercial Software
*/

#define WIN32_LEAN_AND_MEAN

// +-------------------------[ Qt Lib ]--------------------------+
#include <QtWidgets/QApplication>
#include <QSystemSemaphore>
#include <QErrorMessage>

// +-------------------------[ Boost Lib ]-----------------------+
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

// +-------------------------[ Content ]-------------------------+
#include "MainWindow.h"
#include "Data.h"
#include "Network.h"

// +-------------------------[ Other ]---------------------------+
#include <Windows.h>


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
#if ENABLE_CONSOLE
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif 

    g_data.Init();

    if (g_Net.connectToServer("127.0.0.1", "43990")) // main  server -> "83.221.222.251", "43990"
    {                                                // local server -> "127.0.0.1", "43990"
        g_Net.Is_ServerAvailable = true;
        g_Net.Identify("kassa_po");
    }
    else
    {
        g_Net.Is_ServerAvailable = false;
    }

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();

    return 0;
}
