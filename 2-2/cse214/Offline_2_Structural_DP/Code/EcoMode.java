import java.util.List;

public class EcoMode extends DeviceDecorator{
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

