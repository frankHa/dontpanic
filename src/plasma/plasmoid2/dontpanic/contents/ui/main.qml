import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
 
 
Item {
    PlasmaCore.DataSource {
     id: dp
     engine: "dontpanic"
     connectedSources: sources
     interval: 500
    }
    
    Plasmoid.compactRepresentation: PlasmaCore.IconItem {
        source: dp.data["icon"]["source"]
        smooth: true
        width: 36;
        height: 36;
        MouseArea {
            anchors.fill: parent
            onClicked: plasmoid.expanded = !plasmoid.expanded
        }
    }
    
    Item
    {
      id: currentAction
      property bool active:dp.data.current_activity.active
      property string project: dp.data.current_activity.project
      property string task: dp.data.current_activity.task
      property string start: dp.data.current_activity.start.toLocaleTimeString(Qt.locale(), Locale.ShortFormat);
      property string duration: dp.data.current_activity.duration
      property string description: active ? i18n ( "Currently working on:<br/><b>%1 / %2</b><br/>since: <b>%3 (%4h)</b>",project, task, start, duration) : i18n ( "There is currently no running activity..." )
    }
    
    Plasmoid.icon:dp.data["icon"]["source"]
    Plasmoid.toolTipMainText: dp.data.today.Time
    Plasmoid.toolTipSubText : currentAction.description
    Plasmoid.fullRepresentation: FullRepresentation {}
    
    Action
    {
      id: startAction
      text: i18n ( "Start a new action" )
      iconName: "media-playback-start"      
    }
    
    Action
    {
      id: stopCurrentAction
      text: i18n ( "Stop the current action" )
      iconName: "media-playback-stop"
      onTriggered: stopCurrent()
    }
    
    Action
    {
      id: resumeLastAction
      text: i18n ( "Resume the latest action" )
      iconName: "media-seek-forward"
      onTriggered: continueLatest()
    }
    
    function stopCurrent()
    {
      var service = dp.serviceForSource("dontpanic")
      var op = service.operationDescription("stopCurrentAction")
      service.startOperationCall(op)
    }
    
    function continueLatest()
    {
      var service = dp.serviceForSource("dontpanic")
      var op = service.operationDescription("continueLastAction")
      service.startOperationCall(op)
    }
}

