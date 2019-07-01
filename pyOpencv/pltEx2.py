import cv2
from matplotlib import pyplot as plt

imageFile = './lena.jpg'

# Grayscale 포맷으로 읽어서 imgGray 객체에 저장한다.
imgGray = cv2.imread(imageFile, cv2.IMREAD_GRAYSCALE)

# plt.figure 크기를 (6,6) 인치로 설정
plt.figure(figsize=(6,6))

# 여백 조정
plt.subplots_adjust(left=0, right=1, bottom=0, top=1)
#plt.subplots_adjust(left=0.03, right=0.97, bottom=0.03, top=0.97)
plt.imshow(imgGray, cmap='gray')
#plt.axis('tight')
plt.axis('off')

#plot 배열에 저장된 이미지를 파일로 저장
plt.savefig('./data/lena_mat.png')
plt.show()
