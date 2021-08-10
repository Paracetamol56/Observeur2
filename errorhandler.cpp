#include "errorhandler.h"


Error::Error(ErrorPriority prioryty, QString message)
{
    m_message = message;
    m_prioryty = prioryty;
}


void Error::printMessage()
{
    // Main message box
    QMessageBox errorMessage;

    setMessageBoxPriority(&errorMessage);

    // Set the informative message
    errorMessage.setInformativeText(m_message);

    messageBoxExec(&errorMessage);
}


void Error::setMessageBoxPriority(QMessageBox *errorMessage)
{
    // Priority setting
    // Set the title
    // Set the icon
    // Set the buttons
    switch (m_prioryty) {
    case ErrorPriority::Undefined:
        errorMessage->setStandardButtons(QMessageBox::Ok);
        errorMessage->setIcon(QMessageBox::NoIcon);
        break;

    case ErrorPriority::Warning:
        errorMessage->setWindowTitle("Warning");
        errorMessage->setStandardButtons(QMessageBox::Ok);
        errorMessage->setIconPixmap(QPixmap(":/Ressources/icons/errors/icons8-error-96.png"));
        break;

    case ErrorPriority::Critical:
        errorMessage->setWindowTitle("Critical");
        errorMessage->setStandardButtons(QMessageBox::Close);
        errorMessage->setIconPixmap(QPixmap(":/Ressources/icons/errors/icons8-high-priority-96.png"));
        break;

    case ErrorPriority::BadInput:
        errorMessage->setWindowTitle("BadInput");
        errorMessage->setStandardButtons(QMessageBox::Discard | QMessageBox::Retry);
        errorMessage->setIconPixmap(QPixmap(":/Ressources/icons/errors/icons8-error-96.png"));
        break;
    }
}


void Error::messageBoxExec(QMessageBox *errorMessage)
{
    // Action
    switch (errorMessage->exec())
    {
    case QMessageBox::Ok:
        errorMessage->close();
        break;

    case QMessageBox::Close:
        QApplication::quit();
        break;

    case QMessageBox::Discard:
        errorMessage->close();
        break;

    case QMessageBox::Retry:
        errorMessage->close();
        break;
    }
}


InputError::InputError(ErrorPriority prioryty, QString message)
    : Error(prioryty, message)
{}


void InputError::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("InputError");
    errorMessage.setInformativeText(m_message);
    messageBoxExec(&errorMessage);
}


MissingInputError::MissingInputError(ErrorPriority prioryty, QString message)
    : InputError(prioryty, message)
{}


void MissingInputError::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("MissingInputError");
    errorMessage.setInformativeText(m_message);
    messageBoxExec(&errorMessage);
}


FileError::FileError(ErrorPriority prioryty, QString message, QFile *file)
    : Error(prioryty, message)
{
    m_file = file;
}


void FileError::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("FileError");
    errorMessage.setInformativeText(m_message);
    errorMessage.setDetailedText(QString("FILE PATH : \n" + QFileInfo(*m_file).path()));
    messageBoxExec(&errorMessage);
}


FileMissingError::FileMissingError(ErrorPriority prioryty, QString message, QFile *file)
    : FileError(prioryty, message, file)
{}


void FileMissingError::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("FileMissingError");
    errorMessage.setInformativeText(m_message);
    errorMessage.setDetailedText(QString("FILE PATH : \n" + QFileInfo(*m_file).path()));
    messageBoxExec(&errorMessage);
}


SqlError::SqlError(ErrorPriority prioryty, QString message, QSqlQuery *sqlQuery)
    : Error(prioryty, message)
{
    m_sqlQuery = sqlQuery;
}


void SqlError::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("SqlError");
    errorMessage.setInformativeText(m_message);
    errorMessage.setDetailedText("SQL ERROR : \n" + m_sqlQuery->lastError().text() + "\n\nON QUERY : \n" + m_sqlQuery->lastQuery());
    messageBoxExec(&errorMessage);
}

/*
AngleError::AngleError(ErrorPriority prioryty, QString message, Angle *angle)
    : Error(prioryty, message)
{
    m_angle = angle;
}


void AngleError::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("AngleError");
    errorMessage.setInformativeText(m_message);
    messageBoxExec(&errorMessage);
}


InvalidAngleString::InvalidAngleString(ErrorPriority prioryty, QString message, Angle *angle)
    : AngleError(prioryty, message, angle)
{}


void InvalidAngleString::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("InvalidAngleString");
    errorMessage.setInformativeText(m_message);
    messageBoxExec(&errorMessage);
}


InvalidAngleInput::InvalidAngleInput(ErrorPriority prioryty, QString message, Angle *angle)
    : AngleError(prioryty, message, angle)
{}


void InvalidAngleInput::printMessage()
{
    QMessageBox errorMessage;
    setMessageBoxPriority(&errorMessage);
    errorMessage.setText("InvalidAngleInput");
    errorMessage.setInformativeText(m_message);
    errorMessage.setDetailedText("ANGLE : \n" + QString::number(m_angle->getTotalDegree()) + "°");
    messageBoxExec(&errorMessage);
}
*/
