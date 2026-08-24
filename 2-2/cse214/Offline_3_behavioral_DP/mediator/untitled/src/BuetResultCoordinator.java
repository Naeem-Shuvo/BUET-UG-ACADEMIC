import java.util.HashMap;
import java.util.Map;


public class BuetResultCoordinator implements ResultPublicationMediator {

    private DepartmentOffice departmentOffice;
    private ControllerOfExaminations controllerOfExaminations;
    private DSW dsw;
    private final Map<String, Student> students = new HashMap<>();
    private final Map<String, StudentStatus> statusMap = new HashMap<>();


    @Override
    public void registerDepartmentOffice(DepartmentOffice office) {
        this.departmentOffice = office;
    }

    @Override
    public void registerControllerOfExaminations(ControllerOfExaminations coe) {
        this.controllerOfExaminations = coe;
    }

    @Override
    public void registerDSW(DSW dsw) {
        this.dsw = dsw;
    }

    @Override
    public void registerStudent(Student student) {
        students.put(student.getStudentId(), student);
        statusMap.putIfAbsent(student.getStudentId(), new StudentStatus(student.getStudentId()));
    }

    private StudentStatus statusOf(String studentId) {
        return statusMap.computeIfAbsent(studentId, StudentStatus::new);
    }



    @Override
    public void submitDepartmentalConfirmation(String studentId) {
        StudentStatus status = statusOf(studentId);
        status.setDepartmentConfirmed(true);
        System.out.println("[Coordinator] Departmental confirmation recorded for " + studentId);
    }

    @Override
    public void issueOfficeOrder(String studentId) {
        StudentStatus status = statusOf(studentId);

        if (!status.isDepartmentConfirmed()) {
            System.out.println("[Coordinator] REJECTED: Cannot issue office order for "
                    + studentId + " - departmental confirmation is missing.");
            return;
        }
        if (status.isOfficeOrderIssued()) {
            System.out.println("[Coordinator] REJECTED: Office order already issued for " + studentId + ".");
            return;
        }

        status.setOfficeOrderIssued(true);
        System.out.println("[Coordinator] Final-result publication office order issued for " + studentId);
        notifyStudent(studentId, "Your final-result publication office order has been issued.");
    }

    @Override
    public void issueTestimonial(String studentId) {
        StudentStatus status = statusOf(studentId);

        if (!status.isOfficeOrderIssued()) {
            System.out.println("[Coordinator] REJECTED: Cannot issue testimonial for "
                    + studentId + " - office order has not been issued yet.");
            return;
        }
        if (status.isTestimonialIssued()) {
            System.out.println("[Coordinator] REJECTED: Testimonial already issued for " + studentId + ".");
            return;
        }

        status.setTestimonialIssued(true);
        System.out.println("[Coordinator] Testimonial issued for " + studentId);
        notifyStudent(studentId, "Your testimonial has been issued.");
    }

    @Override
    public void issueCertificateAndTranscript(String studentId) {
        StudentStatus status = statusOf(studentId);

        if (!status.isDepartmentConfirmed() || !status.isOfficeOrderIssued() || !status.isTestimonialIssued()) {
            System.out.println("[Coordinator] REJECTED: Cannot issue certificate & transcript for "
                    + studentId + " - required prior steps are not all complete.");
            return;
        }
        if (status.isCertificateIssued()) {
            System.out.println("[Coordinator] REJECTED: Certificate & transcript already issued for " + studentId + ".");
            return;
        }

        status.setCertificateIssued(true);
        System.out.println("[Coordinator] Certificate and academic transcript issued for " + studentId);
        notifyStudent(studentId, "Your certificate and academic transcript have been issued. Process complete!");
    }


    private void notifyStudent(String studentId, String message) {
        Student student = students.get(studentId);
        if (student != null) {
            student.notify(message);
        }
    }

    @Override
    public void displayStatus(String studentId) {
        System.out.println("[Coordinator] " + statusOf(studentId));
    }
}