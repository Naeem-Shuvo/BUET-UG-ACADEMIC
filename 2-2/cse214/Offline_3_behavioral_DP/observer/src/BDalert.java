public class BDalert {
    public static void main(String[] args) {

        Disaster earthquake = new Earthquake();
        Disaster flood = new Flood();
        Disaster fire = new Fire();


        client1 c1 = new client1("Rafiq");
        client2 c2 = new client2("Sultana");
        client3 c3 = new client3("Karim");


        c1.subscribe(earthquake);
        c2.subscribe(earthquake);
        c2.subscribe(flood);
        c3.subscribe(flood);
        c3.subscribe(fire);

        System.out.println("Round 1: one alert per category");
        earthquake.publish("Magnitude 6.2 Earthquake", 6.2f, "Chittagong",
                "Move to open ground, stay away from buildings.");
        flood.publish("Flash Flood Warning", 3.0f, "Sylhet",
                "Move to higher ground immediately.");
        fire.publish("Forest Fire Alert", 4.5f, "Bandarban",
                "Evacuate the area, avoid smoke inhalation.");

        System.out.println("\nSubscription update: Rafiq subscribes to Fire (late)");
        c1.subscribe(fire);

        System.out.println("\nRound 2: publish again on Fire to verify late subscriber");
        fire.publish("Fire Spreading Alert", 5.0f, "Bandarban",
                "Evacuate immediately, roads to the area are closed.");
        // Rafiq should now receive this one, but NOT the Round 1 fire alert.

        System.out.println("\nSubscription update: Karim unsubscribes from Flood");
        c3.unsubscribe(flood);
        flood.publish("Flood Level Rising", 3.8f, "Sylhet",
                "Stay away from riverbanks and low-lying roads.");
        // Karim should NOT receive this one; Sultana still should.

        System.out.println("\nNotifications received by each citizen");
        c1.display();
        c2.display();
        c3.display();
    }
}