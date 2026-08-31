import java.util.ArrayList;

interface subject{
    void register(observer o);
    void removeObserver(observer o);
    void notifyObservers(String s);
}
class Newspaper implements subject{
    private ArrayList<observer> observers;
    Newspaper(){
        observers = new ArrayList<>();
    }
    public void register(observer o) {
        observers.add(o);
    }
    public void removeObserver(observer o) {
        observers.remove(o);
    }
    public void notifyObservers(String changes) {
        for (observer o : observers) {
            o.update(changes);
        }
    }
    void changedContent(String content){
        notifyObservers(content);
    }
}
class OTT implements subject{
    private ArrayList<observer> observers;
    OTT(){
        observers = new ArrayList<>();
    }
    public void register(observer o) {
        observers.add(o);
    }
    public void removeObserver(observer o) {
        observers.remove(o);
    }
    public void notifyObservers(String changes) {
        for (observer o : observers) {
            o.update(changes);
        }
    }
    void changedContent(String content){
        notifyObservers(content);
    }
}
interface observer{
    void update(String s);
}
class subscriber implements observer{
    subject subject;
    public void subscribe(subject s){
        subject=s;
        subject.register(this);
    }
    public void update(String s){
        display(s);
    }
    public void display(String s){
        System.out.println("changes made "+ s );
    }
}
public class ObserverPattern {
    public static void main(String[] args) {
        subject newspaper=new Newspaper();
        subject ott=new OTT();
        observer o1=new subscriber();
        observer o2=new subscriber();
        ((subscriber) o1).subscribe(newspaper);
        ((subscriber) o2).subscribe(ott);
        ((Newspaper)newspaper).changedContent("added new sections");
        ((OTT)ott).changedContent("added new series");
        ((Newspaper)newspaper).changedContent("added new sports sections");
    }
}
