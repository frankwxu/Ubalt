import org.squirrelframework.foundation.component.SquirrelProvider;
import org.squirrelframework.foundation.fsm.*;
import org.apache.commons.io.FileUtils;
import java.io.File;
import java.io.IOException;

public class PivyFsmMain {
    public static void main(String[] args) throws IOException {
        // builder the state machine
        StateMachineBuilder<PivyFSM, PivyFSM.PivyState, PivyFSM.PivyEvent, Void> builder = StateMachineBuilderFactory.create(
                PivyFSM.class, PivyFSM.PivyState.class, PivyFSM.PivyEvent.class, Void.class);

        //predefined vulnerability events
        builder.externalTransition().from(PivyFSM.PivyState.Secure).to(PivyFSM.PivyState.Penetrated).on(PivyFSM.PivyEvent.pivyNameFound);
        builder.externalTransition().from(PivyFSM.PivyState.Penetrated).to(PivyFSM.PivyState.Exfiltrated).on(PivyFSM.PivyEvent.trafficFound);
        builder.externalTransition().from(PivyFSM.PivyState.Exfiltrated).to(PivyFSM.PivyState.Explored).on(PivyFSM.PivyEvent.changeSrcIPFound);
        builder.externalTransition().from(PivyFSM.PivyState.Penetrated).to(PivyFSM.PivyState.Explored).on(PivyFSM.PivyEvent.changeSrcIPFound);

        PivyFSM stateMachine = builder.newStateMachine(PivyFSM.PivyState.Secure);

        //Start the state machine
        stateMachine.start();

        // check for vulnerability events
        final String pivyName = "piosionIvy.exe";
        final String logName="fileLogs.txt";

        if (FileUtils.readFileToString(new File(logName),"UTF-8").contains(pivyName)){
            stateMachine.fire(PivyFSM.PivyEvent.pivyNameFound);
        }

        // check for exfiltrating traffic
        final String networkTrafficFile="networkTraffic.txt";
        final String dst_ip = "dst_ref.value = \'44.3.2.12\'";
        if (FileUtils.readFileToString(new File(networkTrafficFile),"UTF-8").contains(dst_ip)) {
            stateMachine.fire(PivyFSM.PivyEvent.trafficFound);
        }

        // check for lateral movement
        final String networkLateralTrafficFile="networkTraffic.txt";
        final String src_ip = "src_ref.value = \'10.0.2.10\'";
        if (FileUtils.readFileToString(new File(networkLateralTrafficFile),"UTF-8").contains(src_ip)) {
            stateMachine.fire(PivyFSM.PivyEvent.changeSrcIPFound);
        }

        // check for current state
        System.out.println("================");
        System.out.println("Current State: "+stateMachine.getCurrentState());

        //export state machine definition in [SCXML] 2 document
        SCXMLVisitor visitor = SquirrelProvider.getInstance().newInstance(SCXMLVisitor.class);
        stateMachine.accept(visitor);
        visitor.convertSCXMLFile("MyStateMachine", true);

        // viewed by [GraphViz] 3.
        // C:\Users\Fxu\Anaconda3\Library\bin\graphviz\gvedit.exe to display the dot file
        // open with gvedit.exe
        DotVisitor dotVisitor = SquirrelProvider.getInstance().newInstance(DotVisitor.class);
        stateMachine.accept(dotVisitor);
        dotVisitor.convertDotFile("MyStateMachine");
    }
}
