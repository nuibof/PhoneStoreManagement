#pragma once

#include <QAbstractItemView>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

namespace UiStyle {
inline void page(QWidget *widget) {
    if (widget->layout()) {
        widget->layout()->setContentsMargins(24, 24, 24, 24);
        widget->layout()->setSpacing(16);
    }
    if (auto *search = widget->findChild<QLineEdit *>("txtSearch")) {
        search->setClearButtonEnabled(true);
        search->setMinimumWidth(180);
        search->setFixedHeight(40);
    }
    if (auto *subtitle = widget->findChild<QLabel *>("lblSubtitle"))
        subtitle->setWordWrap(true);
}

inline void table(QTableWidget *table, int actionsColumn) {
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setShowGrid(false);
    table->verticalHeader()->hide();
    table->verticalHeader()->setDefaultSectionSize(45);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(actionsColumn, QHeaderView::Fixed);
    table->setColumnWidth(actionsColumn, 88);
}

inline void actions(QPushButton *edit, QPushButton *remove, QHBoxLayout *layout) {
    for (auto *button : {edit, remove}) {
        const bool isEdit = button == edit;
        button->setText({});
        button->setIcon(QIcon(isEdit ? ":/icons/edit.svg" : ":/icons/delete.svg"));
        button->setIconSize(QSize(18, 18));
        button->setFixedSize(30, 30);
        button->setToolTip(isEdit ? "Edit" : "Delete");
        button->setCursor(Qt::PointingHandCursor);
    }
    layout->setContentsMargins(4, 2, 4, 2);
    layout->setSpacing(6);
    layout->setAlignment(Qt::AlignCenter);
}

inline void form(QDialogButtonBox *buttons, bool editing) {
    if (auto *save = buttons->button(QDialogButtonBox::Ok))
        save->setText(editing ? "Save changes" : "Add");
}
}
