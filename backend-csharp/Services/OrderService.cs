using DeliveryHub.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;

namespace DeliveryHub.Services;

public class OrderService
{
    private readonly DeliveryHubContext _context;
    private readonly string _connectionString;

    public OrderService(DeliveryHubContext context, IConfiguration configuration)
    {
        _context = context;
        _connectionString = configuration.GetConnectionString("DefaultConnection") ?? "";
    }

    public Order CreateOrder(Order order)
    {
        order.Status = "PENDING";
        order.CreatedAt = DateTime.Now;
        order.UpdatedAt = DateTime.Now;
        _context.Orders.Add(order);
        _context.SaveChanges();
        return order;
    }

    public Order? GetOrderById(int id)
    {
        try
        {
            var order = _context.Orders.Find(id);
            if (order == null)
            {
                throw new Exception("주문을 찾을 수 없습니다: " + id);
            }
            return order;
        }
        catch (InvalidOperationException e)
        {
            Console.WriteLine("잘못된 작업: " + e.Message);
            return null;
        }
        catch (Exception e)
        {
            Console.WriteLine("에러 발생: " + e.Message);
            return null;
        }
    }

    public List<Order> GetAllOrders()
    {
        return _context.Orders.ToList();
    }

    public Order? UpdateOrderStatus(int id, string status)
    {
        var order = _context.Orders.Find(id);
        if (order != null)
        {
            order.Status = status;
            order.UpdatedAt = DateTime.Now;
            _context.SaveChanges();
        }
        return order;
    }

    public List<Order> SearchOrders(string keyword)
    {
        return _context.Orders
            .Where(o => o.CustomerName.Contains(keyword) || o.StoreName.Contains(keyword))
            .ToList();
    }

    public async Task ProcessOrderAsync(int orderId)
    {
        await Task.Run(async () =>
        {
            var order = GetOrderById(orderId);
            await Task.Delay(3000);
            UpdateOrderStatus(orderId, "PROCESSING");
        });
    }

    public int CalculateTotal(List<Order> orders)
    {
        int total = 0;
        foreach (var order in orders)
        {
            total += order.TotalPrice;
        }
        return total;
    }
}
