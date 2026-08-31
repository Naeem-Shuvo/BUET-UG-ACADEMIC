import javax.print.attribute.standard.Media;

interface Mediator{
    void notify(Component sender, String event);
}
class MediatorImpl implements Mediator{
    public void notify(Component sender, String event){
        if(sender instanceof Button  && event.equals("onclick")){
            System.out.println("button is onclick");
        } else if (sender instanceof textBox && event.equals("select")) {
            System.out.println("text is select");
        }
    }
}
abstract class Component {
     Mediator mediator;
    public Component(Mediator mediator){
        this.mediator = mediator;
    }
}
class Button extends Component {
    public Button(Mediator mediator){
        super(mediator);
    }
    void onClick(){
        mediator.notify(this,"onclick");
    }
}
class textBox extends Component {
    public textBox(Mediator mediator){
        super(mediator);
    }
    void select(){
        mediator.notify(this,"select");
    }
}
public class MediatorPattern {
    static void main(String[] args) {
        Mediator mediator = new MediatorImpl();
        Button button = new Button(mediator);
        button.onClick();
        textBox textBox = new textBox(mediator);
        textBox.select();
    }
}
