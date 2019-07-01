import cv2
from matplotlib import pyplot as plt

path='./data/'
imgBGR1 = cv2.imread(path+'cat.jpeg')
imgBGR2 = cv2.imread(path+'apple.jpeg')
imgBGR3 = cv2.imread(path+'lena2.png')
imgBGR4 = cv2.imread(path+'lena_mat.png')

#컬러 순서 변환 : BGR -> RGB
imgRGB1 = cv2.cvtColor(imgBGR1, cv2.COLOR_BGR2RGB)
imgRGB2 = cv2.cvtColor(imgBGR2, cv2.COLOR_BGR2RGB)
imgRGB3 = cv2.cvtColor(imgBGR3, cv2.COLOR_BGR2RGB)
imgRGB4 = cv2.cvtColor(imgBGR4, cv2.COLOR_BGR2RGB)

# subplots 2x2 총 4개로 설정하고 Window를 (10,10) 사이즈로 정의하고,
# window의 이름을 ‘Sample Pictures’로 정의 한다.
fig, ax = plt.subplots(2, 2, figsize=(5,5), sharey=True)
fig.canvas.set_window_title('Sample Pictures')

# 왼쪽 위 Window의 좌표 축을 ‘off’하고,
# imgRGB1(orange이미지) 비율을 ‘auto’로 설정한다.
ax[0][0].axis('off')
ax[0][0].imshow(imgRGB1, aspect = 'auto')

# 오른쪽 위 Window의 좌표 축을 ‘off’하고,
# imgRGB2(apple이미지) 비율을 ‘auto’로 설정한다.
ax[0][1].axis('off')
ax[0][1].imshow(imgRGB2, aspect = 'auto')

# 왼쪽 아래 Window의 좌표 축을 ‘off’하고,
# imgRGB3(baboon이미지) 비율을 ‘auto’로 설정한다.
ax[1][0].axis("off")
ax[1][0].imshow(imgRGB3, aspect = 'auto')

# 오른쪽 아래 Window의 좌표 축을 ‘off’하고,
# imgRGB3(lena이미지) 비율을 ‘auto’로 설정한다.
ax[1][1].axis("off")
ax[1][1].imshow(imgRGB4, aspect = 'auto')

# 주어진 사이즈의 Window에서 크기를 최대로 하고,
# sub window간의 공간을 가로(wspace)=0.05, 세로(hspace)=0.05로 설정한다.
plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0.05, hspace=0.05)
plt.savefig("./data/0206.png", bbox_inches='tight')
plt.show()
