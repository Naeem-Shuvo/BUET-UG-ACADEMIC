public interface Client {
    void update(String title, float severity, String location, String category, String instruction);
    void subscribe(Disaster disaster);
    void unsubscribe(Disaster disaster);
}