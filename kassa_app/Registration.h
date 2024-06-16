#pragma once

#define WIN32_LEAN_AND_MEAN

// +-------------------------[ Content ]-------------------------+
#include "MainPage.h"
#include "Data.h"
#include "Network.h"
#include "Admin.h"
#include "Customer.h"
#include "ErrorBox.h"

// +-------------------------[ Qt Lib ]--------------------------+
#include <QApplication>
#include <QPropertyAnimation>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QToolButton>
#include <QIcon>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QErrorMessage>

// +-------------------------[ Other ]---------------------------+
#include <iostream>

class Registrartion : public QWidget
{
    Q_OBJECT

public:

    Registrartion(QWidget* parent = nullptr) : QWidget(parent)
    {

    }

    
    void Init()
    {
        
        // [ Main Page ] 
        {
            m_MainPage = new MainPage(this);
            m_MainPage->move(0, 0);
            m_MainPage->resize(this->width(), this->height());
            m_MainPage->Init();
            m_MainPage->hide();
        }

        // [ FONTS ]
        {
            int id = QFontDatabase::addApplicationFont(":/UIUX/UIUX/Fonts/MenuObjects-SemiBoldItalic.ttf");
            QString family = QFontDatabase::applicationFontFamilies(id).at(0);
            m_HeaderFont.setFamily(family);
            m_HeaderFont.setPointSize(this->width() * 0.03);
        }
        
        // [ LOG IN ]
        {
            m_LoginInput = new QLineEdit(this); // поле ввода логина
            m_LoginInput->move(this->width() * 0.35, this->height() * 0.35);
            m_LoginInput->resize(this->width() * 0.35, this->height() * 0.07);
            m_LoginInput->setPlaceholderText("login");
            m_LoginInput->setAlignment(Qt::AlignCenter);
            m_LoginInput->setFont(m_HeaderFont);
            m_LoginInput->setStyleSheet("QLineEdit { background-color: transparent; color: white; border: none; border-bottom: 3px solid rgba(28, 29, 36, 210); font-size: 15px; } "
                                        "QLineEdit:hover { background-color: rgba(28, 29, 36, 210); } ");
            m_LoginInput->hide();

            m_PasswordInput = new QLineEdit(this); // поле ввода пароля
            m_PasswordInput->move(this->width() * 0.35, this->height() * 0.42);
            m_PasswordInput->resize(this->width() * 0.35, this->height() * 0.07);
            m_PasswordInput->setPlaceholderText("password");
            m_PasswordInput->setAlignment(Qt::AlignCenter);
            m_PasswordInput->setFont(m_HeaderFont);
            m_PasswordInput->setStyleSheet("QLineEdit { background-color: transparent; color: white; border: none; border-bottom: 3px solid rgba(28, 29, 36, 210); font-size: 15px; } "
                                           "QLineEdit:hover { background-color: rgba(28, 29, 36, 210); } ");
            m_PasswordInput->hide();

            m_Remember = new QCheckBox("remember me", this);
            m_Remember->setChecked(false);
            m_Remember->move(this->width() * 0.48, this->height() * 0.5);
            m_Remember->setStyleSheet("QCheckBox { background-color: transparent; color: white; border: none; } ");
            connect(m_Remember, &QCheckBox::stateChanged, [=](int state) {
                if (state == Qt::Checked)
                {
                    is_RememperButtonPressed = true;
                }
                else if (state == Qt::Unchecked)
                {
                    is_RememperButtonPressed = false;
                }
                });

            m_LogInButton = new QToolButton(this); // кнопка LogIn 
            m_LogInButton->move(this->width() * 0.38, this->height() * 0.8);
            m_LogInButton->resize(this->width() * 0.3, this->height() * 0.12);
            m_LogInButton->setStyleSheet("QToolButton { color: white; border: none; border-radius: 30px; background-color: transparent; padding-left: 10px; padding-right: 10px;  }"
                                         "QToolButton:enabled { border-top: 3px solid rgba(28, 29, 36, 255); border-top-right-radius: 30px; }"
                                         "QToolButton:hover { background-color: rgba(28, 29, 36, 100); border-bottom: 3px solid rgba(28, 29, 36, 255); border-bottom-right-radius: 30px; } ");
            m_LogInButton->setFont(m_HeaderFont);
            m_LogInButton->setText("Login");
            m_LogInButton->hide();
            connect(m_LogInButton, &QToolButton::clicked, [=]() {
                if (g_Net.Is_ServerAvailable == false)
                {
                    m_ErrorBox = new ErrorBox(this);
                    m_ErrorBox->setErrorText("ERROR\nNO CONNECTION TO SERVER");
                    m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
                    m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
                    m_ErrorBox->Init();
                    m_ErrorBox->show();
                }
                else
                {
                    QString data_login = m_LoginInput->text();
                    QString data_password = m_PasswordInput->text();

                    try
                    {
                        if (!data_login.isEmpty() && !data_password.isEmpty())
                        {
                            std::string for_request = data_login.toStdString() + ":" + data_password.toStdString();
                            bool response = g_Net.Authenticate(for_request);
                            if (response == true)
                            {

                                g_Admin.name = data_login.toStdString();
                                //g_Admin.state = g_Net.GetUserState(g_Admin.name);   //->  приложение зависает
                                g_Net.GetUserState(g_Admin.name, &g_Admin.state);

                                m_LoginInput->clear();
                                m_PasswordInput->clear();

                                m_MainPage->show();
                                m_LoginInput->hide();
                                m_PasswordInput->hide();
                                m_LogInButton->hide();
                                m_Remember->hide();

                                m_MainPage->SetTop_ADMIN_Name_State();

                                if (is_RememperButtonPressed == true)
                                {
                                    nlohmann::json j;
                                    j["login"] = data_login.toStdString();
                                    j["password"] = data_password.toStdString();
                                    std::ofstream file(g_data.path_to_json);
                                    file << j.dump(4);
                                    file.close();
                                }
                            }
                            if (response == false)
                            {
                                m_ErrorBox = new ErrorBox(this);
                                m_ErrorBox->setErrorText("ERROR\nNOT CORRECT DATA");
                                m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
                                m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
                                m_ErrorBox->Init();
                                m_ErrorBox->show();
                            }
                        }
                        else
                        {
                            m_ErrorBox = new ErrorBox(this);
                            m_ErrorBox->setErrorText("ERROR\nNOT CORRECT DATA");
                            m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
                            m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
                            m_ErrorBox->Init();
                            m_ErrorBox->show();
                        }
                    }
                    catch (std::exception& e)
                    {
                        std::cerr << "Exception: " << e.what() << std::endl;
                    }
                }
                });
        }

        if (g_Net.Is_ServerAvailable == false)
        {
            m_ErrorBox = new ErrorBox(this);
            m_ErrorBox->setErrorText("ERROR\nNO CONNECTION TO SERVER");
            m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
            m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
            m_ErrorBox->Init();
            m_ErrorBox->show();

            m_MainPage->hide();
            m_LoginInput->show();
            m_PasswordInput->show();
            m_LogInButton->show();
            m_Remember->show();
        }
        else
        {
            std::string log_from_lastJson;
            std::string pas_from_lastJson;

            std::ifstream file(g_data.path_to_json);
            nlohmann::json j;
            file >> j;
            log_from_lastJson = j["login"];
            pas_from_lastJson = j["password"];
            file.close();

            if ((log_from_lastJson == "") && (pas_from_lastJson == ""))
            {
                m_MainPage->hide();
                m_LoginInput->show();
                m_PasswordInput->show();
                m_LogInButton->show();
                m_Remember->show();
            }
            else
            {
                m_LoginInput->clear();
                m_PasswordInput->clear();
                m_LoginInput->setText(QString(log_from_lastJson.c_str()));
                m_PasswordInput->setText(QString(pas_from_lastJson.c_str()));
                m_LogInButton->click();
            }
        }
        
        connect(m_MainPage, &MainPage::Signal_LogOut, this, &Registrartion::ON_Signal_LogOut);
    }
    

    void paintEvent(QPaintEvent* paint_event) override
    {
        QPainter MainWidget_painter(this);

        MainWidget_painter.setBrush(QColor(14, 14, 14, 255));
        MainWidget_painter.drawRect(QRect(0, 0, this->width(), this->height()));

    }


    QFont           m_HeaderFont;
    MainPage*       m_MainPage;
    bool            is_RememperButtonPressed = false;
    ErrorBox*       m_ErrorBox;

    // [ LOG IN ]
    QToolButton*    m_LogInButton;      // кнопка авторизации
    QCheckBox*      m_Remember;
    QLineEdit*      m_LoginInput;       // поле ввода логина
    QLineEdit*      m_PasswordInput;    // поле ввода пароля

    
public slots:

    void ON_Signal_LogOut()
    {
        // ДОБАВИТЬ ПРОВЕРКУ ЧТО НЕТ ОТКРЫТОГО ЗАКАЗА && Смена закрыта

        m_LoginInput->show();
        m_PasswordInput->show();
        m_LogInButton->show();
        m_Remember->show();
        m_MainPage->hide();

        nlohmann::json j;
        j["login"] = "";
        j["password"] = "";
        std::ofstream file(g_data.path_to_json);
        file << j.dump(4);
        file.close();
    }


};












