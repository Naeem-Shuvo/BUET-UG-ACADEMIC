package service;

import model.DeliveryType;
import model.MenuItem;
import model.Order;
import model.OrderItem;
import model.PaymentMethod;
import model.Size;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class OrderService {
        private final Director director = new Director();
        private int nextNumber = 1001;

        public OrderItem createOrderItem(MenuItem item, int quantity, Size size, boolean extraCheese, boolean spicy,
                        String note) {
                return new OrderItem.Builder(item, quantity)
                                .size(size)
                                .extraCheese(extraCheese)
                                .spicy(spicy)
                                .note(note)
                                .build();
        }

        public Order createDeliveryOrder(String customerName,
                        String phone,
                        String address,
                        List<OrderItem> items,
                        String couponCode,
                        boolean rushOrder,
                        String specialInstructions) {
                model.OrderBuilder builder = new model.ConcreteOrderBuilder();
                director.constructDeliveryOrder(builder, nextOrderId(), customerName, phone, items, address, couponCode, rushOrder, specialInstructions);
                return builder.getOrder();
        }

        public Order createPickupOrder(String customerName, String phone, List<OrderItem> items) {
                model.OrderBuilder builder = new model.ConcreteOrderBuilder();
                director.constructPickupOrder(builder, nextOrderId(), customerName, phone, items);
                return builder.getOrder();
        }

        public Order createScheduledGiftOrder(String customerName,
                        String phone,
                        String address,
                        List<OrderItem> items,
                        LocalDateTime scheduledTime) {
                model.OrderBuilder builder = new model.ConcreteOrderBuilder();
                director.constructScheduledGiftOrder(builder, nextOrderId(), customerName, phone, items, address, scheduledTime);
                return builder.getOrder();
        }

        public Order createSampleFamilyOrder(MenuCatalog catalog) {
                List<OrderItem> items = new ArrayList<>();
                items.add(new OrderItem.Builder(catalog.findByCode("P01"), 2)
                                .size(Size.LARGE)
                                .extraCheese(true)
                                .spicy(false)
                                .note("half spicy")
                                .build());
                items.add(new OrderItem.Builder(catalog.findByCode("B02"), 3)
                                .size(Size.MEDIUM)
                                .extraCheese(true)
                                .spicy(true)
                                .build());
                items.add(new OrderItem.Builder(catalog.findByCode("D02"), 4)
                                .size(Size.MEDIUM)
                                .extraCheese(false)
                                .spicy(false)
                                .note("less sugar")
                                .build());
                items.add(new OrderItem.Builder(catalog.findByCode("S02"), 2)
                                .size(Size.LARGE)
                                .extraCheese(false)
                                .spicy(true)
                                .build());

                model.OrderBuilder builder = new model.ConcreteOrderBuilder();
                director.constructSampleFamilyOrder(builder, nextOrderId(), items);
                return builder.getOrder();
        }

        private String nextOrderId() {
                return "FF-" + nextNumber++;
        }
}
