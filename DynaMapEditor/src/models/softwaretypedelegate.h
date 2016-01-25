#ifndef SOFTWARETYPEDELEGATE_H
#define SOFTWARETYPEDELEGATE_H

#include <QStyledItemDelegate>

class SoftwareTypeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SoftwareTypeDelegate(QObject* parent = 0);
    ~SoftwareTypeDelegate();

    virtual QWidget *createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    virtual void setEditorData ( QWidget *editor, const QModelIndex &index ) const;
    virtual void setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const;
};

#endif // SOFTWARETYPEDELEGATE_H
