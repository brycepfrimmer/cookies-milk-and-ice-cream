import bb.cascades 1.2

Page {
    Container {
        background: Color.Black
        Label {
            // Localized text with the dynamic translation and locale updates support
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            text: qsTr("BB10 Terminal App") + Retranslate.onLocaleOrLanguageChanged
            textStyle.base: tsd.style
            textStyle.fontSize: FontSize.Medium
        }
        ScrollView {
            topPadding: 0
            topMargin: 0
            bottomPadding: 5
            bottomMargin: 0
            scrollViewProperties {
                scrollMode: ScrollMode.Vertical
            }
            TextArea {
                text: _terminalHandler.fullStatus
                enabled: false
                editable: false
                textStyle.base: tsd.style
            }
        }
        Container {
            background: Color.Black
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            topPadding: 5
            topMargin: 0
            bottomPadding: 0
            bottomMargin: 0
            TextArea {
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 0.1
                }
                id: pathField
                text: _terminalHandler.getPath()
                enabled: false
                editable: false
                textStyle.base: tsd.style
                minWidth: text.length
                rightPadding: 0
            }
            TextArea {
                id: inputField
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 0.9
                }
                enabled: true
                editable: true
                textStyle.base: tsd.style
                leftPadding: 0
                onTextChanging: {
                    if (text.search("\n") >= 0) {
                        _terminalHandler.handleCommand(inputField.text);
                        inputField.text = "";
                    }
                }
            }
        }
        attachedObjects: [
            TextStyleDefinition {
                id: tsd
                base: SystemDefaults.TextStyles.BodyText
                fontFamily: "Monospace"
                fontSize: FontSize.Small
                fontWeight: FontWeight.Bold
                color: Color.Green
            }
        ]
    }
}
