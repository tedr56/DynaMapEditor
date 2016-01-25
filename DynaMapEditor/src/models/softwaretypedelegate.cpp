#include "softwaretypedelegate.h"
#include <QComboBox>

SoftwareTypeDelegate::SoftwareTypeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


SoftwareTypeDelegate::~SoftwareTypeDelegate()
{
}


QWidget* SoftwareTypeDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    // ComboBox ony in column 2
    //if(index.column() != 1)
    //    return QStyledItemDelegate::createEditor(parent, option, index);

    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);
    cb->addItem(QString("Group"));
    cb->addItem(QString("Instance"));
    cb->addItem(QString("Normal"));
    return cb;
}


void SoftwareTypeDelegate::setEditorData ( QWidget *editor, const QModelIndex &index ) const
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor)) {
        // get the index of the text in the combobox that matches the current value of the itenm
        QString currentText = index.data(Qt::EditRole).toString();
        int cbIndex = cb->findText(currentText);
        // if it is valid, adjust the combobox
        if(cbIndex >= 0)
            cb->setCurrentIndex(cbIndex);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}


void SoftwareTypeDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}
