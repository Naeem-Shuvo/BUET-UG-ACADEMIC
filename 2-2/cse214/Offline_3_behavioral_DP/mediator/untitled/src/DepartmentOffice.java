
public class DepartmentOffice extends Colleague {

    public DepartmentOffice(ResultPublicationMediator mediator) {
        super(mediator);
        mediator.registerDepartmentOffice(this);
    }

    /** Confirms that the student has completed all academic requirements. */
    public void confirmCompletion(String studentId) {
        System.out.println("[DepartmentOffice] Confirming academic completion for " + studentId);
        mediator.submitDepartmentalConfirmation(studentId);
    }
}