
import udp.marautec.com 23.2
import QtQuick 2.15

Rectangle{
    width:500
    height:500
    color:"#FF0000"

    NavMesg{
    id: _navmsg
        onHeadingChanged:{
            radarObjTrack(_navmsg.heading);
            console.log("NavMesg = " + _navmsg.heading)
        }
    }

}
