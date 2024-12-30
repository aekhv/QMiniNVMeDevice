#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMiniNVMeDevice.h>
#include <QTimer>

#define output(s) ui->plainTextEdit->appendPlainText(s)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->refreshButton, &QPushButton::pressed, this, &MainWindow::refresh);
    connect(ui->commonInfoButton, &QPushButton::pressed, this, &MainWindow::commonInfo);
    connect(ui->healthButton, &QPushButton::pressed, this, &MainWindow::healthInfo);
    connect(ui->readTestButton, &QPushButton::pressed, this, &MainWindow::readTest);
    connect(ui->resetButton, &QPushButton::pressed, this, &MainWindow::controllerReset);

    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    ui->deviceBox->clear();
    const QStringList devices = QMiniNVMeDevice::availableDevices();
    foreach (const QString dev, devices)
        ui->deviceBox->addItem(dev);
}

void MainWindow::commonInfo()
{
    QMiniNVMeDevice nvme;
    const QString dev = ui->deviceBox->currentText();

    output("");

    if (!nvme.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** COMMON INFO ***\n");

    QMiniNVMeControllerVersion ver = nvme.controllerVersion();
    output(QString("NVMe controller version: %1")
           .arg(ver.toString()));

    QMiniNVMeControllerState state = nvme.controllerState();
    output(QString("NVMe controller state: enabled - %1, ready - %2, fatal - %3\n")
           .arg(state.enabled() ? "YES" : "NO")
           .arg(state.ready() ? "YES" : "NO")
           .arg(state.fatal() ? "YES" : "NO"));

    QMiniNVMeControllerInfo ci = nvme.controllerInfo();
    if (!nvme.lastError().success()) {
        output("Device communication error!");
        return;
    }
    output(QString("Model name: %1")
           .arg(ci.modelName()));
    output(QString("Firmware revision: %1")
           .arg(ci.firmwareRevision()));
    output(QString("Serial number: %1")
           .arg(ci.serialNumber()));
    output(QString("Capacity: %1 GB")
           .arg(ci.totalCapacity() / (1000.0 * 1000.0 * 1000.0), 0, 'f', 1));
    output(QString("Maximum data transef size: %1 bytes\n")
           .arg(ci.maxDataTransferSize()));

    if (ci.namespaceCount() == 0) {
        output("Namespaces are not found!");
        return;
    }

    for (int i = 1; i <= ci.namespaceCount(); i++) {
        output(QString("Namespace %1 details:").arg(i));

        QMiniNVMeNamespaceInfo ni = nvme.namespaceInfo(i);
        if (!nvme.lastError().success()) {
            output("Device communication error!");
            return;
        }
        output(QString("-> Total size: %1 sectors")
               .arg(ni.totalSize()));
        output(QString("-> Sector size: %1 bytes\n")
               .arg(ni.sectorSize()));
    }
}

void MainWindow::healthInfo()
{
    QMiniNVMeDevice nvme;
    const QString dev = ui->deviceBox->currentText();

    output("");

    if (!nvme.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** HEALTH INFO ***\n");

    QMiniNVMeLogPageHealthInfo health = nvme.logPageHealthInfo();
    if (!nvme.lastError().success()) {
        output("Device communication error!");
        return;
    }

    output(QString("Critical warning: %1")
           .arg(QMiniNVMeLogPageHealthInfo::criticalWarningToStringList(health.criticalWarning()).join("; ")));
    output(QString("Composite temperature: %1 °C")
           .arg(health.compositeTemperature() - 273));
    output(QString("Available spare: %1 %")
           .arg(health.availableSpare()));
    output(QString("Available spare threshold: %1 %")
           .arg(health.availableSpareThreshold()));
    output(QString("Percentage used: %1 %")
           .arg(health.percentageUsed()));
    output(QString("Data units read: %1 (%2 GiB)")
           .arg(health.dataUnitsRead()).arg(health.dataUnitsRead() * 512 * 1000 / (1024 * 1024 * 1024)));
    output(QString("Data units written: %1 (%2 GiB)")
           .arg(health.dataUnitsWritten()).arg(health.dataUnitsWritten() * 512 * 1000 / (1024 * 1024 * 1024)));
    output(QString("Host read commands: %1")
           .arg(health.hostReadCommands()));
    output(QString("Host write commands: %1")
           .arg(health.hostWriteCommands()));
    output(QString("Controller busy time: %1 m")
           .arg(health.controllerBusyTime()));
    output(QString("Power cycles: %1")
           .arg(health.powerCycles()));
    output(QString("Power on hours: %1")
           .arg(health.powerOnHours()));
    output(QString("Unsafe shutdowns: %1")
           .arg(health.unsafeShutdowns()));
    output(QString("Media and data integrity errors: %1")
           .arg(health.mediaAndDataIntegrityErrors()));
    output(QString("Number of error information log entries: %1")
           .arg(health.numberOfErrorInformationLogEntries()));
    output(QString("Warning composite temperature time: %1 m")
           .arg(health.warningCompositeTemperatureTime()));
    output(QString("Critical composite temperature time: %1 m")
           .arg(health.criticalCompositeTemperatureTime()));
    int n = 0;
    foreach (int t, health.temperatureSensors()) {
        n++;
        if (t != 0)
            output(QString("Temperature sensor #%1: %2 °C")
                   .arg(n).arg(t - 273));
        else
            output(QString("Temperature sensor #%1: no sensor")
                   .arg(n));
    }
    output(QString("Thermal management temperature 1 transition count: %1")
           .arg(health.TMT1TransitionCount()));
    output(QString("Thermal management temperature 2 transition count: %1")
           .arg(health.TMT2TransitionCount()));
    output(QString("Total time for thermal management temperature 1: %1 s")
           .arg(health.totalTimeForTMT1()));
    output(QString("Total time for thermal management temperature 2: %1 s")
           .arg(health.totalTimeForTMT2()));
}

void MainWindow::readTest()
{
    QMiniNVMeDevice nvme;
    const QString dev = ui->deviceBox->currentText();

    output("");

    if (!nvme.open(dev)) {
        output("Device opening error!");
        return;
    }

    QMiniNVMeControllerInfo ci = nvme.controllerInfo();
    if (!nvme.lastError().success()) {
        output("Device communication error!");
        return;
    }

    output("*** READ TEST ***\n");

    if (ci.namespaceCount() == 0) {
        output("Namespaces are not found!");
        return;
    }

    // NOTE! You should never request a data:
    // 1. more than ci.maxDataTransferSize();
    // 2. more tnan NVME_BUFFER_SIZE_MAX described in "mininvme/driver.h"
    QByteArray buffer(ci.maxDataTransferSize(), 0);

    for (int i = 1; i <= ci.namespaceCount(); i++) {
        QMiniNVMeNamespaceInfo ni = nvme.namespaceInfo(i);
        if (!nvme.lastError().success()) {
            output("\nDevice communication error!\n");
            return;
        }

        const quint32 count = buffer.size() / ni.sectorSize();
        quint64 offset = 0;

        int t = 5000; // Time for testing in ms
        QTimer timer;
        timer.setSingleShot(true);
        timer.start(t);

        while (timer.remainingTime() > 0) {
            nvme.read(offset, count, buffer.data(), buffer.size(), i);

            // Basic error handling...
            if (!nvme.lastError().success()) {
                output(nvme.lastError().toString());
                if (nvme.lastError().type() == QMiniPCIError::DeviceError) {
                    QMiniNVMeError err = nvme.deviceError();
                    output(QString("Status code type: %1")
                           .arg(QMiniNVMeError::statusCodeTypeToString(err.statusCodeType())));
                    output(QString("Status code: %1")
                           .arg(QMiniNVMeError::statusCodeToString(err.statusCodeType(), err.statusCode())));
                    output(QString("More bit: %1")
                           .arg(err.moreBit() ? "TRUE" : "FALSE"));
                    output(QString("Do not retry bit: %1")
                           .arg(err.moreBit() ? "TRUE" : "FALSE"));
                }
                return;
            }

            offset += count;
        }

        double speed = (offset * ni.sectorSize()) / (t * 1000.0);
        output(QString("Namespace %1 average read speed: %2 MB/sec\n")
               .arg(i)
               .arg(speed, 0, 'f', 1));
    }
}

void MainWindow::controllerReset()
{
    QMiniNVMeDevice nvme;
    const QString dev = ui->deviceBox->currentText();

    if (!nvme.open(dev)) {
        output("Device opening error!");
        return;
    }

    nvme.controllerReset();
}

