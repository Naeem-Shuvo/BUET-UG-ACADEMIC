// ---- Implementor ----
interface MessageSender {
    void send(String msg);
}

// ---- Concrete Implementors ----
class EmailSender implements MessageSender {
    public void send(String msg) {
        System.out.println("[Email] " + msg);
    }
}

class SMSSender implements MessageSender {
    public void send(String msg) {
        System.out.println("[SMS] " + msg);
    }
}

class PushSender implements MessageSender {
    public void send(String msg) {
        System.out.println("[Push] " + msg);
    }
}

class WhatsAppSender implements MessageSender {
    public void send(String msg) {
        System.out.println("[WhatsApp] " + msg);
    }
}

// ---- Abstraction ----
abstract class Notification {
    protected MessageSender sender;

    Notification(MessageSender sender) {
        this.sender = sender;
    }

    abstract void notifyUser();
}

// ---- Refined Abstractions ----
class BazarConfirmedNotification extends Notification {
    BazarConfirmedNotification(MessageSender sender) {
        super(sender);
    }
    void notifyUser() {
        sender.send("Your monthly bazar has been confirmed.");
    }
}

class DispatchedNotification extends Notification {
    DispatchedNotification(MessageSender sender) {
        super(sender);
    }
    void notifyUser() {
        sender.send("Your bazar is on the way!");
    }
}

class RenewedNotification extends Notification {
    RenewedNotification(MessageSender sender) {
        super(sender);
    }
    void notifyUser() {
        sender.send("Your subscription has been renewed for next month.");
    }
}

class PaymentFailedNotification extends Notification {
    PaymentFailedNotification(MessageSender sender) {
        super(sender);
    }
    void notifyUser() {
        sender.send("Payment failed. Please update your payment method.");
    }
}

// ---- Client ----
public class NotificationBridge {
    public static void main(String[] args) {
        Notification[] events = {
                new BazarConfirmedNotification(new EmailSender()),
                new DispatchedNotification(new SMSSender()),
                new RenewedNotification(new PushSender()),
                new PaymentFailedNotification(new WhatsAppSender()),
                // same event, different channel -> proves the two hierarchies are independent
                new DispatchedNotification(new WhatsAppSender())
        };

        for (Notification n : events) {
            n.notifyUser();
        }
    }
}