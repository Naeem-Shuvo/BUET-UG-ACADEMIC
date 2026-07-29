import java.util.Set;

public class GuestMode extends DeviceDecorator {
    private Room room;
    private Set<Class<?>> allowedTypes;

    public GuestMode(Room room, Set<Class<?>> allowedTypes) {
        super(room);
        this.room = room;
        this.allowedTypes = allowedTypes;
    }

    @Override
    public void activate() {
        // Only activate devices jader class matche kore  allowedTypes
        for (SmartDevice device : room.devices) {
            if (allowedTypes.contains(device.getClass())) {
                device.activate();
            }
        }
    }

    @Override
    public double getPowerUsage() {

        double totalPower = 0.0;
        for (SmartDevice device : room.devices) {
            if (allowedTypes.contains(device.getClass())) {
                totalPower += device.getPowerUsage();
            }
        }
        return totalPower;
    }

    @Override
    public String getStatus() {
        String[] lines = super.getStatus().split("\n");
        StringBuilder sb = new StringBuilder("[GUEST MODE]\n");
        sb.append(lines[0]); // Room title er name

        for (int i = 0; i < room.devices.size(); i++) {
            sb.append("\n").append(lines[i + 1]);
            SmartDevice device = room.devices.get(i);
            if (!allowedTypes.contains(device.getClass())) {
                sb.append(" [guest-restricted]");
            }
        }
        return sb.toString();
    }
}