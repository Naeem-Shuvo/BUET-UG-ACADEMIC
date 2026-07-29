abstract class Beverage {
    protected String description;
    protected double cost;
    public String getDescription(){
        return description; //sob coffee te getDescription lekha lagbe na
    };
    double getCost(){
        return cost;
    };
}
class Dark extends Beverage {
    public Dark() {
        description = "Dark Beverage";
        cost = 1.99;
    }
}
abstract class decorator extends Beverage {
    public abstract String getDescription();
    public abstract  double getCost();
}
class Mocha extends Beverage {
    private Beverage beverage;
    public Mocha(Beverage beverage) {
        this.beverage = beverage;
    }
    public String getDescription() {
        return beverage.getDescription()+"mocha";
    }
    public double getCost() {
        return beverage.getCost()+.50;
    }
}
class Whip extends decorator{
    private Beverage beverage;
    public Whip(Beverage beverage) {
        this.beverage = beverage;
    }
    public String getDescription() {
        return beverage.getDescription()+"whip";
    }
    public double getCost() {
        return beverage.getCost()+.50;
    }
}
class  Main {
    public static void main(String[] args) {
        Beverage dark = new Dark();
        System.out.println(dark.getDescription());
        System.out.println(dark.getCost());
        Beverage mocha = new Mocha(dark);
        System.out.println(mocha.getDescription());
        System.out.println(mocha.getCost());
        Beverage whip = new Whip(mocha);
        System.out.println(whip.getDescription());
        System.out.println(whip.getCost());
    }
}