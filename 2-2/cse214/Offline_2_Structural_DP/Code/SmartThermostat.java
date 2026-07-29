public class SmartThermostat implements SmartDevice {
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
