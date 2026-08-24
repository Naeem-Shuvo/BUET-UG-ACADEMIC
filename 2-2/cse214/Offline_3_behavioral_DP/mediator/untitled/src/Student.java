
public class Student extends Colleague {
    private final String studentId;

    public Student(ResultPublicationMediator mediator, String studentId) {
        super(mediator);
        this.studentId = studentId;
        mediator.registerStudent(this);
    }

    public String getStudentId() { return studentId; }

    /** Called BY the mediator to push a notification to this student. */
    public void notify(String message) {
        System.out.println("[Notify -> " + studentId + "] " + message);
    }

    /** Student asks the mediator to display where their processing stands. */
    public void checkStatus() {
        mediator.displayStatus(studentId);
    }
}