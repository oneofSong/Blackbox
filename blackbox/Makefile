blackbox: t_videoRec.cpp t_threadMain.cpp t_blackbox_Util.cpp
	g++ -o $@ $^ -lpthread `pkg-config --cflags --libs opencv`

clean: blackbox
	clean -rf $@
