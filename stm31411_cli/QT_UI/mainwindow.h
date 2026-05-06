#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QMap>
#include "serialworker.h"
#include "packetparser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPacketParsed(QMap<int, SensorNode> nodes);
    void onLogLine(const QString &line);
    void onConnected(const QString &portName);
    void onDisconnected();
    void onSerialError(const QString &msg);

    void onBtnConnect();
    void onBtnSystemOn();
    void onBtnSystemOff();
    void onBtnSystemReset();
    void onBtnTare();
    void onBtnMonOn();
    void onBtnSendCli();
    void onBtnSaveSettings();
    void refreshPorts();

private:
    void setupUi();
    void setupConnections();
    void applyStyles();
    void updateStateLabel(const QString &state);
    void setConnectedState(bool connected);

    // ── UI 위젯 ──────────────────────────────────────────
    // Serial panel
    QComboBox    *m_cbPort;
    QPushButton  *m_btnConnect;
    QLabel       *m_lblConnStatus;

    // System control
    QPushButton  *m_btnSysOn;
    QPushButton  *m_btnSysOff;
    QPushButton  *m_btnSysReset;
    QPushButton  *m_btnTare;
    QPushButton  *m_btnMonOn;

    // State visualization
    QLabel       *m_lblState1;   // Weight Detection
    QLabel       *m_lblState2;   // Robot Arm Action
    QLabel       *m_lblState3;   // Conveyor Belt
    QLabel       *m_lblState4;   // Sorting Complete

    // Weight display
    QLabel       *m_lblWeight;
    QLabel       *m_lblSortResult;
    QLabel       *m_lblRefWeight;

    // Counters
    QLabel       *m_lblHeavyCount;
    QLabel       *m_lblLightCount;
    QProgressBar *m_pbHeavy;
    QProgressBar *m_pbLight;

    // Sensor values
    QLabel       *m_lblTemp;
    QLabel       *m_lblLed;
    QLabel       *m_lblUptime;

    // Log
    QTextEdit    *m_logEdit;

    // CLI
    QLineEdit    *m_cliInput;
    QPushButton  *m_btnSendCli;

    // Settings
    QLineEdit    *m_edRefWeight;
    QPushButton  *m_btnSaveSettings;

    // ── 내부 상태 ──────────────────────────────────────────
    SerialWorker *m_serial;
    PacketParser *m_parser;
    QTimer       *m_portTimer;

    bool    m_isConnected  = false;
    bool    m_monOn        = false;
    int     m_heavyCount   = 0;
    int     m_lightCount   = 0;
    float   m_refWeight    = 60.0f;  // CLASSIFY_HEAVY_G
    float   m_lastWeight   = 0.0f;
    QString m_currentState = "IDLE";
};