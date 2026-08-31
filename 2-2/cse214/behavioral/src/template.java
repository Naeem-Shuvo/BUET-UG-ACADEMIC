abstract class caffeine{
    protected String name;
    void prepare(){
        boil();
        brew();
        pour();
        addCondiments();
    }
    void boil(){
        System.out.println("water being boiled");
    }
    abstract void brew();
    abstract void addCondiments();
    void pour(){
        System.out.println("poured the "+name);
    }
}
class Coffee extends caffeine{
    Coffee(){name="coffee";}
    void brew(){
        System.out.println("coffee grinded and added");
    }
    void addCondiments(){
        System.out.println("sugar added to coffee");
    }
}
class Tea extends caffeine{
    Tea(){name="tea";}
    void brew(){
        System.out.println("teabag added");
    }
    void addCondiments(){
        System.out.println("lemon and liqoure added to tea");
    }
}
public class template {
    static void main(String[] args) {
        caffeine coffee = new Coffee();

        caffeine tea = new Tea();
        tea.prepare();
        coffee.prepare();
    }
}
