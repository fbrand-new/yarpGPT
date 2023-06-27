#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>

class Message
{
public:
    Message(const QString &type, const QString &content) : m_type{type}, m_content{content}
    {

    }

    QString type() const { return m_type; }
    QString content() const { return m_content; }

private:
    QString m_type;
    QString m_content;
};

class ConversationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ConversationRoles
    {
        TypeRole = Qt::UserRole + 1,
        ContentRole
    };

    explicit ConversationModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        std::string lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
        m_conversation << Message(QString::fromStdString("system"),QString::fromStdString(lorem));
        // conversation.push_back(std::make_pair("system", "hei!"));
        // conversation.push_back(std::make_pair("assistant", "how are you?"));
    }

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void addMessage(const Message &message);

    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    // Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void sendMessage(const QString &message);
protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Message> m_conversation;
};

#endif // CONVERSATIONMODEL_H