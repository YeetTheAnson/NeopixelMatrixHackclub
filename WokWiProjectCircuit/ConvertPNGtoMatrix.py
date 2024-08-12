from PIL import Image
import numpy as np

def rgb_to_hex(r, g, b):
    return (r << 16) + (g << 8) + b

def resize_and_center(image, target_width, target_height):
    original_width, original_height = image.size
    
    aspect_ratio = original_width / original_height
    
    if target_width / target_height > aspect_ratio:
        new_height = target_height
        new_width = int(aspect_ratio * new_height)
    else:
        new_width = target_width
        new_height = int(new_width / aspect_ratio)
    
    image = image.resize((new_width, new_height), Image.LANCZOS)
    
    new_image = Image.new("RGBA", (target_width, target_height), (0, 0, 0, 255))
    
    paste_x = (target_width - new_width) // 2
    paste_y = (target_height - new_height) // 2
    
    new_image.paste(image, (paste_x, paste_y))
    
    return new_image

def convert_image_to_matrix(image_path, width, height):
    with Image.open(image_path) as img:
        img = img.convert('RGBA')
        
        img = resize_and_center(img, width, height)
        
        data = np.array(img)
        
        hex_matrix = [
            [rgb_to_hex(*data[y, x, :3]) for x in range(width)]
            for y in range(height)
        ]
        
        return hex_matrix

def format_neopixel_code(matrix):
    return '{' + ', '.join(
        '{' + ', '.join(f'0x{val:06X}' for val in row) + '}'
        for row in matrix
    ) + '}'

image_path = 'flag.png'

matrix = convert_image_to_matrix(image_path, 32, 8)

neopixel_code = format_neopixel_code(matrix)

print(neopixel_code)
