IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) 

SRC=src
ODIR=obj

_DEPS = bmp.h util.h pointcloud.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = bmp.o util.o pointcloud.o pointcloudio.o display.o watershed.o
OBJ = $(patsubst %,$(SRC)/$(ODIR)/%,$(_OBJ))

$(SRC)/$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

watershed: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(SRC)/$(ODIR)/*.o *~ core $(IDIR)/*~ 
