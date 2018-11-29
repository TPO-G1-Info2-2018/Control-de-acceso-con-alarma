#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QFile>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QFile file("/home/ignacio/TPO/QT/data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        ui->textEditBaseDatos->append(line);
        }
    file.close();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_lineEdit_Nom_textChanged(const QString &arg1)
{

    Nombre = ui->lineEdit_Nom ->displayText();

}

void Dialog::on_lineEdit_ID_textEdited(const QString &arg1)
{

    ID = ui->lineEdit_ID ->displayText();

}


void Dialog::on_pushButton_Enrolar_clicked()
{
   int aux=ID.toInt();

   if(!ID.isEmpty() && !Nombre.isEmpty()){
       if(aux!=0 && aux<256 && aux>0){
            aplicar = 1;
            close();
       }
       else
           QMessageBox::information(this,tr("ERROR"),tr("El PageID debe ser un numero entre 1 y 255"));
   }
   else
   {
       QMessageBox::information(this,tr("ERROR"),tr("Falta completar campos"));
   }

}
void Dialog::on_pushButton_clicked()
{
    int aux=ID.toInt();

    if(!ID.isEmpty() && Nombre.isEmpty()){
        if(aux!=0 && aux<256 && aux>0){
             borrar = 1;
             close();
        }
        else
            QMessageBox::information(this,tr("ERROR"),tr("El PageID debe ser un numero entre 1 y 255"));
    }
    else
    {
        QMessageBox::information(this,tr("ERROR"),tr("Falta ID o hay nombre"));
    }

}
