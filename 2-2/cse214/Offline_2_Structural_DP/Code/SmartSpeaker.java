public class SmartSpeaker implements SmartDevice {
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
