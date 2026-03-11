using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllers();
builder.Services.AddDbContext<DeliveryHubContext>(options =>
    options.UseInMemoryDatabase("DeliveryHubDb"));
builder.Services.AddEndpointsApiExplorer();

var app = builder.Build();

app.MapControllers();
app.Run();

public class DeliveryHubContext : DbContext
{
    public DeliveryHubContext(DbContextOptions<DeliveryHubContext> options) : base(options) { }
    public DbSet<DeliveryHub.Models.Order> Orders { get; set; }
}
