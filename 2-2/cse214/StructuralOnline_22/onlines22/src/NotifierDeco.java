abstract class Notifier{
    String name;
    String notifyUser(){
        return name;
    }
}
class emailNotifier1 extends Notifier{
    emailNotifier1(){
        this.name = "Email Notifier ";
    }
}
abstract class notifierWrapper extends Notifier{
    abstract String notifyUser();
}
class EncryptedNotifier extends notifierWrapper{
    Notifier notifier;
    EncryptedNotifier(Notifier notifier){
        this.notifier = notifier;
    }
    public String notifyUser(){
        return notifier.notifyUser()+" encrypted msg";
    }
}


public class NotifierDeco {
    public static void main(String[] args) {
        Notifier sender = new EncryptedNotifier(new emailNotifier1());
        System.out.println(sender.notifyUser());
    }
}
