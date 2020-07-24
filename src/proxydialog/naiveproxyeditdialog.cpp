#include "naiveproxyeditdialog.h"
#include "ui_naiveproxyeditdialog.h"
#include "portvalidator.h"

NaiveProxyEditDialog::NaiveProxyEditDialog(Connection *_connection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NaiveProxyEditDialog),
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

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NaiveProxyEditDialog::save);

    this->adjustSize();
}

NaiveProxyEditDialog::~NaiveProxyEditDialog()
{
    delete ui;
}

void NaiveProxyEditDialog::save()
{
    connection->profile.type = "naiveproxy";
    connection->profile.name = ui->nameEdit->text();
    connection->profile.serverAddress = ui->serverAddrEdit->text().trimmed();
    connection->profile.serverPort = ui->serverPortEdit->text().toUShort();
    connection->profile.username = ui->usernameEdit->text();
    connection->profile.password = ui->pwdEdit->text();

    this->accept();
}
