public class PowerThrottled extends DeviceDecorator{
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
