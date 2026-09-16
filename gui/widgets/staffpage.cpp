#include "../UiStyle.h"
//
// Created by Nam B on 9/13/2026.
//

#include "staffpage.h"
#include "ui_StaffPage.h"

#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "addstaffdialog.h"
#include "managers/EmployeeManager.h"
#include "managers/AuthManager.h"

StaffPage::StaffPage(AuthManager *authManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StaffPage)
    , authManager(authManager)
{
    ui->setupUi(this);
    UiStyle::page(this);

    setupTable();

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &StaffPage::onAddStaff);

    connect(ui->btnRefresh, &QPushButton::clicked,
            this, &StaffPage::onRefresh);

    connect(ui->txtSearch, &QLineEdit::textChanged,
            this, &StaffPage::onSearch);

    loadStaff();
}


StaffPage::~StaffPage()
{
    delete ui;
}


void StaffPage::setupTable()
{
    ui->tblStaff->setColumnCount(7);

    QStringList headers = {
        "ID",
        "Full Name",
        "Phone",
        "Email",
        "Position",
        "Username",
        "Actions"
    };

    ui->tblStaff->setHorizontalHeaderLabels(headers);

    ui->tblStaff->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    ui->tblStaff->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    ui->tblStaff->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    ui->tblStaff->setAlternatingRowColors(true);

    ui->tblStaff->verticalHeader()->setVisible(false);
    ui->tblStaff->verticalHeader()->setDefaultSectionSize(45);

    QHeaderView *header = ui->tblStaff->horizontalHeader();

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::Stretch);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    UiStyle::table(ui->tblStaff, 6);
}

void StaffPage::loadStaff()
{
    ui->tblStaff->setRowCount(0);

    EmployeeManager employeeManager;
    QList<EmployeeData> employees = employeeManager.getAllEmployees();

    for (const auto &staff : employees)
    {
        int row = ui->tblStaff->rowCount();

        ui->tblStaff->insertRow(row);

        // ID
        ui->tblStaff->setItem(
            row,
            0,
            new QTableWidgetItem(QString::number(staff.id))
        );

        // Full Name
        ui->tblStaff->setItem(
            row,
            1,
            new QTableWidgetItem(staff.fullName)
        );

        // Phone
        ui->tblStaff->setItem(
            row,
            2,
            new QTableWidgetItem(staff.phone)
        );

        // Email
        ui->tblStaff->setItem(
            row,
            3,
            new QTableWidgetItem(staff.email)
        );

        // Position
        ui->tblStaff->setItem(
            row,
            4,
            new QTableWidgetItem(staff.position)
        );

        // Username
        ui->tblStaff->setItem(
            row,
            5,
            new QTableWidgetItem(staff.username)
        );

        // Actions
        QWidget *actionWidget = new QWidget();
        actionWidget->setObjectName("actionWidget");

        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(4, 2, 4, 2);
        actionLayout->setSpacing(6);

        QPushButton *btnEdit = new QPushButton("Edit");
        QPushButton *btnDelete = new QPushButton("Delete");

        btnEdit->setProperty("employeeId", staff.id);
        btnDelete->setProperty("employeeId", staff.id);

        btnEdit->setFixedHeight(30);
        btnDelete->setFixedHeight(30);

        btnEdit->setCursor(Qt::PointingHandCursor);
        btnDelete->setCursor(Qt::PointingHandCursor);

        // ===== EDIT STYLE =====

        // ===== DELETE STYLE =====

        actionLayout->addWidget(btnEdit);
        actionLayout->addWidget(btnDelete);
        UiStyle::actions(btnEdit, btnDelete, actionLayout);


        ui->tblStaff->setCellWidget(
            row,
            6,
            actionWidget
        );

        connect(
            btnEdit,
            &QPushButton::clicked,
            this,
            &StaffPage::onEditStaff
        );

        connect(
            btnDelete,
            &QPushButton::clicked,
            this,
            &StaffPage::onDeleteStaff
        );
    }
    onSearch();
}


void StaffPage::onAddStaff()
{
    AddStaffDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        loadStaff();
    }
}


void StaffPage::onEditStaff()
{
    auto *button =
        qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int employeeId =
        button->property("employeeId").toInt();

    AddStaffDialog dialog(employeeId, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        loadStaff();
    }
}


void StaffPage::onDeleteStaff()
{
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int employeeId =
        button->property("employeeId").toInt();

    EmployeeManager employeeManager;

    EmployeeData employee =
        employeeManager.getEmployeeById(employeeId);

    // Không cho nhân viên tự xóa chính tài khoản đang đăng nhập
    if (employee.username == authManager->getCurrentUsername())
    {
        QMessageBox::warning(
            this,
            "Delete Staff",
            "You cannot delete your own account."
        );
        return;
    }

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Delete Staff",
            QString(
                "Are you sure you want to delete staff ID %1?"
            ).arg(employeeId),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No
        );

    if (reply != QMessageBox::Yes)
        return;

    if (employeeManager.deleteEmployee(employeeId))
    {
        QMessageBox::information(
            this,
            "Delete Staff",
            "Staff deleted successfully."
        );

        loadStaff();
    }
    else
    {
        QMessageBox::critical(
            this,
            "Delete Staff",
            "Failed to delete staff."
        );
    }
}

void StaffPage::onRefresh()
{
    loadStaff();
}


void StaffPage::onSearch()
{
    QString searchTerm =
        ui->txtSearch->text().trimmed();

    if (searchTerm.isEmpty())
    {
        for (int row = 0;
             row < ui->tblStaff->rowCount();
             ++row)
        {
            ui->tblStaff->setRowHidden(row, false);
        }

        return;
    }

    for (int row = 0;
         row < ui->tblStaff->rowCount();
         ++row)
    {
        bool match = false;

        // Search columns 0 -> 5
        // Do not search Actions column
        for (int col = 0; col < 6; ++col)
        {
            QTableWidgetItem *item =
                ui->tblStaff->item(row, col);

            if (item &&
                item->text().contains(
                    searchTerm,
                    Qt::CaseInsensitive
                ))
            {
                match = true;
                break;
            }
        }

        ui->tblStaff->setRowHidden(
            row,
            !match
        );
    }
}