package model;

import java.time.LocalDateTime;
import java.util.List;

/**
 * Common interface for constructing Order products.
 */
public interface OrderBuilder {
    void buildBaseDetails(String orderId, String customerName, String phone, List<OrderItem> items);

    void buildDeliveryDetails(DeliveryType deliveryType, String address);

    void buildPaymentDetails(PaymentMethod paymentMethod, String couponCode, int loyaltyPoints);

    void buildOptionalDetails(boolean giftWrap, boolean cutleryRequired, boolean rushOrder, LocalDateTime scheduledTime,
            String specialInstructions);

    Order getOrder();
}
