#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include <ILLM.hpp>
#include <yarp/dev/PolyDriver.h>
#include <yarp/os/Property.h>

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
        yarp::os::Property prop;
        prop.put("device","GPT_nwc_yarp");
        m_poly.open(prop);
        m_poly.view(m_iLlm);
    }

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void addMessage(const Message &message);
    void refreshConversation(); //Added so that we don't rely on keeping local data in sync.
    void eraseConversation();
     
    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    // Qt::ItemFlags flags(const QModelIndex &index) const override;
    
    Q_INVOKABLE void deleteConversation(); //TODO: We have to come up with better names for this one
    Q_INVOKABLE void eraseMessage(const int &index);
    Q_INVOKABLE void sendMessage(const QString &message);
protected:
    QHash<int, QByteArray> roleNames() const;

private:
    yarp::dev::PolyDriver m_poly;
    yarp::dev::ILLM* m_iLlm;
    QList<Message> m_conversation;
};

#endif // CONVERSATIONMODEL_H