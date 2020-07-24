#include "socks5editdialog.h"
#include "ui_socks5editdialog.h"
#include "portvalidator.h"

Socks5EditDialog::Socks5EditDialog(Connection *_connection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Socks5EditDialog),
    connection(_connection)
{
    ui->setupUi(this);

    /* initialisation and validator setup */
    PortValidator *portValidator = new PortValidator(this);
    ui->serverPortEdit->setValidator(portValidator);

    ui->nameEdit->setText(connection->profile.name);
    ui->serverAddrEdit->setText(connection->profile.serverAddress);
    ui->serverPortEdit->setText(QString::number(connection->profile.serverPort));
    ui->usernameEdit->setText(connection->profile.username);
    ui->pwdEdit->setText(connection->profile.password);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Socks5EditDialog::save);

    this->adjustSize();
}

Socks5EditDialog::~Socks5EditDialog()
{
    delete ui;
}

void Socks5EditDialog::save()
{
    connection->profile.type = "socks5";
    connection->profile.name = ui->nameEdit->text();
    connection->profile.serverAddress = ui->serverAddrEdit->text().trimmed();
    connection->profile.serverPort = ui->serverPortEdit->text().toUShort();
    connection->profile.username = ui->usernameEdit->text();
    connection->profile.password = ui->pwdEdit->text();

    this->accept();
}
