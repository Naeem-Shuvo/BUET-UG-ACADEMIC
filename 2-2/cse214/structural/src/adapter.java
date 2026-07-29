interface Duck{
    void quack();
    void fly();
}
class MallardDuck implements Duck{
    @Override
    public void quack() {
        System.out.println("quack");
    }
    @Override
    public void fly() {
        System.out.println("fly 5 meters");
    }
}
interface Car{
    void sound();
    void run();
}
class RoyceCar implements Car{
    @Override
    public void sound() {
        System.out.println("vrooom");
    }
    @Override
    public void run() {
        System.out.println("runs 50km/hr");
    }
}
class testerDuck{
    public testerDuck(Duck duck){
        duck.quack();
        duck.fly();
    }
}

class adapterCar implements Duck{
    Car car;
    public adapterCar(Car car){
        this.car = car;
    }
    @Override
    public void quack(){
        car.sound();
    }
    public void fly(){
        car.run();
    }
}

public class adapter {
    public static void main(String[] args) {
        testerDuck duck = new testerDuck(new MallardDuck());
        System.out.println();
        testerDuck car=new testerDuck(new adapterCar(new  RoyceCar()));
    }
}
