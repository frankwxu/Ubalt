import org.squirrelframework.foundation.fsm.annotation.ContextInsensitive;
import org.squirrelframework.foundation.fsm.annotation.Transitions;
import org.squirrelframework.foundation.fsm.impl.AbstractStateMachine;

@ContextInsensitive
public class PivyFSM extends AbstractStateMachine <PivyFSM, PivyFSM.PivyState, PivyFSM.PivyEvent, Void> {
    public enum PivyEvent {
        pivyNameFound, trafficFound, changeSrcIPFound
    }

    // Penetrated state indicates malicious code has been successfully installed on an SUI by an attacker
    // Explored indicates an SUI has been explored by attackers to gain a better understanding of the environment for future actions.
    //          change to a new src id=10.0.2.10
    // Exfiltrated indicates the SUI has an unauthorized movement of data.
    public enum PivyState {
        Secure, Penetrated, Explored, Exfiltrated
    }

    private StringBuilder logger = new StringBuilder();

    //for future visualization
    public void transitFromSecureToPenetratedOnpivyNameFound(PivyState from, PivyState to, PivyFSM.PivyEvent event) {
        logger.append("Vulnerability found! Transit From Secure To Penetrated On pivyNameFound");
        System.out.println(logger.toString());
    }

    public void transitFromPenetratedToExfiltratedOntrafficFound(PivyState from, PivyState to, PivyFSM.PivyEvent event) {
        logger.append("-> Transit From Penetrated To Exfiltrated On trafficeFound");
        System.out.println(logger.toString());
    }

    public void transitFromExfiltratedToExploredOnchangeSrcIPFound(PivyState from, PivyState to, PivyFSM.PivyEvent event) {
        logger.append("-> Transit From Exfiltrated To Explored On changeSrcIPFound");
        System.out.println(logger.toString());
    }

    public void transitFromPenetratedToExploredOnchangeSrcIPFound(PivyState from, PivyState to, PivyFSM.PivyEvent event) {
        logger.append("-> Transit From Penetrated To Explored On changeSrcIPFound");
        System.out.println(logger.toString());
    }
}
