#pragma once
#include <QApplication>
#include <QFile>
#include <QFont>
#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QIcon>
#include <QTimer>
#include <QEvent>

namespace UiStyle {
inline void install(QApplication &app) {
    app.setFont(QFont("Segoe UI", 10));
    QFile file(":/styles/app.qss");
    if (file.open(QIODevice::ReadOnly)) app.setStyleSheet(QString::fromUtf8(file.readAll()));
}
inline void page(QWidget *widget) {
    if (widget->layout()) {
        widget->layout()->setContentsMargins(24, 24, 24, 24);
        widget->layout()->setSpacing(16);
    }
    if (auto *search = widget->findChild<QLineEdit*>("txtSearch")) {
        search->setClearButtonEnabled(true);
        search->setAccessibleName("Search");
        search->setMinimumWidth(180);
        search->setFixedHeight(40);
    }
    for (const auto &name : {"btnAdd", "btnRefresh"}) {
        if (auto *button = widget->findChild<QPushButton*>(name)) {
            button->setFixedHeight(40);
            button->setCursor(Qt::PointingHandCursor);
        }
    }
    if (auto *subtitle = widget->findChild<QLabel*>("lblSubtitle")) subtitle->setWordWrap(true);
}
// Fit content first, then share spare viewport space between data columns.
class ResponsiveColumns : public QObject {
public:
    ResponsiveColumns(QTableWidget *table, int actions)
        : QObject(table), table_(table), actions_(actions) {
        table_->installEventFilter(this);
        table_->viewport()->installEventFilter(this);
        auto *model = table_->model();
        connect(model, &QAbstractItemModel::dataChanged, this, [this] { schedule(); });
        connect(model, &QAbstractItemModel::rowsInserted, this, [this] { schedule(); });
        connect(model, &QAbstractItemModel::rowsRemoved, this, [this] { schedule(); });
        connect(model, &QAbstractItemModel::modelReset, this, [this] { schedule(); });
        schedule();
    }
protected:
    bool eventFilter(QObject *object, QEvent *event) override {
        if (event->type() == QEvent::Resize || event->type() == QEvent::Show
            || event->type() == QEvent::FontChange || event->type() == QEvent::StyleChange)
            schedule();
        return QObject::eventFilter(object, event);
    }
private:
    void schedule() {
        if (pending_) return;
        pending_ = true;
        QTimer::singleShot(0, this, [this] {
            pending_ = false;
            auto *header = table_->horizontalHeader();
            header->resizeSections(QHeaderView::ResizeToContents);
            header->resizeSection(actions_, 88);
            int total = 0;
            QList<int> flexible;
            for (int column = 0; column < header->count(); ++column) {
                if (header->isSectionHidden(column)) continue;
                total += header->sectionSize(column);
                if (column != 0 && column != actions_) flexible.append(column);
            }
            const int spare = table_->viewport()->width() - total;
            if (spare > 0 && !flexible.isEmpty()) {
                const int share = spare / flexible.size();
                int remainder = spare % flexible.size();
                for (int column : flexible)
                    header->resizeSection(column, header->sectionSize(column) + share
                        + (remainder-- > 0 ? 1 : 0));
            }
        });
    }
    QTableWidget *table_;
    int actions_;
    bool pending_ = false;
};


inline void table(QTableWidget *table, int actions) {
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setShowGrid(false);
    table->setWordWrap(false);
    table->verticalHeader()->hide();
    table->verticalHeader()->setDefaultSectionSize(45);
    auto *header = table->horizontalHeader();
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Fixed);
    header->setResizeContentsPrecision(-1);
    header->setSectionResizeMode(actions, QHeaderView::Fixed);
    table->setColumnWidth(actions, 88);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    new ResponsiveColumns(table, actions);
}
inline void actions(QPushButton *edit, QPushButton *remove, QHBoxLayout *layout) {
    for (auto *button : {edit, remove}) {
        const bool editing = button == edit;
        button->setStyleSheet({});
        button->setText({});
        button->setProperty("action", editing ? "edit" : "delete");
        button->setIcon(QIcon(editing ? ":/icons/edit.svg" : ":/icons/delete.svg"));
        button->setIconSize(QSize(18,18));
        button->ensurePolished();
        button->setFixedSize(30,30);
        button->setToolTip(editing ? "Edit" : "Delete");
        button->setAccessibleName(editing ? "Edit" : "Delete");
        button->setCursor(Qt::PointingHandCursor);
    }
    layout->setContentsMargins(4,2,4,2);
    layout->setSpacing(6);
    layout->setAlignment(Qt::AlignCenter);
}
inline void form(QDialogButtonBox *buttons, bool editing) {
    if (auto *save = buttons->button(QDialogButtonBox::Ok)) {
        save->setText(editing ? "Save changes" : "Add");
        save->setProperty("primary", true);
    }
}
}
