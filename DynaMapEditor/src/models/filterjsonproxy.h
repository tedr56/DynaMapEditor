#ifndef FILTERJSONPROXY_H
#define FILTERJSONPROXY_H

#include <QSortFilterProxyModel>
#include "qjsonmodel.h"

namespace JsonFilter {
    typedef enum {
        Accept = 0,
        Reject = 1
    } Action;
    typedef enum {
        Add = 10,
        Del = 11
    } Operation;
}

class FilterJsonProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    FilterJsonProxy(QObject* parent = 0);
    ~FilterJsonProxy();
    void setSourceModel(QJsonModel *SourceJsonModel); Q_DECL_OVERRIDE;
    void clearFilter();
    void setItemTypeFilter(QStringList Types, JsonFilter::Action Action = JsonFilter::Reject, JsonFilter::Operation Operation = JsonFilter::Add);
    void setItemTypeFilter(QString Type, JsonFilter::Action Action = JsonFilter::Reject, JsonFilter::Operation Operation = JsonFilter::Add);
    void resetFilter();
protected:
     bool filterAcceptsRow (int source_row, const QModelIndex & source_parent) const;

private:
    QStringList AcceptedTypes;
    QStringList RejectedTypes;
    bool FilterSelection;

    QJsonModel* JsonModel;
};

#endif // FILTERJSONPROXY_H
