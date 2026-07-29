abstract class Package{
     String name;
     double price;

    public String getName(){
        return name;
     };
    public double getPrice(){
         return price;
     };
}
class Standard extends Package{
    Standard(){
       name="Standard";
       price=100.00;
    }
}
class Premium extends Package{
    Premium(){
        name="Premium";
        price=200.00;
    }
}
class Special extends Package{
    Special(){
        name="Special";
        price=300.00;
    }
}
abstract class Optional extends Package{
    public abstract String getName();
}
class Fruits extends Optional{
    Package aPackage;
    Fruits(Package aPackage){
        this.aPackage=aPackage;
    }

    @Override
    public double getPrice() {
        return aPackage.getPrice()+75;
    }
    public String getName(){
        return aPackage.getName()+" added fruits";
    }
}
class Gift extends Optional{
    Package aPackage;
    Gift(Package aPackage){
        this.aPackage=aPackage;
    }

    @Override
    public double getPrice() {
        return aPackage.getPrice()+25;
    }
    public String getName(){
        return aPackage.getName()+" wrapped in gift";
    }
}
class Sweets extends Optional{
    Package aPackage;
    Sweets(Package aPackage){
        this.aPackage=aPackage;
    }

    @Override
    public double getPrice() {
        return aPackage.getPrice()+60;
    }
    public String getName(){
        return aPackage.getName()+" added Sweets";
    }
}
public class DecoC1{
    public static void main(String[] args){
        Package[] orders = {
                new Standard(),
                new Premium(),
                new Special(),
                new Fruits(new Standard()),
                new Gift(new Standard()),
                new Sweets(new Premium()),
                new Gift(new Fruits(new Standard())),
                new Sweets(new Gift(new Fruits(new Special())))
        };

        for (Package p : orders) {
            System.out.println(p.getName() + " -> Tk " + p.getPrice());
        }
    }
}