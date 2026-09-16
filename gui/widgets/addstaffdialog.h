#ifndef PHONESTOREMANAGEMENT_ADDSTAFFDIALOG_H
#define PHONESTOREMANAGEMENT_ADDSTAFFDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui {
    class AddStaffDialog;
}

QT_END_NAMESPACE

class AddStaffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffDialog(QWidget *parent = nullptr);

    explicit AddStaffDialog(
        int employeeId,
        QWidget *parent = nullptr
    );

    ~AddStaffDialog() override;

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    Ui::AddStaffDialog *ui;

    int employeeId;
    bool editMode;

    void loadEmployee();
};

#endif