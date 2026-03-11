namespace DeliveryHub.Models;

public class Order
{
    public int Id { get; set; }
    public string CustomerName { get; set; } = "";
    public string CustomerPhone { get; set; } = "";
    public string DeliveryAddress { get; set; } = "";
    public string StoreName { get; set; } = "";
    public string MenuItems { get; set; } = "";
    public int TotalPrice { get; set; }
    public string Status { get; set; } = "PENDING";
    public DateTime CreatedAt { get; set; }
    public DateTime UpdatedAt { get; set; }
}
