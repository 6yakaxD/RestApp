#pragma once

// +-------------------------[ Content ]-------------------------+
#include "Data.h"
#include "Admin.h"
#include "Customer.h"
#include "ErrorBox.h"
#include "Order.h"

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
#include <QGridLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QTableWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHeaderView>
#include <QSignalMapper>
#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMap>
#include <QPair>
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>

// +-------------------------[ Other ]---------------------------+
#include <iostream>
#include <vector>
#include <string>



class MainPage : public QWidget
{
    Q_OBJECT

public:

    MainPage(QWidget* parent = nullptr) : QWidget(parent)
    {

    }

    // [ VARS FOR CHANGINGS ]
    bool    Is_SettingsWidget_Open      = false;  // ������ �� ������ ��������
    bool    Is_SeatPlaceWidget_Open     = false;  // ������ �� ������ ������ �����
    bool    Is_DishDescription_Open     = false;  // ������ �� ������ �������� �����
    bool    Is_NewGuestWidget_Open      = false;  // ������ �� ������ ���������� ������� 
    bool    Is_GuestRegisteredForOrder  = false;  // ������ �� ������ ��� ������
    bool    Is_PaymentWidget_Open       = false;  // ������ �� ������ ������
    bool    Is_OrderPaidOkay            = false;  // ������� �� �����
    int     Dish_type                   = 0;      // ��� ����� {5}
    int     Dish_id                     = 0;      // id �����  {}
    int     Place_id                    = 0;      // id �����


    void Init()
    {
        // [ Fonts ]
        {
            int id_1 = QFontDatabase::addApplicationFont(":/UIUX/UIUX/Fonts/bold_straight.ttf");
            QString family_1 = QFontDatabase::applicationFontFamilies(id_1).at(0);
            m_FirstFont.setFamily(family_1);
            m_FirstFont.setPointSize(this->width() * 0.015);

            int id_2 = QFontDatabase::addApplicationFont(":/UIUX/UIUX/Fonts/not_bold.ttf");
            QString family_2 = QFontDatabase::applicationFontFamilies(id_2).at(0);
            m_SecondFont.setFamily(family_2);
            m_SecondFont.setPointSize(this->width() * 0.012);
        }

        // [ TOP INFO Bar ]
        {
            m_TOP_InfoBar_Widget = new QWidget(this);
            m_TOP_InfoBar_Widget->move(this->width() * 0.009, this->height() * 0.02);
            m_TOP_InfoBar_Widget->resize(this->width() * 0.98, this->height() * 0.08);
            m_TOP_InfoBar_Widget->setStyleSheet("QWidget { color: white; background-color: rgba(255, 255, 255, 255); border: none; border-radius: 20px}");
            m_TOP_InfoBar_Widget->show();

            m_TOP_AdmiName_Label = new QLabel(this);
            m_TOP_AdmiName_Label->move(this->width() * 0.08, this->height() * 0.06);
            m_TOP_AdmiName_Label->resize(this->width() * 0.2, this->height() * 0.04);
            m_TOP_AdmiName_Label->setStyleSheet("QLabel { color: black; border: none; background: transparent; }");
            m_TOP_AdmiName_Label->setFont(m_FirstFont);
            m_TOP_AdmiName_Label->setAlignment(Qt::AlignLeft);
            m_TOP_AdmiName_Label->show();

            m_TOP_AdminState_Label = new QLabel(this);
            m_TOP_AdminState_Label->move(this->width() * 0.08, this->height() * 0.03);
            m_TOP_AdminState_Label->resize(this->width() * 0.12, this->height() * 0.03);
            m_TOP_AdminState_Label->setStyleSheet("QLabel { color: rgba(0,0,0,255); border: none; background: transparent; }");
            m_TOP_AdminState_Label->setFont(m_SecondFont);
            m_TOP_AdminState_Label->setAlignment(Qt::AlignLeft);
            m_TOP_AdminState_Label->show();

            m_TOP_GuestName_Label = new QLabel(this);
            m_TOP_GuestName_Label->move(this->width() * 0.68, this->height() * 0.06);
            m_TOP_GuestName_Label->resize(this->width() * 0.2, this->height() * 0.04);
            m_TOP_GuestName_Label->setStyleSheet("QLabel { color: black; border: none; background: transparent; }");
            m_TOP_GuestName_Label->setFont(m_FirstFont);
            m_TOP_GuestName_Label->setAlignment(Qt::AlignLeft);
            m_TOP_GuestName_Label->hide();

            m_TOP_GuestState_Label = new QLabel(this);
            m_TOP_GuestState_Label->move(this->width() * 0.68, this->height() * 0.03);
            m_TOP_GuestState_Label->resize(this->width() * 0.12, this->height() * 0.03);
            m_TOP_GuestState_Label->setStyleSheet("QLabel { color: rgba(0,0,0,255); border: none; background: transparent; }");
            m_TOP_GuestState_Label->setFont(m_SecondFont);
            m_TOP_GuestState_Label->setAlignment(Qt::AlignLeft);
            m_TOP_GuestState_Label->hide();

            m_TOP_NewGuest_Button = new QToolButton(m_TOP_InfoBar_Widget);
            m_TOP_NewGuest_Button->move(m_TOP_InfoBar_Widget->width() * 0.62, m_TOP_InfoBar_Widget->height() * 0.1);
            m_TOP_NewGuest_Button->resize(m_TOP_InfoBar_Widget->width() * 0.2, m_TOP_InfoBar_Widget->height() * 0.8);
            m_TOP_NewGuest_Button->setText("Add Client");
            m_TOP_NewGuest_Button->setFont(m_FirstFont);
            m_TOP_NewGuest_Button->setStyleSheet("QToolButton { color: black; border: none; background-color: rgba(222, 236, 248, 255); border-radius: 10px; } QToolButton:hover {  }");
            m_TOP_NewGuest_Button->setCheckable(true);
            m_TOP_NewGuest_Button->show();
            connect(m_TOP_NewGuest_Button, &QToolButton::toggled, [=](bool checked) {
                if ((Is_DishDescription_Open == false) && (Is_SeatPlaceWidget_Open == false) && (Is_SettingsWidget_Open == false) && (Is_PaymentWidget_Open == false))
                {
                    if (checked)
                    {
                        m_RIGHT_ScrollArea_ScrollArea->hide();
                        m_RIGHT_Background_Widget->hide();

                        close_for_dishDescription(Dish_type);

                        m_TOP_NewGuest_Widget->show();

                        Is_NewGuestWidget_Open = true;
                    }
                    else
                    {
                        m_RIGHT_ScrollArea_ScrollArea->show();
                        m_RIGHT_Background_Widget->show();

                        show_for_dishDescription(Dish_type);

                        m_TOP_NewGuest_Widget->hide();

                        Is_NewGuestWidget_Open = false;
                    }
                }
                });
            // [ New Guest Widget ]
            {
                m_TOP_NewGuest_Widget = new QWidget(this);
                m_TOP_NewGuest_Widget->move(this->width() * 0.05, this->height() * 0.12);
                m_TOP_NewGuest_Widget->resize(this->width() * 0.90, this->height() * 0.85);
                m_TOP_NewGuest_Widget->setStyleSheet("QWidget { background-color: white }");
                m_TOP_NewGuest_Widget->hide();

                m_NewGuestLogin_Input = new QLineEdit(m_TOP_NewGuest_Widget);
                m_NewGuestLogin_Input->move(m_TOP_NewGuest_Widget->width() * 0.15, m_TOP_NewGuest_Widget->height() * 0.35);
                m_NewGuestLogin_Input->resize(m_TOP_NewGuest_Widget->width() * 0.22, m_TOP_NewGuest_Widget->height() * 0.07);
                m_NewGuestLogin_Input->setPlaceholderText("clients login");
                m_NewGuestLogin_Input->setAlignment(Qt::AlignCenter);
                m_NewGuestLogin_Input->setFont(m_FirstFont);
                m_NewGuestLogin_Input->setStyleSheet("QLineEdit { background-color: transparent; color: rgba(28, 29, 36, 210); border: none; border-bottom: 3px solid rgba(28, 29, 36, 210); font-size: 15px; } ");
                m_NewGuestLogin_Input->show();

                m_NewGuestFROMloginContinue = new QToolButton(m_TOP_NewGuest_Widget);
                m_NewGuestFROMloginContinue->move(m_TOP_NewGuest_Widget->width() * 0.15, m_TOP_NewGuest_Widget->height() * 0.44);
                m_NewGuestFROMloginContinue->resize(m_TOP_NewGuest_Widget->width() * 0.22, m_TOP_NewGuest_Widget->height() * 0.08);
                m_NewGuestFROMloginContinue->setStyleSheet("QToolButton { color: black; border: none; background-color: transparent; }"
                    "QToolButton:hover { background-color: rgba(28, 29, 36, 100); border-radius: 30px; border: 1px solid rgba(28, 29, 36, 255) } ");
                m_NewGuestFROMloginContinue->setFont(m_FirstFont);
                m_NewGuestFROMloginContinue->setText("Continue");
                m_NewGuestFROMloginContinue->show();
                connect(m_NewGuestFROMloginContinue, &QToolButton::clicked, [=]() {
                    g_Customer.name = m_NewGuestLogin_Input->text().toStdString();
                    if (g_Customer.name == "")
                    {
                        m_ErrorBox = new ErrorBox(m_TOP_NewGuest_Widget);
                        m_ErrorBox->setErrorText("ERROR\nNOT CORRECT USER LOGIN");
                        m_ErrorBox->move(m_TOP_NewGuest_Widget->width() * 0.30, m_TOP_NewGuest_Widget->height() * 0.26);
                        m_ErrorBox->resize(m_TOP_NewGuest_Widget->width() * 0.46, m_TOP_NewGuest_Widget->height() * 0.46);
                        m_ErrorBox->Init();
                        m_ErrorBox->show();
                    }
                    else
                    {
                        g_Customer.state = "customer";
                        m_TOP_NewGuest_Widget->hide();
                        m_TOP_NewGuest_Button->hide();
                        m_NewGuestLogin_Input->clear();
                        SetTop_Guest_Name_State();
                        m_TOP_GuestName_Label->show();
                        m_TOP_GuestState_Label->show();

                        m_RIGHT_ScrollArea_ScrollArea->show();
                        m_RIGHT_Background_Widget->show();
                        show_for_dishDescription(Dish_type);
                        m_TOP_NewGuest_Widget->hide();
                        Is_NewGuestWidget_Open = false;
                        Is_GuestRegisteredForOrder = true;

                        m_TOP_NewGuest_Button->click();
                    }
                    });

                m_NewGuestWITHOUTloginContinue = new QToolButton(m_TOP_NewGuest_Widget);
                m_NewGuestWITHOUTloginContinue->move(m_TOP_NewGuest_Widget->width() * 0.55, m_TOP_NewGuest_Widget->height() * 0.42);
                m_NewGuestWITHOUTloginContinue->resize(m_TOP_NewGuest_Widget->width() * 0.22, m_TOP_NewGuest_Widget->height() * 0.10);
                m_NewGuestWITHOUTloginContinue->setStyleSheet("QToolButton { color: black; border: none; background-color: transparent; }"
                    "QToolButton:hover { background-color: rgba(28, 29, 36, 100); border-radius: 30px; border: 1px solid rgba(28, 29, 36, 255) } ");
                m_NewGuestWITHOUTloginContinue->setFont(m_FirstFont);
                m_NewGuestWITHOUTloginContinue->setText("Continue without\nclient account");
                m_NewGuestWITHOUTloginContinue->show();
                connect(m_NewGuestWITHOUTloginContinue, &QToolButton::clicked, [=]() {
                    m_TOP_NewGuest_Widget->hide();
                    m_TOP_NewGuest_Button->hide();
                    g_Customer.name = "guest";
                    g_Customer.state = "customer";
                    SetTop_Guest_Name_State();
                    m_TOP_GuestName_Label->show();
                    m_TOP_GuestState_Label->show();

                    m_RIGHT_ScrollArea_ScrollArea->show();
                    m_RIGHT_Background_Widget->show();
                    show_for_dishDescription(Dish_type);
                    m_TOP_NewGuest_Widget->hide();
                    Is_NewGuestWidget_Open = false;
                    Is_GuestRegisteredForOrder = true;

                    m_TOP_NewGuest_Button->click();
                    });

            }

            m_TOP_Settings_Button = new QToolButton(m_TOP_InfoBar_Widget);
            m_TOP_Settings_Button->move(m_TOP_InfoBar_Widget->width() * 0.28, m_TOP_InfoBar_Widget->height() * 0.1);
            m_TOP_Settings_Button->setIconSize(QSize(40, 40));
            m_TOP_Settings_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
            m_TOP_Settings_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/settings.png"));
            m_TOP_Settings_Button->setCheckable(true);
            m_TOP_Settings_Button->show();
            connect(m_TOP_Settings_Button, &QToolButton::toggled, [=](bool checked) {
                if ((Is_DishDescription_Open == false) && (Is_SeatPlaceWidget_Open == false) && (Is_NewGuestWidget_Open == false) && (Is_PaymentWidget_Open == false))
                {
                    if (checked)
                    {
                        m_RIGHT_ScrollArea_ScrollArea->hide();
                        m_RIGHT_Background_Widget->hide();

                        close_for_dishDescription(Dish_type);

                        m_TOP_Settings_Widget->show();

                        Is_SettingsWidget_Open = true;
                    }
                    else
                    {
                        m_RIGHT_ScrollArea_ScrollArea->show();
                        m_RIGHT_Background_Widget->show();

                        show_for_dishDescription(Dish_type);

                        m_TOP_Settings_Widget->hide();

                        Is_SettingsWidget_Open = false;
                    }
                }
                });
            // [ Settings widget ]
            {
                m_TOP_Settings_Widget = new QWidget(this);
                m_TOP_Settings_Widget->move(this->width() * 0.05, this->height() * 0.12);
                m_TOP_Settings_Widget->resize(this->width() * 0.90, this->height() * 0.85);
                m_TOP_Settings_Widget->setStyleSheet("QWidget { background-color: white }");
                m_TOP_Settings_Widget->hide();

                m_SETTINGS_NewShift_Button = new QToolButton(m_TOP_Settings_Widget);
                m_SETTINGS_NewShift_Button->move(m_TOP_Settings_Widget->width() * 0.15, m_TOP_Settings_Widget->height() * 0.92);
                m_SETTINGS_NewShift_Button->resize(m_TOP_Settings_Widget->width() * 0.15, m_TOP_Settings_Widget->height() * 0.08);
                m_SETTINGS_NewShift_Button->setStyleSheet("QToolButton { color: white; border: none; border-radius: 30px; background-color: #f49454; padding-left: 10px; padding-right: 10px;  }"
                    "QToolButton:enabled { border-top: 3px solid rgba(200, 0, 0, 255); border-top-right-radius: 30px; }"
                    "QToolButton:hover { background-color: white; color: #f49454; } ");
                //m_NewOrderButton->setFont(m_HeaderFont);
                m_SETTINGS_NewShift_Button->setText("Your Shift");
                m_SETTINGS_NewShift_Button->show();
                connect(m_SETTINGS_NewShift_Button, &QToolButton::clicked, [=]() {
                    // �����
                    });

                m_SETTINGS_LogOut_Button = new QToolButton(m_TOP_Settings_Widget);
                m_SETTINGS_LogOut_Button->setIconSize(QSize(130, 130));
                m_SETTINGS_LogOut_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_SETTINGS_LogOut_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/back.png"));
                connect(m_SETTINGS_LogOut_Button, &QToolButton::clicked, [=]() {
                    emit Signal_LogOut();

                    m_TOP_Settings_Button->click();
                    });
            }

            m_TOP_GuestSeatPlace_Button = new QToolButton(m_TOP_InfoBar_Widget);
            m_TOP_GuestSeatPlace_Button->move(m_TOP_InfoBar_Widget->width() * 0.35, m_TOP_InfoBar_Widget->height() * 0.1);
            m_TOP_GuestSeatPlace_Button->resize(m_TOP_InfoBar_Widget->width() * 0.26, m_TOP_InfoBar_Widget->height() * 0.8);
            m_TOP_GuestSeatPlace_Button->setFont(m_FirstFont);
            set_GuestSeatPlace_Text(g_Customer.SeatPlace_id);                       // ID SEAT_PLACE
            m_TOP_GuestSeatPlace_Button->setStyleSheet("QToolButton { color: black; border: none; background-color: rgba(222, 236, 248, 255); border-radius: 10px; } QToolButton:hover {  }");
            m_TOP_GuestSeatPlace_Button->setCheckable(true);
            m_TOP_GuestSeatPlace_Button->show();
            connect(m_TOP_GuestSeatPlace_Button, &QToolButton::toggled, [=](bool checked) {
                if ((Is_DishDescription_Open == false) && (Is_SettingsWidget_Open == false) && (Is_NewGuestWidget_Open == false) && (Is_PaymentWidget_Open == false))
                {
                    if (checked)
                    {
                        m_RIGHT_ScrollArea_ScrollArea->hide();
                        m_RIGHT_Background_Widget->hide();

                        close_for_dishDescription(Dish_type);

                        m_TOP_SeatPlace_Widget->show();

                        Is_SeatPlaceWidget_Open = true;
                    }
                    else
                    {
                        m_RIGHT_ScrollArea_ScrollArea->show();
                        m_RIGHT_Background_Widget->show();

                        show_for_dishDescription(Dish_type);

                        m_TOP_SeatPlace_Widget->hide();

                        Is_SeatPlaceWidget_Open = false;
                    }
                }
                });
            // [ Seat palace choose widget ]
            {
                m_TOP_SeatPlace_Widget = new QWidget(this);
                m_TOP_SeatPlace_Widget->move(this->width() * 0.05, this->height() * 0.12);
                m_TOP_SeatPlace_Widget->resize(this->width() * 0.90, this->height() * 0.85);
                m_TOP_SeatPlace_Widget->setStyleSheet("QWidget { background-color: white }");
                m_TOP_SeatPlace_Widget->hide();
            }
        }

        // [ Left Menu ]
        {
            m_left_MAINBackWidget = new QWidget(this);
            m_left_MAINBackWidget->setStyleSheet("QWidget { background: transparent; border-radius: 10px; }");
            m_left_MAINBackWidget->move(this->width() * 0.009, this->height() * 0.11);
            m_left_MAINBackWidget->resize(this->width() * 0.55, this->height() * 0.88);
            m_left_MAINBackWidget->show();

            m_left_DeleteGuest_Button = new QToolButton(m_left_MAINBackWidget);
            m_left_DeleteGuest_Button->move(m_left_MAINBackWidget->width() * 0.02, m_left_MAINBackWidget->height() * 0.91);
            m_left_DeleteGuest_Button->resize(m_left_MAINBackWidget->width() * 0.2, m_left_MAINBackWidget->height() * 0.08);
            m_left_DeleteGuest_Button->setText("Delete Guest");
            m_left_DeleteGuest_Button->setStyleSheet("QToolButton { color: white; background-color: rgba(137, 65, 218, 255); border-radius: 10px; }");
            m_left_DeleteGuest_Button->show();
            connect(m_left_DeleteGuest_Button, &QToolButton::clicked, [=]() {
                m_TOP_GuestName_Label->hide();
                m_TOP_GuestState_Label->hide();
                m_TOP_NewGuest_Button->show();
                g_Customer.name = "";
                g_Customer.state = "";

                Is_GuestRegisteredForOrder = false;
                });

            // [ Dish Description ]
            {
                m_DishDescription_Widget = new QWidget(this);
                m_DishDescription_Widget->move(this->width() * 0.009, this->height() * 0.11);
                m_DishDescription_Widget->resize(this->width() * 0.55, this->height() * 0.80);
                m_DishDescription_Widget->setStyleSheet("QWidget { background: transparent; } ");
                m_DishDescription_Widget->hide();

                m_DishDescription_AddButton = new QToolButton(m_DishDescription_Widget);
                m_DishDescription_AddButton->move(m_DishDescription_Widget->width() * 0.02, m_DishDescription_Widget->height() * 0.89);
                m_DishDescription_AddButton->resize(m_DishDescription_Widget->width() * 0.96, m_DishDescription_Widget->height() * 0.1);
                m_DishDescription_AddButton->setText("ADD TO ORDER");
                m_DishDescription_AddButton->setStyleSheet("QToolButton { background-color: #f49454; border-radius: 10px; font-color: white; }");
                m_DishDescription_AddButton->show();
                connect(m_DishDescription_AddButton, &QToolButton::clicked, [=]() {
                    if (Is_GuestRegisteredForOrder == false)
                    {
                        m_ErrorBox = new ErrorBox(this);
                        m_ErrorBox->setErrorText("ERROR\nClient not added\nAdd New Client");
                        m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
                        m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
                        m_ErrorBox->Init();
                        m_ErrorBox->show();
                    }
                    else
                    {
                        addRow(Dish_id);

                        Is_DishDescription_Open = false;

                        m_DishDescription_Widget->hide();
                        show_for_dishDescription(Dish_type);
                        Dish_id = 0;
                    }
                    });

                m_DishDescription_ShowToCustomerButton = new QToolButton(m_DishDescription_Widget);
                m_DishDescription_ShowToCustomerButton->move(m_DishDescription_Widget->width() * 0.02, m_DishDescription_Widget->height() * 0.78);
                m_DishDescription_ShowToCustomerButton->resize(m_DishDescription_Widget->width() * 0.5, m_DishDescription_Widget->height() * 0.1);
                m_DishDescription_ShowToCustomerButton->setText("SHOW TO CUSTOMER");
                m_DishDescription_ShowToCustomerButton->setStyleSheet("QToolButton { background-color: #f49454; border-radius: 10px; font-color: white; }");
                m_DishDescription_ShowToCustomerButton->show();
                connect(m_DishDescription_ShowToCustomerButton, &QToolButton::clicked, [=]() {
                    //  ������� �� ������� �������� ������

                    });

                m_DishDescription_CloseButton = new QToolButton(m_DishDescription_Widget);
                m_DishDescription_CloseButton->move(m_DishDescription_Widget->width() * 0.92, m_DishDescription_Widget->height() * 0.01);
                m_DishDescription_CloseButton->setIconSize(QSize(30, 30));
                m_DishDescription_CloseButton->setIcon(QIcon(":/UIUX/UIUX/Pictures/exit_button.png"));
                m_DishDescription_CloseButton->setStyleSheet("QToolButton { background: transparent; } ");
                m_DishDescription_CloseButton->show();
                connect(m_DishDescription_CloseButton, &QToolButton::clicked, [=]() {
                    Is_DishDescription_Open = false;

                    m_DishDescription_Widget->hide();
                    show_for_dishDescription(Dish_type);
                    Dish_id = 0;
                    });

                m_DishDescription_DishPicture = new QToolButton(m_DishDescription_Widget);
                m_DishDescription_DishPicture->move(m_DishDescription_Widget->width() * 0.02, m_DishDescription_Widget->height() * 0.02);
                m_DishDescription_DishPicture->setIconSize(QSize(300, 300));
                m_DishDescription_DishPicture->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_DishDescription_DishPicture->show();

                m_DishDescription_DishName = new QLabel(m_DishDescription_Widget);
                m_DishDescription_DishName->move(m_DishDescription_Widget->width() * 0.6, m_DishDescription_Widget->height() * 0.14);
                m_DishDescription_DishName->resize(m_DishDescription_Widget->width() * 0.38, m_DishDescription_Widget->height() * 0.06);
                m_DishDescription_DishName->setStyleSheet(" QLabel { background: transparent; } ");
                m_DishDescription_DishName->setFont(m_FirstFont);
                m_DishDescription_DishName->show();

                m_DishDescription_DishIngredients = new QLabel(m_DishDescription_Widget);
                m_DishDescription_DishIngredients->move(m_DishDescription_Widget->width() * 0.6, m_DishDescription_Widget->height() * 0.2);
                m_DishDescription_DishIngredients->resize(m_DishDescription_Widget->width() * 0.38, m_DishDescription_Widget->height() * 0.6);
                m_DishDescription_DishIngredients->setStyleSheet(" QLabel { background: transparent; } ");
                m_DishDescription_DishIngredients->setAlignment(Qt::AlignTop);
                m_DishDescription_DishIngredients->setFont(m_SecondFont);
                m_DishDescription_DishIngredients->show();
            }
            
            // [ MAIN Type Dishes]
            {
                m_left_MAINGridLayout = new QGridLayout(m_left_MAINBackWidget);

                m_left_MAINBackWidget->setLayout(m_left_MAINGridLayout);

                // ���������������� ���������� ����� ��������/���������
                m_left_MAINGridLayout->setRowStretch(0, 1);
                m_left_MAINGridLayout->setColumnStretch(0, 1);

                m_left_MAINGridLayout->setRowMinimumHeight(0, 150);
                m_left_MAINGridLayout->setRowMinimumHeight(1, 150);
                m_left_MAINGridLayout->setRowMinimumHeight(2, 150);
                m_left_MAINGridLayout->setRowMinimumHeight(3, 150);
                m_left_MAINGridLayout->setColumnMinimumWidth(0, 100);
                m_left_MAINGridLayout->setColumnMinimumWidth(1, 100);
                m_left_MAINGridLayout->setColumnMinimumWidth(2, 100);
                m_left_MAINGridLayout->setColumnMinimumWidth(3, 100);

                m_dishType1 = new QToolButton(this);
                m_dishType1->setIconSize(QSize(130, 130));
                m_dishType1->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_dishType1->setIcon(QIcon(":/UIUX/UIUX/Pictures/a.png"));
                m_left_MAINGridLayout->setContentsMargins(0, 0, 0, 0);
                m_left_MAINGridLayout->addWidget(m_dishType1, 0, 0);
                connect(m_dishType1, &QToolButton::clicked, [=]() {
                    Dish_type = 1;

                    m_left_MAINBackWidget->hide();
                    m_left_1_TypeBackWidget->show();
                    });
                // [ Type 1 Dishes ]
                {
                    m_left_1_TypeBackWidget = new QWidget(this);
                    m_left_1_TypeBackWidget->setStyleSheet("QWidget { background: transparent; border-radius: 10px; }");
                    m_left_1_TypeBackWidget->move(this->width() * 0.009, this->height() * 0.11);
                    m_left_1_TypeBackWidget->resize(this->width() * 0.55, this->height() * 0.80);
                    m_left_1_TypeBackWidget->hide();

                    m_left_1_TypeGridLayout = new QGridLayout(this);

                    m_left_1_TypeBackWidget->setLayout(m_left_1_TypeGridLayout);

                    // ���������������� ���������� ����� ��������/���������
                    m_left_1_TypeGridLayout->setRowStretch(0, 1);
                    m_left_1_TypeGridLayout->setColumnStretch(0, 1);

                    m_left_1_TypeGridLayout->setRowMinimumHeight(0, 150);
                    m_left_1_TypeGridLayout->setRowMinimumHeight(1, 150);
                    m_left_1_TypeGridLayout->setRowMinimumHeight(2, 150);
                    m_left_1_TypeGridLayout->setRowMinimumHeight(3, 150);
                    m_left_1_TypeGridLayout->setColumnMinimumWidth(0, 100);
                    m_left_1_TypeGridLayout->setColumnMinimumWidth(1, 100);
                    m_left_1_TypeGridLayout->setColumnMinimumWidth(2, 100);
                    m_left_1_TypeGridLayout->setColumnMinimumWidth(3, 100);

                    m_dishType1_1 = new QToolButton(this);
                    m_dishType1_1->setIconSize(QSize(130, 130));
                    m_dishType1_1->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType1_1->setIcon(QIcon(":/UIUX/UIUX/Pictures/settings.png"));
                    m_left_1_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_1_TypeGridLayout->addWidget(m_dishType1_1, 0, 0);
                    connect(m_dishType1_1, &QToolButton::clicked, [=]() {
                        Dish_id = 1;                            // ��� ����� - 1
                        m_DishDescription_Widget->show();       // ������� �������� �����
                        set_DishOptions(Dish_id);               // ��������� �������� � �������� ����� 
                        close_for_dishDescription(Dish_type);   // ������� ��� ��� ���� �� ���� 
                        Is_DishDescription_Open = true;         // ������� ��������

                        });

                    m_dishType1_2 = new QToolButton(this);
                    m_dishType1_2->setIconSize(QSize(130, 130));
                    m_dishType1_2->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType1_2->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_1_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_1_TypeGridLayout->addWidget(m_dishType1_2, 0, 1);
                    connect(m_dishType1_2, &QToolButton::clicked, [=]() {
                        Dish_id = 2;                            // ��� ����� - 2
                        m_DishDescription_Widget->show();       // ������� �������� �����
                        set_DishOptions(Dish_id);               // ��������� �������� � �������� ����� 
                        close_for_dishDescription(Dish_type);   // ������� ��� ��� ���� �� ���� 
                        Is_DishDescription_Open = true;         // ������� ��������

                        });

                    m_dishType1_3 = new QToolButton(this);
                    m_dishType1_3->setIconSize(QSize(130, 130));
                    m_dishType1_3->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType1_3->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_1_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_1_TypeGridLayout->addWidget(m_dishType1_3, 0, 2);
                    connect(m_dishType1_3, &QToolButton::clicked, [=]() {
                        Dish_id = 3;                            // ��� ����� - 3
                        m_DishDescription_Widget->show();       // ������� �������� �����
                        set_DishOptions(Dish_id);               // ��������� �������� � �������� ����� 
                        close_for_dishDescription(Dish_type);   // ������� ��� ��� ���� �� ���� 
                        Is_DishDescription_Open = true;         // ������� ��������

                        });

                    // ������ ��������
                    m_dishType1_BACK_Button = new QToolButton(this);
                    m_dishType1_BACK_Button->setIconSize(QSize(130, 130));
                    m_dishType1_BACK_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType1_BACK_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/back.png"));
                    m_left_1_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_1_TypeGridLayout->addWidget(m_dishType1_BACK_Button, 0, 3);
                    connect(m_dishType1_BACK_Button, &QToolButton::clicked, [=]() {
                        close_for_dishDescription(Dish_type);   // ������� ��� ��� ���� �� ����
                        m_left_MAINBackWidget->show();          // �������� ������� ���� ���� 
                        Dish_type = 0;                          // ��� ����� = 0
                        });
                }

                m_dishType2 = new QToolButton(this);
                m_dishType2->setIconSize(QSize(130, 130));
                m_dishType2->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_dishType2->setIcon(QIcon(":/UIUX/UIUX/Pictures/b.png"));
                m_left_MAINGridLayout->setContentsMargins(0, 0, 0, 0);
                m_left_MAINGridLayout->addWidget(m_dishType2, 0, 1);
                connect(m_dishType2, &QToolButton::clicked, [=]() {
                    Dish_type = 2;

                    m_left_MAINBackWidget->hide();
                    m_left_2_TypeBackWidget->show();
                    });
                // [ Type 2 Dishes ]
                {
                    m_left_2_TypeBackWidget = new QWidget(this);
                    m_left_2_TypeBackWidget->setStyleSheet("QWidget { background: transparent; border-radius: 10px; }");
                    m_left_2_TypeBackWidget->move(this->width() * 0.009, this->height() * 0.11);
                    m_left_2_TypeBackWidget->resize(this->width() * 0.55, this->height() * 0.80);
                    m_left_2_TypeBackWidget->hide();

                    m_left_2_TypeGridLayout = new QGridLayout(this);

                    m_left_2_TypeBackWidget->setLayout(m_left_2_TypeGridLayout);

                    // ���������������� ���������� ����� ��������/���������
                    m_left_2_TypeGridLayout->setRowStretch(0, 1);
                    m_left_2_TypeGridLayout->setColumnStretch(0, 1);

                    m_left_2_TypeGridLayout->setRowMinimumHeight(0, 150);
                    m_left_2_TypeGridLayout->setRowMinimumHeight(1, 150);
                    m_left_2_TypeGridLayout->setRowMinimumHeight(2, 150);
                    m_left_2_TypeGridLayout->setRowMinimumHeight(3, 150);
                    m_left_2_TypeGridLayout->setColumnMinimumWidth(0, 100);
                    m_left_2_TypeGridLayout->setColumnMinimumWidth(1, 100);
                    m_left_2_TypeGridLayout->setColumnMinimumWidth(2, 100);
                    m_left_2_TypeGridLayout->setColumnMinimumWidth(3, 100);

                    m_dishType2_1 = new QToolButton(this);
                    m_dishType2_1->setIconSize(QSize(130, 130));
                    m_dishType2_1->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType2_1->setIcon(QIcon(":/UIUX/UIUX/Pictures/exit_button.png"));
                    m_left_2_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_2_TypeGridLayout->addWidget(m_dishType2_1, 0, 0);
                    connect(m_dishType2_1, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);
                        });

                    m_dishType2_2 = new QToolButton(this);
                    m_dishType2_2->setIconSize(QSize(130, 130));
                    m_dishType2_2->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType2_2->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_2_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_2_TypeGridLayout->addWidget(m_dishType2_2, 0, 1);
                    connect(m_dishType2_2, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);
                        });

                    m_dishType2_3 = new QToolButton(this);
                    m_dishType2_3->setIconSize(QSize(130, 130));
                    m_dishType2_3->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType2_3->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_2_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_2_TypeGridLayout->addWidget(m_dishType2_3, 0, 2);
                    connect(m_dishType2_3, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);
                        });

                    // ������ �������� 
                    m_dishType2_BACK_Button = new QToolButton(this);
                    m_dishType2_BACK_Button->setIconSize(QSize(130, 130));
                    m_dishType2_BACK_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType2_BACK_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/back.png"));
                    m_left_2_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_2_TypeGridLayout->addWidget(m_dishType2_BACK_Button, 0, 3);
                    connect(m_dishType2_BACK_Button, &QToolButton::clicked, [=]() {

                        m_left_2_TypeBackWidget->hide();
                        m_left_MAINBackWidget->show();

                        Dish_type = 0;
                        });
                }

                m_dishType3 = new QToolButton(this);
                m_dishType3->setIconSize(QSize(130, 130));
                m_dishType3->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_dishType3->setIcon(QIcon(":/UIUX/UIUX/Pictures/c.png"));
                m_left_MAINGridLayout->setContentsMargins(0, 0, 0, 0);
                m_left_MAINGridLayout->addWidget(m_dishType3, 0, 2);
                connect(m_dishType3, &QToolButton::clicked, [=]() {
                    Dish_type = 3;

                    m_left_MAINBackWidget->hide();
                    m_left_3_TypeBackWidget->show();
                    });
                // [ Type 3 Dishes ]
                {
                    m_left_3_TypeBackWidget = new QWidget(this);
                    m_left_3_TypeBackWidget->setStyleSheet("QWidget { background: transparent; border-radius: 10px; }");
                    m_left_3_TypeBackWidget->move(this->width() * 0.009, this->height() * 0.11);
                    m_left_3_TypeBackWidget->resize(this->width() * 0.55, this->height() * 0.80);
                    m_left_3_TypeBackWidget->hide();

                    m_left_3_TypeGridLayout = new QGridLayout(this);

                    m_left_3_TypeBackWidget->setLayout(m_left_3_TypeGridLayout);

                    // ���������������� ���������� ����� ��������/���������
                    m_left_3_TypeGridLayout->setRowStretch(0, 1);
                    m_left_3_TypeGridLayout->setColumnStretch(0, 1);

                    m_left_3_TypeGridLayout->setRowMinimumHeight(0, 150);
                    m_left_3_TypeGridLayout->setRowMinimumHeight(1, 150);
                    m_left_3_TypeGridLayout->setRowMinimumHeight(2, 150);
                    m_left_3_TypeGridLayout->setRowMinimumHeight(3, 150);
                    m_left_3_TypeGridLayout->setColumnMinimumWidth(0, 100);
                    m_left_3_TypeGridLayout->setColumnMinimumWidth(1, 100);
                    m_left_3_TypeGridLayout->setColumnMinimumWidth(2, 100);
                    m_left_3_TypeGridLayout->setColumnMinimumWidth(3, 100);


                    m_dishType3_1 = new QToolButton(this);
                    m_dishType3_1->setIconSize(QSize(130, 130));
                    m_dishType3_1->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType3_1->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_3_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_3_TypeGridLayout->addWidget(m_dishType3_1, 0, 0);
                    connect(m_dishType3_1, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });


                    m_dishType3_2 = new QToolButton(this);
                    m_dishType3_2->setIconSize(QSize(130, 130));
                    m_dishType3_2->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType3_2->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_3_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_3_TypeGridLayout->addWidget(m_dishType3_2, 0, 1);
                    connect(m_dishType3_2, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });

                    m_dishType3_3 = new QToolButton(this);
                    m_dishType3_3->setIconSize(QSize(130, 130));
                    m_dishType3_3->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType3_3->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_3_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_3_TypeGridLayout->addWidget(m_dishType3_3, 0, 2);
                    connect(m_dishType3_3, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });

                    m_dishType3_BACK_Button = new QToolButton(this);
                    m_dishType3_BACK_Button->setIconSize(QSize(130, 130));
                    m_dishType3_BACK_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType3_BACK_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/back.png"));
                    m_left_3_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_3_TypeGridLayout->addWidget(m_dishType3_BACK_Button, 0, 3);
                    connect(m_dishType3_BACK_Button, &QToolButton::clicked, [=]() {

                        m_left_3_TypeBackWidget->hide();
                        m_left_MAINBackWidget->show();
                        Dish_type = 0;
                        });


                }

                m_dishType4 = new QToolButton(this);
                m_dishType4->setIconSize(QSize(130, 130));
                m_dishType4->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_dishType4->setIcon(QIcon(":/UIUX/UIUX/Pictures/d.png"));
                m_left_MAINGridLayout->setContentsMargins(0, 0, 0, 0);
                m_left_MAINGridLayout->addWidget(m_dishType4, 0, 3);
                connect(m_dishType4, &QToolButton::clicked, [=]() {
                    Dish_type = 4;

                    m_left_MAINBackWidget->hide();
                    m_left_4_TypeBackWidget->show();
                    });
                // [ Type 4 Dishes ]
                {
                    m_left_4_TypeBackWidget = new QWidget(this);
                    m_left_4_TypeBackWidget->setStyleSheet("QWidget { background: transparent; border-radius: 10px; }");
                    m_left_4_TypeBackWidget->move(this->width() * 0.009, this->height() * 0.11);
                    m_left_4_TypeBackWidget->resize(this->width() * 0.55, this->height() * 0.80);
                    m_left_4_TypeBackWidget->hide();


                    m_left_4_TypeGridLayout = new QGridLayout(this);

                    m_left_4_TypeBackWidget->setLayout(m_left_4_TypeGridLayout);

                    // ���������������� ���������� ����� ��������/���������
                    m_left_4_TypeGridLayout->setRowStretch(0, 1);
                    m_left_4_TypeGridLayout->setColumnStretch(0, 1);

                    m_left_4_TypeGridLayout->setRowMinimumHeight(0, 150);
                    m_left_4_TypeGridLayout->setRowMinimumHeight(1, 150);
                    m_left_4_TypeGridLayout->setRowMinimumHeight(2, 150);
                    m_left_4_TypeGridLayout->setRowMinimumHeight(3, 150);
                    m_left_4_TypeGridLayout->setColumnMinimumWidth(0, 100);
                    m_left_4_TypeGridLayout->setColumnMinimumWidth(1, 100);
                    m_left_4_TypeGridLayout->setColumnMinimumWidth(2, 100);
                    m_left_4_TypeGridLayout->setColumnMinimumWidth(3, 100);


                    m_dishType4_1 = new QToolButton(this);
                    m_dishType4_1->setIconSize(QSize(130, 130));
                    m_dishType4_1->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType4_1->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_4_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_4_TypeGridLayout->addWidget(m_dishType4_1, 0, 0);
                    connect(m_dishType4_1, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });


                    m_dishType4_2 = new QToolButton(this);
                    m_dishType4_2->setIconSize(QSize(130, 130));
                    m_dishType4_2->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType4_2->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_4_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_4_TypeGridLayout->addWidget(m_dishType4_2, 0, 1);
                    connect(m_dishType4_2, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });

                    m_dishType4_3 = new QToolButton(this);
                    m_dishType4_3->setIconSize(QSize(130, 130));
                    m_dishType4_3->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType4_3->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_4_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_4_TypeGridLayout->addWidget(m_dishType4_3, 0, 2);
                    connect(m_dishType4_3, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });

                    m_dishType4_BACK_Button = new QToolButton(this);
                    m_dishType4_BACK_Button->setIconSize(QSize(130, 130));
                    m_dishType4_BACK_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType4_BACK_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/back.png"));
                    m_left_4_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_4_TypeGridLayout->addWidget(m_dishType4_BACK_Button, 0, 3);
                    connect(m_dishType4_BACK_Button, &QToolButton::clicked, [=]() {

                        m_left_4_TypeBackWidget->hide();
                        m_left_MAINBackWidget->show();

                        Dish_type = 0;
                        });


                }

                m_dishType5 = new QToolButton(this);
                m_dishType5->setIconSize(QSize(130, 130));
                m_dishType5->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                m_dishType5->setIcon(QIcon(":/UIUX/UIUX/Pictures/e.png"));
                m_left_MAINGridLayout->setContentsMargins(0, 0, 0, 0);
                m_left_MAINGridLayout->addWidget(m_dishType5, 1, 0);
                connect(m_dishType5, &QToolButton::clicked, [=]() {
                    Dish_type = 5;

                    m_left_MAINBackWidget->hide();
                    m_left_5_TypeBackWidget->show();
                    });
                // [ Type 5 Dishes ]
                {
                    m_left_5_TypeBackWidget = new QWidget(this);
                    m_left_5_TypeBackWidget->setStyleSheet("QWidget { background: transparent; border-radius: 10px; }");
                    m_left_5_TypeBackWidget->move(this->width() * 0.009, this->height() * 0.11);
                    m_left_5_TypeBackWidget->resize(this->width() * 0.55, this->height() * 0.80);
                    m_left_5_TypeBackWidget->hide();


                    m_left_5_TypeGridLayout = new QGridLayout(this);

                    m_left_5_TypeBackWidget->setLayout(m_left_5_TypeGridLayout);

                    // ���������������� ���������� ����� ��������/���������
                    m_left_5_TypeGridLayout->setRowStretch(0, 1);
                    m_left_5_TypeGridLayout->setColumnStretch(0, 1);

                    m_left_5_TypeGridLayout->setRowMinimumHeight(0, 150);
                    m_left_5_TypeGridLayout->setRowMinimumHeight(1, 150);
                    m_left_5_TypeGridLayout->setRowMinimumHeight(2, 150);
                    m_left_5_TypeGridLayout->setRowMinimumHeight(3, 150);
                    m_left_5_TypeGridLayout->setColumnMinimumWidth(0, 100);
                    m_left_5_TypeGridLayout->setColumnMinimumWidth(1, 100);
                    m_left_5_TypeGridLayout->setColumnMinimumWidth(2, 100);
                    m_left_5_TypeGridLayout->setColumnMinimumWidth(3, 100);


                    m_dishType5_1 = new QToolButton(this);
                    m_dishType5_1->setIconSize(QSize(130, 130));
                    m_dishType5_1->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType5_1->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_5_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_5_TypeGridLayout->addWidget(m_dishType5_1, 0, 0);
                    connect(m_dishType5_1, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });


                    m_dishType5_2 = new QToolButton(this);
                    m_dishType5_2->setIconSize(QSize(130, 130));
                    m_dishType5_2->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType5_2->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_5_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_5_TypeGridLayout->addWidget(m_dishType5_2, 0, 1);
                    connect(m_dishType5_2, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });

                    m_dishType5_3 = new QToolButton(this);
                    m_dishType5_3->setIconSize(QSize(130, 130));
                    m_dishType5_3->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType5_3->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
                    m_left_5_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_5_TypeGridLayout->addWidget(m_dishType5_3, 0, 2);
                    connect(m_dishType5_3, &QToolButton::clicked, [=]() {
                        Is_DishDescription_Open = true;

                        m_DishDescription_Widget->show();
                        close_for_dishDescription(Dish_type);

                        });

                    m_dishType5_BACK_Button = new QToolButton(this);
                    m_dishType5_BACK_Button->setIconSize(QSize(130, 130));
                    m_dishType5_BACK_Button->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
                    m_dishType5_BACK_Button->setIcon(QIcon(":/UIUX/UIUX/Pictures/back.png"));
                    m_left_5_TypeGridLayout->setContentsMargins(0, 0, 0, 0);
                    m_left_5_TypeGridLayout->addWidget(m_dishType5_BACK_Button, 0, 3);
                    connect(m_dishType5_BACK_Button, &QToolButton::clicked, [=]() {

                        m_left_5_TypeBackWidget->hide();
                        m_left_MAINBackWidget->show();

                        Dish_type = 0;
                        });


                }
            }            
        }

        

        // [ Right Order List ]
        {
            // [ Payment (Left) Widget ]
            {
                m_PAYMENT_Background_Widget = new QWidget(this);
                m_PAYMENT_Background_Widget->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 100); border-radius: 10px; }");
                m_PAYMENT_Background_Widget->move(this->width() * 0.009, this->height() * 0.11);
                m_PAYMENT_Background_Widget->resize(this->width() * 0.55, this->height() * 0.88);
                m_PAYMENT_Background_Widget->hide();

                m_PAYMENT_Discount_Box = new QComboBox(m_PAYMENT_Background_Widget);
                m_PAYMENT_Discount_Box->move(m_PAYMENT_Background_Widget->width() * 0.02, m_PAYMENT_Background_Widget->height() * 0.38);
                m_PAYMENT_Discount_Box->resize(m_PAYMENT_Background_Widget->width() * 0.3, m_PAYMENT_Background_Widget->height() * 0.06);
                m_PAYMENT_Discount_Box->setStyleSheet("QComboBox { border: none; border-radius: 0px; }" 
                                                      "QComboBox::drop-down { border: none; border-radius: 0px; }");
                m_PAYMENT_Discount_Box->addItem("None");
                m_PAYMENT_Discount_Box->addItem("Write down order");
                m_PAYMENT_Discount_Box->addItem("At the expense of Rest");
                m_PAYMENT_Discount_Box->setCurrentIndex(0);
                connect(m_PAYMENT_Discount_Box, QOverload<int>::of(&QComboBox::activated), [=](int index) {
                    switch (index)
                    {
                    case 0:
                    {
                        g_Order.discount_type_ = "None";
                    }
                    break;
                    case 1:
                    {
                        g_Order.discount_type_ = "Write down order";
                    }
                    break;
                    case 2:
                    {
                        g_Order.discount_type_ = "At the expense of Rest";
                    }
                    break;
                    }
                    });
                
                m_PAYMENT_Discount_text = new QLabel(m_PAYMENT_Background_Widget);
                m_PAYMENT_Discount_text->move(m_PAYMENT_Background_Widget->width() * 0.02, m_PAYMENT_Background_Widget->height() * 0.32);
                m_PAYMENT_Discount_text->resize(m_PAYMENT_Background_Widget->width() * 0.16, m_PAYMENT_Background_Widget->height() * 0.04);
                m_PAYMENT_Discount_text->setAlignment(Qt::AlignCenter);
                m_PAYMENT_Discount_text->setText(QString("Discount"));
                m_PAYMENT_Discount_text->setFont(m_FirstFont);
                m_PAYMENT_Discount_text->setStyleSheet("QLabel { color: black; background-color: transparent; }");
                
                m_PAYMENT_TotalSumma_text = new QLabel(m_PAYMENT_Background_Widget);
                m_PAYMENT_TotalSumma_text->move(m_PAYMENT_Background_Widget->width() * 0.02, m_PAYMENT_Background_Widget->height() * 0.02);
                m_PAYMENT_TotalSumma_text->resize(m_PAYMENT_Background_Widget->width() * 0.16, m_PAYMENT_Background_Widget->height() * 0.04);
                m_PAYMENT_TotalSumma_text->setAlignment(Qt::AlignCenter);
                m_PAYMENT_TotalSumma_text->setText(QString("Summa"));
                m_PAYMENT_TotalSumma_text->setFont(m_FirstFont);
                m_PAYMENT_TotalSumma_text->setStyleSheet("QLabel { color: black; background-color: transparent; }");

                m_PAYMENT_TotalSumma_Label = new QLabel(m_PAYMENT_Background_Widget);
                m_PAYMENT_TotalSumma_Label->move(m_PAYMENT_Background_Widget->width() * 0.02, m_PAYMENT_Background_Widget->height() * 0.08);
                m_PAYMENT_TotalSumma_Label->resize(m_PAYMENT_Background_Widget->width() * 0.36, m_PAYMENT_Background_Widget->height() * 0.1);
                m_PAYMENT_TotalSumma_Label->setAlignment(Qt::AlignCenter);
                m_PAYMENT_TotalSumma_Label->setStyleSheet("QLabel { color: black; background-color: white; }" );
                
                m_PAYMMENT_OutputMoney = new QLabel(m_PAYMENT_Background_Widget);
                m_PAYMMENT_OutputMoney->move(m_PAYMENT_Background_Widget->width() * 0.26, m_PAYMENT_Background_Widget->height() * 0.20);
                m_PAYMMENT_OutputMoney->resize(m_PAYMENT_Background_Widget->width() * 0.22, m_PAYMENT_Background_Widget->height() * 0.08);
                m_PAYMMENT_OutputMoney->setAlignment(Qt::AlignCenter);
                m_PAYMMENT_OutputMoney->setStyleSheet("QLineEdit { color: black; background-color: white; }");

                m_PAYMENT_InputMoney = new QLineEdit(m_PAYMENT_Background_Widget);
                m_PAYMENT_InputMoney->move(m_PAYMENT_Background_Widget->width() * 0.02, m_PAYMENT_Background_Widget->height() * 0.20);
                m_PAYMENT_InputMoney->resize(m_PAYMENT_Background_Widget->width() * 0.22, m_PAYMENT_Background_Widget->height() * 0.08);
                m_PAYMENT_InputMoney->setAlignment(Qt::AlignCenter);
                m_PAYMENT_InputMoney->setPlaceholderText("Input Cash");
                m_PAYMENT_InputMoney->setStyleSheet("QLineEdit { color: black; background-color: white; }");
                connect(m_PAYMENT_InputMoney, &QLineEdit::textEdited, [=]() {
                    double input_amount = m_PAYMENT_InputMoney->text().toDouble();
                    double ans = g_Order.summa_ - input_amount;

                    m_PAYMMENT_OutputMoney->setText(QString::number(ans));
                    });

                m_PAYMENT_CashOrCardMethod = new QToolButton(m_PAYMENT_Background_Widget);
                m_PAYMENT_CashOrCardMethod->move(m_PAYMENT_Background_Widget->width() * 0.40, m_PAYMENT_Background_Widget->height() * 0.08);
                m_PAYMENT_CashOrCardMethod->setIconSize(QSize(60, 60));
                m_PAYMENT_CashOrCardMethod->setIcon(QIcon(":/UIUX/UIUX/Pictures/cash.png"));
                g_Order.way_to_pay_ = "cash";
                m_PAYMENT_CashOrCardMethod->setStyleSheet("QToolButton { background: transparent; } ");
                connect(m_PAYMENT_CashOrCardMethod, &QToolButton::clicked, [=]() {
                    static int count = 0;
                    count++;
                    if (count % 2 == 0)
                    {
                        m_PAYMENT_CashOrCardMethod->setIcon(QIcon(":/UIUX/UIUX/Pictures/cash.png"));
                        g_Order.way_to_pay_ = "cash";
                        m_PAYMMENT_OutputMoney->show();
                    }
                    else
                    {
                        m_PAYMENT_CashOrCardMethod->setIcon(QIcon(":/UIUX/UIUX/Pictures/card.png"));
                        g_Order.way_to_pay_ = "card";
                        m_PAYMMENT_OutputMoney->hide();
                    }
                    });
                
                m_PAYMENT_AdditionalComment = new QTextEdit(m_PAYMENT_Background_Widget);
                m_PAYMENT_AdditionalComment->move(m_PAYMENT_Background_Widget->width() * 0.54, m_PAYMENT_Background_Widget->height() * 0.06);
                m_PAYMENT_AdditionalComment->resize(m_PAYMENT_Background_Widget->width() * 0.45, m_PAYMENT_Background_Widget->height() * 0.25);
                m_PAYMENT_AdditionalComment->setAlignment(Qt::AlignCenter);
                m_PAYMENT_AdditionalComment->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
                m_PAYMENT_AdditionalComment->setPlaceholderText("Write Additional Comment for Order");
                m_PAYMENT_AdditionalComment->setStyleSheet("QLineEdit { color: black; background-color: white; }");

                m_PAYMENT_PayedTrue_Button = new QToolButton(m_PAYMENT_Background_Widget);
                m_PAYMENT_PayedTrue_Button->move(m_PAYMENT_Background_Widget->width() * 0.24, m_PAYMENT_Background_Widget->height() * 0.91);
                m_PAYMENT_PayedTrue_Button->resize(m_PAYMENT_Background_Widget->width() * 0.4, m_PAYMENT_Background_Widget->height() * 0.08);
                m_PAYMENT_PayedTrue_Button->setText("NOT Paid");
                m_PAYMENT_PayedTrue_Button->setStyleSheet("QToolButton { color: white; background-color: red; border-radius: 10px; }");
                m_PAYMENT_PayedTrue_Button->setCheckable(true);               
                connect(m_PAYMENT_PayedTrue_Button, &QToolButton::toggled, [=](bool checked) {
                    if (checked)
                    {
                        m_PAYMENT_PayedTrue_Button->setText("Paid");
                        m_PAYMENT_PayedTrue_Button->setStyleSheet("QToolButton { color: white; background-color: green; border-radius: 10px; }");
                        Is_OrderPaidOkay = true;
                    }
                    else
                    {
                        m_PAYMENT_PayedTrue_Button->setText("NOT Paid");
                        m_PAYMENT_PayedTrue_Button->setStyleSheet("QToolButton { color: white; background-color: red; border-radius: 10px; }");
                        Is_OrderPaidOkay = false;
                    }
                    });

                m_PAYMENT_Back_Button = new QToolButton(m_PAYMENT_Background_Widget);
                m_PAYMENT_Back_Button->move(m_PAYMENT_Background_Widget->width() * 0.02, m_PAYMENT_Background_Widget->height() * 0.91);
                m_PAYMENT_Back_Button->resize(m_PAYMENT_Background_Widget->width() * 0.2, m_PAYMENT_Background_Widget->height() * 0.08);
                m_PAYMENT_Back_Button->setText("Back");
                m_PAYMENT_Back_Button->setStyleSheet("QToolButton { color: black; background-color: #f49454; border-radius: 10px; }");
                connect(m_PAYMENT_Back_Button, &QToolButton::clicked, [=]() {
                    close_dishTypes(Dish_type);
                    m_left_MAINBackWidget->show();
                    m_PAYMENT_Background_Widget->hide();
                    m_RIGHT_Payment_Button->show();
                    m_RIGHT_SendToKitchen_Button->hide();
                    
                    Is_PaymentWidget_Open = false;
                    });
            }

            // [ Right Widget ]
            {
                m_RIGHT_Background_Widget = new QWidget(this);
                m_RIGHT_Background_Widget->move(this->width() * 0.57, this->height() * 0.11);
                m_RIGHT_Background_Widget->resize(this->width() * 0.42, this->height() * 0.88);
                m_RIGHT_Background_Widget->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 150); border-radius: 10px; } ");
                m_RIGHT_Background_Widget->show();

                m_RIGHT_SendToKitchen_Button = new QToolButton(m_RIGHT_Background_Widget);
                m_RIGHT_SendToKitchen_Button->move(m_RIGHT_Background_Widget->width() * 0.02, m_RIGHT_Background_Widget->height() * 0.79);
                m_RIGHT_SendToKitchen_Button->resize(m_RIGHT_Background_Widget->width() * 0.96, m_RIGHT_Background_Widget->height() * 0.1);
                m_RIGHT_SendToKitchen_Button->setText("SEND TO COOK");
                m_RIGHT_SendToKitchen_Button->setStyleSheet("QToolButton { color: white; background-color: #f49454; border-radius: 10px; }");
                m_RIGHT_SendToKitchen_Button->hide();
                connect(m_RIGHT_SendToKitchen_Button, &QToolButton::clicked, [=]() {
                    if (Is_OrderPaidOkay == false)
                    {
                        m_ErrorBox = new ErrorBox(this);
                        m_ErrorBox->setErrorText("ERROR\nConfirm that order is paid");
                        m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
                        m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
                        m_ErrorBox->Init();
                        m_ErrorBox->show();
                    }
                    else
                    {
                        // ��������� �� ����� � ��
                        
                    }
                    });

                m_RIGHT_Payment_Button = new QToolButton(m_RIGHT_Background_Widget);
                m_RIGHT_Payment_Button->move(m_RIGHT_Background_Widget->width() * 0.02, m_RIGHT_Background_Widget->height() * 0.89);
                m_RIGHT_Payment_Button->resize(m_RIGHT_Background_Widget->width() * 0.96, m_RIGHT_Background_Widget->height() * 0.1);
                m_RIGHT_Payment_Button->setText("Pay for order");
                m_RIGHT_Payment_Button->setStyleSheet("QToolButton { background-color: #f49454; border-radius: 10px; font-color: white; }");
                m_RIGHT_Payment_Button->show();
                connect(m_RIGHT_Payment_Button, &QToolButton::clicked, [=]() {
                    if (Is_GuestRegisteredForOrder == true)
                    {
                        int numRows = m_RIGHT_Table_Qtable->rowCount();
                        int numCols = m_RIGHT_Table_Qtable->columnCount();
                        
                        for (int i = 0; i < numRows; i++) {
                            std::vector<std::string> row;
                            for (int j = 0; j < numCols; j++) {
                                QTableWidgetItem* item = m_RIGHT_Table_Qtable->item(i, j);
                                if (item) {
                                    row.push_back(item->text().toStdString());
                                }
                                else {
                                    row.push_back("");
                                }
                            }
                            g_Order.order_full_list_.push_back(row);
                        }
                        for (int i = 0; i < numRows; i++) {
                            g_Order.summa_ += stoi(g_Order.order_full_list_[i][2]);
                        }
                        // �������� �����
                        for (int i = 0; i < numRows; i++) {
                            for (int j = 0; j < numCols; j++) {
                                std::cout << g_Order.order_full_list_[i][j] << " ";
                            }
                            std::cout << "\n";
                        }

                        g_Order.customer_name_ = g_Customer.name;
                        QString TotalSummText_inLabel = "Total: " + QString::number(g_Order.summa_);
                        m_PAYMENT_TotalSumma_Label->setText(TotalSummText_inLabel);
                        m_left_MAINBackWidget->hide();
                        m_PAYMENT_Background_Widget->show();
                        m_RIGHT_Payment_Button->hide();
                        m_RIGHT_SendToKitchen_Button->show();

                        close_dishTypes(Dish_type);
                        m_DishDescription_Widget->hide();

                        Is_PaymentWidget_Open = true;
                    }
                    else
                    {
                        m_ErrorBox = new ErrorBox(this);
                        m_ErrorBox->setErrorText("ERROR\nClient not added\nAdd New Client");
                        m_ErrorBox->move(this->width() * 0.30, this->height() * 0.26);
                        m_ErrorBox->resize(this->width() * 0.46, this->height() * 0.46);
                        m_ErrorBox->Init();
                        m_ErrorBox->show();
                    }
                    });

                m_RIGHT_ScrollArea_ScrollArea = new QScrollArea(this);
                m_RIGHT_ScrollArea_ScrollArea->setWidgetResizable(true);
                m_RIGHT_ScrollArea_ScrollArea->setAlignment(Qt::AlignLeft);
                m_RIGHT_ScrollArea_ScrollArea->move(this->width() * 0.58, this->height() * 0.12);
                m_RIGHT_ScrollArea_ScrollArea->resize(this->width() * 0.4, this->height() * 0.65);
                m_RIGHT_ScrollArea_ScrollArea->setStyleSheet("QScrollArea {background: transparent; border-radius: 10px; } QScrollBar:horizontal, QScrollBar:vertical {background: transparent; width: 0px;}");
                m_RIGHT_ScrollArea_ScrollArea->setMinimumSize(400, 300);
                m_RIGHT_ScrollArea_ScrollArea->show();

                m_RIGHT_Table_Qtable = new QTableWidget(this);
                m_RIGHT_Table_Qtable->setColumnCount(3);
                QStringList text = { "Name", "ID", "Price" };
                m_RIGHT_Table_Qtable->setHorizontalHeaderLabels(text);
                m_RIGHT_Table_Qtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
                m_RIGHT_Table_Qtable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

                m_RIGHT_Table_Qtable->setColumnWidth(0, 250);
                m_RIGHT_Table_Qtable->setColumnWidth(1, 50);
                m_RIGHT_Table_Qtable->setColumnWidth(2, 68);

                m_RIGHT_ScrollArea_ScrollArea->ensureWidgetVisible(m_RIGHT_Table_Qtable);
                m_RIGHT_ScrollArea_ScrollArea->setWidget(m_RIGHT_Table_Qtable);
            }
        }

            
    }

    void SetTop_ADMIN_Name_State()
    {
        m_TOP_AdmiName_Label->setText(QString::fromStdString(g_Admin.name));         // NAME
        m_TOP_AdminState_Label->setText(QString::fromStdString(g_Admin.state));      // STATE
    }
    void SetTop_Guest_Name_State()
    {
        m_TOP_GuestName_Label->setText(QString::fromStdString(g_Customer.name));     // NAME
        m_TOP_GuestState_Label->setText(QString::fromStdString(g_Customer.state));   // STATE
    }

    void set_GuestSeatPlace_Text(int id)
    {
        switch (id)
        {
        case 0:
        {
            m_TOP_GuestSeatPlace_Button->setText("none place selected");
        }
        break;
        case 1:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 1");
        }
        break;
        case 2:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 2");
        }
        break;
        case 3:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 3");
        }
        break;
        case 4:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 4");
        }
        break;
        case 5:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 5");
        }
        break;
        case 6:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 6");
        }
        break;
        case 7:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 7");
        }
        break;
        case 8:
        {
            m_TOP_GuestSeatPlace_Button->setText("place 8");
        }
        break;
        default:
        {
            m_TOP_GuestSeatPlace_Button->setText("none place selected");
        }
        }
    }
    
    void close_for_dishDescription(int a)
    {
        switch (a)
        {
        case 0:
        {
            m_left_MAINBackWidget->hide();
        }
        break;
        case 1:
        {
            m_left_1_TypeBackWidget->hide();
        }
        break;
        case 2:
        {
            m_left_2_TypeBackWidget->hide();
        }
        break;
        case 3:
        {
            m_left_3_TypeBackWidget->hide();
        }
        break;
        case 4:
        {
            m_left_4_TypeBackWidget->hide();
        }
        break;
        case 5:
        {
            m_left_5_TypeBackWidget->hide();
        }
        break;
        default:
        {
            m_left_1_TypeBackWidget->hide();
            m_left_2_TypeBackWidget->hide();
            m_left_3_TypeBackWidget->hide();
            m_left_4_TypeBackWidget->hide();
            m_left_5_TypeBackWidget->hide();
            m_left_MAINBackWidget->hide();
        }
        }
    }
    void show_for_dishDescription(int a)
    {
        switch (a)
        {
        case 0:
        {
            m_left_MAINBackWidget->show();
        }
        break;
        case 1:
        {
            m_left_1_TypeBackWidget->show();
        }
        break;
        case 2:
        {
            m_left_2_TypeBackWidget->show();
        }
        break;
        case 3:
        {
            m_left_3_TypeBackWidget->show();
        }
        break;
        case 4:
        {
            m_left_4_TypeBackWidget->show();
        }
        break;
        case 5:
        {
            m_left_5_TypeBackWidget->show();
        }
        break;
        default:
        {
            m_left_MAINBackWidget->show();
            m_left_1_TypeBackWidget->show();
            m_left_2_TypeBackWidget->show();
            m_left_3_TypeBackWidget->show();
            m_left_4_TypeBackWidget->show();
            m_left_5_TypeBackWidget->show();
        }
        break;
        }
    }
    void close_dishTypes(int id)
    {
        switch (id)
        {
        case 1: 
        {
            m_left_1_TypeBackWidget->hide();
        }
        break;
        case 2:
        {
            m_left_2_TypeBackWidget->hide();
        }
        break;
        case 3:
        {
            m_left_3_TypeBackWidget->hide();
        }
        break;
        case 4:
        {
            m_left_4_TypeBackWidget->hide();
        }
        break;
        case 5:
        {
            m_left_5_TypeBackWidget->hide();
        }
        break;
        default:
        {
            m_left_1_TypeBackWidget->hide();
            m_left_2_TypeBackWidget->hide();
            m_left_3_TypeBackWidget->hide();
            m_left_4_TypeBackWidget->hide();
            m_left_5_TypeBackWidget->hide();
        }
        break;
        }
    }

    void set_DishOptions(int id)
    {
        switch (id)
        {
        case 0:
        {
            m_DishDescription_DishName->setText("Dish name");
            m_DishDescription_DishIngredients->setText("Ingredients");
            m_DishDescription_DishPicture->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
        }
        break;
        case 1:
        {
            m_DishDescription_DishName->setText("Burger");
            m_DishDescription_DishIngredients->setText("beef\nmilk");
            m_DishDescription_DishPicture->setIcon(QIcon(":/UIUX/UIUX/Pictures/not_correct_password.png"));
        }
        break;
        case 2:
        {
            m_DishDescription_DishName->setText("Pizza");
            m_DishDescription_DishIngredients->setText("tomato\nmilk");
            m_DishDescription_DishPicture->setIcon(QIcon(":/UIUX/UIUX/Pictures/not_correct_password.png"));
        }
        break;
        case 3:
        {
            m_DishDescription_DishName->setText("Lahmajdoon");
            m_DishDescription_DishIngredients->setText("beef\nmilk");
            m_DishDescription_DishPicture->setIcon(QIcon(":/UIUX/UIUX/Pictures/not_correct_password.png"));
        }
        break;
        default:
        {
            m_DishDescription_DishName->setText("Dish name");
            m_DishDescription_DishIngredients->setText("Ingredients");
            m_DishDescription_DishPicture->setIcon(QIcon(":/UIUX/UIUX/Pictures/food-app.png"));
        }
        }
    }
    std::string ReturnDishNameById(int id)
    {
        switch (id)
        {
        case 0:
        {
            return "none";
        }
        break;
        case 1:
        {
            return "burger";
        }
        break;
        case 2:
        {
            return "pizza";
        }
        break;
        case 3:
        {
            return "lahmadjoon";
        }
        break;
        default:
        {
            return "none";
        }
        }
    }


    void    addRow(int id) 
    {
        int row = m_RIGHT_Table_Qtable->rowCount();
        m_RIGHT_Table_Qtable->insertRow(row);

        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(ReturnDishNameById(id)));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // ������ ��������� ������
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable); // ��������� ��������
        m_RIGHT_Table_Qtable->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::number(id));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // ������ ��������� ������
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable); // ��������� ��������
        m_RIGHT_Table_Qtable->setItem(row, 1, item);

        int price = 100;
        item = new QTableWidgetItem(QString::number(price));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // ������ ��������� ������
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable); // ��������� ��������
        m_RIGHT_Table_Qtable->setItem(row, 2, item);

    }
    int     findProduct(const QString& productName) {
        for (int i = 0; i < m_RIGHT_Table_Qtable->rowCount(); ++i) {
            if (m_RIGHT_Table_Qtable->item(i, 0)->text() == productName) {
                return i;
            }
        }
        return -1;
    }
    void    removeProduct(const QString& productName) {
        int row = findProduct(productName);
        if (row != -1) {
            m_RIGHT_Table_Qtable->removeRow(row);
        }
    }


    // +-------------------------[ Fonts ]---------------------------------+
    QFont           m_FirstFont;
    QFont           m_SecondFont;

    // +-------------------------[ Error Box ]-----------------------------+
    ErrorBox*       m_ErrorBox;

    // +-------------------------[ TOP INFO Bar ]--------------------------+
    QWidget*        m_TOP_InfoBar_Widget;
    QLabel*         m_TOP_AdminState_Label;
    QLabel*         m_TOP_AdmiName_Label;
    QLabel*         m_TOP_GuestState_Label;
    QLabel*         m_TOP_GuestName_Label;

    QToolButton*    m_TOP_NewGuest_Button;
    QWidget*        m_TOP_NewGuest_Widget;
    QLineEdit*      m_NewGuestLogin_Input;
    QToolButton*    m_NewGuestFROMloginContinue;
    QToolButton*    m_NewGuestWITHOUTloginContinue;

    QToolButton*    m_TOP_GuestSeatPlace_Button;
    QWidget*        m_TOP_SeatPlace_Widget;

    QToolButton*    m_TOP_Settings_Button;
    QToolButton*    m_SETTINGS_NewShift_Button;
    QWidget*        m_TOP_Settings_Widget;
    QToolButton*    m_SETTINGS_LogOut_Button;

    // +-------------------------[ Left Menu ]-----------------------------+
    QWidget*        m_left_MAINBackWidget;      // ������� ������ ������ ���� ����� ����
    QGridLayout*    m_left_MAINGridLayout;      // ��� layout
    QToolButton*    m_dishType1;                // ��� ����� 1
    QToolButton*    m_dishType2;                // ��� ����� 2
    QToolButton*    m_dishType3;                // ��� ����� 3
    QToolButton*    m_dishType4;                // ��� ����� 4
    QToolButton*    m_dishType5;                // ��� ����� 5

    QToolButton*    m_left_DeleteGuest_Button;  // ������ �������� �������

    // 1 Type
    QWidget*        m_left_1_TypeBackWidget;    // ������ 1 ���� �����
    QGridLayout*    m_left_1_TypeGridLayout;    // ��� layout
    QToolButton*    m_dishType1_1;              // ��� ����� 1 ����� 1
    QToolButton*    m_dishType1_2;              // ��� ����� 1 ����� 2
    QToolButton*    m_dishType1_3;              // ��� ����� 1 ����� 3
    QToolButton*    m_dishType1_BACK_Button;    // ��� ����� 1 ����� 4

    // 2 Type
    QWidget*        m_left_2_TypeBackWidget;    // ������ 2 ���� �����
    QGridLayout*    m_left_2_TypeGridLayout;    // ��� layout
    QToolButton*    m_dishType2_1;              // ��� ����� 2 ����� 1
    QToolButton*    m_dishType2_2;              // ��� ����� 2 ����� 2
    QToolButton*    m_dishType2_3;              // ��� ����� 2 ����� 3
    QToolButton*    m_dishType2_BACK_Button;    // ��� ����� 2 ����� 4

    // 3 Type
    QWidget*        m_left_3_TypeBackWidget;    // ������ 3 ���� �����
    QGridLayout*    m_left_3_TypeGridLayout;    // ��� layout
    QToolButton*    m_dishType3_1;              // ��� ����� 3 ����� 1
    QToolButton*    m_dishType3_2;              // ��� ����� 3 ����� 2
    QToolButton*    m_dishType3_3;              // ��� ����� 3 ����� 3
    QToolButton*    m_dishType3_BACK_Button;    // ��� ����� 3 ����� 4

    // 4 Type
    QWidget*        m_left_4_TypeBackWidget;    // ������ 4 ���� �����
    QGridLayout*    m_left_4_TypeGridLayout;    // ��� layout
    QToolButton*    m_dishType4_1;              // ��� ����� 4 ����� 1
    QToolButton*    m_dishType4_2;              // ��� ����� 4 ����� 2
    QToolButton*    m_dishType4_3;              // ��� ����� 4 ����� 3
    QToolButton*    m_dishType4_BACK_Button;    // ��� ����� 4 ����� 4
    
    // 5 Type
    QWidget*        m_left_5_TypeBackWidget;    // ������ 5 ���� �����
    QGridLayout*    m_left_5_TypeGridLayout;    // ��� layout
    QToolButton*    m_dishType5_1;              // ��� ����� 5 ����� 1
    QToolButton*    m_dishType5_2;              // ��� ����� 5 ����� 2
    QToolButton*    m_dishType5_3;              // ��� ����� 5 ����� 3
    QToolButton*    m_dishType5_BACK_Button;    // ��� ����� 5 ����� 4

    // +--------------------------[ Dish Description ]--------------------------+
    QWidget*        m_DishDescription_Widget;
    QToolButton*    m_DishDescription_AddButton;
    QToolButton*    m_DishDescription_ShowToCustomerButton;
    QToolButton*    m_DishDescription_CloseButton;
    QToolButton*    m_DishDescription_DishPicture;
    QLabel*         m_DishDescription_DishName;
    QLabel*         m_DishDescription_DishIngredients;

    // +--------------------------[ Right Order List ]--------------------------+
    QWidget*        m_RIGHT_Background_Widget;
    QScrollArea*    m_RIGHT_ScrollArea_ScrollArea;
    QTableWidget*   m_RIGHT_Table_Qtable;
    QToolButton*    m_RIGHT_Payment_Button;
    QToolButton*    m_RIGHT_SendToKitchen_Button;

    // +--------------------------[ Payment Widget ]----------------------------+
    QWidget*        m_PAYMENT_Background_Widget;
    QToolButton*    m_PAYMENT_Back_Button;
    QToolButton*    m_PAYMENT_PayedTrue_Button;
    QLabel*         m_PAYMENT_TotalSumma_Label;
    QLineEdit*      m_PAYMENT_InputMoney;
    QLabel*         m_PAYMMENT_OutputMoney;
    QToolButton*    m_PAYMENT_CashOrCardMethod;
    QTextEdit*      m_PAYMENT_AdditionalComment;
    QComboBox*      m_PAYMENT_Discount_Box;
    QLabel*         m_PAYMENT_Discount_text;
    QLabel*         m_PAYMENT_TotalSumma_text;


    void paintEvent(QPaintEvent* paint_event) override
    {
        QPainter MainWidget_painter(this);

        MainWidget_painter.setBrush(QColor(82, 148, 208, 255));
        MainWidget_painter.drawRect(QRect(0, 0, this->width(), this->height()));

    }

signals:
    void Signal_LogOut();

};