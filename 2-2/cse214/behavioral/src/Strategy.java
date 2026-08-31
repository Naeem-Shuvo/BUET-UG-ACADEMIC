interface flyable {
    void fly();
}

interface quackable {
    void quack();
}

class flynoway implements flyable {
    public void fly() {
        System.out.println("dosnt fly");
    }
}

class flylong implements flyable {
    public void fly() {
        System.out.println("long fly");
    }
}

class loudquack implements quackable {
    public void quack() {
        System.out.println("loud quack");
    }
}

class mutequack implements quackable {
    public void quack() {
        System.out.println("doesnt; mute quack");
    }
}

abstract class Duck {
    flyable fly;
    quackable quack;

    public void setFly(flyable fly) {
        this.fly = fly;
    }

    public void setQuack(quackable quack) {
        this.quack = quack;
    }

    public void fly() {
        fly.fly();
    }

    public void quack() {
        quack.quack();
    }

    abstract void display();
}

class mallardDuck extends Duck {
    void display() {
        System.out.println("Mallard Duck");
        fly.fly();
        quack.quack();
    }
}

class ModelDuck extends Duck {
    void display() {
        System.out.println("Model Duck");
        fly.fly();
        quack.quack();
    }
}

public class Strategy {
    static void main(String[] args) {
        Duck duck = new mallardDuck();
        duck.setFly(new flylong());
        duck.setQuack(new loudquack());
        duck.display();
        Duck duck2 = new ModelDuck();
        duck2.setFly(new flynoway());
        duck2.setQuack(new mutequack());
        duck2.display();
    }
}