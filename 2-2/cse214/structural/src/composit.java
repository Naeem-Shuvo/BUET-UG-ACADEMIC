
import java.util.ArrayList;
import java.util.List;

interface MenuComponent
{
   String getName();
   String getDescription();
   void print();
   default void add(MenuComponent c){};
   default void remove( MenuComponent c){};
    //default void show(){};
}
class MenuItem implements MenuComponent{
    private String name;
    private String description;
    public MenuItem(String name , String description){
        this.name = name;
        this.description = description;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getDescription() {
return description;
    }

    @Override
    public void print() {
        System.out.println(name+ ", " +description);
    }
}
class Menu implements MenuComponent{
    private String name;
    private String description;
    List<MenuComponent> menu=new ArrayList<MenuComponent>();
    Menu(String name , String description){
        this.name = name;
        this.description = description;
    }
    @Override
    public String getName() {
        return name;
    }
    @Override
    public String getDescription() {
        return description;
    }
    @Override
    public void print() {
        for (MenuComponent c : menu) {
            c.print();
        }
        System.out.println("menu name:"+name+" description:"+description);
    }
    @Override
    public void add(MenuComponent c){
        menu.add(c);
    }
    @Override
    public void remove(MenuComponent c){
       menu.remove(c);
    }
}

class Waitress{
    MenuComponent menu;
    public Waitress(MenuComponent menu){
        this.menu=menu;
    }
    public void printMenu() {
         menu.print();
    }
}
public class composit {
    public static void main(String[] args) {
        Menu pancakeHouseMenu = new Menu("Pancake House Menu", "Breakfast");
        Menu dinerMenu = new Menu("Diner Menu", "Lunch");
        Menu dessertMenu = new Menu("Dessert Menu", "Dessert of course!");
        Menu cafeMenu = new Menu("Cafe Menu", "Dinner");

        Menu allMenus = new Menu("All Menus", "All menus combined");//menues inside menu
        allMenus.add(pancakeHouseMenu);
        allMenus.add(dinerMenu);
        allMenus.add(cafeMenu);

        // Nesting: Dessert Menu goes INSIDE Diner Menu — this is the recursive part
        dinerMenu.add(dessertMenu);

        pancakeHouseMenu.add(new MenuItem("K&B's Pancake Breakfast",
                "Pancakes with scrambled eggs and toast"));
        dinerMenu.add(new MenuItem("Vegetarian BLT",
                "Fakin' Bacon with lettuce & tomato on wheat"));
        dessertMenu.add(new MenuItem("Apple Pie",
                "Apple pie with a flaky crust"));

        Waitress waitress = new Waitress(allMenus);
        waitress.printMenu(); // one call, prints EVERYTHING recursively
    }
}
