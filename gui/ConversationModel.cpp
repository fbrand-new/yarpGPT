#include "ConversationModel.h"
#include <iostream>

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_conversation.count())
        return QVariant();

    const Message &message = m_conversation[index.row()];
    if (role == TypeRole)
        return message.type();
    else if (role == ContentRole)
        return message.content();

    return QVariant();
}

int ConversationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_conversation.count();
}

QHash<int, QByteArray> ConversationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[ContentRole] = "content";
    return roles;
}

void ConversationModel::addMessage(const Message &message)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_conversation << message;
    endInsertRows();
}

void ConversationModel::sendMessage(const QString &message)
{

    if (rowCount() == 0)
    {
        m_iLlm->setPrompt(message.toStdString());
        addMessage(Message(QString::fromStdString("system"), message));
    }
    else
    {
        std::string answer = m_iLlm->ask(message.toStdString());
        addMessage(Message(QString::fromStdString("user"),message));
        addMessage(Message(QString::fromStdString("assistant"),QString::fromStdString(answer)));
    }
    
}

void ConversationModel::eraseMessage(const int &index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_conversation.removeAt(index);
    endRemoveRows();
}

// bool ConversationModel::setData(const QModelIndex &index, const QVariant &value, int role)
// {
//     conversation[index.row()] = std::make_pair("assistant",value.toString().toStdString());
//     return true;
// }

// Qt::ItemFlags ConversationModel::flags(const QModelIndex &index) const
// {
//     if (!index.isValid())
//         return Qt::NoItemFlags;

//     return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
// }
