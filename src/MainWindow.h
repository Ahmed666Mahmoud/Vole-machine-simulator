#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "Machine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLoad_clicked();
    void on_actionLoadFile_triggered();
    void on_btnStep_clicked();
    void on_actionStep_triggered();
    void on_btnRun_clicked();
    void on_actionRun_triggered();
    void on_btnReset_clicked();
    void on_actionReset_triggered();
    void on_btnClearAll_clicked();
    void on_actionClearAll_triggered();
    void on_actionExit_triggered();
    void on_btnSetMemory_clicked();
    void on_btnClearMemory_clicked();
    void on_actionClearMemory_triggered();
    void on_btnSetRegister_clicked();
    void on_btnClearRegisters_clicked();
    void on_actionClearRegisters_triggered();
    void on_btnClearScreen_clicked();
    void on_btnClearLog_clicked();
    void on_tableMemory_cellClicked(int row, int column);
    void on_tableRegisters_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Machine machine;

    void setupTables();
    void updateUI();
    void updateMemoryTable();
    void updateRegisterTable();
    void updateCPUState();
    void updateScreenOutput();
    void logMessage(const QString &msg);
};

#endif // MAINWINDOW_H
