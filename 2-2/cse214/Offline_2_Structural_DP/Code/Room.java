import java.util.ArrayList;
import java.util.List;

public class Room implements SmartDevice {
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
