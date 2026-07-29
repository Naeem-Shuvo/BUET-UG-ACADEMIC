interface color{
    public void colorItem();
}
class Red implements color{
    public void colorItem(){
        System.out.println("coloring Red");
    }
}
class Green implements color{
    public void colorItem(){
        System.out.println("coloring Green");
    }
}
abstract class Shape{
    protected color c;
    protected Shape(color c){
        this.c=c;
    }
    abstract void draw();
}
class Circle extends Shape{
    public Circle(color c){
        super(c);
    }
    public void draw(){
        System.out.println("drawing Circle");
        c.colorItem();
    }
}
class Square extends Shape{
    public Square(color c){
        super(c);
    }
    public void draw(){
        System.out.println("drawing Square");
        c.colorItem();
    }
}
public class bridge {
    public static void main(String[] args) {
         Shape circle=new Circle(new Red());
         Shape square=new Square(new Green());
         circle.draw();
         square.draw();
    }
}
