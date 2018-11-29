#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "dialog.h"

#define ESPERO_MENSAJE      0
#define RECIBO_DATOS        1
#define FIN_DE_TRAMA        2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool conectado();
    void enumerarPuertos();
    void actualizarEstadoConexion();
    void procesarDatosRecibidos();

    void LeerBdD();

private slots:
    void on_datosRecibidos();
    void on_pushButtonRefreshPorts_clicked();
    void on_pushButtonConectar_clicked();


    void on_pushButtonEnroll_clicked();


private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QByteArray datosRecibidos;
    bool medidorActivo;
    Dialog* enrolldlog;
};

#endif // MAINWINDOW_H
