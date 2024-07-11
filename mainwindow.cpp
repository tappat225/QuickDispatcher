#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>
#include <IPHlpApi.h>
#include <vector>
#include <string>

std::vector<std::string> getNetworkInterfaceNames() {
    std::vector<std::string> interfaceNames;

    ULONG bufferSize = 0;
    if (GetAdaptersInfo(NULL, &bufferSize) != ERROR_BUFFER_OVERFLOW) {
        return interfaceNames;
    }

    std::vector<BYTE> buffer(bufferSize);
    PIP_ADAPTER_INFO pAdapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(buffer.data());

    if (GetAdaptersInfo(pAdapterInfo, &bufferSize) == NO_ERROR) {
        while (pAdapterInfo) {
            interfaceNames.push_back(pAdapterInfo->Description);
            pAdapterInfo = pAdapterInfo->Next;
        }
    }

    return interfaceNames;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
    // networkInterfacesComboBox = new QComboBox(this);
    // setCentralWidget(networkInterfacesComboBox);

    // // 获取网络接口列表
    // QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    // // 将网络接口名称添加到下拉菜单
    // for (const QNetworkInterface &interface : interfaces) {
    //     networkInterfacesComboBox->addItem(interface.name());
    // }

    networkInterfacesComboBox = new QComboBox(this);
    setCentralWidget(networkInterfacesComboBox);

    // 获取网络接口名称
    std::vector<std::string> interfaceNames = getNetworkInterfaceNames();

    // 将网络接口名称添加到下拉菜单
    for (const auto& name : interfaceNames) {
        networkInterfacesComboBox->addItem(QString::fromStdString(name));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
