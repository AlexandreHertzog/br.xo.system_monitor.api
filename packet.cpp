#include "packet.h"

#include <QJsonArray>
#include "exception.h"

namespace API
{
Packet::Packet(int client_id, double memLoad, double cpuLoad, size_t numProcs)
    : m_clientId(client_id)
    , m_memLoad(memLoad)
    , m_cpuLoad(cpuLoad)
    , m_numProcs(numProcs)
{
}

Packet::Packet(const QJsonObject &json)
    : Packet()
{
    parse(json);
}

void Packet::parse(const QJsonObject &json)
{
    auto cliendIdIt = json.find("client_id");
    auto memLoadIt = json.find("memory_load");
    auto cpuLoadIt = json.find("cpu_load");
    auto numProcsIt = json.find("num_processes");
    if (cliendIdIt == json.end() || memLoadIt == json.end() || cpuLoadIt == json.end() || numProcsIt == json.end())
    {
        Exception("Missing fields in received JSON").raise();
    }
    m_clientId = (*cliendIdIt).toInt(-1);
    m_memLoad = (*memLoadIt).toDouble(-1.0);
    m_cpuLoad = (*cpuLoadIt).toDouble(-1.0);
    m_numProcs = (*numProcsIt).toInt(-1);
    if (m_clientId < 0 || m_memLoad < 0 || m_cpuLoad < 0 || m_numProcs < 0)
    {
        Exception("Failed to parse packet: failed to parse values").raise();
    }
}

QJsonObject Packet::toJson() const
{
    QJsonObject json;
    json.insert("client_id", m_clientId);
    json.insert("memory_load", m_memLoad);
    json.insert("cpu_load", m_cpuLoad);
    json.insert("num_processes", m_numProcs);
    return json;
}

int Packet::getId() const
{
    return m_clientId;
}

void Packet::setId(int id)
{
    m_clientId = id;
}

double Packet::getMemoryLoad() const
{
    return m_memLoad;
}

double Packet::getCPULoad() const
{
    return m_cpuLoad;
}

size_t Packet::getNumProcesses() const
{
    return m_numProcs;
}
} // namespace API
