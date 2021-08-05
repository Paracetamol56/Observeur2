#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>
#include <QErrorMessage>

enum class ErrorPriority
{
    Undefined,
    Critical,
    Warning
};

enum class ErrorType
{
    Undefined,
    InvalidInput,
    MissingInput
    FileMissing
};

class Error
{
private:
    QString m_message = "";
    ErrorPrioryty m_prioryty;
    ErrorType m_type;

public:
    Error(ErrorPriority prioryty = ErrorPriority::Undefined, ErrorType type = ErrorType::Undefined, QString message = "");

    void printMessage();

    // Getters
    int getMessage();
    int getPrioryty();
    int getType();

    // Setters
    void setMessage();
    void setPrioryty();
    void setType();
};

#endif // ERRORHANDLER_H
