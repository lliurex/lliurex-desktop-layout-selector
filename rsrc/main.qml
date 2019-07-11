import QtQuick 2.6
import QtQuick.Controls 2.0

ListView {
    id: packages
    width: 600; height: 600
    visible: true
    model: kcm
    focus: true
    onCurrentItemChanged: console.log(packages.currentIndex + ' selected')
    
    delegate: 
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: childrenRect.height+20
            color: (packages.currentIndex==index) ? "#bfdcf1" : "#f1f2f3"
            
            MouseArea {
                anchors.fill: preview
                onClicked: {
                    console.log("clicked on "+index)
                    packages.currentIndex=index
                }
              }
            
            Image {
                id: preview
                y: 10
                anchors.horizontalCenter: parent.horizontalCenter
                source: "file:"+path+"/contents/previews/preview.png"
                
            }
            
            Text {
                anchors.top: preview.bottom
                anchors.margins: 5
                anchors.horizontalCenter: preview.horizontalCenter
                
                text: name
            }
        }
    
}