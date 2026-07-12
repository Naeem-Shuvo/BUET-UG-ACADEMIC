package model;

import java.time.LocalDateTime;
import java.util.List;

/**
 * Concrete implementation of the OrderBuilder interface.
 */
public class ConcreteOrderBuilder implements OrderBuilder {
    private String specialInstructions;
    private String customerName;
    private int loyaltyPointsToRedeem;
    private String phone;
    private boolean giftWrap;
    private String deliveryAddress;
    private boolean rushOrder;
    private PaymentMethod paymentMethod;
    private String orderId;
    private LocalDateTime scheduledTime;
    private boolean cutleryRequired;
    private String couponCode;
    private DeliveryType deliveryType;
    private List<OrderItem> items;

    @Override
    public void buildBaseDetails(String orderId, String customerName, String phone, List<OrderItem> items) {
        this.orderId = orderId;
        this.customerName = customerName;
        this.phone = phone;
        this.items = items;
    }

    @Override
    public void buildDeliveryDetails(DeliveryType deliveryType, String address) {
        this.deliveryType = deliveryType;
        this.deliveryAddress = address;
    }

    @Override
    public void buildPaymentDetails(PaymentMethod paymentMethod, String couponCode, int loyaltyPoints) {
        this.paymentMethod = paymentMethod;
        this.couponCode = couponCode;
        this.loyaltyPointsToRedeem = loyaltyPoints;
    }

    @Override
    public void buildOptionalDetails(boolean giftWrap, boolean cutleryRequired, boolean rushOrder, LocalDateTime scheduledTime, String specialInstructions) {
        this.giftWrap = giftWrap;
        this.cutleryRequired = cutleryRequired;
        this.rushOrder = rushOrder;
        this.scheduledTime = scheduledTime;
        this.specialInstructions = specialInstructions;
    }

    @Override
    public Order getOrder() {
        return new Order.Builder(orderId, customerName, phone, items)
                .deliveryType(deliveryType)
                .deliveryAddress(deliveryAddress)
                .paymentMethod(paymentMethod)
                .scheduledTime(scheduledTime)
                .couponCode(couponCode)
                .giftWrap(giftWrap)
                .cutleryRequired(cutleryRequired)
                .loyaltyPointsToRedeem(loyaltyPointsToRedeem)
                .rushOrder(rushOrder)
                .specialInstructions(specialInstructions)
                .build();
    }
}
