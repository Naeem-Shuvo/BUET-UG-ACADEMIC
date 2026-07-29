public class TimerControlled extends DeviceDecorator {
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
