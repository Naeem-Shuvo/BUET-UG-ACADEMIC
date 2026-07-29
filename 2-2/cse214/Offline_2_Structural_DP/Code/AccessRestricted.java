public class AccessRestricted extends DeviceDecorator {
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