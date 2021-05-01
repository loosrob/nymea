/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2021, nymea GmbH
* Contact: contact@nymea.io
*
* This file is part of nymea.
* This project including source code and documentation is protected by
* copyright law, and remains the property of nymea GmbH. All rights, including
* reproduction, publication, editing and translation, are reserved. The use of
* this project is subject to the terms of a license agreement to be concluded
* with nymea GmbH in accordance with the terms of use of nymea GmbH, available
* under https://nymea.io/license
*
* GNU Lesser General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; version 3. This project is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MODBUSRTUMASTERIMPL_H
#define MODBUSRTUMASTERIMPL_H

#include <QObject>
#include <QSerialPort>

#ifdef WITH_QTSERIALBUS
#include <QtSerialBus/QtSerialBus>
#endif

#include "hardware/modbus/modbusrtumaster.h"

namespace nymeaserver {

class ModbusRtuMasterImpl : public ModbusRtuMaster
{
    Q_OBJECT
public:
    explicit ModbusRtuMasterImpl(const QUuid &modbusUuid, const QString &serialPort, qint32 baudrate, QSerialPort::Parity parity, QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits, QObject *parent = nullptr);
    ~ModbusRtuMasterImpl() override = default;

    QUuid modbusUuid() const override;
    QString serialPort() const override;
    qint32 baudrate() const override;
    QSerialPort::Parity parity() const override;
    QSerialPort::DataBits dataBits() const override;
    QSerialPort::StopBits stopBits() override;

    bool connected() const override;

    // Requests
    ModbusRtuReply *readCoil(int slaveAddress, int registerAddress, quint16 size = 1) override;
    ModbusRtuReply *readDiscreteInput(int slaveAddress, int registerAddress, quint16 size = 1) override;
    ModbusRtuReply *readInputRegister(int slaveAddress, int registerAddress, quint16 size = 1) override;
    ModbusRtuReply *readHoldingRegister(int slaveAddress, int registerAddress, quint16 size = 1) override;

    ModbusRtuReply *writeCoils(int slaveAddress, int registerAddress, const QVector<quint16> &values) override;
    ModbusRtuReply *writeHoldingRegisters(int slaveAddress, int registerAddress, const QVector<quint16> &values) override;

private:
    QUuid m_modbusUuid;
    bool m_connected = false;

#ifdef WITH_QTSERIALBUS
    QModbusRtuSerialMaster *m_modbus = nullptr;
#endif

    QString m_serialPort;
    qint32 m_baudrate;
    QSerialPort::Parity m_parity;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::StopBits m_stopBits;
};

}

#endif // MODBUSRTUMASTERIMPL_H
