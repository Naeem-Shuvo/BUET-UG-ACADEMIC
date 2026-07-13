package service;

import model.DeliveryType;
import model.OrderBuilder;
import model.OrderItem;
import model.PaymentMethod;

import java.time.LocalDateTime;
import java.util.List;

/**
 * Director class coordinates the build steps using an OrderBuilder interface.
 */
public class Director {
    public void constructPickupOrder(OrderBuilder builder, String orderId, String customerName, String phone,
            List<OrderItem> items) {
        builder.buildBaseDetails(orderId, customerName, phone, items);
        builder.buildDeliveryDetails(DeliveryType.PICKUP, "");
        builder.buildPaymentDetails(PaymentMethod.CASH, "", 0);
        builder.buildOptionalDetails(false, true, false, null, "");
    }

    public void constructDeliveryOrder(OrderBuilder builder, String orderId, String customerName, String phone,
            List<OrderItem> items, String address, String couponCode, boolean rushOrder, String specialInstructions) {
        builder.buildBaseDetails(orderId, customerName, phone, items);
        builder.buildDeliveryDetails(DeliveryType.DELIVERY, address);
        builder.buildPaymentDetails(PaymentMethod.CASH, couponCode, 0);
        builder.buildOptionalDetails(false, true, rushOrder, null, specialInstructions);
    }

    public void constructScheduledGiftOrder(OrderBuilder builder, String orderId, String customerName, String phone,
            List<OrderItem> items, String address, LocalDateTime scheduledTime) {
        builder.buildBaseDetails(orderId, customerName, phone, items);
        builder.buildDeliveryDetails(DeliveryType.DELIVERY, address);
        builder.buildPaymentDetails(PaymentMethod.CARD, "WELCOME10", 25);
        builder.buildOptionalDetails(true, false, false, scheduledTime, "Please call before delivery");
    }

    public void constructSampleFamilyOrder(OrderBuilder builder, String orderId, List<OrderItem> items) {
        builder.buildBaseDetails(orderId, "Sample Family", "01711111111", items);
        builder.buildDeliveryDetails(DeliveryType.DELIVERY, "House 25, Road 4, Dhanmondi");
        builder.buildPaymentDetails(PaymentMethod.MOBILE_BANKING, "FAMILY15", 50);
        builder.buildOptionalDetails(false, true, true, null, "Deliver together");
    }
}
