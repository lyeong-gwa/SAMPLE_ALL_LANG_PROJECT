package com.deliveryhub.service;

import com.deliveryhub.model.Order;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Service
public class OrderService {

    @PersistenceContext
    private EntityManager entityManager;

    @Value("${spring.datasource.url}")
    private String dbUrl;

    @Value("${spring.datasource.username}")
    private String dbUser;

    @Value("${spring.datasource.password}")
    private String dbPassword;

    private final ExecutorService executorService = Executors.newFixedThreadPool(4);

    @Transactional
    public Order createOrder(Order order) {
        order.setStatus("PENDING");
        order.setCreatedAt(LocalDateTime.now());
        order.setUpdatedAt(LocalDateTime.now());
        entityManager.persist(order);
        return order;
    }

    public Order getOrderById(Long id) {
        Order order = null;
        try {
            order = entityManager.find(Order.class, id);
            if (order == null) {
                throw new RuntimeException("주문을 찾을 수 없습니다: " + id);
            }
        } catch (RuntimeException e) {
            System.out.println("런타임 에러: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("에러 발생: " + e.getMessage());
        }
        return order;
    }

    public List<Order> getAllOrders() {
        return entityManager.createQuery("SELECT o FROM Order o", Order.class).getResultList();
    }

    @Transactional
    public Order updateOrderStatus(Long id, String status) {
        Order order = entityManager.find(Order.class, id);
        order.setStatus(status);
        order.setUpdatedAt(LocalDateTime.now());
        return entityManager.merge(order);
    }

    public List<Order> searchOrders(String keyword) {
        return entityManager.createQuery(
                "SELECT o FROM Order o WHERE o.customerName LIKE :keyword OR o.storeName LIKE :keyword",
                Order.class)
            .setParameter("keyword", "%" + keyword + "%")
            .getResultList();
    }

    public void processOrderAsync(Long orderId) {
        executorService.submit(() -> {
            try {
                Order order = getOrderById(orderId);
                Thread.sleep(3000);
                updateOrderStatus(orderId, "PROCESSING");
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
}
