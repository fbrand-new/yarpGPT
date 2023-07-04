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

void ConversationModel::eraseConversation()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_conversation.clear();
    endRemoveRows();
}

void ConversationModel::deleteConversation()
{
    m_iLlm->deleteConversation();
    refreshConversation();
}

void ConversationModel::refreshConversation()
{

    this->eraseConversation();

    std::vector<std::pair<Author, Content>> conversation;
    auto ok = m_iLlm->getConversation(conversation);

    for (const auto &[author, message] : conversation)
    {
        addMessage(Message(QString::fromStdString(author), QString::fromStdString(message)));
    }
}

void ConversationModel::addMessage(const Message &message)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_conversation << message;
    endInsertRows();
}

void ConversationModel::sendMessage(const QString &message)
{

    std::string answer;

    if (rowCount() == 0)
    {
        m_iLlm->setPrompt(message.toStdString());
    }
    else
    {
        m_iLlm->ask(message.toStdString(), answer);
    }

    this->refreshConversation();
}

void ConversationModel::eraseMessage(const int &index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_conversation.removeAt(index);
    endRemoveRows();
}