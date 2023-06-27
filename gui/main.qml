
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import conversationmodel 1.0
import QtQuick.Controls.Material 2.15

ApplicationWindow {
    width: 540
    height: 960
    visible: true

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.TopToBottom
            spacing: 12
            model: ConversationModel {
            }
            delegate: Row {
                readonly property bool isPrompt: index == 0 //TODO: not robust.
                readonly property bool sentByMe: (index+1) % 2 == 0

                id: messageRow
                //anchors.right: sentByMe ? listView.contentItem.right : undefined
                anchors.centerIn: parent
                spacing: 6

                Rectangle {
                    width: Math.min(messageText.implicitWidth + 24,
                            listView.width - (!sentByMe ? erase.width + messageRow.spacing + listView.width/8 : 0))
                    height: messageText.implicitHeight + 24
                    color: isPrompt ? "green" : (sentByMe ? "lightgrey" : "steelblue")

                    Label {
                        id: messageText
                        anchors.centerIn: parent
                        text: model.content
                        color: sentByMe ? "black" : "white"    
                        anchors.fill: parent
                        anchors.margins: 12
                        wrapMode: Label.Wrap
                    }
                }

                Button {
                    background: Rectangle {
                        implicitWidth: 45
                        implicitHeight: 45
                        opacity: enabled ? 1 : 0.3
                        border.width: 1
                        radius: 2
                    }
                    id: erase 
                    icon.source: "/usr/share/icons/ubuntu-mobile/actions/scalable/reload.svg"
                }

            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                    onClicked: {
                        listView.model.sendMessage(messageField.text);
                        messageField.text = "";
                    }
                }
            }
        }
    }

}
