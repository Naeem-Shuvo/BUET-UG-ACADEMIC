
public class StudentStatus {
    private final String studentId;
    private boolean departmentConfirmed = false;
    private boolean officeOrderIssued = false;
    private boolean testimonialIssued = false;
    private boolean certificateIssued = false;

    public StudentStatus(String studentId) {
        this.studentId = studentId;
    }

    public String getStudentId() { return studentId; }

    public boolean isDepartmentConfirmed() { return departmentConfirmed; }
    public void setDepartmentConfirmed(boolean v) { departmentConfirmed = v; }

    public boolean isOfficeOrderIssued() { return officeOrderIssued; }
    public void setOfficeOrderIssued(boolean v) { officeOrderIssued = v; }

    public boolean isTestimonialIssued() { return testimonialIssued; }
    public void setTestimonialIssued(boolean v) { testimonialIssued = v; }

    public boolean isCertificateIssued() { return certificateIssued; }
    public void setCertificateIssued(boolean v) { certificateIssued = v; }

    @Override
    public String toString() {
        return String.format(
                "Student[%s] -> DeptConfirmed=%s, OfficeOrder=%s, Testimonial=%s, Certificate&Transcript=%s",
                studentId, departmentConfirmed, officeOrderIssued, testimonialIssued, certificateIssued);
    }
}