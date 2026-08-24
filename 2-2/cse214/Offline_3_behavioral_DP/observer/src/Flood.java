import java.util.ArrayList;

public class Flood implements Disaster {
    private static final String CATEGORY = "Flood";

    private String title;
    private float severity;
    private String location;
    private String instruction;
    private ArrayList<Client> clients;

    public Flood() {
        this.clients = new ArrayList<>();
    }

    @Override
    public void registerUser(Client client) {
        clients.add(client);
    }

    @Override
    public void removeUser(Client client) {
        clients.remove(client);
    }

    @Override
    public void notifyUser() {
        for (Client client : clients) {
            client.update(title, severity, location, CATEGORY, instruction);
        }
    }

    @Override
    public void publish(String title, float severity, String location, String instruction) {
        this.title = title;
        this.severity = severity;
        this.location = location;
        this.instruction = instruction;
        notifyUser();
    }
}