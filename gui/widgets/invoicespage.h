#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class InvoicesPage;
}
QT_END_NAMESPACE

class InvoicesPage : public QWidget
{
    Q_OBJECT

public:
    explicit InvoicesPage(QWidget *parent = nullptr);
    ~InvoicesPage();

private slots:
    void onAddInvoice();
    void onEditInvoice();
    void onDeleteInvoice();
    void onRefresh();
    void onSearch();

private:
    Ui::InvoicesPage *ui;

    void setupTable();
    void loadInvoices();
};