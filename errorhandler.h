#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

// MessageBox
#include <QMessageBox>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>

// File
#include <QFile>
#include <QDir>

// Utilities
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QApplication>
#include <QIcon>

#include "angleutilities/angle.h"



enum class ErrorPriority
{
    // Undefine
    Undefined,
    // Close the program
    Critical,
    // Warn the user and continue
    Warning,
    // Ask for retry
    BadInput,
};

struct Error
{
    QString m_message = "";
    ErrorPriority m_prioryty = ErrorPriority::Undefined;

    // Classic constructor
    Error(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "");
    // Display the error in a QMessageBox
    virtual void printMessage();
    void setMessageBoxPriority(QMessageBox *errorMessage = nullptr);
    void messageBoxExec(QMessageBox *errorMessage = nullptr);
};


struct InputError
    : Error
{
    InputError(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "");
    void printMessage() override;
};


struct MissingInputError
    : InputError
{
    MissingInputError(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "");
    void printMessage() override;
};


struct FileError
    : Error
{
    QFile *m_file = nullptr;

    FileError(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "", QFile *file = nullptr);
    void printMessage() override;
};


struct MissingFileError
    : FileError
{
    MissingFileError(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "", QFile *file = nullptr);
    virtual void printMessage() override;
};


struct SqlError
    : Error
{
    QSqlQuery *m_sqlQuery = nullptr;

    SqlError(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "", QSqlQuery *sqlQuery = nullptr);
    virtual void printMessage() override;
};

/*
struct AngleError
    : Error
{
    Angle *m_angle = nullptr;

    AngleError(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "", Angle *angle = nullptr);
    virtual void printMessage() override;
};


struct InvalidAngleString
    : AngleError
{
    InvalidAngleString(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "", Angle *angle = nullptr);
    virtual void printMessage() override;
};


struct InvalidAngleInput
    : AngleError
{
    InvalidAngleInput(ErrorPriority prioryty = ErrorPriority::Undefined, QString message = "", Angle *angle = nullptr);
    virtual void printMessage() override;
};
*/
#endif // ERRORHANDLER_H
