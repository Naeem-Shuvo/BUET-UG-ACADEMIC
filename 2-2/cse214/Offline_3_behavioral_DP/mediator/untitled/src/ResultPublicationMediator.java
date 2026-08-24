
public interface ResultPublicationMediator {


    void registerDepartmentOffice(DepartmentOffice office);
    void registerControllerOfExaminations(ControllerOfExaminations coe);
    void registerDSW(DSW dsw);
    void registerStudent(Student student);


    void submitDepartmentalConfirmation(String studentId);
    void issueOfficeOrder(String studentId);
    void issueTestimonial(String studentId);
    void issueCertificateAndTranscript(String studentId);


    void displayStatus(String studentId);
}