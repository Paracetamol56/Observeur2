#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

// MessageBox
#include <QMessageBox>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>

// Utilities
#include <QString>
#include <QStringList>
#include <QApplication>

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

enum class ErrorType
{
    Undefined,
    InvalidInput,
    MissingInput,
    FileMissing,
    SqlError,
    AngleError
};

class Error
{
private:

    QString m_message = "";
    ErrorPriority m_prioryty = ErrorPriority::Undefined;
    ErrorType m_type = ErrorType::Undefined;
    QSqlQuery *m_sqlQuery = nullptr;

public:

    // Constructors
    // Classic
    Error(ErrorPriority prioryty = ErrorPriority::Undefined, ErrorType type = ErrorType::Undefined, QString message = "");
    // SQL error
    Error(ErrorPriority prioryty = ErrorPriority::Undefined, QSqlQuery *query = nullptr);

    // Display the error in a QMessageBox
    void printMessage();

    // Getters
    QString getMessage();
    ErrorPriority getPrioryty();
    ErrorType getType();
    QSqlQuery *getSqlQuery();

    // Setters
    void setMessage(QString message);
    void setPrioryty(ErrorPriority priority);
    void setType(ErrorType type);
    void setSqlQuery(QSqlQuery *query);
};

#endif // ERRORHANDLER_H
