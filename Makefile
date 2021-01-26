TARGET = main

CFLAGS = -g -O2 -Wall -pedantic
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`


all: $(TARGET)

$(TARGET):
	gcc $(CFLAGS) main.c map.c graphique2d.c graphique3d.c math.c -o projet $(LDLIBS)


clean:
	-rm -rf	$(TARGET)