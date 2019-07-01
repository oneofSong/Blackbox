import matplotlib.pyplot as plt

def handle_close(evt):
	print('Closed Figure!')

def handle_resize(evt):
	print('Resized Figure!')

fig = plt.figure()
fig.canvas.mpl_connect('close_event', handle_close)
fig.canvas.mpl_connect('resize_event', handle_resize)

plt.text(0.35, 0.5, 'Close Me!', dict(size=30))
plt.show()
