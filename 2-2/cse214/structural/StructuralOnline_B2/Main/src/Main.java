import java.util.ArrayList;
import java.util.List;

 class Order {

    private List<OrderItem> items = new ArrayList<>();

    public void add(OrderItem item) {
        items.add(item);
    }

    public double getTotalPrice() {

        double total = 0;

        for (OrderItem item : items) {
            total += item.getPrice();
        }

        return total;
    }

    public void printReceipt() {

        System.out.println("========== RECEIPT ==========");

        for (OrderItem item : items) {
            item.print();
        }

        System.out.println("-----------------------------");
        System.out.printf("Total Bill: £%.2f%n", getTotalPrice());
    }
}
interface OrderItem {
    double getPrice();
    void print();
}
class Food implements OrderItem {
    private String name;
    private double price;
    public Food(String name, double price) {
        this.name = name;
        this.price = price;
    }
    @Override
    public double getPrice() {
        return price;
    }
    @Override
    public void print() {
        System.out.println("Food: "+name+" (£"+price+")");
    }
}
class SetMenu implements OrderItem {
    private String name;
    private double price;
    List<OrderItem> items = new ArrayList<>();

    public SetMenu(String name) {
        this.name = name;
    }

    void addFood(OrderItem item) {
        if (item instanceof Food) {
            items.add(item);
        }
    }
        @Override
        public double getPrice () {
            price = 0;
            for (OrderItem item : items) {
                price += item.getPrice();
            }
            return price * .9;
        }
        @Override
        public void print () {
            System.out.println("Set menu: " + name);
            for (OrderItem item : items) {

                item.print();
            }
        }

}
class GroceryPackage implements OrderItem {
    private String name;
    private double price;
    private List<OrderItem> items = new ArrayList<>();
    public GroceryPackage(String name) {
        this.name = name;
    }
    void add(OrderItem item) {
        items.add(item);
    }
    @Override
    public double getPrice() {
        price=0;
        for (OrderItem item : items) {
            price += item.getPrice();
        }
        return price;
    }
    @Override
    public void print() {
        System.out.println("Grocery package: "+name);
        for (OrderItem item : items) {
            item.print();
        }
    }
}
class Grocery implements OrderItem {
    private String name;
    private double price;
    public Grocery(String name, double price) {
        this.name = name;
        this.price = price;
    }
    @Override
    public double getPrice() {
        return price;
    }
    @Override
    public void print() {
        System.out.println("Grocery: "+name+"("+price+")");
    }
}
public class Main {

    public static void main(String[] args) {

        // Foods
        Food burger = new Food("Burger", 8);
        Food pizza = new Food("Pizza", 10);
        Food fries = new Food("French Fries", 3);

        // Set Menu
        SetMenu lunch = new SetMenu("Lunch Combo");
        lunch.addFood(burger);
        lunch.addFood(fries);

        // Grocery Items
        Grocery rice = new Grocery("Rice", 20);
        Grocery oil = new Grocery("Cooking Oil", 12);
        Grocery eggs = new Grocery("Eggs", 6);
        Grocery sugar = new Grocery("Sugar", 5);

        // Small Package
        GroceryPackage breakfastPack = new GroceryPackage("Breakfast Pack");
        breakfastPack.add(eggs);
        breakfastPack.add(sugar);

        // Large Package (contains another package)
        GroceryPackage monthlyPack = new GroceryPackage("Monthly Essentials");
        monthlyPack.add(rice);
        monthlyPack.add(oil);
        monthlyPack.add(breakfastPack);

        // Customer Order
        Order order = new Order();

        order.add(pizza);
        order.add(lunch);
        order.add(rice);
        order.add(monthlyPack);

        order.printReceipt();
    }
}