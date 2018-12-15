#include "exception.h"

namespace API
{
Exception::Exception(QString message)
    : m_message(std::move(message))
{
}

const QString& Exception::message() const
{
    return m_message;
}

void Exception::raise() const {
    throw *this;
}

Exception* Exception::clone() const {
    return new Exception(*this);
}

Exception& Exception::append(QString message)
{
    m_message += message;
    return *this;
}
} // namespace API
