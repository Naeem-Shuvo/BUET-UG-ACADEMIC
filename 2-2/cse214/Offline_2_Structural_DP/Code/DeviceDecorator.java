public abstract class DeviceDecorator implements SmartDevice{
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
