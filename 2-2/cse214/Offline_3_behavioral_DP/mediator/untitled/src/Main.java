
public class Main {
    public static void main(String[] args) {

        ResultPublicationMediator coordinator = new BuetResultCoordinator();

        DepartmentOffice deptOffice = new DepartmentOffice(coordinator);
        ControllerOfExaminations coe = new ControllerOfExaminations(coordinator);
        DSW dsw = new DSW(coordinator);
        Student student = new Student(coordinator, "S-2021-CSE-042");

        String id = student.getStudentId();

        System.out.println("\n--- Step 1: Attempt to publish result BEFORE departmental confirmation ---");
        coe.issueOfficeOrder(id); // must be rejected

        System.out.println("\n--- Step 2: Submission of departmental confirmation ---");
        deptOffice.confirmCompletion(id);

        System.out.println("\n--- Step 3: Early attempt to issue certificate/transcript ---");
        coe.issueCertificateAndTranscript(id); // must be rejected (no office order / testimonial yet)

        System.out.println("\n--- Step 4: Issuance of the final-result office order ---");
        coe.issueOfficeOrder(id);

        System.out.println("\n--- Step 5: Issuance of the testimonial ---");
        dsw.issueTestimonial(id);

        System.out.println("\n--- Step 6: Issuance of the certificate and transcript ---");
        coe.issueCertificateAndTranscript(id);

        System.out.println("\n--- Step 7: Student notifications and final status ---");
        student.checkStatus();
    }
}