#include "errorhandler.h"


///
/// Constructor
/// \brief Error::Error
/// \param prioryty
/// \param type
/// \param message
///
Error::Error(ErrorPriority prioryty, ErrorType type, QString message)
{
    m_message = message;
    m_type = type;
    m_prioryty = prioryty;
}


///
/// Display the error in a QMessageBox
/// \brief Error::printMessage
///
void Error::printMessage()
{
    QMessageBox errorMessage;
    switch (m_prioryty) {
    case ErrorPriority::Undefined:
        errorMessage.setStandardButtons(QMessageBox::Ok);
        errorMessage.setIcon(QMessageBox::NoIcon);
        break;

    case ErrorPriority::Warning:
        errorMessage.setWindowTitle("Warning");
        errorMessage.setStandardButtons(QMessageBox::Ok);
        errorMessage.setIcon(QMessageBox::Warning);
        break;

    case ErrorPriority::Critical:
        errorMessage.setWindowTitle("Critical");
        errorMessage.setStandardButtons(QMessageBox::Close);
        errorMessage.setIcon(QMessageBox::Critical);
        break;

    case ErrorPriority::BadInput:
        errorMessage.setWindowTitle("BadInput");
        errorMessage.setStandardButtons(QMessageBox::Discard | QMessageBox::Retry);
        errorMessage.setIcon(QMessageBox::Warning);
        break;
    }

    switch (m_type) {
    case ErrorType::Undefined:
        errorMessage.setText("Error code 0x00");
        break;

    case ErrorType::InvalidInput:
        errorMessage.setText("Error code 0x01 : InvalidInput");
        break;

    case ErrorType::MissingInput:
        errorMessage.setText("Error code 0x02 : MissingInput");
        break;

    case ErrorType::FileMissing:
        errorMessage.setText("Error code 0x03 : FileMissing");
        break;
    }

    errorMessage.setInformativeText(m_message);



    switch (errorMessage.exec())
    {
    case QMessageBox::Ok:
        errorMessage.close();
        break;

    case QMessageBox::Close:

        break;

    case QMessageBox::Discard:
        errorMessage.close();
        break;

    case QMessageBox::Retry:
        errorMessage.close();
        break;
    }
}


// Getters
QString Error::getMessage()
{
    return m_message;
}

ErrorPriority Error::getPrioryty()
{
    return m_prioryty;
}

ErrorType Error::getType()
{
    return m_type;
}


// Setters
void Error::setMessage(QString message)
{
    m_message = message;
}

void Error::setPrioryty(ErrorPriority priority)
{
    m_prioryty = priority;
}

void Error::setType(ErrorType type)
{
    m_type = type;
}
