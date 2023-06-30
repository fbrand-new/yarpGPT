#include "ConversationModel.h"
#include <iostream>

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    std::cout << "Data is called" << std::endl;
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

    std::cout << "conversation pre: " << std::endl;
    for(size_t i=0; i<m_conversation.count(); ++i)
    {
        std::cout << "cont: " << m_conversation[i].content().toStdString() <<std::endl;
    }

    const auto &conversation = m_iLlm->getConversation();

    for(const auto& [author,message]: conversation)
    {
        std::cout << "message: " << message << std::endl;
        addMessage(Message(QString::fromStdString(author),QString::fromStdString(message)));
    }

    std::cout << "conversation post: " << std::endl;
    for(size_t i=0; i<m_conversation.count(); ++i)
    {
        std::cout << "cont: " << m_conversation[i].content().toStdString() <<std::endl;
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

    if (rowCount() == 0)
    {
        m_iLlm->setPrompt(message.toStdString());
    }
    else
    {
        std::string answer = m_iLlm->ask(message.toStdString());
    }

    this->refreshConversation();
    
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
