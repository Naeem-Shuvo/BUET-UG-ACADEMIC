
public class ControllerOfExaminations extends Colleague {

    public ControllerOfExaminations(ResultPublicationMediator mediator) {
        super(mediator);
        mediator.registerControllerOfExaminations(this);
    }

    /** Attempts to issue the final-result publication office order. */
    public void issueOfficeOrder(String studentId) {
        System.out.println("[ControllerOfExaminations] Attempting to issue office order for " + studentId);
        mediator.issueOfficeOrder(studentId);
    }

    /** Attempts to issue the certificate and transcript (final step). */
    public void issueCertificateAndTranscript(String studentId) {
        System.out.println("[ControllerOfExaminations] Attempting to issue certificate & transcript for " + studentId);
        mediator.issueCertificateAndTranscript(studentId);
    }
}