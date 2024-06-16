#pragma once

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

class ErrorBox : public QWidget
{
    Q_OBJECT

public:

    ErrorBox(QWidget* parent = nullptr) : QWidget(parent)
    {

    }

    void setErrorText(std::string error_text)
    {
        ErrorText = QString(error_text.c_str());
    }

    void Init()
    {

        // [ FONTS ]
        {
            int id = QFontDatabase::addApplicationFont(":/UIUX/UIUX/Fonts/MenuObjects-SemiBoldItalic.ttf");
            QString family = QFontDatabase::applicationFontFamilies(id).at(0);
            m_HeaderFont.setFamily(family);
            m_HeaderFont.setPointSize(this->width() * 0.04);
        }

        m_ErrorText = new QLabel(this);
        m_ErrorText->move(this->width() * 0.02, this->height() * 0.16);
        m_ErrorText->resize(this->width() * 0.64, this->height() * 0.6);
        m_ErrorText->setText(ErrorText);
        m_ErrorText->setFont(m_HeaderFont);
        m_ErrorText->show();

        m_Image = new QToolButton(this);
        m_Image->move(this->width() * 0.6, this->height() * 0.2);
        m_Image->setIconSize(QSize(this->width() * 0.4, this->height() * 0.36));
        m_Image->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
        m_Image->setIcon(QIcon(":/UIUX/UIUX/Pictures/no_connection.png"));
        m_Image->show();

        m_ExitButton = new QToolButton(this);
        m_ExitButton->move(this->width() * 0.45, this->height() * 0.90);
        m_ExitButton->resize(this->width() * 0.2, this->height() * 0.1);
        m_ExitButton->setText("Okey");
        //m_ExitButton->setStyleSheet("QToolButton { border: none; background: transparent; } QToolButton:hover {  }");
        m_ExitButton->show();
        connect(m_ExitButton, &QToolButton::clicked, [=]() {
            this->close();
            this->deleteLater();
            });


    }

    void paintEvent(QPaintEvent* paint_event) override
    {
        QPainter MainWidget_painter(this);

        MainWidget_painter.setBrush(QColor(255, 255, 255, 255));
        MainWidget_painter.drawRect(QRect(0, 0, this->width(), this->height()));

    }

    QString         ErrorText;
    QFont           m_HeaderFont;
    QLabel*         m_ErrorText;
    QToolButton*    m_Image;
    QToolButton*    m_ExitButton;

};