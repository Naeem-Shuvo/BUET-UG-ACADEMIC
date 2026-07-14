import java.util.Scanner;

interface Transport {
        public void deliver();
    }

    class Truck implements Transport {
        public void deliver(){
            System.out.println("deliver by truckAC");
        }
    }
    class Ship implements Transport{
        public void deliver(){
            System.out.println("deliver by ship");
        }
    }


    class DeliverFactory {
        private String deliveryWay;

        public DeliverFactory(String deliveryWay) {
            this.deliveryWay = deliveryWay;
        }

        public Transport getdeliver() {
            if (deliveryWay == null) {
                throw new IllegalArgumentException("deliveryWay is null");
            }
            switch (deliveryWay.toUpperCase()) {
                case "ROAD":
                    return new Truck();
                case "SEA":
                    return new Ship();
                default:
                    throw new IllegalArgumentException("deliveryWay is " + deliveryWay);
            }

        }
    }


public class Main{
    public static void main(String[] args){
        Transport medium;
        Scanner input = new Scanner(System.in);
        String med=input.nextLine();
        DeliverFactory deliverFactory=new DeliverFactory(med);
        medium=deliverFactory.getdeliver();
        medium.deliver();
    }
}