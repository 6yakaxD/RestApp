#pragma once

// +-------------------------[ Content ]-------------------------+
#include "Registration.h"

// +-------------------------[ Qt Lib ]--------------------------+
#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QGridLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>
#include <QProgressBar>
#include <QMessageBox>
#include <QFontDatabase>
#include <QPainterPath>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QThread>

// +-------------------------[ Other ]---------------------------+
#include <iostream>
#include <thread>

#define WINDOW_WIDTH 1000 // default for this project -> 1000x650
#define WINDOW_HEIGHT 650

#define ENABLE_CONSOLE 1

#pragma warning(disable : 4828)
#pragma warning(disable : 26495)


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget* parent = nullptr)
    {

        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        this->setAttribute(Qt::WA_TranslucentBackground, true);

        this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        INIT();
    }

    
    void INIT()
    {
        //setWindowIcon(QIcon(":/MainWindow/UIUX/Pictures/FirstButton.png"));

        m_WelcomeAnimation = new QPropertyAnimation(this, "windowOpacity", this);
        m_WelcomeAnimation->setDuration(500);
        m_WelcomeAnimation->setStartValue(0);
        m_WelcomeAnimation->setEndValue(1);
        m_WelcomeAnimation->start();

        m_IsLeftMButtonPressed = false;
        m_LastMousePosition = { 0, 0 };

        WindowSize = { WINDOW_WIDTH, WINDOW_HEIGHT };

        m_Registrartion = new Registrartion(this);
        m_Registrartion->move(0, 0);
        m_Registrartion->resize(WindowSize.x(), WindowSize.y());
        m_Registrartion->Init();
        m_Registrartion->show();


        m_ExitButton = new QToolButton(this);
        m_ExitButton->move(this->width() * 0.945, this->height() * 0.036);
        m_ExitButton->resize(this->width() * 0.038, this->height() * 0.054);
        m_ExitButton->setIconSize(QSize(30, 30));
        m_ExitButton->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
        m_ExitButton->setIcon(QIcon(":/UIUX/UIUX/Pictures/exit_button.png"));
        connect(m_ExitButton, &QToolButton::clicked, [=]() {
            QApplication::exit();
            });

    }

    

    void paintEvent(QPaintEvent* paint_event) override
    {
        QPainter main_painter(this);
        main_painter.setBrush(QColor(14, 14, 14, 0));
        main_painter.drawRect(QRect(0, 0, WindowSize.x(), WindowSize.y()));
    }

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape)
        {
            QApplication::exit();
        }
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        m_LastMousePosition = event->pos();
        switch (event->button())
        {
        case Qt::LeftButton:
        {
            m_IsLeftMButtonPressed = true;
        }
        break;

        default:
        {
            m_IsLeftMButtonPressed = false;
        }
        break;
        }
        QMainWindow::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        m_IsLeftMButtonPressed = false;
        QMainWindow::mouseReleaseEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (m_IsLeftMButtonPressed)
        {
            QPoint shift = event->pos() - m_LastMousePosition;
            this->move(this->pos() + shift);

        }
        QMainWindow::mouseMoveEvent(event);
    }



    Registrartion*      m_Registrartion;

    bool                m_IsLeftMButtonPressed; /*    [Handle for mouse]    */ 
    QPoint              m_LastMousePosition;    /* [Handle mouse position]  */ 
    QPoint              WindowSize;             /*       [Window Size]      */ 

    QPropertyAnimation* m_WelcomeAnimation;

    QToolButton*        m_ExitButton;

};






