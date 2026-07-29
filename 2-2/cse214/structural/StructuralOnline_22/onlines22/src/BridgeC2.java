interface TransportType{
    void transport();
}
class Drone implements TransportType{
    @Override
    public void transport(){
        System.out.println("Drone transported successfully");
    }
}
class Bike implements TransportType{
    @Override
    public void transport(){
        System.out.println("Bike transported successfully");
    }
}
abstract class DeliveryType{
    TransportType transport;
    DeliveryType(TransportType transport){
        this.transport=transport;
    }
    abstract void businessLogic();
}
class standard extends DeliveryType{
    standard(TransportType transport){
        super(transport);
    }
    void businessLogic(){
        System.out.println("delivered within 24hr ");
        transport.transport();
    }
}
class Express extends DeliveryType{
    Express(TransportType transport){
        super(transport);
    }
    void businessLogic(){
        System.out.println("delivered within 4hr ");
        transport.transport();
    }
}
public class BridgeC2 {
    public static void main(String[] args){
        DeliveryType[] orders = {
                new standard(new Bike()),
                new standard(new Drone()),
                new Express(new Drone()),
                new Express(new Bike())
        };

        for (DeliveryType d : orders) {
            d.businessLogic();
            System.out.println("---");
        }
    }
}
