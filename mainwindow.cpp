#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPortInfo>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <iostream>


static int valorRecibido;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    port = NULL;
    enumerarPuertos();
    actualizarEstadoConexion();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (port != NULL) {
        port->close();
        delete port;
    }
}

void MainWindow::enumerarPuertos()
{
    ui->comboBoxPuertos->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i < ports.size(); i++){
        ui->comboBoxPuertos->addItem(ports.at(i).portName(), ports.at(i).portName());
    }
}

void MainWindow::actualizarEstadoConexion()
{
    if (conectado()) {
        ui->lineEditEstado->setStyleSheet("font-weight: bold; color: black; background-color: lightgreen;");
        ui->lineEditEstado->setText("CONECTADO");
        ui->pushButtonConectar->setText("Desconectar");
    } else {
        ui->lineEditEstado->setStyleSheet("font-weight: normal; color: white; background-color: red;");
        ui->lineEditEstado->setText("Desconectado");
        ui->pushButtonConectar->setText("Conectar");
    }
}

bool MainWindow::conectado()
{
    if (port != NULL) {
        return (port->isOpen());
    } else
        return false;
}


void MainWindow::on_datosRecibidos()
{
    QByteArray bytesRx;
    int cant = port->bytesAvailable(); // devuelve la cantidad de bytes disponibles
    bytesRx.resize(cant);

    port->read(bytesRx.data(), bytesRx.size()); // guarda en bytesRx los datos recibidos

    datosRecibidos.append(bytesRx);

    procesarDatosRecibidos();

    LeerBdD();
}

void MainWindow::procesarDatosRecibidos()
{
    static unsigned int estadoRx = ESPERO_MENSAJE;
//    static int valorRecibido;


    for (int i = 0; i < datosRecibidos.count(); i++) {
        unsigned char dato = datosRecibidos.at(i);
        switch(estadoRx) {
        case ESPERO_MENSAJE:
            if(dato == '#') {
                valorRecibido = 0;
                estadoRx = RECIBO_DATOS;
            }
            break;

        case RECIBO_DATOS:
            valorRecibido = (dato);
            estadoRx = FIN_DE_TRAMA;
            break;

        case FIN_DE_TRAMA:
            if(dato == '$') {
                // agrego el nuevo dato recibido
                ui->textEditRecibido->append("RX: #"+QString::number(valorRecibido)+"$");
            }
            estadoRx = ESPERO_MENSAJE;
            break;
        }
    }
    datosRecibidos.clear();
}

void MainWindow::on_pushButtonRefreshPorts_clicked()
{
    enumerarPuertos();
}

void MainWindow::on_pushButtonConectar_clicked()
{
    //Si no hay conexión activa, creamos una nueva
    if (!port) {
        //Obtenemos el nombre del puerto del comboBox
        QString portName;
        int i = ui->comboBoxPuertos->currentIndex();
        portName = ui->comboBoxPuertos->itemData(i).toString();
        if (portName.isEmpty()) {
   //         QMessageBox::critical(this, QString::fromLatin1("Error de conexión"), QString::fromLatin1("Seleccione un puerto válido"));
            return;
        }
        //Creamos y configuramos el puerto
        port = new QSerialPort(portName);
        port->setBaudRate(QSerialPort::Baud9600);
        port->setFlowControl(QSerialPort::NoFlowControl);
        port->setParity(QSerialPort::NoParity);
        port->setDataBits(QSerialPort::Data8);
        port->setStopBits(QSerialPort::OneStop);
        //Abrimos el puerto en modo lectura-escritura
        if (port->open(QIODevice::ReadWrite) == true) {
            //Conectamos las señales que nos interesen
            connect(port, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
        }
        else {
            // Si hubo un error en la apertura...
  //          QMessageBox::critical(this, "Error", "No se puede abrir el puerto "+port->portName());
            delete port;
            port = NULL;
        }
    }
    else {
        //Si había una conexión activa, la cerramos
        port->close();
        delete port;
        port = NULL;
    }

    actualizarEstadoConexion();
}



void MainWindow::on_pushButtonEnroll_clicked()
{
    QString comando;

    if (conectado()) {

        //Para abrir el dialogo de enroll o borrado
        Dialog dialog;
        dialog.setModal(true);
        dialog.exec();

        if (dialog.aplicar){

            QFile file("/home/ignacio/TPO/QT/data.txt");
            if (file.open(QIODevice::Append)){

               QTextStream stream(&file);

               stream << dialog.ID << "," << dialog.Nombre << endl;

               file.close();

            }

            comando = "#"+(dialog.ID)+"$";
            dialog.aplicar = 0;

        }

        if(dialog.borrar){

            QFile file("/home/ignacio/TPO/QT/data.txt");
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
                return;

            QString s;

            QTextStream t(&file);

            while(!t.atEnd()){

                QString line = t.readLine();
                if(!line.contains(dialog.ID))
                    s.append(line + "\n");
            }

            file.resize(0);
            t << s;
            file.close();

            comando = "<"+(dialog.ID)+">";
            dialog.borrar = 0;

        }


        QByteArray msg;
        msg.append(comando);
        port->write(msg);
        ui->textEditRecibido->append("TX: "+comando);
    }
}

void MainWindow::LeerBdD(){

    QList<QByteArray> aux;

    QFile file("/home/ignacio/TPO/QT/data.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            aux = line.split(',');
            if(aux.first().toInt()== valorRecibido)
                ui->textEditBienvenido->append("Bienvenido: "+aux.last());
        }

    file.close();
}
