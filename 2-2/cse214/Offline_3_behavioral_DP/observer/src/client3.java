import java.util.ArrayList;

public class client3 implements Client {
    private String name;
    private ArrayList<String> notifications;

    public client3(String name) {
        this.name = name;
        this.notifications = new ArrayList<>();
    }

    @Override
    public void subscribe(Disaster disaster) {
        disaster.registerUser(this);
    }

    @Override
    public void unsubscribe(Disaster disaster) {
        disaster.removeUser(this);
    }

    @Override
    public void update(String title, float severity, String location, String category, String instruction) {
        String alert = String.format("[%s] %s | Severity: %.1f | Location: %s | Instruction: %s",
                category, title, severity, location, instruction);
        notifications.add(alert);
        display(alert);
    }

    private void display(String latestAlert) {
        System.out.println(name + " (client3) received: " + latestAlert);
    }

    public void display() {
        System.out.println("\nNotifications received by " + name + " (client3):");
        for (String note : notifications) {
            System.out.println("  - " + note);
        }
    }
}