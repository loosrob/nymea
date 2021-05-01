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

#ifndef MODBUSRTUMASTER_H
#define MODBUSRTUMASTER_H

#include <QObject>
#include <QUuid>

#include "modbusrtureply.h"

class ModbusRtuMaster : public QObject
{
    Q_OBJECT
public:
    // Properties
    virtual QUuid modbusUuid() const = 0;
    virtual QString serialPort() const = 0;

    virtual bool connected() const = 0;

    // Requests
    virtual ModbusRtuReply *readCoil(uint slaveAddress, uint registerAddress, uint size = 1) = 0;
    virtual ModbusRtuReply *readDiscreteInput(uint slaveAddress, uint registerAddress, uint size = 1) = 0;
    virtual ModbusRtuReply *readInputRegister(uint slaveAddress, uint registerAddress, uint size = 1) = 0;
    virtual ModbusRtuReply *readHoldingRegister(uint slaveAddress, uint registerAddress, uint size = 1) = 0;

    virtual ModbusRtuReply *writeCoil(uint slaveAddress, uint registerAddress, bool status) = 0;
    virtual ModbusRtuReply *writeCoils(uint slaveAddress, uint registerAddress, const QVector<quint16> &values) = 0;

    virtual ModbusRtuReply *writeHoldingRegister(uint slaveAddress, uint registerAddress, quint16 value) = 0;
    virtual ModbusRtuReply *writeHoldingRegisters(uint slaveAddress, uint registerAddress, const QVector<quint16> &values) = 0;

protected:
    explicit ModbusRtuMaster(QObject *parent = nullptr) : QObject(parent) { };
    virtual ~ModbusRtuMaster() = default;

signals:
    void connectedChanged(bool connected);

};

#endif // MODBUSRTUMASTER_H
