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


StaffPage::StaffPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StaffPage)
{
    ui->setupUi(this);

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

    // Row height
    ui->tblStaff->verticalHeader()->setDefaultSectionSize(45);
}


void StaffPage::loadStaff()
{
    ui->tblStaff->setRowCount(0);

    struct StaffData
    {
        int id;
        QString name;
        QString phone;
        QString email;
        QString position;
        QString username;
    };

    const QList<StaffData> staffList = {
        {
            1,
            "Nguyen Van An",
            "0901234567",
            "an@example.com",
            "Manager",
            "admin"
        },
        {
            2,
            "Tran Thi Binh",
            "0912345678",
            "binh@example.com",
            "Sales",
            "sales01"
        },
        {
            3,
            "Le Van Cuong",
            "0923456789",
            "cuong@example.com",
            "Warehouse",
            "warehouse01"
        },
        {
            4,
            "Pham Thi Dung",
            "0934567890",
            "dung@example.com",
            "Sales",
            "sales02"
        },
        {
            5,
            "Hoang Van Em",
            "0945678901",
            "em@example.com",
            "Warehouse",
            "warehouse02"
        }
    };

    for (const auto &staff : staffList)
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
            new QTableWidgetItem(staff.name)
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

        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(4, 2, 4, 2);
        actionLayout->setSpacing(6);

        QPushButton *btnEdit = new QPushButton("Edit");
        QPushButton *btnDelete = new QPushButton("Delete");

        btnEdit->setProperty(
            "employeeId",
            staff.id
        );

        btnDelete->setProperty(
            "employeeId",
            staff.id
        );

        btnEdit->setMinimumHeight(30);
        btnDelete->setMinimumHeight(30);

        actionLayout->addWidget(btnEdit);
        actionLayout->addWidget(btnDelete);

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
}


void StaffPage::onAddStaff()
{
    QMessageBox::information(
        this,
        "Add Staff",
        "Add staff functionality is not implemented yet."
    );
}


void StaffPage::onEditStaff()
{
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int employeeId =
        button->property("employeeId").toInt();

    QMessageBox::information(
        this,
        "Edit Staff",
        QString("Edit staff ID: %1").arg(employeeId)
    );
}


void StaffPage::onDeleteStaff()
{
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int employeeId =
        button->property("employeeId").toInt();

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Delete Staff",
            QString(
                "Are you sure you want to delete staff ID %1?"
            ).arg(employeeId),
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(
            this,
            "Delete Staff",
            "Staff deleted successfully."
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