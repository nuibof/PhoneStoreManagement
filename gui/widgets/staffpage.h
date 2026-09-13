//
// Created by Nam B on 9/13/2026.
//

#ifndef PHONESTOREMANAGEMENT_STAFFPAGE_H
#define PHONESTOREMANAGEMENT_STAFFPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class StaffPage;
}

QT_END_NAMESPACE

class StaffPage : public QWidget {
    Q_OBJECT

public:
    explicit StaffPage(QWidget *parent = nullptr);

    ~StaffPage() override;
public slots:
    void onAddStaff();
    void onEditStaff();
    void onDeleteStaff();
    void onRefresh();
    void onSearch();
private:
    Ui::StaffPage *ui;
    void setupTable();
    void loadStaff();
};


#endif //PHONESTOREMANAGEMENT_STAFFPAGE_H
