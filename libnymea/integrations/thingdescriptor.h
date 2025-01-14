/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2020, nymea GmbH
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

#ifndef THINGDESCRIPTION_H
#define THINGDESCRIPTION_H

#include "libnymea.h"
#include "typeutils.h"
#include "types/param.h"

#include <QVariantMap>

class LIBNYMEA_EXPORT ThingDescriptor
{
    Q_GADGET
    Q_PROPERTY(QUuid id READ id)
    Q_PROPERTY(QUuid thingId READ thingId USER true)
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(ParamList deviceParams READ params REVISION 1) // Had been forgotten in the device->thing transition.
    Q_PROPERTY(ParamList params READ params)                  // added in 0.27

public:
    ThingDescriptor();
    ThingDescriptor(const ThingClassId &thingClassId, const QString &title = QString(), const QString &description = QString(), const ThingId &parentId = ThingId());
    ThingDescriptor(const ThingDescriptorId &id, const ThingClassId &thingClassId, const QString &title = QString(), const QString &description = QString(), const ThingId &parentId = ThingId());

    bool isValid() const;

    ThingDescriptorId id() const;
    ThingClassId thingClassId() const;

    ThingId thingId() const;
    void setThingId(const ThingId &thingId);

    QString title() const;
    void setTitle(const QString &title);

    QString description() const;
    void setDescription(const QString &description);

    ThingId parentId() const;
    void setParentId(const ThingId &parentId);

    ParamList params() const;
    void setParams(const ParamList &params);

private:
    ThingDescriptorId m_id;
    ThingClassId m_thingClassId;
    ThingId m_thingId;
    QString m_title;
    QString m_description;
    ThingId m_parentId;
    ParamList m_params;
};

class ThingDescriptors: public QList<ThingDescriptor>
{
    Q_GADGET
    Q_PROPERTY(int count READ count)
public:
    ThingDescriptors() {}
    inline ThingDescriptors(std::initializer_list<ThingDescriptor> args): QList(args) {}
    ThingDescriptors(const QList<ThingDescriptor> &other): QList<ThingDescriptor>(other) {}
    Q_INVOKABLE QVariant get(int index) const;
    Q_INVOKABLE void put(const QVariant &variant);
};

Q_DECLARE_METATYPE(ThingDescriptor)
Q_DECLARE_METATYPE(ThingDescriptors)

#endif // THINGDESCRIPTION_H
