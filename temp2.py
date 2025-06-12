from PIL import Image

def read_binary_grid():
    print("Enter a 21x21 binary matrix (21 lines of 21 characters each, only 0s and 1s):")
    grid = []
    for i in range(21):
        while True:
            line = input().strip()
            if len(line) == 21 and all(c in '01' for c in line):
                grid.append(line)
                break
            else:
                print("Invalid input. Please enter exactly 21 characters consisting only of 0s and 1s.")
    return grid

def create_image_from_grid(binary_grid, scale=10):
    data = [[int(bit) for bit in row] for row in binary_grid]
    size = len(data)
    image = Image.new("1", (size * scale, size * scale), 1)
    pixels = image.load()

    for y in range(size):
        for x in range(size):
            color = 0 if data[y][x] == 1 else 1
            for dy in range(scale):
                for dx in range(scale):
                    pixels[x * scale + dx, y * scale + dy] = color

    image.show()  # or image.save("output.png")

if __name__ == "__main__":
    binary_grid = read_binary_grid()
    create_image_from_grid(binary_grid)