from PIL import Image
name = ""
while name != "break":
    name = input("Input filename or 'break' to stop: ")
    png = Image.open(name).convert("RGBA")
    bg = Image.new("RGBA", png.size, (0,0,0))
    ac = Image.alpha_composite(bg, png)
    ac.save(name, "PNG")
