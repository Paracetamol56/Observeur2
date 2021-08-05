#include "errorhandler.h"


Error::Error(ErrorPriority prioryty, ErrorType type, QString message)
{
    m_message = message;
    m_type = type;
    m_prioryty = prioryty;
}

Error::printMessage()
{
    QErrorMessage errorMessage();
}


// Getters
QString Error::getMessage()
{

}

int Error::getPrioryty()
{

}

int Error::getType()
{

}


// Setters
void Error::setMessage()
{

}

void Error::setPrioryty()
{

}

void Error::setType()
{

}
