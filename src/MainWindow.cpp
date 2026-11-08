#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set initial splitter distribution so memory table has full width
    ui->splitterMain->setSizes(QList<int>() << 650 << 450);

    setupTables();
    updateUI();
    logMessage("Vole Machine Simulator initialized. Ready.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTables()
{
    // Apply clean styling to guarantee visibility across Dark/Light system themes
    QString tableStyle = 
        "QTableWidget { background-color: #ffffff; color: #111111; gridline-color: #d0d0d0; "
        "font-family: 'Consolas', 'Courier New', monospace; font-size: 12px; }"
        "QHeaderView::section { background-color: #e8e8e8; color: #111111; font-weight: bold; border: 1px solid #c0c0c0; }"
        "QTableWidget::item:selected { background-color: #0078d7; color: #ffffff; }";

    ui->tableMemory->setStyleSheet(tableStyle);
    ui->tableRegisters->setStyleSheet(tableStyle);

    // Setup Memory Table (16 x 16 Grid)
    ui->tableMemory->setRowCount(16);
    ui->tableMemory->setColumnCount(16);

    QStringList colHeaders;
    for (int c = 0; c < 16; ++c) {
        colHeaders << QString("%1").arg(c, 1, 16).toUpper();
    }
    ui->tableMemory->setHorizontalHeaderLabels(colHeaders);

    QStringList rowHeaders;
    for (int r = 0; r < 16; ++r) {
        rowHeaders << QString("%1").arg(r * 16, 2, 16, QChar('0')).toUpper();
    }
    ui->tableMemory->setVerticalHeaderLabels(rowHeaders);

    ui->tableMemory->horizontalHeader()->setDefaultSectionSize(36);
    ui->tableMemory->verticalHeader()->setDefaultSectionSize(26);

    for (int r = 0; r < 16; ++r) {
        for (int c = 0; c < 16; ++c) {
            QTableWidgetItem *item = new QTableWidgetItem("00");
            item->setTextAlignment(Qt::AlignCenter);
            item->setForeground(QColor(17, 17, 17));
            item->setBackground(QColor(255, 255, 255));
            ui->tableMemory->setItem(r, c, item);
        }
    }

    // Setup Register Table (16 rows, 2 columns: Reg Name, Value)
    ui->tableRegisters->setRowCount(16);
    ui->tableRegisters->setColumnCount(2);
    ui->tableRegisters->setHorizontalHeaderLabels(QStringList() << "Register" << "Value");
    ui->tableRegisters->horizontalHeader()->setStretchLastSection(true);
    ui->tableRegisters->verticalHeader()->setVisible(false);

    ui->comboRegister->clear();
    for (int i = 0; i < 16; ++i) {
        QString regName = QString("R%1").arg(i, 1, 16).toUpper();
        ui->comboRegister->addItem(regName);

        QTableWidgetItem *nameItem = new QTableWidgetItem(regName);
        nameItem->setTextAlignment(Qt::AlignCenter);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        nameItem->setForeground(QColor(17, 17, 17));
        nameItem->setBackground(QColor(245, 245, 245));
        ui->tableRegisters->setItem(i, 0, nameItem);

        QTableWidgetItem *valItem = new QTableWidgetItem("00");
        valItem->setTextAlignment(Qt::AlignCenter);
        valItem->setForeground(QColor(17, 17, 17));
        valItem->setBackground(QColor(255, 255, 255));
        ui->tableRegisters->setItem(i, 1, valItem);
    }
}

void MainWindow::updateUI()
{
    updateCPUState();
    updateMemoryTable();
    updateRegisterTable();
    updateScreenOutput();
}

void MainWindow::updateCPUState()
{
    int pc = machine.getPC();
    ui->lblPCValue->setText(QString("0x%1").arg(pc, 2, 16, QChar('0')).toUpper());

    string ir = machine.getIR();
    ui->lblIRValue->setText(ir.empty() ? "----" : QString::fromStdString(ir));

    if (machine.isHalted()) {
        ui->lblStatusValue->setText("HALTED");
        ui->lblStatusValue->setStyleSheet("font-size: 14px; font-weight: bold; color: red;");
    } else {
        ui->lblStatusValue->setText("READY");
        ui->lblStatusValue->setStyleSheet("font-size: 14px; font-weight: bold; color: green;");
    }
}

void MainWindow::updateMemoryTable()
{
    int currentPC = machine.getPC();

    for (int r = 0; r < 16; ++r) {
        for (int c = 0; c < 16; ++c) {
            int address = r * 16 + c;
            int value = machine.getMemoryCell(address);

            QTableWidgetItem *item = ui->tableMemory->item(r, c);
            if (!item) {
                item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableMemory->setItem(r, c, item);
            }

            item->setText(QString("%1").arg(value, 2, 16, QChar('0')).toUpper());

            // Highlight cells corresponding to the current PC (fetch address)
            if (!machine.isHalted() && (address == currentPC || address == currentPC + 1)) {
                item->setBackground(QColor(255, 230, 130)); // Distinct gold/yellow
                item->setForeground(QColor(0, 0, 0));       // Always black text
                QFont font = item->font();
                font.setBold(true);
                item->setFont(font);
            } else {
                item->setBackground(QColor(255, 255, 255)); // White background
                item->setForeground(QColor(17, 17, 17));    // Crisp black/dark text
                QFont font = item->font();
                font.setBold(false);
                item->setFont(font);
            }
        }
    }
}

void MainWindow::updateRegisterTable()
{
    for (int i = 0; i < 16; ++i) {
        string val = machine.getRegisterValue(i);
        QTableWidgetItem *valItem = ui->tableRegisters->item(i, 1);
        if (valItem) {
            valItem->setText(QString::fromStdString(val).toUpper());
            valItem->setForeground(QColor(17, 17, 17));
            valItem->setBackground(QColor(255, 255, 255));
        }
    }
}

void MainWindow::updateScreenOutput()
{
    string buf = machine.getScreenBuffer();
    if (buf.empty()) {
        ui->textScreen->setPlainText("");
        return;
    }

    QString displayText;
    for (unsigned char c : buf) {
        if (c >= 32 && c <= 126) {
            displayText += (char)c;
        } else if (c == '\n' || c == '\r' || c == '\t') {
            displayText += (char)c;
        } else {
            // Non-printable control characters (e.g. numeric byte 0x05)
            displayText += QString("[%1]").arg(c, 2, 16, QChar('0')).toUpper();
        }
    }
    ui->textScreen->setPlainText(displayText);
}

void MainWindow::logMessage(const QString &msg)
{
    QString timestamp = QTime::currentTime().toString("hh:mm:ss");
    ui->textLog->appendPlainText(QString("[%1] %2").arg(timestamp, msg));
    statusBar()->showMessage(msg, 3000);
}

void MainWindow::on_btnLoad_clicked()
{
    on_actionLoadFile_triggered();
}

void MainWindow::on_actionLoadFile_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Vole Machine Program",
        "",
        "Program Files (*.txt *.vole *.hex);;All Files (*.*)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    bool ok = false;
    int startAddress = ui->editStartAddress->text().trimmed().toInt(&ok, 16);
    if (!ok || startAddress < 0 || startAddress > 0xFE || startAddress % 2 != 0) {
        QMessageBox::warning(this, "Invalid Start Address",
                             "Start address must be an even hexadecimal number between 00 and FE.");
        return;
    }

    machine.clearScreen();

    if (machine.loadProgram(filePath.toStdString(), startAddress)) {
        logMessage(QString("Program loaded from '%1' at address 0x%2.")
                       .arg(filePath)
                       .arg(startAddress, 2, 16, QChar('0')).toUpper());
        updateUI();
        QMessageBox::information(this, "Success", "Program loaded successfully!");
    } else {
        logMessage("Failed to load program file.");
        QMessageBox::critical(this, "Error", "Failed to load program file. Please verify file format and content.");
    }
}

void MainWindow::on_btnStep_clicked()
{
    on_actionStep_triggered();
}

void MainWindow::on_actionStep_triggered()
{
    if (machine.isHalted()) {
        QMessageBox::information(this, "CPU Halted",
                                 "CPU is currently halted. Reset the CPU or load a new program.");
        return;
    }

    int pcBefore = machine.getPC();
    machine.step();
    int pcAfter = machine.getPC();
    string ir = machine.getIR();

    logMessage(QString("Step executed | PC: 0x%1 | IR: %2 | Next PC: 0x%3%4")
                   .arg(pcBefore, 2, 16, QChar('0')).toUpper()
                   .arg(QString::fromStdString(ir))
                   .arg(pcAfter, 2, 16, QChar('0')).toUpper()
                   .arg(machine.isHalted() ? " [HALTED]" : ""));

    updateUI();
}

void MainWindow::on_btnRun_clicked()
{
    on_actionRun_triggered();
}

void MainWindow::on_actionRun_triggered()
{
    if (machine.isHalted()) {
        QMessageBox::information(this, "CPU Halted",
                                 "CPU is currently halted. Reset the CPU or load a new program.");
        return;
    }

    const int MAX_STEPS = 50000;
    int stepsTaken = 0;

    while (!machine.isHalted() && stepsTaken < MAX_STEPS) {
        machine.step();
        stepsTaken++;
    }

    updateUI();

    if (stepsTaken >= MAX_STEPS && !machine.isHalted()) {
        logMessage(QString("Execution paused: Safety limit of %1 steps reached (possible infinite loop).").arg(MAX_STEPS));
        QMessageBox::warning(this, "Execution Paused",
                             "Safety step limit reached. Program was paused to prevent an infinite loop.");
    } else {
        logMessage(QString("Program completed in %1 step(s). CPU halted.").arg(stepsTaken));
    }
}

void MainWindow::on_btnReset_clicked()
{
    on_actionReset_triggered();
}

void MainWindow::on_actionReset_triggered()
{
    bool ok = false;
    int startAddress = ui->editStartAddress->text().trimmed().toInt(&ok, 16);
    if (!ok || startAddress < 0 || startAddress > 0xFE || startAddress % 2 != 0) {
        startAddress = 0;
        ui->editStartAddress->setText("00");
    }

    machine.reset(startAddress);
    logMessage(QString("CPU reset to address 0x%1.").arg(startAddress, 2, 16, QChar('0')).toUpper());
    updateUI();
}

void MainWindow::on_btnClearAll_clicked()
{
    on_actionClearAll_triggered();
}

void MainWindow::on_actionClearAll_triggered()
{
    bool ok = false;
    int startAddress = ui->editStartAddress->text().trimmed().toInt(&ok, 16);
    if (!ok || startAddress < 0 || startAddress > 0xFE || startAddress % 2 != 0) {
        startAddress = 0;
        ui->editStartAddress->setText("00");
    }

    machine.fullReset(startAddress);
    logMessage(QString("Full Reset executed: CPU, all 256 memory cells, registers, and screen cleared (PC = 0x%1).")
                   .arg(startAddress, 2, 16, QChar('0')).toUpper());
    updateUI();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_btnSetMemory_clicked()
{
    bool okAddr = false;
    int address = ui->editMemAddr->text().trimmed().toInt(&okAddr, 16);
    if (!okAddr || address < 0 || address > 0xFF) {
        QMessageBox::warning(this, "Invalid Address", "Address must be a hexadecimal number between 00 and FF.");
        return;
    }

    bool okVal = false;
    int value = ui->editMemVal->text().trimmed().toInt(&okVal, 16);
    if (!okVal || value < 0 || value > 0xFF) {
        QMessageBox::warning(this, "Invalid Value", "Value must be a hexadecimal byte between 00 and FF.");
        return;
    }

    machine.setMemoryCell(address, value);
    logMessage(QString("Memory [0x%1] updated to 0x%2")
                   .arg(address, 2, 16, QChar('0')).toUpper()
                   .arg(value, 2, 16, QChar('0')).toUpper());
    updateUI();
}

void MainWindow::on_btnClearMemory_clicked()
{
    on_actionClearMemory_triggered();
}

void MainWindow::on_actionClearMemory_triggered()
{
    machine.clearMemory();
    logMessage("Memory cleared: All 256 cells reset to 00.");
    updateUI();
}

void MainWindow::on_btnSetRegister_clicked()
{
    int regIndex = ui->comboRegister->currentIndex();
    if (regIndex < 0 || regIndex > 15) {
        return;
    }

    QString valStr = ui->editRegVal->text().trimmed().toUpper();
    bool ok = false;
    int val = valStr.toInt(&ok, 16);
    if (!ok || val < 0 || val > 0xFF) {
        QMessageBox::warning(this, "Invalid Value", "Register value must be a valid 2-digit hex byte (00 to FF).");
        return;
    }

    QString formattedVal = QString("%1").arg(val, 2, 16, QChar('0')).toUpper();
    machine.setRegisterValue(regIndex, formattedVal.toStdString());
    logMessage(QString("Register R%1 updated to %2").arg(regIndex, 1, 16).toUpper().arg(formattedVal));
    updateUI();
}

void MainWindow::on_btnClearRegisters_clicked()
{
    on_actionClearRegisters_triggered();
}

void MainWindow::on_actionClearRegisters_triggered()
{
    machine.clearRegisters();
    logMessage("Registers cleared: All registers (R0 to RF) reset to 00.");
    updateUI();
}

void MainWindow::on_btnClearScreen_clicked()
{
    machine.clearScreen();
    updateScreenOutput();
    logMessage("Screen buffer cleared.");
}

void MainWindow::on_btnClearLog_clicked()
{
    ui->textLog->clear();
}

void MainWindow::on_tableMemory_cellClicked(int row, int column)
{
    int address = row * 16 + column;
    ui->editMemAddr->setText(QString("%1").arg(address, 2, 16, QChar('0')).toUpper());
    int val = machine.getMemoryCell(address);
    ui->editMemVal->setText(QString("%1").arg(val, 2, 16, QChar('0')).toUpper());
}

void MainWindow::on_tableRegisters_cellClicked(int row, int /*column*/)
{
    if (row >= 0 && row < 16) {
        ui->comboRegister->setCurrentIndex(row);
        string val = machine.getRegisterValue(row);
        ui->editRegVal->setText(QString::fromStdString(val).toUpper());
    }
}
