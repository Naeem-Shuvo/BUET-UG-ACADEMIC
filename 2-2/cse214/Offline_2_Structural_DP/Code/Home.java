import java.util.List;

public class Home implements SmartDevice {
    String name;
    List<Room> rooms;
    Home(String name){
        this.name = name;
    }
    void  addRoom(Room room){
        rooms.add(room);
    }
    @Override
    public void activate() {
        for (Room room : rooms) {
            room.activate();
        }
    }

    @Override
    public void deactivate() {
 for (Room room : rooms) {
     room.deactivate();
 }
    }

    @Override
    public double getPowerUsage() {
        double total=0;
        for (Room room : rooms) {
            total+=room.getPowerUsage();
        }
        return total;
    }

    @Override
    public String getStatus() {
        return "";
    }
}
