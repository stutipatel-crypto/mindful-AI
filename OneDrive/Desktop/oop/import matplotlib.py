import matplotlib.pyplot as plt

# Month names
months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]

# Method 3 CUSUM values
cusum = [1135.4, 2659.8, 4292.2, 7702.6, 10377.0, 14949.4,
         16583.8, 18609.2, 20286.6, 22133.0, 23312.4, 24352.8]

# Create figure
plt.figure(figsize=(10, 6))

# Plot line with markers
plt.plot(months, cusum, marker='o')

# Draw x-axis (zero line)
plt.axhline(0)

# Titles and labels
plt.title("CUSUM Chart (Method 3, Ȳ = 620.6)")
plt.xlabel("Month")
plt.ylabel("CUSUM Value")

# Add value labels on each point
for x, y in zip(months, cusum):
    plt.text(x, y + 300, str(round(y, 1)), ha='center')

# Grid for better readability
plt.grid()

# Adjust y-axis limits
plt.ylim(min(cusum) - 500, max(cusum) + 1000)

# Show graph
plt.show()