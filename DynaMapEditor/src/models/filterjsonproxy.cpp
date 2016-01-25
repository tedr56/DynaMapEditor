#include "filterjsonproxy.h"

FilterJsonProxy::FilterJsonProxy(QObject* parent) : QSortFilterProxyModel(parent)
{
    FilterSelection = true;
    AcceptedTypes = QStringList();
    AcceptedTypes = QStringList();
}

FilterJsonProxy::~FilterJsonProxy()
{
}

void FilterJsonProxy::setSourceModel(QJsonModel *SourceJsonModel)
{
    JsonModel = SourceJsonModel;
    QSortFilterProxyModel::setSourceModel(SourceJsonModel);
    invalidateFilter();
}

void FilterJsonProxy::clearFilter()
{
    AcceptedTypes.clear();
    RejectedTypes.clear();
    invalidateFilter();
}

void FilterJsonProxy::setItemTypeFilter(QStringList Types, JsonFilter::Action Action, JsonFilter::Operation Operation)
{
    if (Action == JsonFilter::Accept)
    {
        foreach (QString Type, Types) {
            if (Operation == JsonFilter::Add && !AcceptedTypes.contains(Type))
            {
                AcceptedTypes.append(Type);
            }
            if (Operation == JsonFilter::Del && AcceptedTypes.contains(Type))
            {
                AcceptedTypes.removeAll(Type);
            }
        }
    }
    else
    {
        foreach (QString Type, Types) {
            if (Operation == JsonFilter::Add && !RejectedTypes.contains(Type))
            {
                RejectedTypes.append(Type);
            }
            if (Operation == JsonFilter::Del && RejectedTypes.contains(Type))
            {
                RejectedTypes.removeAll(Type);
            }
        }
    }
    invalidateFilter();
}

void FilterJsonProxy::setItemTypeFilter(QString Type, JsonFilter::Action Action, JsonFilter::Operation Operation)
{
    setItemTypeFilter(QStringList(Type), Action, Operation);
}

void FilterJsonProxy::resetFilter()
{
    invalidateFilter();
}

bool FilterJsonProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{

    QModelIndex Index = sourceModel()->index(source_row, 0, source_parent);
    QString ItemType  = JsonModel->getItemType(Index);
    if (AcceptedTypes.size())
    {
        if (!AcceptedTypes.contains(ItemType))
        {
            return false;
        }
    }
    if (RejectedTypes.contains(ItemType))
    {
        return false;
    }
    return true;
}

