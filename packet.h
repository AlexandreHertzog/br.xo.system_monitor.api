#ifndef CPACKET_H
#define CPACKET_H

#include <QJsonObject>
#include <QStringList>

namespace API
{
// Represents the packets that transit between the client and the server.
class Packet
{
    int m_clientId;
    double m_memLoad;
    double m_cpuLoad;
    int m_numProcs;

public:
    Packet(int clientId = 0, double memLoad = 0.0, double cpuLoad = 0.0, size_t numProcs = 0);
    Packet(const QJsonObject &json);

    QJsonObject toJson() const;
    void parse(const QJsonObject &json);

    void setId(int id);
    int getId() const;
    double getMemoryLoad() const;
    double getCPULoad() const;
    size_t getNumProcesses() const;
};
} // namespace API

#endif // CPACKET_H
