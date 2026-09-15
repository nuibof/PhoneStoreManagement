#pragma once

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ProductsPage;
}
QT_END_NAMESPACE

class ProductsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsPage(
        const QString &position,
        QWidget *parent = nullptr
    );

    ~ProductsPage() override;

private slots:
    void onAddProduct();
    void onEditProduct();
    void onDeleteProduct();
    void onRefresh();
    void onSearch();

private:
    Ui::ProductsPage *ui;

    QString position;

    void setupTable();
    void loadProducts();
    void showProductDialog(int productId);
};