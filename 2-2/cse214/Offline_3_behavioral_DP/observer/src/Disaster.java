public interface Disaster {
    void registerUser(Client client);
    void removeUser(Client client);
    void notifyUser();
    void publish(String title, float severity, String location, String instruction);
}