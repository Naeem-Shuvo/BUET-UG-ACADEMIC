public class SmartLight implements SmartDevice {
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
