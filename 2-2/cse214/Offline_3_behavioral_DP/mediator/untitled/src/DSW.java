
public class DSW extends Colleague {

    public DSW(ResultPublicationMediator mediator) {
        super(mediator);
        mediator.registerDSW(this);
    }

    /** Attempts to issue the testimonial for the student. */
    public void issueTestimonial(String studentId) {
        System.out.println("[DSW] Attempting to issue testimonial for " + studentId);
        mediator.issueTestimonial(studentId);
    }
}