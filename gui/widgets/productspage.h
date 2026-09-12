#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ProductsPage;
}
QT_END_NAMESPACE

class ProductsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsPage(QWidget *parent = nullptr);
    ~ProductsPage();

private slots:
    void onAddProduct();
    void onEditProduct();
    void onDeleteProduct();
    void onRefresh();
    void onSearch();

private:
    Ui::ProductsPage *ui;

    void setupTable();
    void loadProducts();
};