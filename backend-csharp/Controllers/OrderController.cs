using DeliveryHub.Models;
using DeliveryHub.Services;
using Microsoft.AspNetCore.Mvc;

namespace DeliveryHub.Controllers;

[ApiController]
[Route("api/[controller]")]
public class OrderController : ControllerBase
{
    private readonly OrderService _orderService;

    public OrderController(DeliveryHubContext context)
    {
        _orderService = new OrderService(context);
    }

    [HttpPost]
    public IActionResult CreateOrder([FromBody] Order order)
    {
        var created = _orderService.CreateOrder(order);
        return Ok(created);
    }

    [HttpGet("{id}")]
    public IActionResult GetOrder(int id)
    {
        var order = _orderService.GetOrderById(id);
        if (order == null) return NotFound();
        return Ok(order);
    }

    [HttpGet]
    public IActionResult GetAllOrders()
    {
        return Ok(_orderService.GetAllOrders());
    }

    [HttpPut("{id}/status")]
    public IActionResult UpdateStatus(int id, [FromQuery] string status)
    {
        var order = _orderService.UpdateOrderStatus(id, status);
        if (order == null) return NotFound();
        return Ok(order);
    }

    [HttpGet("search")]
    public IActionResult SearchOrders([FromQuery] string keyword)
    {
        return Ok(_orderService.SearchOrders(keyword));
    }
}
