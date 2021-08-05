#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>
#include <QMessageBox>

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
    FileMissing
};

class Error
{
private:
    // ###################### Private attributes ####################### //

    QString m_message = "";
    ErrorPriority m_prioryty;
    ErrorType m_type;

public:
    // ######################## Public methods ######################### //

    // Constructor
    Error(ErrorPriority prioryty = ErrorPriority::Undefined, ErrorType type = ErrorType::Undefined, QString message = "");

    // Display the error in a QMessageBox
    void printMessage();

    // Getters
    QString getMessage();
    ErrorPriority getPrioryty();
    ErrorType getType();

    // Setters
    void setMessage(QString message);
    void setPrioryty(ErrorPriority priority);
    void setType(ErrorType type);
};

#endif // ERRORHANDLER_H
