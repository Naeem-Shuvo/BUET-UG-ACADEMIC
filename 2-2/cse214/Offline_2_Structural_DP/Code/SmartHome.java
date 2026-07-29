import java.util.ArrayList;
import java.util.List;
import java.util.Set;

 interface SmartDevice {
    void activate();
    void deactivate();
    double getPowerUsage();
    String getStatus();
}
 abstract class DeviceDecorator implements SmartDevice{
    SmartDevice wrapped;
    public DeviceDecorator(SmartDevice wrapped) {
        this.wrapped = wrapped;
    }
    public void activate() {
        wrapped.activate();
    }
    public void deactivate() {
        wrapped.deactivate();
    }
    @Override
    public double getPowerUsage() {
        return wrapped.getPowerUsage();
    }

    @Override
    public String getStatus() {
        return wrapped.getStatus();
    }
}


 class EcoMode extends DeviceDecorator{
    private Room room;
    private double budget;
    public EcoMode(Room room, double budget) {

        super(room);
        this.budget = budget;
        this.room=room;
    }
    @Override
    public  void activate() {
        super.activate();
        List<SmartDevice> list=room.devices;
        for(int i=list.size()-1;i>=0;i--){
            if(room.getPowerUsage()<=budget){
                break;
            }
            list.get(i).deactivate();
        }
    }
    @Override
    public String getStatus() {
        return "[ECO: " + budget + "W budget]\n" + super.getStatus();
    }

}



 class GuestMode extends DeviceDecorator {
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
 class AccessRestricted extends DeviceDecorator {
    private int pin;
    private boolean locked = true; // Devices start locked by default

    public AccessRestricted(SmartDevice device, int pin) {
        super(device);
        this.pin = pin;
    }

    public void unlock(int enteredPin) {
        if (enteredPin == this.pin) {
            this.locked = false;
        }
    }

    @Override
    public void activate() {
        if (!locked) {
            super.activate();
        }
    }

    @Override
    public void deactivate() {
        if (!locked) {
            super.deactivate();
        }
    }

    @Override
    public String getStatus() {
        String status = super.getStatus();
        return locked ? status + " [LOCKED]" : status;
    }
}

class Home implements SmartDevice {
    String name;
    // 1. Initialize the list and change type to SmartDevice to accept decorated rooms
    List<SmartDevice> rooms = new ArrayList<>();

    Home(String name){
        this.name = name;
    }

    // 2. Accept SmartDevice instead of Room
    void addRoom(SmartDevice room){
        rooms.add(room);
    }

    @Override
    public void activate() {
        for (SmartDevice room : rooms) { // Update loop variable
            room.activate();
        }
    }

    @Override
    public void deactivate() {
        for (SmartDevice room : rooms) { // Update loop variable
            room.deactivate();
        }
    }

    @Override
    public double getPowerUsage() {
        double total = 0;
        for (SmartDevice room : rooms) { // Update loop variable
            total += room.getPowerUsage();
        }
        return total;
    }

    @Override
    public String getStatus() {
        return "";
    }
}

 class Room implements SmartDevice {
    String name;
    List<SmartDevice> devices=new ArrayList<>();
    //List<smartDevice> insertionOrder=new ArrayList<>();

    Room(String name){
        this.name=name;
    }
    public void addDevice(SmartDevice device) {
        devices.add(device);
        //   insertionOrder.add(device);
    }

    @Override
    public void activate() {
        for(SmartDevice l:devices){
            l.activate();
        }
    }

    @Override
    public void deactivate() {
        for(SmartDevice l:devices){
            l.deactivate();
        }
    }

    @Override
    public double getPowerUsage() {
        double sum=0;
        for(SmartDevice l:devices){
            sum+=l.getPowerUsage();
        }
        return sum;
    }

    @Override
    public String getStatus() {
        return "";
    }
}
 class SmartLight implements SmartDevice {
    boolean on=false;
    double power=0;
    String status="";
    public void activate(){
        on=true;
    }
    public void deactivate(){
        on=false;
    }
    public double getPowerUsa(){
        power=on?10.0:0.0;
        return power;
    }
    public String getStatus(){
        status=on?"ON":"OFF";
        return status;
    }
}
 class SmartSpeaker implements SmartDevice {
    boolean on=false;
    double power=0;
    String status="";
    public void activate(){
        on=true;
    }
    public void deactivate(){
        on=false;
    }
    public double getPowerUsage(){
        power=on?5.0:0.0;
        return power;
    }
    public String getStatus(){
        status="speaker"+(on?"playing":"idle");
        return status;
    }
}


 class SmartThermostat implements SmartDevice {
    boolean on=false;
    double power=0;
    String status="";
    @Override
    public void activate() {
        on=true;
    }

    @Override
    public void deactivate() {
        on=false;
    }

    @Override
    public double getPowerUsage() {
        power=on?150.0:0.0;
        return power;
    }

    @Override
    public String getStatus() {
        status = "Thermostat: " + (on ? "ON" : "OFF");
        return status;
    }
}
 class TimerControlled extends DeviceDecorator {
    private boolean timeCtrl=false;
    private int seconds;

    public TimerControlled(SmartDevice device,int seconds) {
        super(device);
        this.seconds = seconds;
    }
    public void activate(){
        super.activate();
        //jdi lock thake
        if (super.getPowerUsage() > 0) {
            timeCtrl = true;
        }
    }
    public void deactivate(){
        super.deactivate();
        timeCtrl=false;
    }
    public void simulateTimerExpiry(){
        this.deactivate();
    }

    @Override
    public String getStatus() {
        return timeCtrl?super.getStatus()+" (auto-off in " + seconds + "s)":super.getStatus();
    }
}
 class PowerThrottled extends DeviceDecorator{
    private double powerCap;
    //private boolean capped=false;
    public PowerThrottled(SmartDevice device, double powerCap) {
        super(device);
        this.powerCap = powerCap;
        // capped=true;
    }
    @Override
    public double getPowerUsage() {
        double rawPower = super.getPowerUsage();
        if (rawPower > powerCap) {
            return powerCap;
        }
        return rawPower;
    }
    @Override
    public String getStatus() {
        String baseStatus = super.getStatus();
        if (super.getPowerUsage() > powerCap) {
            return baseStatus + " [throttled to " + powerCap + "W]";
        }
        return baseStatus;
    }

}
