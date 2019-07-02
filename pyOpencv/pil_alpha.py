from PIL import Image

# Take two images for blending them together
image1 = Image.open("./data/red.jpg")
image2 = Image.open("./data/green.png")

# Make sure images got an alpha channel
image5 = image1.convert("RGBA")
image6 = image2.convert("RGBA")
image6 = image6.resize(image5.size)

# alpha-blend the images with varying values of alpha
alphaBlended1 = Image.blend(image5, image6, alpha=.2)
alphaBlended2 = Image.blend(image5, image6, alpha=.8)

# Display the alpha-blended images
alphaBlended1.show()
alphaBlended2.show()
