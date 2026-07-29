interface Device{
    void on();
    void off();
}
class fan implements Device{
    @Override
    public void on() {
        System.out.println("fan on");
    }
    @Override
    public void off() {
        System.out.println("fan off");
    }
}
class heater {
    void start(){
        System.out.println("heater start");
    }
    void stop(){
        System.out.println("heater stop");
    }
}
class heaterAdapter implements Device{
    private heater h;
    public heaterAdapter(heater h){
        this.h = h;
    }
    @Override
    public void on() {
        h.start();
    }
    @Override
    public void off() {
        h.stop();
    }
}
public class Adapter {
    public static void main(String[] args) {
        Device d = new fan();
        d.off();
        d.on();
        heater h = new heater();
        Device d2 = new heaterAdapter(h);
        d2.off();
        d2.on();
    }
}
