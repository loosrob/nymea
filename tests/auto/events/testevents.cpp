/****************************************************************************
 *                                                                          *
 *  This file is part of guh.                                               *
 *                                                                          *
 *  Guh is free software: you can redistribute it and/or modify             *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, version 2 of the License.                 *
 *                                                                          *
 *  Guh is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *  GNU General Public License for more details.                            *
 *                                                                          *
 *  You should have received a copy of the GNU General Public License       *
 *  along with guh.  If not, see <http://www.gnu.org/licenses/>.            *
 *                                                                          *
 ***************************************************************************/

#include "guhtestbase.h"
#include "guhcore.h"
#include "devicemanager.h"
#include "mocktcpserver.h"

#include <QtTest/QtTest>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCoreApplication>

class TestEvents: public GuhTestBase
{
    Q_OBJECT

private slots:
    void triggerEvent();
};

void TestEvents::triggerEvent()
{
    QList<Device*> devices = GuhCore::instance()->deviceManager()->findConfiguredDevices(mockDeviceClassId);
    QVERIFY2(devices.count() > 0, "There needs to be at least one configured Mock Device for this test");
    Device *device = devices.first();

    QSignalSpy spy(GuhCore::instance()->deviceManager(), SIGNAL(eventTriggered(const Event&)));

    // Setup connection to mock client
    QNetworkAccessManager nam;

    // trigger event in mock device
    int port = device->paramValue("httpport").toInt();
    QNetworkRequest request(QUrl(QString("http://localhost:%1/generateevent?eventtypeid=%2").arg(port).arg(mockEvent1Id.toString())));
    QNetworkReply *reply = nam.get(request);
    reply->deleteLater();

    // Lets wait for the notification
    spy.wait();
    QCOMPARE(spy.count(), 1);

    // Make sure the event contains all the stuff we expect
    Event event = spy.at(0).at(0).value<Event>();
    QCOMPARE(event.eventTypeId(), mockEvent1Id);
    QCOMPARE(event.deviceId(), device->id());
}

#include "testevents.moc"
QTEST_MAIN(TestEvents)