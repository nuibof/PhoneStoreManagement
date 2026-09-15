#include "addstaffdialog.h"
#include "ui_AddStaffDialog.h"

#include "managers/EmployeeManager.h"
#include "managers/EmployeeData.h"

#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>

AddStaffDialog::AddStaffDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddStaffDialog),
      employeeId(0),
      editMode(false)
{
    ui->setupUi(this);

    ui->cmbPosition->addItem("Manager");
    ui->cmbPosition->addItem("Sales");
    ui->cmbPosition->addItem("Warehouse");

    ui->btnSave->setText("Save");

    connect(
        ui->btnSave,
        &QPushButton::clicked,
        this,
        &AddStaffDialog::onSaveClicked
    );

    connect(
        ui->btnCancel,
        &QPushButton::clicked,
        this,
        &AddStaffDialog::onCancelClicked
    );
}


AddStaffDialog::AddStaffDialog(int employeeId,
                               QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddStaffDialog),
      employeeId(employeeId),
      editMode(true)
{
    ui->setupUi(this);

    ui->cmbPosition->addItem("Manager");
    ui->cmbPosition->addItem("Sales");
    ui->cmbPosition->addItem("Warehouse");

    ui->lblTitle->setText("Edit Staff");

    ui->lblSubtitle->setText(
        "Update staff information and account details."
    );

    ui->btnSave->setText("Update");

    loadEmployee();

    connect(
        ui->btnSave,
        &QPushButton::clicked,
        this,
        &AddStaffDialog::onSaveClicked
    );
    // Enter key press triggers save
    connect(
        ui->txtPassword,
        &QLineEdit::returnPressed,
        this,
        &AddStaffDialog::onSaveClicked
    );

    connect(
        ui->btnCancel,
        &QPushButton::clicked,
        this,
        &AddStaffDialog::onCancelClicked
    );
}


AddStaffDialog::~AddStaffDialog()
{
    delete ui;
}


void AddStaffDialog::onSaveClicked()
{
    qDebug() << "=== Add Staff Save Clicked ===";

    QString fullName =
        ui->txtFullName->text().trimmed();

    QString phone =
        ui->txtPhone->text().trimmed();

    QString email =
        ui->txtEmail->text().trimmed();

    QString username =
        ui->txtUsername->text().trimmed();

    QString password =
        ui->txtPassword->text();

    QString position =
        ui->cmbPosition->currentText();

    qDebug() << "Full Name:" << fullName;
    qDebug() << "Phone:" << phone;
    qDebug() << "Email:" << email;
    qDebug() << "Position:" << position;
    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;


    // =========================
    // VALIDATION
    // =========================

    if (fullName.isEmpty())
    {
        QMessageBox::warning(
            this,
            editMode ? "Edit Staff" : "Add Staff",
            "Please enter full name."
        );
        return;
    }

    if (phone.isEmpty())
    {
        QMessageBox::warning(
            this,
            editMode ? "Edit Staff" : "Add Staff",
            "Please enter phone number."
        );
        return;
    }

    if (email.isEmpty())
    {
        QMessageBox::warning(
            this,
            editMode ? "Edit Staff" : "Add Staff",
            "Please enter email."
        );
        return;
    }

    if (username.isEmpty())
    {
        QMessageBox::warning(
            this,
            editMode ? "Edit Staff" : "Add Staff",
            "Please enter username."
        );
        return;
    }

    if (password.isEmpty())
    {
        QMessageBox::warning(
            this,
            editMode ? "Edit Staff" : "Add Staff",
            "Please enter password."
        );
        return;
    }


    // =========================
    // CREATE EMPLOYEE DATA
    // =========================

    EmployeeData employee;

    employee.id = editMode ? employeeId : 0;
    employee.fullName = fullName;
    employee.phone = phone;
    employee.email = email;
    employee.position = position;
    employee.username = username;
    employee.password = password;


    // =========================
    // DATABASE
    // =========================

    EmployeeManager employeeManager;

    bool success = false;

    if (editMode)
    {
        qDebug() << "Updating employee ID:"
                 << employeeId;

        success =
            employeeManager.updateEmployee(employee);
    }
    else
    {
        qDebug() << "Adding employee:"
                 << employee.username;

        success =
            employeeManager.addEmployee(employee);
    }

    qDebug() << "Database result:"
             << success;


    // =========================
    // RESULT
    // =========================

    if (!success)
    {
        QMessageBox::critical(
            this,
            editMode ? "Edit Staff" : "Add Staff",
            editMode
                ? "Failed to update staff."
                : "Failed to add staff."
        );

        return;
    }

    QMessageBox::information(
        this,
        editMode ? "Edit Staff" : "Add Staff",
        editMode
            ? "Staff updated successfully."
            : "Staff added successfully."
    );

    accept();
}


void AddStaffDialog::loadEmployee()
{
    EmployeeManager employeeManager;

    EmployeeData employee =
        employeeManager.getEmployeeById(employeeId);

    if (employee.id == 0)
    {
        QMessageBox::critical(
            this,
            "Edit Staff",
            "Staff not found."
        );

        reject();
        return;
    }

    ui->txtFullName->setText(
        employee.fullName
    );

    ui->txtPhone->setText(
        employee.phone
    );

    ui->txtEmail->setText(
        employee.email
    );

    ui->txtUsername->setText(
        employee.username
    );

    ui->txtPassword->setText(
        employee.password
    );

    int positionIndex =
        ui->cmbPosition->findText(
            employee.position
        );

    if (positionIndex >= 0)
    {
        ui->cmbPosition->setCurrentIndex(
            positionIndex
        );
    }
}


void AddStaffDialog::onCancelClicked()
{
    reject();
}