#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT


public:

    QString Nombre;
    QString ID;
    int indice;
    bool aplicar = 0;
    bool borrar = 0;
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_lineEdit_Nom_textChanged(const QString &arg1);

    void on_lineEdit_ID_textEdited(const QString &arg1);

    void on_pushButton_Enrolar_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
