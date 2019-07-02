from PIL import Image, ImageFilter

im = Image.open('./lena.jpg')

# resize
im_resize = im.resize((600,600))

# blur
blurImage = im_resize.filter(ImageFilter.BLUR)
blurImage.show()
#blurImage.save('./data/lena-blur.jpg')

#sharpen
sharpImage = blurImage.filter(ImageFilter.SHARPEN)
sharpImage.show()
