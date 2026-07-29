import java.util.ArrayList;
import java.util.List;

interface packages{
    double getWt();
    double getPrice();
    void getName();
}
class Custom implements packages{
    double price;
    List<packages> packages=new ArrayList<packages>();
    void add(packages p){
        packages.add(p);
    }

    @Override
    public double getWt() {double wt=0;
        for(packages p:packages){
            wt+=p.getWt();
        }
        return wt;
    }

    public double getPrice(){
        price=0;
        for(packages p:packages){
           price+= p.getPrice();
        }
        return price;
    }

    @Override
    public void getName() {
        System.out.println("custom: ");
      for (packages p:packages){
          p.getName();
      }
    }
}
class Grocery implements packages{
    double price;
    String name;
    double wt;
    Grocery(String name, double price,double wt){
        this.name=name;
        this.price=price;
        this.wt=wt;
    }
    public double getPrice(){
        return price;
    }
    public void getName(){
        System.out.println(name);
    }
    public double getWt(){
        return wt;
    }
}
class preset implements packages{
    double price;
    List<packages> packages=new ArrayList<>();
    void add(packages p){
        if(p instanceof Grocery) {
            packages.add(p);
        }
    }
    public double getPrice(){
        price=0;
        for(packages p:packages){
            price+= p.getPrice();
        }
        return price;
    }
    public void getName(){System.out.println("preset :");
        for(packages p:packages){
            System.out.print("   ");
            p.getName();
        }
    }
    public double getWt(){
       double wt=0;
        for(packages p:packages){
            wt+=p.getWt();
        }
               return wt;
    }
}
public class CompositeA2 {
    public static void main(String[] args) {
        // Individual items (Leaves)
        Grocery rice  = new Grocery("Rice", 60, 5);
        Grocery oil   = new Grocery("Oil", 150, 2);
        Grocery pulse = new Grocery("Pulse", 90, 1);
        Grocery salt  = new Grocery("Salt", 20, 1);
        Grocery sugar = new Grocery("Sugar", 70, 2);

        // Preset packages: only individual items allowed
        preset small = new preset();
        small.add(rice);
        small.add(oil);

        preset family = new preset();
        family.add(rice);
        family.add(oil);
        family.add(pulse);
        family.add(salt);

        // Custom package: a preset + an individual item
        Custom myCustom = new Custom();
        myCustom.add(small);
        myCustom.add(sugar);

        // Custom package that reuses a previously created custom package,
        // plus another preset and another individual item
        Custom biggerCustom = new Custom();
        biggerCustom.add(family);
        biggerCustom.add(myCustom);
        biggerCustom.add(pulse);

        System.out.println("---- myCustom ----");
        myCustom.getName();
        System.out.println("Total price: " + myCustom.getPrice());
        System.out.println("Total weight: " + myCustom.getWt());

        System.out.println();
        System.out.println("---- biggerCustom (reuses myCustom) ----");
        biggerCustom.getName();
        System.out.println("Total price: " + biggerCustom.getPrice());
        System.out.println("Total weight: " + biggerCustom.getWt());
    }
}
