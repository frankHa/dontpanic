import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.extras 2.0 as PlasmaExtras

Item
{
  id: main
  clip: true  
  ColumnLayout
  {
    id: overview
    anchors.top: parent.top
    RowLayout
    {
      anchors.top: parent.top
      PlasmaCore.IconItem 
      {
        anchors.top: parent.top
        source: dp.data["icon"]["source"]
        smooth: true
        width: 42;
        height: 42;
      }
      
      PlasmaExtras.Heading 
      {
        anchors.top: parent.top
        width: parent.width
        level: 3
        opacity: 0.6
        text: currentAction.description
      }
    }
    PlasmaComponents.ToolButton
    {
      action: startAction   
      onClicked: main.state = "stateStartAction"
    }
    PlasmaComponents.ToolButton
    {
      action: currentAction.active ? stopCurrentAction : resumeLastAction
    }
  }
  
  ColumnLayout
  {
    id: actionStarter
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: parent.width
    //anchors.fill: parent
    
    PlasmaComponents.ToolButton
    {
      id: cancel
      iconSource: "edit-delete"
      text: i18n("Cancel")
      onClicked: main.state = "stateOverview"
    }
      
    PlasmaExtras.ScrollArea 
    {
      Layout.fillWidth: true
      Layout.fillHeight: true      
      
      anchors.fill:parent
      anchors.topMargin: cancel.height + 10
      anchors.leftMargin: 20
      ListView 
      {
        model: PlasmaCore.DataModel 
        {
              dataSource: dp
              sourceFilter: "favorites.*"
        }
        
        boundsBehavior: Flickable.StopAtBounds
        interactive: contentHeight > height
        highlight: PlasmaComponents.Highlight {
            anchors.bottomMargin: -listMargins.bottom
            y: 1
        }
        highlightMoveDuration: 0
        highlightResizeDuration: 0
        currentIndex: -1
        
        delegate: PlasmaComponents.ToolButton
        {
          property string fav_id:id
          
          function startFrom(id)
          {
            var service = dp.serviceForSource("dontpanic")
            var op = service.operationDescription("startFromFavorite")
            op["favId"]=id
            service.startOperationCall(op)
            main.state= "stateOverview"
          }
          
          iconSource: icon
          text: name
          onClicked: startFrom(fav_id)
        }
      }        
    }
  }
  
  states:
  [
    State{
      name: "stateOverview"
      PropertyChanges {target: overview; x:main.x}
      PropertyChanges {target: actionStarter; x:main.x+main.width}
    },    
    State{
      name: "stateStartAction"
      PropertyChanges {target: overview; x:main.x-main.width}
      PropertyChanges {target: actionStarter; x:main.x}
    }
  ]
  
  
  property int _duration:150
    transitions:
        [
        Transition {
            to: "stateOverview"
            SequentialAnimation
            {
                ScriptAction{script: overview.visible=true;}
                NumberAnimation {target:overview; property: "x";  from:main.x-main.width;easing.type: Easing.InOutQuad; duration: _duration}
            }
            SequentialAnimation
            {
                NumberAnimation {target:actionStarter; property: "x";  from:main.x;easing.type: Easing.InOutQuad; duration: _duration}
                ScriptAction{script: actionStarter.visible=false;}
            }
        }
        ,
        Transition {
            to: "stateStartAction"
            SequentialAnimation
            {
                ScriptAction{script: actionStarter.visible=true;}
                NumberAnimation {target:actionStarter; property: "x";  from:main.x+main.width;easing.type: Easing.InOutQuad; duration: _duration}
                ScriptAction{script: actionStarter.anchors.fill=parent;}
            }
            SequentialAnimation
            {
                NumberAnimation {target:overview; property: "x";  from:main.x;easing.type: Easing.InOutQuad; duration: _duration}
                ScriptAction{script: overview.visible=false;}
            }
        }
    ]
    
    state: "stateOverview"
}