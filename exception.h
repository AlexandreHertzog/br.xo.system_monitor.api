#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <QString>
#include <QException>

namespace API
{
// Basic exception class, used for error reporting.
class Exception : public QException
{
private:
    QString m_message;

public:
    Exception(QString message);

    const QString& message() const;
    void raise() const override;
    Exception* clone() const override;
    Exception& append(QString message);
};
} // namespace API

#endif // CEXCEPTION_H
