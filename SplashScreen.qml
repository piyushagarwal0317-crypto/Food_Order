import QtQuick
import QtQuick.Window

Window {
    id: splashWindow
    width: 400
    height: 600
    visible: true
    title: "Food Villa"

    // This removes the Windows title bar, making it a true splash screen!
    flags: Qt.SplashScreen | Qt.FramelessWindowHint

    // Warm gradient background
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#FF7E5F" }
            GradientStop { position: 1.0; color: "#FEB47B" }
        }
    }

    // Main Restaurant Title
    Text {
        id: titleText
        text: "Food Villa"
        font.pixelSize: 54
        font.bold: true
        color: "white"
        anchors.centerIn: parent

        scale: 0.1
        opacity: 0.0
    }

    // Loading / Subtitle Text
    Text {
        id: loadingText
        text: "Setting the table..."
        font.pixelSize: 18
        font.italic: true
        color: "white"
        anchors.top: titleText.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0.0
    }

    // Main Animation Sequence
    SequentialAnimation {
        running: true
        loops: 1

        ParallelAnimation {
            NumberAnimation {
                target: titleText
                property: "scale"
                to: 1.2
                duration: 800
                easing.type: Easing.OutBack
            }
            NumberAnimation {
                target: titleText
                property: "opacity"
                to: 1.0
                duration: 600
            }
        }

        NumberAnimation {
            target: titleText
            property: "scale"
            to: 1.0
            duration: 300
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            target: loadingText
            property: "opacity"
            to: 1.0
            duration: 400
        }

        ScriptAction {
            script: pulseAnimation.start()
        }
    }

    // Pulsing animation
    SequentialAnimation {
        id: pulseAnimation
        loops: Animation.Infinite

        NumberAnimation {
            target: loadingText
            property: "opacity"
            to: 0.3
            duration: 700
            easing.type: Easing.InOutSine
        }
        NumberAnimation {
            target: loadingText
            property: "opacity"
            to: 1.0
            duration: 700
            easing.type: Easing.InOutSine
        }
    }
}